#ifndef PAGE_H
#define PAGE_H

#include "stock.h"
#include "global.h"

#define STOCK_NUM 10

typedef struct
{
    char name[12];
    char password[12];
}user_data;

void choose_page( const user_data* use, bool isnew );
void indicator_page( const stock_data* stock );
void predict_page( const stock_data* stock );

#endif