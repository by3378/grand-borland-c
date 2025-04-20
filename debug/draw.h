#ifndef DRAW_H
#define DRAW_H

#include "global.h"

#define CALCULATE_Y(axis, value) \
( axis->y + ROUND( \
    (axis->max-value) * axis->length / (axis->max-axis->min) ))
/* axis->y + ROUND( (axis->max - value) * axis->length / (axis->max - axis->min) ) */

#define ROUND(X) (int)( ( (X)>=0.0 ) ? floor( (X)+0.5 ) : ceil( (X)-0.5 ) )

enum gear_type{ SMALL, MEDIUM, LARGE };

typedef struct 
{
    int x;  /* x-coordinate of the upper side of the axis */
    int y;  /* y-coordinate of the upper side of the axis */
    int length;  /* length of the axis( in pixels ) */
    int max;  /* maximum mark of the axis */
    int min;  /* minimum mark of the axis */
    int unit_num;  /* number of units */
}axis_data;

typedef struct
{
    int num; 
    int width;
    int gap; /* the distance between two lines */

}rectangle_info;
/* gap > width */

void get_most( const stock_data* stock, enum line_type type , int num, most_value* most);
void write_axis_number( const most_value* most, axis_data* axis );

void choose_rectangle( rectangle_info* rectangle , enum gear_type gear);
bool tell_line( enum line_type type , int* line_num );

void calculate_xy( float* buffer, int* xy_buffer, const rectangle_info* rectangle , const axis_data* axis );
void draw_line( const stock_data* stock, const rectangle_info* rectangle, enum line_type type, const axis_data* axis );
void draw_kline( FILE* fp , enum line_type type, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis );
void draw_simple_line( FILE* fp , int line_num, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis );
void draw_macd( FILE* fp, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis );

void draw_ar_pred( const stock_data* stock, rectangle_info* rectangle, axis_data* axis );


#endif