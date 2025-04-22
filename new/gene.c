#include "global.h"

void initialize_population(individual_data* population)
{
    int i, j;
    for (i = 0; i < MAX_POPULATION; i++)
        for (j = 0; j < GENE_NUM; j++)
            population[i].weights[j] = SYMMETRY_RAND(2.0f);
}

float calculate_fitness(const individual_data* individual, const feature_data* features)
{
    int correct = 0, i;
    for (i = 0; i < TRAIN_DAYS; i++)
    {
        int result = predict(individual, &features[i]);
        int predict_trend = (result > 0.5) ? 1 : 0;
        if (predict_trend == features[i].trend)
            correct++;
    }
    return (float)correct / TRAIN_DAYS;
}

float predict(const individual_data* individual, const feature_data* feature)
{
    float score = 0.0f;
    score += feature->ma * individual->weights[0];
    score += feature->expma * individual->weights[1];
    score += feature->xuechi * individual->weights[2];
    score += feature->kdj * individual->weights[3];
    score += feature->macd * individual->weights[4];
    return SIGMOID(score);
}

individual_data roulette_selection(const individual_data* population)
{
    float total = 0.0f, threshold, sum = 0.0f;
    int i;
    for (i = 0; i < MAX_POPULATION; i++)
        total += population[i].fitness;
    threshold = (float)rand() / RAND_MAX * total;

    for (i = 0; i < MAX_POPULATION; i++)
    {
        sum += population[i].fitness;
        if (sum >= threshold)
            return population[i];
    }
}

void crossover(const individual_data* p1, const individual_data* p2, individual_data* child)
{
    int point, i;
    if (CHECK_RATE(CROSS_RATE))
    {
        point = rand() % GENE_NUM;
        for (i = 0; i < point; i++)
            child->weights[i] = p1->weights[i];
        for (i = point; i < GENE_NUM; i++)
            child->weights[i] = p2->weights[i];
    }
    else
        *child = *p1;
}

void mutate(individual_data* individual)
{
    int i;
    for (i = 0; i < GENE_NUM; i++)
    {
        if (CHECK_RATE(MUTATE_RATE))
        {
            individual->weights[i] += SYMMETRY_RAND(0.3f);
            individual->weights[i] = (individual->weights[i] < -2.0) ? -2.0 : individual->weights[i];
            individual->weights[i] = (individual->weights[i] > 2.0) ? 2.0 : individual->weights[i];
        }
    }
}

individual_data get_best_weights(feature_data* features)
{
    individual_data population[MAX_POPULATION];
    individual_data new_population[MAX_POPULATION];
    individual_data current_best, total_best;
    int generation, i;

    initialize_population(population);
    current_best = population[0];
    total_best = population[0];
    total_best.fitness = -FLT_MAX;

    for (generation = 0; generation < MAX_GENERATION; generation++)
    {
        current_best = population[0];
        for (i = 0; i < MAX_POPULATION; i++)
        {
            population[i].fitness = calculate_fitness(&population[i], features);
            if (population[i].fitness > current_best.fitness)
                current_best = population[i];
        }

        for (i = 0; i < MAX_POPULATION; i++)
        {
            individual_data p1 = roulette_selection(population);
            individual_data p2 = roulette_selection(population);

            crossover(&p1, &p2, &new_population[i]);
            mutate(&new_population[i]);
        }

        population[0] = current_best;
        for (i = 1; i < MAX_POPULATION; i++)
            population[i] = new_population[i];

        if (total_best.fitness < current_best.fitness)
            total_best = current_best;
    }

    return total_best;
}

