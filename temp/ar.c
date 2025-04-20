#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <graphics.h>
#include "ar.h"
#include "file.h"
#include "stock.h"
#include "draw.h"


float minus_average( float* arr , int n ) 
{
    float sum = 0;
    for(int i=0; i<n ; i++) 
        sum += arr[i];
    float average  = sum / n;

    for(int i=0; i<n; i++) 
        arr[i] -= average;

    return average;
}


void calculate_r( float* arr, int n, float* r, int p)
{
    for( int i=0; i<=p; i++)
    {
        r[i] = 0.0;
        for (int t = i; t < n; t++) 
            r[i] += arr[t] * arr[ t-i ];
        
        r[i] /= ( n-i );
    }

    assert( fabs( r[0] ) > 1e-6 );
    for( int i=1; i<=p; i++)
        r[i] /= r[0];
}



float levinson_durbin( float* r, float* phi, int p)
{
    /* 0~P*/
    float* a = (float*)safe_malloc( (p+1)*sizeof(float) );      // 当前阶系数
    float* prev_a = (float*)safe_malloc( (p+1)*sizeof(float) ); // 上一阶系数

    /* m=0 */
    float epsilon = r[0];
    a[0] = 1.0;

    for( int m=1; m<=p; m++)
    {
        /* \lambda_m = -\frac{ \sum_{j=0}^{m-1} a_j^(m-1) r_{m-j} }{ \epsilon_{m-1} } */
        float lambda = 0.0;
        for( int j = 0; j < m; j++) 
            lambda -= a[j] * r[ m-j ];
        lambda /= epsilon;

        /* a:a^(m) */
        /* prev_a:a^(m-1) */
        memmove( prev_a, a, m*sizeof(float) );
        
        /* a_m^(m) = \lambda_m */
        /* a_j^(m) = a_j^(m-1) + \lambda_m * a_{m-j}^(m-1) */
        a[m] = lambda;
        for( int j = 1; j < m; j++) 
            a[j] = prev_a[j] + lambda * prev_a[ m-j ];
        
        epsilon *= ( 1 - lambda*lambda );
    }

    /* \phi_i = -a_i^(P) */
    for( int i = 1; i <= p; i++) 
        phi[ i-1 ] = -a[i];

    free( a );
    free( prev_a );

    return epsilon;
    
}


void predict_close( const stock_data* stock )
{
    FILE* fp = open_file( stock->code, ".kday", "rb" );
    FILE* predfp = open_file( stock->code, ".pred", "wb" );

    day_price info;
    float* close_buffer = (float*)safe_malloc( sizeof(float) * stock->days );
    for( int i=0; i<stock->days; i++)
    {
        SAFE_READ( &info, sizeof(day_price), 1, fp );
        close_buffer[i] = info.close;
    }
    SAFE_WRITE( close_buffer, sizeof(float), stock->days, predfp );

    float average = minus_average( close_buffer, stock->days );
    int p = choose_p( close_buffer, stock->days, 5 );
    float* r = (float*)safe_malloc( (p+1)*sizeof(float) );
    float* phi = (float*)safe_malloc( p*sizeof(float) );

    calculate_r( close_buffer, stock->days, r, p );
    levinson_durbin( r, phi, p );

    /* X_{t-p},X_{t-p+1},...,X_{t-1},X_{t},X_{t+1},...,X_{t+FORECAST_DAYS-1} */
    float* x = (float*)safe_malloc( (p+FORECAST_DAYS)*sizeof(float) );  
    memmove( x, close_buffer + stock->days - p, p * sizeof(float) );
    free( close_buffer );
    close_file( fp, stock->code, ".kday" );

    for( int i=0; i<FORECAST_DAYS; i++)
    {
        x[ i+p ] = 0.0;
        for(int j=0; j<p; j++)
            x[ i+p ] += phi[j] * x[ i+p-1-j];
    }

    for( int i=0; i<FORECAST_DAYS; i++)
        x[ i+p ] += average;
    SAFE_WRITE( x+p, sizeof(float), FORECAST_DAYS, predfp );

    free( r );
    free( phi );
    free( x );

    most_value most = { -FLT_MAX, FLT_MAX };
    fseek( predfp, -(FORECAST_DAYS+3)*sizeof(float), SEEK_END );
    float* temp = (float*)safe_malloc( (FORECAST_DAYS+3)*sizeof(float) );
    SAFE_READ( temp, sizeof(float), FORECAST_DAYS+3, predfp );
    for( int i=0; i<FORECAST_DAYS+3; i++)
    {
        most.max = most.max > temp[i] ? most.max : temp[i];
        most.min = most.min < temp[i] ? most.min : temp[i];
    }
    free( temp );
    SAFE_WRITE( &most, sizeof(most_value), 1, predfp );
    close_file( predfp, stock->code, ".pred" );

}


int choose_p( float* data, int n, int max_p )
{
    float* r = (float*)safe_malloc( (max_p+1)*sizeof(float) );
    float* phi = (float*)safe_malloc( max_p*sizeof(float) );

    float prev_aic = FLT_MAX;
    int result_p = 0;

    for(int p=1; p<=max_p; p++)
    {
        calculate_r( data, n, r, p );

        float sigma2 = levinson_durbin( r, phi, p);  /* \sigma_p^2 = \epsilon_p */
        float aic = 2*p + n * log(sigma2);  
        /* float bic = p*log(n) + n * log(sigma2); */

        if( aic < prev_aic )
        {
            result_p = p;
            prev_aic = aic;
        }
    }

    free( r );
    free( phi );

    return result_p;
}

