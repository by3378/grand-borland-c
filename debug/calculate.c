#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#include "stock.h"
#include "calculate.h"
#include "global.h"
#include "file.h"
#include "queue.h"
#include "draw.h"
#include "ar.h"
#include "gene.h"

/********** KLINE *************/
void calculate_kline( stock_data* stock, enum line_type type )
{
    FILE* source;
    FILE* output;
    int* pt = NULL;
    const char* format = NULL;
    switch( type )
    {
        case KDAY:
        {
            source = open_file( stock->code, DAY , "r");
            format = "%lu %f %f %f %f %*f %*f";
            pt = &stock->days;
            break;
        }
        case KWEEK:
        {
            source = open_file( stock->code, WEEK, "r");
            format = "%lu %f %f %f %f %*f";
            pt = &stock->weeks;
            break;
        }
        default:
        {
            fprintf( stderr, "Error: Invalid argv\n" );
            return;
        }
    }
    output = open_file( stock->code, type , "wb");

    #if defined( DEBUG )
        printf( "\n%s:\n", stock->code );
    #endif
    
    int num = 0;
    day_price info;
    bool isend = false;
    while( !isend )
    {
        k_scanf( source, format, &info, &isend );
        if( !isend )
        {
            num++;
            SAFE_WRITE( &info, sizeof(day_price), 1, output );
            #if defined( DEBUG )
                printf( "date:%lu, open:%.2f, high:%.2f, low:%.2f, close:%.2f\n", info.date, info.open, info.high, info.low, info.close );
            #endif
        }
    }
    *pt = num;  /* ATTENTION! valid weeks or days are saved into stock here ,
                      but have NOT been saved permanently yet! */
    #if defined( DEBUG )
        printf( "num:%d\n", num );
        putchar( '\n' );
    #endif

    close_file( source, stock->code, ".txt" );
    close_file( output, stock->code, ".kline" );

}
void k_scanf( FILE* fp,  const char* format, day_price* info, bool* isend ) 
{
    int check;
    check = fscanf( fp, format, &info->date, &info->open, &info->high, &info->low, &info->close );
    if( check != 5 )
    {
        if( feof( fp ))
            (*isend) = true;
        else
        {
            if( ferror( fp ) )
                perror("Read error");
            else
                fprintf(stderr, "Failed to read all 5 values.\n");
            exit(EXIT_FAILURE);
        }
    }
}

/********** MALINE *************/
void calculate_maline( const stock_data* stock )
{

    FILE* kdayfp = open_file( stock->code , KDAY, "rb");
    FILE* mafp   = open_file( stock->code , MA  , "wb");
    
    int types[] = { MA5, MA10, MA20 };  /* add more if needed */
    int line_num = sizeof(types) / sizeof(types[0]); 
    
    int argv;
    float sum;
    day_price info;
    for( int p = 0; p < line_num; p++ )
    {
        rewind( kdayfp );

        sum = 0.0f;
        argv = types[p];  /* 5\10\20 */

        /* needs to be initialized to 0 */
        float* close_buffer  = (float* )safe_calloc( argv , sizeof(float));       /* 5\10\20 * 4 = max 80   bytes */
        float* result_buffer = (float* )safe_calloc( stock->days , sizeof(float));/* nearly 300*4= max 1200 bytes */
        
        /* the first "argv-1" days are invalid and are 0 */
        /* using circular buffer */
        for( int i=0,j=0; i < stock->days; i++ )
        {
            SAFE_READ( &info, sizeof(day_price), 1, kdayfp );

            sum -= close_buffer[j];
            close_buffer[j] = info.close;
            sum += close_buffer[j];

            if( ++j == argv )
                j = 0;
    
            /* using present day's data */
            if( i>=argv-1 )
                result_buffer[ i ] = sum / argv;
            
        }        
        
        #if defined( DEBUG )
            printf( "\n%s:\n", stock->code );
            printf( "\n MA:\n" );
            print_array( result_buffer, stock->days , FLOAT);
        #endif

        SAFE_WRITE( result_buffer, sizeof(float), stock->days, mafp );

        free( result_buffer);
        free( close_buffer );

    }

    close_file( kdayfp, stock->code, ".kday" );
    close_file( mafp  , stock->code, ".ma"   );

}

