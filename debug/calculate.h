#ifndef CALCULATE_H
#define CALCULATE_H

#include <stdio.h>
#include "stock.h"
#include "global.h"

#define CALCULATE_EMA(close, argv, ema_prev) (2.0*(close)/((argv)+1) + (ema_prev)*(1-2.0/((argv)+1)))

enum data_type{ DAY_PRICE, FLOAT, MOST_VALUE };


/********** KLINE *************/
void calculate_kline( stock_data* stock, enum line_type type );
void k_scanf( FILE* fp,  const char* format, day_price* info, bool* isend );
/********** MALINE *************/
void calculate_maline( const stock_data* stock );
/********** KDJLINE *************/
void calculate_kdjline( const stock_data* stock );
/********** MACD *************/
float initialize_ema( FILE* kdayfp, int starting_day, int argv );
float initialize_dea( FILE* kdayfp, int starting_day , macd_data* macd );
void calculate_macd( const stock_data* stock );
/********** EXPMALINE *************/
void calculate_expmaline( const stock_data* stock );
/********** XUECHI *************/
void initialize_truerange( FILE* kdayfp, int argv , float* truerange_buffer );
float get_max( float* arr, int size );
float get_sum( float* arr, int size );
void calculate_xuechi( const stock_data* stock );
/********** SAVE MOST *************/
void save_most( stock_data* stock, enum line_type type , int argv );
void process_day_price( void* data, most_value* most, int num );
void process_float( void* data, most_value* most, int num );
/********** MAIN FUNCTION *************/
void calculate( stock_data* stock , int period_length );
void load(void);
/********** DEBUG ***************/
void print_array( void* arr, int size , enum data_type type );
void print_day_price( void* data, int index );
void print_float( void* data, int index );
void print_most_value( void* data, int index );

bool tell_line( enum line_type type , int* line_num );

#endif