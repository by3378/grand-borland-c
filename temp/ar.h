#ifndef AR_H
#define AR_H

#include "stock.h"

float minus_average( float* arr , int n );
void calculate_r( float* arr, int n, float* r, int p);
float levinson_durbin( float* r, float* phi, int p);
void predict_close( const stock_data* stock );
int choose_p( float* data, int n, int max_p );

#endif