/********** KDJLINE *************/
void calculate_kdjline( const stock_data* stock )
{

    FILE* kdayfp = open_file( stock->code , KDAY, "rb");

    float* k_buffer = (float* )safe_calloc( stock->days , sizeof(float)); /* nearly 300*4= max 1200 bytes */
    float* d_buffer = (float* )safe_calloc( stock->days , sizeof(float));
    float* j_buffer = (float* )safe_calloc( stock->days , sizeof(float)); /* totaly 3600 bytes */

    int size = 9;
    monotonic_queue max_queue, min_queue;
    init_queue( &max_queue, size );
    init_queue( &min_queue, size );

    day_price info;
    kdj_data kdj = { 50.0f, 50.0f, 0.0f };
    float highest, lowest;
    float rsv, close_t;

    for( int i=0; i < stock->days; i++ )
    {
        SAFE_READ( &info, sizeof(day_price), 1, kdayfp );

        enqueue( &max_queue, info.high, i, max_compare );
        enqueue( &min_queue, info.low , i, min_compare );

        /* starting index of the window: i-size+1 */
        dequeue( &max_queue, i - size + 1 );
        dequeue( &min_queue, i - size + 1 );

        if( i < size-1 )
            continue;

        close_t = info.close;
        highest = get_front( &max_queue );
        lowest  = get_front( &min_queue );
        rsv = ( close_t - lowest ) *100 / ( highest - lowest );

        kdj.k = kdj.k * 2/3 + rsv /3;
        kdj.d = kdj.d * 2/3 + kdj.k /3;
        kdj.j = 3* kdj.k - 2* kdj.d;

        k_buffer[ i ] = kdj.k;
        d_buffer[ i ] = kdj.d;
        j_buffer[ i ] = kdj.j;

    }

    free_queue( &max_queue );
    free_queue( &min_queue );
    close_file( kdayfp, stock->code, ".kday" );

    #if defined( DEBUG )
        printf( "\n%s:\n", stock->code );
        printf( "\n KDJ:\n" );
        print_array( k_buffer, stock->days , FLOAT );
        putchar('\n');
        print_array( d_buffer, stock->days , FLOAT );
        putchar('\n');
        print_array( j_buffer, stock->days , FLOAT );
        putchar('\n');
    #endif

    FILE* kdjfp = open_file( stock->code , KDJ, "wb");
    SAFE_WRITE( k_buffer, sizeof(float), stock->days, kdjfp );
    SAFE_WRITE( d_buffer, sizeof(float), stock->days, kdjfp );
    SAFE_WRITE( j_buffer, sizeof(float), stock->days, kdjfp );
    close_file( kdjfp, stock->code, ".kdj" );

    free(k_buffer);
    free(d_buffer);
    free(j_buffer);

}


/********** MACD *************/
/* initialize ema is calculating sma of close */
float initialize_ema( FILE* kdayfp, int starting_day, int argv )
{
    float sum = 0.0f;
    day_price info;
    /* if argv=12, skip 26-12=14 days */
    /* if argv=26, skip 26-26=0  days */
    fseek( kdayfp, sizeof(day_price)*(starting_day), SEEK_SET );
    for( int i=0 ; i < argv; i++ )
    {
        SAFE_READ( &info, sizeof(day_price), 1, kdayfp );
        sum += info.close;
    }
    return sum/argv;
}
/* calculating sma of dif*/
float initialize_dea( FILE* kdayfp, int starting_day , macd_data* macd )
{
    float sum = 0.0f;
    day_price info;
    fseek( kdayfp, sizeof(day_price)*(starting_day), SEEK_SET );
    for( int i=0; i < 9; i++ )
    {

        SAFE_READ( &info, sizeof(day_price), 1, kdayfp );
        macd->ema_12 = CALCULATE_EMA( info.close, 12, macd->ema_12 );
        macd->ema_26 = CALCULATE_EMA( info.close, 26, macd->ema_26 );
   
        sum += macd->ema_12 - macd->ema_26;
   
    }
    return sum/9;
   
}
void calculate_macd( const stock_data* stock )
{

    FILE* kdayfp = open_file( stock->code , KDAY, "rb");

    /* 26 days for initializing ema  */
    /*  9 days for initializing dea  */
    /* the first 35 days are invalid */
    macd_data macd;
    macd.ema_12 = initialize_ema( kdayfp, 14, 12 );
    macd.ema_26 = initialize_ema( kdayfp,  0, 26 );
    macd.dea = initialize_dea( kdayfp, 26, &macd );


    float* dif_buffer = (float* )safe_calloc( (stock->days)*2 , sizeof(float));
    float* dea_buffer = (float* )safe_calloc( (stock->days)*2 , sizeof(float));
    float* macd_buffer =(float* )safe_calloc( (stock->days)*2 , sizeof(float));


    day_price info;
    fseek( kdayfp, sizeof(day_price)*35, SEEK_SET );
    for( int i=35 ; i < stock->days; i++ )
    {
        SAFE_READ( &info, sizeof(day_price), 1, kdayfp );

        macd.ema_12 = CALCULATE_EMA( info.close, 12, macd.ema_12 );
        macd.ema_26 = CALCULATE_EMA( info.close, 26, macd.ema_26 );
        macd.dif = macd.ema_12 - macd.ema_26;
        macd.dea = CALCULATE_EMA( macd.dif, 9, macd.dea );
        macd.macd_value = (macd.dif - macd.dea)*2;

        dif_buffer[ i ] = macd.dif;
        dea_buffer[ i ] = macd.dea;
        macd_buffer[ i ] = macd.macd_value;

    }

    close_file( kdayfp, stock->code, ".kday" );

    #if defined( DEBUG )
        printf( "\n%s:\n", stock->code );
        printf( "\n MACD:\n" );
        print_array( dif_buffer, stock->days , FLOAT );
        putchar('\n');
        print_array( dea_buffer, stock->days , FLOAT );
        putchar('\n');
        print_array( macd_buffer,stock->days , FLOAT );
        putchar('\n');
    #endif
    
    FILE* fpmacd = open_file( stock->code , MACD, "wb");
    SAFE_WRITE( dif_buffer, sizeof(float), stock->days, fpmacd );
    SAFE_WRITE( dea_buffer, sizeof(float), stock->days, fpmacd );
    SAFE_WRITE( macd_buffer, sizeof(float), stock->days, fpmacd );
    close_file( fpmacd, stock->code, ".macd" );

    free(dif_buffer);
    free(dea_buffer);
    free(macd_buffer);

}

