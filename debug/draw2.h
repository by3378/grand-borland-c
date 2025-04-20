#ifndef DRAW2_H
#define DRAW2_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <graphics.h>
#include <dos.h>
#include "use.h"
#include "file.h"
#include "draw.h"
#include "hzo.h"


void draw_tongdaxin();
void draw_welcome();
void draw_register();
void draw_home();
void draw_stock(); 
void draw_market(); 
//void draw_analysis(); 
void draw_wenxiaoda();
void draw_search();
void draw_predict();
void draw_gene_pred(const stock_data* stock);
void draw_ar_pred(const stock_data* stock, rectangle_info* rectangle, axis_data* axis);

#endif