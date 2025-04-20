#ifndef PAGE_H
#define PAGE_H
/*
#include "stock.h"

void indicator_page( const stock_data* stock );
void predict_page( const stock_data* stock );
*/

int page_welcome();
int page_register();
int page_stock();
int page_market();
int page_search();
int page_predict(const stock_data* stock);
#endif