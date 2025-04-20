#include "global.h"

void write_axis_number( const most_value* most, axis_data* axis )
{
    
    int gap = most->max - most->min;
    float unit_gap;/* gap between two marks */ 
    float marks[] = { 0.1f, 0.5f, 1, 2, 5, 10, 20, 50, 100 };
    int mark_num = sizeof(marks) / sizeof(marks[0]); /* the number of possible marks */
    for( int i=0; i<mark_num; i++ )
    {
        if( gap> axis->unit_num*marks[i] )
            continue;

        unit_gap = marks[i];
        axis->max = (int)ceil ( most->max/marks[i] ) *marks[i];
        axis->min = (int)floor( most->min/marks[i] ) *marks[i];
        break;
    }

    /* the length of one unit (in pixels)*/
    int unit_length = axis->length / axis->unit_num; 

    /* write the numbers of the coordinate axis */
    char buffer[6];/* contain 000.1-999.9 */
    int mark_y;
    float mark_value;
    for( int i=0; i< axis->unit_num +1; i++)
    {
        mark_y = axis->y + unit_length*i ;
        mark_value = axis->max - i*unit_gap;

        sprintf( buffer, "%.1f", mark_value );
        outtextxy( axis->x+5, mark_y, buffer);
    }

}


/* choose_gear function */
void choose_rectangle( rectangle_info* rectangle , enum gear_type gear)
{
    switch( gear )
    {
        case SMALL:
        {
            rectangle->width = ;
            rectangle->gap = ;
            rectangle->num = 63;
            break;
        } /* 63 rectangles */
        case MEDIUM:
        {
            rectangle->width = ;
            rectangle->gap = ;
            rectangle->num = 35;
            break;
        } /* 35 rectangles */
        case LARGE:
        {
            rectangle->width = ;
            rectangle->gap = ;
            rectangle->num = 14;
            break;
        } /* 14 rectangles */
    }
}


/* get the most value of the last num*period_length data  */
void get_most( const stock_data* stock, enum line_type type , int num, most_value* most)
{
    assert( num*stock->period_length <= stock->days );

    int line_num;
    bool ismain;
    ismain = tell_line( type , &line_num );
    FILE* fp = open_file( stock->code , type, "rb");

    most->max = -FLT_MAX;
    most->min = FLT_MAX;

    most_value* buffer = (most_value* )safe_malloc( num * sizeof(most_value));
    fseek( fp, -sizeof(most_value)*num, SEEK_END );
    SAFE_READ( buffer, sizeof(most_value), num, fp );
    close_file( fp, stock->code, ".who cares" );

    for( int i=0; i<num; i++ )
    {
        most->max = buffer[i].max > most->max ? buffer[i].max : most->max;
        most->min = buffer[i].min < most->min ? buffer[i].min : most->min;
    }
    free(buffer);

    if( ismain )
    {
        most_value most2;
        get_most( stock, KDAY , num, &most2);
        most->max = most2.max > most->max ? most2.max : most->max;
        most->min = most2.min < most->min ? most2.min : most->min;
    }

}

void draw_line( const stock_data* stock, const rectangle_info* rectangle, enum line_type type, const axis_data* axis )
{
    most_value most;
    get_most( stock, type, rectangle->num/stock->period_length, &most);
    write_axis_number( &most, axis);

    int line_num;
    bool ismain = tell_line( type , &line_num );
    FILE* fp = open_file( stock->code, type );

    if( type == KDAY || type == KWEEK ) 
        draw_kline( fp, type, stock, rectangle, axis);
    else if( type == MACD )  /* column type sub indicator*/
        draw_macd( fp, stock, rectangle, axis);
    else if( !ismain )       /* line type sub indicator*/
        draw_simple_line( fp, line_num, stock, rectangle, axis);        
    else if( ismain )        /* draw main indicator with KDAY */
    {
        draw_simple_line( fp, line_num, stock, rectangle, axis);
        draw_kline( fp, KDAY, stock, rectangle, axis);
    }

    close_file( fp, stock->code, ".whatever" );
}

