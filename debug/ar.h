#ifndef AR_H
#define AR_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <string.h>
#include "ar.h"
#include "file.h"
#include "stock.h"
#include "draw.h"
#include "global.h"
#include "calculate.h"

int choose_p( float* data, int n, int max_p );
void pre_process( float* arr, int n, float* average, float* standard);
void calculate_r( float* arr, int n, float* r, int p);
float levinson_durbin( float* r, float* phi, int p);
void get_arr( const stock_data* stock , float* arr, int num );
void ar_pred( const stock_data* stock , int num );
void save_pred( const stock_data* stock , float* x );
void save_close( const stock_data* stock , float* arr );

#endif