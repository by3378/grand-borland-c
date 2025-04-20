#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "stock.h"
#include "file.h"
#include "gene.h"

void initialize_population( individual_data* population )
{
    for( int i = 0; i < MAX_POPULATION; i++)
        for (int j = 0; j < GENE_NUM; j++)
            population[i].weights[j] = SYMMETRY_RAND( 2.0f ); 
}

float calculate_fitness( const individual_data* individual, const feature_data* features )
{
    int correct = 0;
    for( int i = 0; i < TRAIN_DAYS; i++)
    {
        int result = predict( individual, &features[i] );
        int predict_trend = ( result > 0.5 ) ? 1 : 0;
        if( predict_trend == features[i].trend)
            correct++;
    }
    return (float)correct / TRAIN_DAYS;
}

individual_data roulette_selection( const individual_data* population )
{
    float total = 0.0f;
    for( int i = 0; i < MAX_POPULATION; i++)
        total += population[i].fitness;
    
    float threshold = (float)rand()/RAND_MAX * total;
    float sum = 0.0f;
    
    for( int i = 0; i < MAX_POPULATION; i++)
    {
        sum += population[i].fitness;
        if( sum >= threshold )
            return population[i];
    }
}

void crossover( const individual_data* p1, const individual_data* p2, individual_data* child)
{
    if( CHECK_RATE(CROSS_RATE) )
    {
        int point = rand() % GENE_NUM;
        for( int i = 0; i < point; i++ )
            child->weights[i] = p1->weights[i];
        for( int i = point; i < GENE_NUM; i++ )
            child->weights[i] = p2->weights[i];
    }
    else 
        *child = *p1;
}

void mutate( individual_data* individual)
{
    for( int i = 0; i < GENE_NUM; i++ )
    {
        if( CHECK_RATE(MUTATE_RATE) )
        {
            individual->weights[i] += SYMMETRY_RAND( 0.3f ) ;
            individual->weights[i] = (individual->weights[i] < -2.0) ? -2.0 : individual->weights[i];
            individual->weights[i] = (individual->weights[i] > 2.0 ) ?  2.0 : individual->weights[i];
        }
    }
}

individual_data get_best_weights( feature_data* features )
{
    individual_data population[ MAX_POPULATION ];
    individual_data new_population[ MAX_POPULATION ];
    
    initialize_population( population );
    individual_data current_best = population[0];
    individual_data total_best = population[0];
    for( int generation = 0; generation < MAX_GENERATION; generation++)
    {
        current_best = population[0];
        for( int i = 0; i < MAX_POPULATION; i++)
        {
            population[i].fitness = calculate_fitness( &population[i], features );
            if( population[i].fitness > current_best.fitness)
                current_best = population[i];
        }
        
        for (int i = 0; i < MAX_POPULATION; i++)
        {
            individual_data p1 = roulette_selection( population );
            individual_data p2 = roulette_selection( population );
            
            crossover( &p1, &p2, &new_population[i] );
            mutate( &new_population[i] );
        }
        
        population[0] = current_best;
        for (int i = 1; i < MAX_POPULATION; i++)
            population[i] = new_population[i];

        if( total_best.fitness < current_best.fitness)
            total_best = current_best ;
    }

    return total_best;
}

void save_gene_result( const stock_data* stock )
{
    srand(time(NULL));

    feature_data* features = (feature_data*)safe_malloc( TRAIN_DAYS * sizeof(feature_data) );
    initialize_feature( stock, features );

    individual_data best = get_best_weights( features );
    feature_data last = features[TRAIN_DAYS-1];
    free( features );
    
    float probability = predict( &best, &last );
    last.trend = ( probability > 0.5 ) ? 1 : 0;

    FILE* fp = open_file( stock->code, ".gene", "wb" );
    SAFE_WRITE( &best, sizeof(individual_data), 1, fp );
    SAFE_WRITE( &last, sizeof(feature_data), 1, fp );
    SAFE_WRITE( &probability, sizeof(float), 1, fp );
    close_file( fp, stock->code, ".gene" );

    return 0;
}

