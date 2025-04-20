#ifndef CALCULATE_H
#define CALCULATE_H

#include <stdio.h>
#include "stock.h"

#define CALCULATE_EMA(close, argv, ema_prev) (2*(close)/((argv)+1) + (ema_prev)*(1-2/((argv)+1)))

void calculate_maline( const stock_data* stock );

void calculate_kdjline( const stock_data* stock );

float initialize_ema( FILE* kdayfp, int starting_day, int argv );
float initialize_dea( FILE* kdayfp, int starting_day , macd_data* macd );
void calculate_macd(  const stock_data* stock );

void calculate_expmaline( const stock_data* stock );

void initialize_truerange( FILE* kdayfp, int argv , float* truerange_buffer );
float get_max( float* arr, int size );
float get_sum( float* arr, int size );
void calculate_xuechi( const stock_data* stock );

int generate_kline_data( stock_data* stock );
int save_kline_most( stock_data* stock, enum line_type type , int argv);
int save_other_most( stock_data* stock, enum line_type type );

void generate_all( stock_data* stock , int period_length );

#endif