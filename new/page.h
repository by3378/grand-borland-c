#ifndef PAGE_H
#define PAGE_H

#include "global.h"

enum page{ WELCOME, REGISTER, INDICATOR, STATUS, MARKET, PREDICT, EXIT, SEARCH, NEWS, NOBUT };

enum page home_button( void );
int page_welcome( user_data* user );
int page_register( user_data* user );
int page_status( const user_data* user , stock_data* stock ); 
void draw_choosed_stock( int* choice , int* total );
int page_indicator( const stock_data* stock );
int page_market( const user_data* user );
int page_search( char* code );
int page_predict( const char* code );

#endif