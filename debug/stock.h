#ifndef STOCK_H
#define STOCK_H

#define MAX_DAYS 305
#define MAX_WEEKS 66
#define CODE_LEN 8 
#define FORECAST_DAYS 3

#include "global.h"
enum line_type { KDAY, KWEEK, MA, EXPMA, XUECHI, KDJ, MACD, NA, PRED, DAY, WEEK , STOCK, GENE , CHOICE };
enum maline_type{ MA5=5, MA10=10, MA20=20};
enum expmaline_type{ EXPMA12=12, EXPMA50=50 };
enum xuechi_type{ XUECHI20=20, XUECHI60=60 };

typedef struct
{
    char code[CODE_LEN+1];
    int days;/* valid market days*/
    int weeks;/* valid weeks*/
    int period_length;/* for most value saving*/
    int period_num;
}stock_data;

typedef struct
{
    int flag;
    char code[CODE_LEN+1];
    char name[ 12 ];
    char region[ 12 ];
    char industry[ 12 ];
    unsigned int date;
    float open;
    float high;
    float low;
    float close;

}stock_data2;

typedef struct
{
    float max;
    float min;
}most_value;

typedef struct
{
    unsigned int date;
    float open;
    float high;
    float low;
    float close;
}day_price;
typedef day_price week_data;

typedef struct 
{
    float k;
    float d;
    float j;
}kdj_data;

typedef struct 
{
    float dif;
    float dea;
    float macd_value;
    float ema_12;
    float ema_26;

}macd_data;


#endif