/********** EXPMALINE *************/
void calculate_expmaline( const stock_data* stock )
{

    FILE* kdayfp  = open_file( stock->code , KDAY , "rb");
    FILE* expmafp = open_file( stock->code , EXPMA, "wb");

    int types[] = { EXPMA12, EXPMA50 };
    int line_num = sizeof(types) / sizeof(types[0]); 

    int argv;
    day_price info;
    for( int p = 0; p < line_num; p++ )
    {
        rewind( kdayfp );

        argv = types[p];
        float expma = initialize_ema( kdayfp, 0, argv );
        #if defined( DEBUG )
            printf( "expma%d:\n",argv);
            printf( "initialize:%.2f\n", expma );
        #endif
        float* result_buffer = (float* )safe_calloc( stock->days , sizeof(float));
        
        fseek( kdayfp, sizeof(day_price)*argv, SEEK_SET );
        for( int i=argv; i < stock->days; i++ )
        {
            SAFE_READ( &info, sizeof(day_price), 1, kdayfp );
            expma = CALCULATE_EMA( info.close, argv, expma );
            result_buffer[ i ] = expma;
        }        

        #if defined( DEBUG )
            printf( "\n%s:\n", stock->code );
            printf( "\n EXPMA:\n" );
            print_array( result_buffer, stock->days , FLOAT );
            putchar('\n');
        #endif

        SAFE_WRITE( result_buffer, sizeof(float), stock->days, expmafp );
        free(result_buffer);

    }

    close_file( kdayfp, stock->code, ".kday" );
    close_file( expmafp, stock->code, ".expma" );

}


