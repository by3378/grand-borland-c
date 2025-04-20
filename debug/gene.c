#include "global.h"

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
            individual->weights[i] = (individual->weights[i] >  2.0) ?  2.0 : individual->weights[i];
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
    total_best.fitness = -FLT_MAX;
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
    assert(TRAIN_DAYS % BLOCK_SIZE == 0);
    feature_data* features = (feature_data*)safe_malloc( TRAIN_DAYS * sizeof(feature_data) );
    initialize_feature( stock, features );

    individual_data best = get_best_weights( features );
    feature_data last = features[TRAIN_DAYS-1];
    free( features );
    
    float probability = predict( &best, &last );
    FILE* fp = open_file( stock->code, GENE, "wb" );
    SAFE_WRITE( &best, sizeof(individual_data), 1, fp );
    SAFE_WRITE( &last, sizeof(feature_data), 1, fp );
    SAFE_WRITE( &probability, sizeof(float), 1, fp );
    close_file( fp, stock->code, ".gene" );

    #if defined(DEBUG)
        printf( "\ngene result:\n" );
        printf( "weights: MA_cross: %.2f, EXPMA_cross: %.2f, XS_channel: %.2f, KDJ_status: %.2f, MACD_change: %.2f\n"
            , best.weights[0], best.weights[1], best.weights[2], best.weights[3], best.weights[4] );
        printf( "last day: trend: %d, MA_cross: %d, EXPMA_cross: %d, XS_channel: %d, KDJ_status: %d, MACD_change: %d\n"
            , last.trend, last.ma, last.expma, last.xuechi, last.kdj, last.macd );
        printf( "probability: %.2f%% \n",  probability * 100 );
    #endif

}


/* TRAIN_DAYS is multiple of BLOCK_SIZE */
void initialize_feature( const stock_data* stock, feature_data* feature )
{
    ma_cross( stock, feature );
    expma_cross( stock, feature );
    xuechi_break_close( stock, feature );
    kdj_status( stock, feature );
    macd_change( stock, feature );
}
void macd_change( const stock_data* stock, feature_data* feature )
{

    FILE* macdfp = open_file( stock->code, MACD, "rb" );

    int block_bytes = BLOCK_SIZE * sizeof(float);
    int block_num = TRAIN_DAYS / BLOCK_SIZE;
    int macd_start = 3 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

    float* macd_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    #if defined(DEBUG)
        printf( "\nmacd change:\n");
    #endif

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
                feature[i*BLOCK_SIZE+j].macd = NONE;

            #if defined(DEBUG)
                printf( "%d ", feature[i*BLOCK_SIZE+j].macd );
            #endif
        }
    }
    free( macd_buffer );
    close_file( macdfp, stock->code, ".macd" );

}

void ma_cross( const stock_data* stock, feature_data* feature )
{
    FILE* mafp = open_file( stock->code, MA, "rb" );

    int block_bytes = BLOCK_SIZE * sizeof(float);
    int block_num = TRAIN_DAYS / BLOCK_SIZE; /* ATTENTIOIN : TRAIN_DAYS is multiple of BLOCK_SIZE */

    int ma5_start = (stock->days - TRAIN_DAYS)* sizeof(float);
    int ma10_start = 2 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

    float* ma5_buffer  = (float* )safe_malloc( block_bytes + sizeof(float) );
    float* ma10_buffer = (float* )safe_malloc( block_bytes + sizeof(float) );

    #if defined(DEBUG)
        printf( "\nma cross:\n");
    #endif

    for( int i = 0; i < block_num; i++)
    {
        /* read 1+BLOCK_SIZE days */
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
                feature[i*BLOCK_SIZE+j].ma = NONE;

            #if defined(DEBUG)
                printf( "%d ", feature[i*BLOCK_SIZE+j].ma );
            #endif
        }
    }

    free( ma5_buffer );
    free( ma10_buffer );
    close_file( mafp, stock->code, ".ma" );
}