void save_gene_result(const stock_data* stock)
{
    feature_data* features;
    individual_data best;
    feature_data last;
    float probability;
    FILE* fp;

    srand(time(NULL));
    assert(TRAIN_DAYS % BLOCK_SIZE == 0);
    features = (feature_data*)safe_malloc(TRAIN_DAYS * sizeof(feature_data));
    initialize_feature(stock, features);

    best = get_best_weights(features);
    last = features[TRAIN_DAYS - 1];
    free(features);

    probability = predict(&best, &last);
    fp = open_file(stock->code, GENE, "wb");
    SAFE_WRITE(&best, sizeof(individual_data), 1, fp);
    SAFE_WRITE(&last, sizeof(feature_data), 1, fp);
    SAFE_WRITE(&probability, sizeof(float), 1, fp);
    close_file(fp, stock->code, ".gene");

#if defined(DEBUG)
    printf("\ngene result:\n");
    printf("weights: MA_cross: %.2f, EXPMA_cross: %.2f, XS_channel: %.2f, KDJ_status: %.2f, MACD_change: %.2f\n",
           best.weights[0], best.weights[1], best.weights[2], best.weights[3], best.weights[4]);
    printf("last day: trend: %d, MA_cross: %d, EXPMA_cross: %d, XS_channel: %d, KDJ_status: %d, MACD_change: %d\n",
           last.trend, last.ma, last.expma, last.xuechi, last.kdj, last.macd);
    printf("probability: %.2f%% \n", probability * 100);
#endif
}

void initialize_feature(const stock_data* stock, feature_data* feature)
{
    ma_cross(stock, feature);
    expma_cross(stock, feature);
    xuechi_break_close(stock, feature);
    kdj_status(stock, feature);
    macd_change(stock, feature);
}

void macd_change(const stock_data* stock, feature_data* feature)
{
    FILE* macdfp;
    int block_bytes, block_num, macd_start, i, j;
    float* macd_buffer;

    macdfp = open_file(stock->code, MACD, "rb");
    block_bytes = BLOCK_SIZE * sizeof(float);
    block_num = TRAIN_DAYS / BLOCK_SIZE;
    macd_start = 3 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);
    macd_buffer = (float*)safe_malloc(block_bytes + sizeof(float));

#if defined(DEBUG)
    printf("\nmacd change:\n");
#endif

    for (i = 0; i < block_num; i++)
    {
        fseek(macdfp, macd_start + i * block_bytes, SEEK_SET);
        fseek(macdfp, -sizeof(float), SEEK_CUR);
        SAFE_READ(macd_buffer, sizeof(float), BLOCK_SIZE + 1, macdfp);

        for (j = 0; j < BLOCK_SIZE; j++)
        {
            if (macd_buffer[j + 1] > 0 && macd_buffer[j] <= 0)
                feature[i * BLOCK_SIZE + j].macd = UP;
            else if (macd_buffer[j + 1] < 0 && macd_buffer[j] >= 0)
                feature[i * BLOCK_SIZE + j].macd = DOWN;
            else
                feature[i * BLOCK_SIZE + j].macd = NONE;

#if defined(DEBUG)
            printf("%d ", feature[i * BLOCK_SIZE + j].macd);
#endif
        }
    }
    free(macd_buffer);
    close_file(macdfp, stock->code, ".macd");
}
void ma_cross(const stock_data* stock, feature_data* feature)
{
    FILE* mafp;
    int block_bytes, block_num, ma5_start, ma10_start, i, j;
    float* ma5_buffer;
    float* ma10_buffer;

    mafp = open_file(stock->code, MA, "rb");
    block_bytes = BLOCK_SIZE * sizeof(float);
    block_num = TRAIN_DAYS / BLOCK_SIZE;
    ma5_start = (stock->days - TRAIN_DAYS) * sizeof(float);
    ma10_start = 2 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

    ma5_buffer = (float*)safe_malloc(block_bytes + sizeof(float));
    ma10_buffer = (float*)safe_malloc(block_bytes + sizeof(float));

#if defined(DEBUG)
    printf("\nma cross:\n");
#endif

    for (i = 0; i < block_num; i++)
    {
        fseek(mafp, ma5_start + i * block_bytes, SEEK_SET);
        fseek(mafp, -sizeof(float), SEEK_CUR);
        SAFE_READ(ma5_buffer, sizeof(float), BLOCK_SIZE + 1, mafp);
        fseek(mafp, ma10_start + i * block_bytes, SEEK_SET);
        fseek(mafp, -sizeof(float), SEEK_CUR);
        SAFE_READ(ma10_buffer, sizeof(float), BLOCK_SIZE + 1, mafp);

        for (j = 0; j < BLOCK_SIZE; j++)
        {
            if (ma5_buffer[j + 1] > ma10_buffer[j + 1] && ma5_buffer[j] <= ma10_buffer[j])
                feature[i * BLOCK_SIZE + j].ma = UP;
            else if (ma5_buffer[j + 1] < ma10_buffer[j + 1] && ma5_buffer[j] >= ma10_buffer[j])
                feature[i * BLOCK_SIZE + j].ma = DOWN;
            else
                feature[i * BLOCK_SIZE + j].ma = NONE;

#if defined(DEBUG)
            printf("%d ", feature[i * BLOCK_SIZE + j].ma);
#endif
        }
    }

    free(ma5_buffer);
    free(ma10_buffer);
    close_file(mafp, stock->code, ".ma");
}