/********** XUECHI *************/
void initialize_truerange( FILE* kdayfp, int argv , float* truerange_buffer )
{
    day_price info;
    float close_prev;
    SAFE_READ( &info, sizeof(day_price), 1, kdayfp );
    close_prev = info.close;

    float temp[3];
    for( int i=0 ; i < argv; i++ )
    {
        SAFE_READ( &info, sizeof(day_price), 1, kdayfp );

        temp[0] = info.high - info.low;
        temp[1] = fabs( info.high - close_prev );
        temp[2] = fabs( info.low - close_prev );
        truerange_buffer[i] = get_max( temp, 3 );

        close_prev = info.close;
    }

}
float get_max( float* arr, int size )
{
    float max = -FLT_MAX;
    for( int i=0; i < size; i++ )
        max = ( arr[i] > max ) ? arr[i] : max;
    return max;
}
float get_sum( float* arr, int size )
{
    float sum = 0.0f;
    for( int i=0; i < size; i++ )
        sum += arr[i];
    return sum;
}
void calculate_xuechi( const stock_data* stock )
{
    FILE* kdayfp   = open_file( stock->code , KDAY  , "rb");
    FILE* xuechifp = open_file( stock->code , XUECHI, "wb");

    int argv;
    int types[] = { XUECHI20, XUECHI60 };
    int line_num = sizeof(types) / sizeof(types[0]); 
    
    float atr,median,close_prev,sum;
    float temp[3];
    day_price info;
    for( int p = 0; p < line_num; p++ )
    {
        rewind( kdayfp );

        argv = types[p];
        float* truerange_buffer = (float* )safe_calloc( argv , sizeof(float));/* 20/60*4 = max 240  bytes */
        float* up_buffer = (float* )safe_calloc( stock->days , sizeof(float));/* nearly 300*4= max 1200 bytes */
        float* dn_buffer = (float* )safe_calloc( stock->days , sizeof(float));

        initialize_truerange( kdayfp, argv, truerange_buffer );
        sum = get_sum( truerange_buffer, argv );
        atr = sum / argv;

        fseek( kdayfp, sizeof(day_price)*(argv-1), SEEK_SET );
        SAFE_READ( &info, sizeof(day_price), 1, kdayfp );
        median = ( info.high + info.low ) / 2;
        close_prev = info.close;

        for( int i=argv,j=0; i < stock->days; i++ )
        {

            up_buffer[ i ] =  median + atr*2;
            dn_buffer[ i ] =  median - atr*2;

            SAFE_READ( &info, sizeof(day_price), 1, kdayfp );
            sum -= truerange_buffer[j];
            temp[0] = info.high - info.low;
            temp[1] = fabs( info.high - close_prev );
            temp[2] = fabs( info.low - close_prev );
            truerange_buffer[j] = get_max( temp, 3 );
            sum += truerange_buffer[j];
    
            if( ++j == argv )
                j = 0;
    
            median = ( info.high + info.low ) / 2;
            atr = sum/argv;
            close_prev = info.close;
    
        }

        #if defined( DEBUG )
            printf( "\n%s:\n", stock->code );
            printf( "\n XUECHI:\n" );
            print_array( up_buffer, stock->days , FLOAT );
            putchar('\n');
            print_array( dn_buffer, stock->days , FLOAT );
            putchar('\n');
        #endif

        SAFE_WRITE( up_buffer, sizeof(float), stock->days, xuechifp );
        SAFE_WRITE( dn_buffer, sizeof(float), stock->days, xuechifp );

        free(truerange_buffer);
        free(up_buffer);
        free(dn_buffer);

    }

    close_file( kdayfp, stock->code, ".kday" );
    close_file( xuechifp, stock->code, ".xuechi" );

}


/********** SAVE MOST *************/
void save_most( stock_data* stock, enum line_type type , int argv )
{
    FILE* fp;
    int left,num; /* for period */
    size_t data_size;
    int data_num;

    int line_num;
    tell_line( type , &line_num );
    fp = open_file( stock->code, type, "rb+" );

    void (*process_data)( void* , most_value* , int );
    switch( type )
    {
        case KDAY:
        {
            data_num = stock->days;
            data_size = sizeof(day_price);
            process_data = process_day_price;
            break;
        }
        case KWEEK:
        {
            data_num = stock->weeks;
            data_size = sizeof(day_price);
            process_data = process_day_price;
            break;
        }
        default:
        {
            data_num = stock->days;
            data_size = sizeof(float);
            process_data = process_float;
            break;
        }
    }

    left = data_num%argv;
    num  = data_num%argv==0 ? data_num/argv : data_num/argv+1;
    if( type == KDAY )
    {
        stock->period_length = argv;
        stock->period_num = num;
    }

    /* store the most value every "argv" days ,the first one may be incomplete */
    most_value most = {-FLT_MAX,FLT_MAX};
    most_value* buffer = (most_value* )safe_malloc( num * sizeof(most_value));
    for( int i=0; i<num; i++ )
        buffer[i] = most;

    void* temp = safe_malloc( data_size*argv );

    int i,j,k;
    for( i=0; i<line_num; i++ )
    {
        /* first period ( incomplete )*/
        fseek( fp, data_num*data_size*i, SEEK_SET );
        SAFE_READ( temp, data_size, left, fp );
        process_data( temp, &buffer[0], left );

        /* left periods ( complete )*/
        for( j = (left==0) ? 0:1 ; j<num; j++ )
        {
            SAFE_READ( temp, data_size, argv, fp );
            process_data( temp, &buffer[j], argv );
        }
    }

    #if defined( DEBUG )
        printf( "\n MOST:\n" );
        print_array( buffer, num , MOST_VALUE );
    #endif

    fseek( fp,  0, SEEK_END );
    SAFE_WRITE( buffer, sizeof(most_value), num, fp );

    free(temp);
    free(buffer);

    close_file( fp , stock->code, ".whatever" );
}
void process_day_price( void* data, most_value* most, int num )
{
    day_price* prices = (day_price*)data;
    for (int i = 0; i < num; i++)
    {
        most->max = most->max > prices[i].high ? most->max : prices[i].high;
        most->min = most->min < prices[i].low  ? most->min : prices[i].low;
    }
}
void process_float( void* data, most_value* most, int num )
{
    float* values = (float*)data;
    for (int i = 0; i < num; i++)
    {
        most->max = most->max > values[i] ? most->max : values[i];
        most->min = most->min < values[i] ? most->min : values[i];
    }
}