void draw_kline( FILE* fp , enum line_type type, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis )
{

    /* has defined: typedef day_price week_data; */
    if( type == KDAY )
        fseek( fp, sizeof(day_price)*stock->days, SEEK_SET );
    else /* KWEEK */
        fseek( fp, sizeof(week_data)*stock->weeks, SEEK_SET );

    fseek( fp, -sizeof(day_price)*rectangle->num, SEEK_CUR );

    day_price info;
    enum COLORS color;
    int high_y, low_y, open_y, close_y;  /* Y coordinates */
    int present_x = axis->x - rectangle->gap*rectangle->num;
    int half_width = ROUND(rectangle->width/2);

    assert( present_x >= 0 ); /* check if the num is too large */

    for( int i = 0; i < rectangle->num ; i++ , present_x += rectangle->gap )
    {

        SAFE_READ( &info, sizeof(day_price), 1, fp );

        if( info.close > info.open )
            color = RED;
        else
            color = GREEN;
        setcolor( color );
        setfillpattern( SOLID_FILL, color );

        high_y = CALCULATE_Y( axis, info.high );
        low_y = CALCULATE_Y( axis, info.low );
        open_y = CALCULATE_Y( axis, info.open );
        close_y = CALCULATE_Y( axis, info.close );

        /* draw kline */
        line( present_x, high_y, present_x, low_y );
        bar( present_x-half_width, open_y, present_x+half_width, close_y );
    }

    close_file( fp, stock->code, ".kday or .kweek" );
}
void draw_simple_line( FILE* fp , int line_num, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis )
{
    for( int p = 0; p < line_num; p++ )
    {
        float* buffer = (float* )safe_calloc( rectangle->num , sizeof(float));
        fseek( fp, sizeof(float)*stock->days*p, SEEK_SET );
        fseek( fp, -sizeof(float)*rectangle->num, SEEK_CUR );
        SAFE_READ( buffer, sizeof(float), rectangle->num, fp );

        int* xy_buffer = (int* )safe_malloc( rectangle->num*2 * sizeof(int));
        calculate_xy( buffer, xy_buffer, rectangle, axis );

        drawpoly( rectangle->num, xy_buffer );
        free(buffer);
        free(xy_buffer);
    }
}
void calculate_xy( float* buffer, int* xy_buffer, const rectangle_info* rectangle , const axis_data* axis )
{
    int present_x = axis->x - rectangle->gap*rectangle->num;

    assert( present_x >= 0 ); /* check if the num is too large */

    for( int i = 0; i < rectangle->num; i++, present_x += rectangle->gap )
    {
        xy_buffer[i*2] = present_x;
        xy_buffer[i*2+1] = CALCULATE_Y( axis, buffer[i] );
    }
}
void draw_macd( FILE* fp, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis )
{
    draw_simple_line( fp, 2, stock, rectangle, axis);

    float* buffer = (float* )safe_calloc( rectangle->num , sizeof(float));
    fseek( fp, sizeof(float)*stock->days*3, SEEK_SET );
    fseek( fp, -sizeof(float)*rectangle->num, SEEK_CUR );
    SAFE_READ( buffer, sizeof(float), rectangle->num, fp );

    int* xy_buffer = (int* )safe_malloc( rectangle->num*2 * sizeof(int));
    calculate_xy( buffer, xy_buffer, rectangle, axis );
    free(buffer);

    int zero_y = CALCULATE_Y( axis, 0 );
    enum COLORS color;
    for( int i=0; i<rectangle->num; i++ )
    {
        if( buffer[i*2+1] > 0 )
            color = RED;
        else
            color = GREEN;
        setcolor( color );

        line( xy_buffer[i*2], zero_y, xy_buffer[i*2], xy_buffer[i*2+1] );
    }
    free(xy_buffer);
}




void draw_gene_pred( const stock_data* stock )
{
    FILE* fp = open_file( stock->code, GENE, "rb" );
    individual_data best;
    feature_data last;
    float probability;
    SAFE_READ( &best, sizeof(individual_data), 1, fp );
    SAFE_READ( &last, sizeof(feature_data), 1, fp );
    SAFE_READ( &probability, sizeof(float), 1, fp );
    close_file( fp, stock->code, ".gene" );

    printf( "\ngene result:\n" );
    printf( "weights: MA_cross: %.2f, EXPMA_cross: %.2f, XS_channel: %.2f, KDJ_status: %.2f, MACD_change: %.2f\n"
        , best.weights[0], best.weights[1], best.weights[2], best.weights[3], best.weights[4] );
    printf( "last day: trend: %d, MA_cross: %d, EXPMA_cross: %d, XS_channel: %d, KDJ_status: %d, MACD_change: %d\n"
        , last.trend, last.ma, last.expma, last.xuechi, last.kdj, last.macd );
    printf( "probability: %.2f%% \n",  probability * 100 );
   
}

void draw_ar_pred( const stock_data* stock, rectangle_info* rectangle, axis_data* axis )
{
    FILE* predfp = open_file( stock->code , PRED, "rb");

    int real_days = 3;
    fseek( predfp, -sizeof(float)*(FORECAST_DAYS+real_days)+sizeof(most_value), SEEK_END );

    float* pred_buffer = (float* )safe_calloc( FORECAST_DAYS+real_days, sizeof(float));
    SAFE_READ( pred_buffer, sizeof(float), FORECAST_DAYS+real_days, predfp );

    most_value most = { -FLT_MAX, FLT_MAX };
    for( int i=0; i< real_days+FORECAST_DAYS; i++)
    {
        most.max = most.max > pred_buffer[i] ? most.max : pred_buffer[i];
        most.min = most.min < pred_buffer[i] ? most.min : pred_buffer[i];
    }
    write_axis_number( &most, axis);

    close_file( predfp, stock->code, ".pred" );

    float* xy_buffer = (float*)safe_malloc( sizeof(int) * 2 * (FORECAST_DAYS+real_days) );
    calculate_xy( pred_buffer, xy_buffer, &rectangle, &axis );
    
    setlinestyle( SOLID_LINE, 0, 1 );
    drawpoly( real_days, xy_buffer );
    setlinestyle( DOTTED_LINE, 0, 1 );
    drawpoly( FORECAST_DAYS, xy_buffer+real_days*2 );

    free(pred_buffer);
    free(xy_buffer);
    
}