float predict( const individual_data* individual, const feature_data* feature)
{
    float score = 0.0f;
    score += feature->ma     * individual->weights[0];
    score += feature->expma  * individual->weights[1];
    score += feature->xuechi * individual->weights[2];
    score += feature->kdj    * individual->weights[3];
    score += feature->macd   * individual->weights[4];
    return SIGMOID(score);
}




/* TRAIN_DAYS is multiple of BLOCK_SIZE */
void initialize_feature( const stock_data* stock, feature_data* feature )
{
    FILE* mafp = open_file( stock->code, ".ma", "rb" );

    int block_bytes = BLOCK_SIZE * sizeof(float);
    int block_num = TRAIN_DAYS / BLOCK_SIZE;

    int ma5_start = (stock->days - TRAIN_DAYS)* sizeof(float);
    int ma10_start = stock->days*sizeof(float) + (stock->days - TRAIN_DAYS)* sizeof(float);

    float* ma5_buffer  = (float*)safe_malloc( block_bytes + sizeof(float) );
    float* ma10_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    for( int i = 0; i < block_num; i++)
    {
        fseek( mafp, ma5_start  + i * block_bytes, SEEK_SET );
        fseek( mafp, -sizeof(float), SEEK_CUR );
        SAFE_READ( ma5_buffer , sizeof(float), BLOCK_SIZE+1, mafp );
        fseek( mafp, ma10_start + i * block_bytes, SEEK_SET );
        fseek( mafp, -sizeof(float), SEEK_CUR );
        SAFE_READ( ma10_buffer, sizeof(float), BLOCK_SIZE+1, mafp );

        for( int j = 0; j < BLOCK_SIZE; j++)
        {
            if( ma5_buffer[j+1] > ma10_buffer[j+1] && ma5_buffer[j] <= ma10_buffer[j] )
                feature[i*BLOCK_SIZE+j].ma = UP;
            else if( ma5_buffer[j+1] < ma10_buffer[j+1] && ma5_buffer[j] >= ma10_buffer[j] )
                feature[i*BLOCK_SIZE+j].ma = DOWN;
            else
                feature[i*BLOCK_SIZE+j].ma = NA;
        }
    }

    free( ma5_buffer );
    free( ma10_buffer );
    close_file( mafp, stock->code, ".ma" );

    FILE* expmafp = open_file( stock->code, ".expma", "rb" );

    int expma12_start = ma5_start;
    int expma50_start = ma10_start;

    float* expma12_buffer  = (float*)safe_malloc( block_bytes + sizeof(float) );
    float* expma50_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    for( int i = 0; i < block_num; i++)
    {
        fseek( expmafp, expma12_start  + i * block_bytes, SEEK_SET );
        fseek( expmafp, -sizeof(float), SEEK_CUR );
        SAFE_READ( expma12_buffer , sizeof(float), BLOCK_SIZE+1, expmafp );
        fseek( expmafp, expma50_start + i * block_bytes, SEEK_SET );
        fseek( expmafp, -sizeof(float), SEEK_CUR );
        SAFE_READ( expma50_buffer, sizeof(float), BLOCK_SIZE+1, expmafp );

        for( int j = 0; j < BLOCK_SIZE; j++)
        {
            if( expma12_buffer[j+1] > expma50_buffer[j+1] && expma12_buffer[j] <= expma50_buffer[j] )
                feature[i*BLOCK_SIZE+j].expma = UP;
            else if( expma12_buffer[j+1] < expma50_buffer[j+1] && expma12_buffer[j] >= expma50_buffer[j] )
                feature[i*BLOCK_SIZE+j].expma = DOWN;
            else
                feature[i*BLOCK_SIZE+j].expma = NA;
        }
    }

    free( expma12_buffer );
    free( expma50_buffer );
    close_file( expmafp, stock->code, ".expma" );

    FILE* xuechifp = open_file( stock->code, ".xuechi", "rb" );
    FILE* closefp = open_file( stock->code, ".pred", "rb" );

    int up_start = ma5_start;
    int down_start = ma10_start;
    int close_start = ma5_start;

    float* up_buffer    = (float*)safe_malloc( block_bytes );
    float* down_buffer  = (float*)safe_malloc( block_bytes );
    float* close_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    for( int i = 0; i < block_num; i++)
    {
        fseek( xuechifp, up_start  + i * block_bytes, SEEK_SET );
        SAFE_READ( up_buffer, sizeof(float), BLOCK_SIZE, xuechifp );
        fseek( xuechifp, down_start  + i * block_bytes, SEEK_SET );
        SAFE_READ( down_buffer, sizeof(float), BLOCK_SIZE, xuechifp );

        fseek( closefp, close_start  + i * block_bytes, SEEK_SET );
        SAFE_READ( close_buffer, sizeof(float), BLOCK_SIZE+1, closefp );
        
        for( int j = 0; j < BLOCK_SIZE; j++)
        {
            if( close_buffer[j] >= up_buffer[j] )
                feature[i*BLOCK_SIZE+j].xuechi = DOWN;
            else if( close_buffer[j] <= down_buffer[j] )
                feature[i*BLOCK_SIZE+j].xuechi = UP;
            else
                feature[i*BLOCK_SIZE+j].xuechi = NA;

            if( close_buffer[j+1] >= close_buffer[j] )
                feature[i*BLOCK_SIZE+j].trend = UP;
            else if( close_buffer[j+1] < close_buffer[j] )
                feature[i*BLOCK_SIZE+j].trend = DOWN;
        }
    }
    free( up_buffer );
    free( down_buffer );
    free( close_buffer );
    close_file( xuechifp, stock->code, ".xuechi" );
    close_file( closefp, stock->code, ".pred" );


    FILE* kdjfp = open_file( stock->code, ".kdj", "rb" );

    int k_start = ma5_start;
    int j_start = stock->days*sizeof(float)*2 + (stock->days - TRAIN_DAYS)*sizeof(float);

    float* k_buffer = (float*)safe_malloc( block_bytes );
    float* j_buffer = (float*)safe_malloc( block_bytes );

    for( int i = 0; i < block_num; i++)
    {
        fseek( kdjfp, k_start  + i * block_bytes, SEEK_SET );
        SAFE_READ( k_buffer, sizeof(float), BLOCK_SIZE, kdjfp );
        fseek( kdjfp, j_start  + i * block_bytes, SEEK_SET );
        SAFE_READ( j_buffer, sizeof(float), BLOCK_SIZE, kdjfp );

        for( int j = 0; j < BLOCK_SIZE; j++)
        {
            if( k_buffer[j] > 80 || j_buffer[j] > 100 )
                feature[i*BLOCK_SIZE+j].kdj = UP;
            else if( k_buffer[j] < 20 && j_buffer[j] < 0 )
                feature[i*BLOCK_SIZE+j].kdj = DOWN;
            else
                feature[i*BLOCK_SIZE+j].kdj = NA;
        }
    }
    free( k_buffer );
    free( j_buffer );
    close_file( kdjfp, stock->code, ".kdj" );

    FILE* macdfp = open_file( stock->code, ".macd", "rb" );

    int macd_start = j_start;

    float* macd_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    for( int i = 0; i < block_num; i++)
    {
        fseek( macdfp, macd_start  + i * block_bytes, SEEK_SET );
        fseek( macdfp, -sizeof(float), SEEK_CUR );
        SAFE_READ( macd_buffer, sizeof(float), BLOCK_SIZE+1, macdfp );

        for( int j = 0; j < BLOCK_SIZE; j++)
        {
            if( macd_buffer[j+1] > 0 && macd_buffer[j] <= 0 )
                feature[i*BLOCK_SIZE+j].macd = UP;
            else if( macd_buffer[j+1] < 0 && macd_buffer[j] >= 0 )
                feature[i*BLOCK_SIZE+j].macd = DOWN;
            else
                feature[i*BLOCK_SIZE+j].macd = NA;
        }
    }
    free( macd_buffer );
    close_file( macdfp, stock->code, ".macd" );

}