/********** MAIN FUNCTION *************/
void calculate( stock_data* stock , int period_length )
{
    calculate_kline( stock, KDAY );
    calculate_kline( stock, KWEEK);
    save_most( stock, KDAY , period_length);
    save_most( stock, KWEEK, period_length);
    #if defined( DEBUG )
        printf( "\nstatistics:\n");
        printf( "\n%s:\n", stock->code );
        printf( "days: %d\n", stock->days );
        printf( "weeks: %d\n", stock->weeks );
        printf( "period_length: %d\n", stock->period_length );
        printf( "period_num: %d\n", stock->period_num );
    #endif

    calculate_maline   ( stock );
    save_most( stock, MA ,period_length);
    calculate_kdjline  ( stock );
    save_most( stock, KDJ ,period_length);
    calculate_macd     ( stock );
    save_most( stock, MACD ,period_length);
    calculate_expmaline( stock );
    save_most( stock, EXPMA ,period_length);
    calculate_xuechi   ( stock );
    save_most( stock, XUECHI ,period_length);

    ar_pred( stock , 120);
    save_gene_result( stock );

}

void load(void)
{
    FILE* fp = open_file( "main", STOCK, "wb");

    stock_data stock[] = 
    {
        { "000988", 0, 0, 0, 0 },
        { "300161", 0, 0, 0, 0 }
    };

    stock_data2 info[] = 
    {
        { 1, "000988", "华工科技", "湖北", "科技行业", 0, 10.0, 10.0, 10.0, 10.0 },
        { 2, "300161", "华中数控", "湖北", "科技行业", 0, 10.0, 10.0, 10.0, 10.0 }
    };

    int count = sizeof(stock) / sizeof(stock[0]);

    for( int i = 0; i < count; i++ ) 
    {
        calculate(&stock[i], 5);
        SAFE_WRITE(&stock[i], sizeof(stock_data), 1, fp);
        SAFE_WRITE(&info[i], sizeof(stock_data2), 1, fp);
    }

    close_file( fp, "main", ".stock");
}

/********** DEBUG ***************/
void print_array( void* arr, int size , enum data_type type )
{

    void (*print_data)( void* data, int index );
    switch( type )
    {
        case DAY_PRICE:
        {
            print_data = print_day_price;
            break;
        }
        case FLOAT:
        {
            print_data = print_float;
            break;
        }
        case MOST_VALUE:
        {
            print_data = print_most_value;
            break;
        }
        default:
        {
            fprintf(stderr, "Invalid type\n");
            return;
        }
    }
    for( int i=0; i<size; i++ )
    {
        print_data( arr, i );
        if( i%10 == 9 )
            putchar('\n');
    }

}
void print_day_price( void* data, int index )
{
    day_price* result = (day_price*)data;
    printf("%lu %.2f %.2f %.2f %.2f\n", result[index].date, result[index].open, result[index].high, result[index].low, result[index].close);
}
void print_float( void* data, int index )
{
    float* result = (float*)data;
    printf("%.2f ", result[index]);
}
void print_most_value( void* data, int index )
{
    most_value* result = (most_value*)data;
    printf("%.2f %.2f \n", result[index].max, result[index].min);
}


bool tell_line( enum line_type type , int* line_num )
{
    bool ismain;
    switch( type )
    {
        case KDAY:
        {
            *line_num = 1;
            ismain = false;/* */
            break;
        }
        case KWEEK:
        {
            *line_num = 1;
            ismain = false;/* */
            break;
        }
        case MA:
        {
            *line_num = 3;
            ismain = true;
            break;
        }
        case EXPMA:
        {
            *line_num = 2;
            ismain = true;
            break;
        }
        case XUECHI:
        {
            *line_num = 4;
            ismain = true;
            break;
        }
        case KDJ:
        {
            *line_num = 3;
            ismain = false;
            break;
        }
        case MACD:
        {
            *line_num = 3;
            ismain = false;
            break;
        }
        case PRED:
        {
            *line_num = 1;
            ismain = false;
            break;
        }
        default:
        {
            fprintf(stderr, "Error: Invalid type\n");
            exit(EXIT_FAILURE);
        }
    }
    return ismain;

}