void expma_cross( const stock_data* stock, feature_data* feature )
{
    FILE* expmafp = open_file( stock->code, EXPMA, "rb" );

    int block_bytes = BLOCK_SIZE * sizeof(float);
    int block_num = TRAIN_DAYS / BLOCK_SIZE; 

    int expma12_start = (stock->days - TRAIN_DAYS)* sizeof(float);
    int expma50_start = 2 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

    float* expma12_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );
    float* expma50_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    #if defined(DEBUG)
        printf( "\nexpma cross:\n");
    #endif

    for( int i = 0; i < block_num; i++)
    {
        fseek( expmafp, expma12_start  + i * block_bytes, SEEK_SET );
        fseek( expmafp, -sizeof(float), SEEK_CUR );
        SAFE_READ( expma12_buffer , sizeof(float), BLOCK_SIZE+1, expmafp );
        fseek( expmafp, expma50_start + i * block_bytes, SEEK_SET );
        fseek( expmafp, -sizeof(float), SEEK_CUR );
        SAFE_READ( expma50_buffer , sizeof(float), BLOCK_SIZE+1, expmafp );

        for( int j = 0; j < BLOCK_SIZE; j++)
        {
            if( expma12_buffer[j+1] > expma50_buffer[j+1] && expma12_buffer[j] <= expma50_buffer[j] )
                feature[i*BLOCK_SIZE+j].expma = UP;
            else if( expma12_buffer[j+1] < expma50_buffer[j+1] && expma12_buffer[j] >= expma50_buffer[j] )
                feature[i*BLOCK_SIZE+j].expma = DOWN;
            else
                feature[i*BLOCK_SIZE+j].expma = NONE;

            #if defined(DEBUG)
                printf( "%d ", feature[i*BLOCK_SIZE+j].expma );
            #endif
        }
    }

    free( expma12_buffer );
    free( expma50_buffer );
    close_file( expmafp, stock->code, ".expma" );

}
void xuechi_break_close( const stock_data* stock, feature_data* feature )
{

    FILE* xuechifp = open_file( stock->code, XUECHI, "rb" );
    FILE* closefp = open_file( stock->code, PRED, "rb" );

    int block_bytes = BLOCK_SIZE * sizeof(float);
    int block_num = TRAIN_DAYS / BLOCK_SIZE; 

    int up_start = (stock->days - TRAIN_DAYS)* sizeof(float);
    int down_start = 2 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);
    int close_start = up_start;

    float* up_buffer    = (float*)safe_malloc( block_bytes );
    float* down_buffer  = (float*)safe_malloc( block_bytes );
    float* close_buffer = (float*)safe_malloc( block_bytes + sizeof(float) );

    #if defined(DEBUG)
        printf( "\nxue chi break:\n");
        printf( "close trend:\n");
    #endif

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
                feature[i*BLOCK_SIZE+j].xuechi = NONE;

            if( close_buffer[j+1] >= close_buffer[j] )
                feature[i*BLOCK_SIZE+j].trend = UP;
            else 
                feature[i*BLOCK_SIZE+j].trend = DOWN;

            #if defined(DEBUG)
                printf( "%d %d\n", feature[i*BLOCK_SIZE+j].xuechi , feature[i*BLOCK_SIZE+j].trend );
            #endif
        }
    }

    free( up_buffer );
    free( down_buffer );
    free( close_buffer );
    close_file( xuechifp, stock->code, ".xuechi" );
    close_file( closefp, stock->code, ".pred" );
}
void kdj_status( const stock_data* stock, feature_data* feature )
{
    
    FILE* kdjfp = open_file( stock->code, KDJ, "rb" );

    int block_bytes = BLOCK_SIZE * sizeof(float);
    int block_num = TRAIN_DAYS / BLOCK_SIZE; 

    int k_start = (stock->days - TRAIN_DAYS)* sizeof(float);
    int j_start = 3 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

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
                feature[i*BLOCK_SIZE+j].kdj = NONE;
        }
    }

    free( k_buffer );
    free( j_buffer );
    close_file( kdjfp, stock->code, ".kdj" );
}