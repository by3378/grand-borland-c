#ifndef GENE_H
#define GENE_H

#include <math.h>
#include "stock.h"
#include "global.h"
#define TRAIN_DAYS 200
#define MAX_POPULATION 50
#define MAX_GENERATION 30
#define GENE_NUM 5 
#define MUTATE_RATE 0.05f
#define CROSS_RATE 0.8f
#define BLOCK_SIZE 20

#define SIGMOID(x) (1.0f / (1.0f + exp(-(x))))
#define CHECK_RATE(x) ( ( (float)rand()/RAND_MAX < x )? 1 : 0 )
#define SYMMETRY_RAND(x) ( (float)rand()/RAND_MAX*2*x - x )   /* [-x, x] */

enum trend_type { UP=1, DOWN=-1, NONE=0 };

typedef struct
{
    signed char ma;
    signed char expma;
    signed char xuechi;
    signed char kdj;
    signed char macd;
    signed char trend; /* up or down on the next day comparing to the current day */
}feature_data;

typedef struct
{
    float weights[5];
    float fitness;
}individual_data;



void initialize_population( individual_data* population );
float calculate_fitness( const individual_data* individual, const feature_data* features );
float predict( const individual_data* individual, const feature_data* feature);
individual_data roulette_selection( const individual_data* population );
void crossover( const individual_data* p1, const individual_data* p2, individual_data* child);
void mutate( individual_data* individual);
individual_data get_best_weights( feature_data* features );
void save_gene_result( const stock_data* stock );
void draw_gene_pred( const stock_data* stock );
/* TRAIN_DAYS is multiple of BLOCK_SIZE */
void initialize_feature( const stock_data* stock, feature_data* feature );
void macd_change( const stock_data* stock, feature_data* feature );
void ma_cross( const stock_data* stock, feature_data* feature );
void expma_cross( const stock_data* stock, feature_data* feature );
void xuechi_break_close( const stock_data* stock, feature_data* feature );
void kdj_status( const stock_data* stock, feature_data* feature );

#endif