void expma_cross(const stock_data* stock, feature_data* feature)
{
    FILE* expmafp;
    int block_bytes, block_num, expma12_start, expma50_start, i, j;
    float* expma12_buffer;
    float* expma50_buffer;

    expmafp = open_file(stock->code, EXPMA, "rb");
    block_bytes = BLOCK_SIZE * sizeof(float);
    block_num = TRAIN_DAYS / BLOCK_SIZE;
    expma12_start = (stock->days - TRAIN_DAYS) * sizeof(float);
    expma50_start = 2 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

    expma12_buffer = (float*)safe_malloc(block_bytes + sizeof(float));
    expma50_buffer = (float*)safe_malloc(block_bytes + sizeof(float));

#if defined(DEBUG)
    printf("\nexpma cross:\n");
#endif

    for (i = 0; i < block_num; i++)
    {
        fseek(expmafp, expma12_start + i * block_bytes, SEEK_SET);
        fseek(expmafp, -sizeof(float), SEEK_CUR);
        SAFE_READ(expma12_buffer, sizeof(float), BLOCK_SIZE + 1, expmafp);
        fseek(expmafp, expma50_start + i * block_bytes, SEEK_SET);
        fseek(expmafp, -sizeof(float), SEEK_CUR);
        SAFE_READ(expma50_buffer, sizeof(float), BLOCK_SIZE + 1, expmafp);

        for (j = 0; j < BLOCK_SIZE; j++)
        {
            if (expma12_buffer[j + 1] > expma50_buffer[j + 1] && expma12_buffer[j] <= expma50_buffer[j])
                feature[i * BLOCK_SIZE + j].expma = UP;
            else if (expma12_buffer[j + 1] < expma50_buffer[j + 1] && expma12_buffer[j] >= expma50_buffer[j])
                feature[i * BLOCK_SIZE + j].expma = DOWN;
            else
                feature[i * BLOCK_SIZE + j].expma = NONE;

#if defined(DEBUG)
            printf("%d ", feature[i * BLOCK_SIZE + j].expma);
#endif
        }
    }

    free(expma12_buffer);
    free(expma50_buffer);
    close_file(expmafp, stock->code, ".expma");
}

