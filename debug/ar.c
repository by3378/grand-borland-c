#include "global.h"

int choose_p( float* data, int n, int max_p )
{
    float prev_aic = FLT_MAX;
    int result_p = 0;

    for( int p=1; p<=max_p; p++)
    {
        float* r = (float*)safe_malloc( (p+1)*sizeof(float) );
        float* phi = (float*)safe_malloc( p*sizeof(float) );

        calculate_r( data, n, r, p );

        float sigma2 = levinson_durbin( r, phi, p); 
        //sigma2 = sigma2 * n / (n-p);
        float aic = 2*p + n * logf(sigma2);  

        if( aic < prev_aic )
        {
            result_p = p;
            prev_aic = aic;
        }

        #if defined( DEBUG )
            printf( "\np=%d,aic=%f\n", p, aic );
        #endif

        free( r );
        free( phi );
    }



    return result_p;
}

void pre_process( float* arr, int n, float* average, float* standard)
{
    float sum = 0.0f;
    for( int i=0; i<n; i++)
        sum += arr[i];
    *average = sum / n;
    for( int i=0; i<n; i++)
        arr[i] -= *average;

    sum = 0.0f;
    for( int i=0; i<n; i++)
        sum += arr[i] * arr[i];
    *standard = sqrt( sum / n );

    assert( *standard > 1e-6 );
    for( int i=0; i<n; i++)
        arr[i] /= *standard;
}


void calculate_r( float* arr, int n, float* r, int p)
{
    for( int i=0; i<=p; i++)
    {
        r[i] = 0.0;
        for (int t = 0; t < n-i; t++) 
            r[i] += arr[t] * arr[ t+i ];
        r[i] /= n;
    }
}

float levinson_durbin( float* r, float* phi, int p)
{

    float* a = (float*)safe_malloc( (p+1)*sizeof(float) );      
    float* prev_a = (float*)safe_malloc( (p+1)*sizeof(float) ); 


    float epsilon = r[0];
    a[0] = 1.0;

    for( int m=1; m<=p; m++)
    {

        float lambda = r[m];
        for( int j = 1; j < m; j++) 
            lambda += a[j] * r[ m-j ];
        lambda = -lambda / epsilon;

 
        memmove( prev_a, a, m*sizeof(float) );
        

        a[m] = lambda;
        for( int j = 1; j < m; j++) 
            a[j] = prev_a[j] + lambda * prev_a[ m-j ];
        
        epsilon *= ( 1 - lambda*lambda );
    }


    for( int i = 1; i <= p; i++) 
        phi[ i-1 ] = -a[i];

    free( a );
    free( prev_a );

    return epsilon;
    
}

void get_arr( const stock_data* stock , float* arr, int num )
{
    FILE* fp = open_file( stock->code, KDAY, "rb" );
    fseek( fp, sizeof(day_price) * (stock->days - num), SEEK_SET );
    day_price info;
    for( int i=0; i<num; i++)
    {
        SAFE_READ( &info, sizeof(day_price), 1, fp );
        arr[i] = info.close;
    }

    close_file( fp, stock->code, ".kday" );

    #if defined( DEBUG )
        printf( "\nclose:\n");
        print_array( arr, num, FLOAT );
    #endif

}
void save_close( const stock_data* stock , float* arr )
{
    FILE* fp = open_file( stock->code, PRED, "wb" );
    SAFE_WRITE( arr, sizeof(float), stock->days, fp );
    close_file( fp, stock->code, ".pred" );
}
void ar_pred( const stock_data* stock , int num )
{
    float* arr = (float*)safe_malloc( sizeof(float) * num );
    get_arr( stock, arr , num);
    save_close( stock, arr );

    float average, standard;
    pre_process( arr, num, &average, &standard);

    int p = choose_p( arr, num, 10 );
    //int p = 5;
    float* r = (float*)safe_malloc( (p+1)*sizeof(float) );
    float* phi = (float*)safe_malloc( p*sizeof(float) );

    calculate_r( arr, num, r, p );
    levinson_durbin( r, phi, p );


    float* x = (float*)safe_malloc( (p+FORECAST_DAYS)*sizeof(float) );  
    memmove( x, arr + num - p, p * sizeof(float) );
    free( arr );

    for( int i=0; i<FORECAST_DAYS; i++)
    {
        x[ i+p ] = 0.0;
        for(int j=0; j<p; j++)
            x[ i+p ] += phi[j] * x[ i+p-1-j];
    }
    for( int i=0; i<p+FORECAST_DAYS; i++)
        x[ i ] = x[ i ] * standard + average;



    #if defined(DEBUG)
        printf( "\nresult:\n");
        printf( "p: %d\n", p );
        printf( "r:");
        print_array( r, p+1, FLOAT );
        printf( "\nphi:");
        print_array( phi, p, FLOAT );
        printf( "\npred:");
        print_array( x, p+FORECAST_DAYS, FLOAT );
    #endif

    save_pred( stock, x+p );

    free( r );
    free( phi );
    free( x );

}
void save_pred( const stock_data* stock , float* x )
{

    FILE* predfp = open_file( stock->code, PRED, "rb+" );
    fseek( predfp, stock->days * sizeof(float), SEEK_SET );
    SAFE_WRITE( x, sizeof(float), FORECAST_DAYS, predfp );
    close_file( predfp, stock->code, ".pred" );

}