void xuechi_break_close(const stock_data* stock, feature_data* feature)
{
    FILE* xuechifp;
    FILE* closefp;
    int block_bytes, block_num, up_start, down_start, close_start, i, j;
    float* up_buffer;
    float* down_buffer;
    float* close_buffer;

    xuechifp = open_file(stock->code, XUECHI, "rb");
    closefp = open_file(stock->code, PRED, "rb");
    block_bytes = BLOCK_SIZE * sizeof(float);
    block_num = TRAIN_DAYS / BLOCK_SIZE;
    up_start = (stock->days - TRAIN_DAYS) * sizeof(float);
    down_start = 2 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);
    close_start = up_start;

    up_buffer = (float*)safe_malloc(block_bytes);
    down_buffer = (float*)safe_malloc(block_bytes);
    close_buffer = (float*)safe_malloc(block_bytes + sizeof(float));

#if defined(DEBUG)
    printf("\nxue chi break:\n");
    printf("close trend:\n");
#endif

    for (i = 0; i < block_num; i++)
    {
        fseek(xuechifp, up_start + i * block_bytes, SEEK_SET);
        SAFE_READ(up_buffer, sizeof(float), BLOCK_SIZE, xuechifp);
        fseek(xuechifp, down_start + i * block_bytes, SEEK_SET);
        SAFE_READ(down_buffer, sizeof(float), BLOCK_SIZE, xuechifp);
        fseek(closefp, close_start + i * block_bytes, SEEK_SET);
        SAFE_READ(close_buffer, sizeof(float), BLOCK_SIZE + 1, closefp);

        for (j = 0; j < BLOCK_SIZE; j++)
        {
            if (close_buffer[j] >= up_buffer[j])
                feature[i * BLOCK_SIZE + j].xuechi = DOWN;
            else if (close_buffer[j] <= down_buffer[j])
                feature[i * BLOCK_SIZE + j].xuechi = UP;
            else
                feature[i * BLOCK_SIZE + j].xuechi = NONE;

            if (close_buffer[j + 1] >= close_buffer[j])
                feature[i * BLOCK_SIZE + j].trend = UP;
            else
                feature[i * BLOCK_SIZE + j].trend = DOWN;

#if defined(DEBUG)
            printf("%d %d\n", feature[i * BLOCK_SIZE + j].xuechi, feature[i * BLOCK_SIZE + j].trend);
#endif
        }
    }

    free(up_buffer);
    free(down_buffer);
    free(close_buffer);
    close_file(xuechifp, stock->code, ".xuechi");
    close_file(closefp, stock->code, ".pred");
}

void kdj_status(const stock_data* stock, feature_data* feature)
{
    FILE* kdjfp;
    int block_bytes, block_num, k_start, j_start, i, j;
    float* k_buffer;
    float* j_buffer;

    kdjfp = open_file(stock->code, KDJ, "rb");
    block_bytes = BLOCK_SIZE * sizeof(float);
    block_num = TRAIN_DAYS / BLOCK_SIZE;
    k_start = (stock->days - TRAIN_DAYS) * sizeof(float);
    j_start = 3 * stock->days * sizeof(float) - TRAIN_DAYS * sizeof(float);

    k_buffer = (float*)safe_malloc(block_bytes);
    j_buffer = (float*)safe_malloc(block_bytes);

    for (i = 0; i < block_num; i++)
    {
        fseek(kdjfp, k_start + i * block_bytes, SEEK_SET);
        SAFE_READ(k_buffer, sizeof(float), BLOCK_SIZE, kdjfp);
        fseek(kdjfp, j_start + i * block_bytes, SEEK_SET);
        SAFE_READ(j_buffer, sizeof(float), BLOCK_SIZE, kdjfp);

        for (j = 0; j < BLOCK_SIZE; j++)
        {
            if (k_buffer[j] > 80 || j_buffer[j] > 100)
                feature[i * BLOCK_SIZE + j].kdj = UP;
            else if (k_buffer[j] < 20 && j_buffer[j] < 0)
                feature[i * BLOCK_SIZE + j].kdj = DOWN;
            else
                feature[i * BLOCK_SIZE + j].kdj = NONE;
        }
    }

    free(k_buffer);
    free(j_buffer);
    close_file(kdjfp, stock->code, ".kdj");
}