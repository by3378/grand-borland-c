#include "global.h"

void write_axis_number(const most_value* most, axis_data* axis)
{
    int gap = most->max - most->min;
    float unit_gap; /* gap between two marks */
    float marks[] = { 0.1f, 0.5f, 1, 2, 5, 10, 20, 50, 100 };
    int mark_num = sizeof(marks) / sizeof(marks[0]);
    int i;
    int unit_length;
    char buffer[6]; /* contain 000.1-999.9 */
    int mark_y;
    float mark_value;

    for (i = 0; i < mark_num; i++)
    {
        if (gap > axis->unit_num * marks[i])
            continue;

        unit_gap = marks[i];
        axis->max = (int)ceil(most->max / marks[i]) * marks[i];
        axis->min = (int)floor(most->min / marks[i]) * marks[i];
        break;
    }

    unit_length = axis->length / axis->unit_num;

    for (i = 0; i < axis->unit_num + 1; i++)
    {
        mark_y = axis->y + unit_length * i;
        mark_value = axis->max - i * unit_gap;

        sprintf(buffer, "%.1f", mark_value);
        outtextxy(axis->x + 5, mark_y, buffer);
    }
}

void choose_rectangle(rectangle_info* rectangle, enum gear_type gear)
{
    switch (gear)
    {
        case SMALL:
        {
            rectangle->width = 3;
            rectangle->gap = 7;
            rectangle->num = 84;
            break;
        }
        case MEDIUM:
        {
            rectangle->width = 5;
            rectangle->gap = 14;
            rectangle->num = 42;
            break;
        }
        case LARGE:
        {
            rectangle->width = 10;
            rectangle->gap = 27;
            rectangle->num = 21;
            break;
        }
    }
}

void get_most(const stock_data* stock, enum line_type type, int num, most_value* most)
{
    int line_num;
    bool ismain;
    FILE* fp;
    most_value* buffer;
    int i;

    assert(num * stock->period_length <= stock->days);

    ismain = tell_line(type, &line_num);
    fp = open_file(stock->code, type, "rb");

    most->max = -FLT_MAX;
    most->min = FLT_MAX;

    buffer = (most_value*)safe_malloc(num * sizeof(most_value));
    fseek(fp, -sizeof(most_value) * num, SEEK_END);
    SAFE_READ(buffer, sizeof(most_value), num, fp);
    close_file(fp, stock->code, ".who cares");

    for (i = 0; i < num; i++)
    {
        most->max = buffer[i].max > most->max ? buffer[i].max : most->max;
        most->min = buffer[i].min < most->min ? buffer[i].min : most->min;
    }
    free(buffer);

    if (ismain)
    {
        most_value most2;
        get_most(stock, KDAY, num, &most2);
        most->max = most2.max > most->max ? most2.max : most->max;
        most->min = most2.min < most->min ? most2.min : most->min;
    }
}

void draw_line(const stock_data* stock, const rectangle_info* rectangle, enum line_type type, const axis_data* axis)
{
    most_value most;
    int line_num;
    bool ismain;
    FILE* fp;

    get_most(stock, type, rectangle->num / stock->period_length, &most);
    write_axis_number(&most, axis);

    ismain = tell_line(type, &line_num);
    fp = open_file(stock->code, type);

    if (type == KDAY || type == KWEEK)
        draw_kline(fp, type, stock, rectangle, axis);
    else if (type == MACD)
        draw_macd(fp, stock, rectangle, axis);
    else if (!ismain)
        draw_simple_line(fp, line_num, stock, rectangle, axis);
    else if (ismain)
    {
        draw_simple_line(fp, line_num, stock, rectangle, axis);
        draw_kline(fp, KDAY, stock, rectangle, axis);
    }

    close_file(fp, stock->code, ".whatever");
}

void draw_kline(FILE* fp, enum line_type type, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis)
{
    day_price info;
    enum COLORS color;
    int high_y, low_y, open_y, close_y;
    int present_x;
    int half_width;
    int i;

    if (type == KDAY)
        fseek(fp, sizeof(day_price) * stock->days, SEEK_SET);
    else
        fseek(fp, sizeof(week_data) * stock->weeks, SEEK_SET);

    fseek(fp, -sizeof(day_price) * rectangle->num, SEEK_CUR);

    present_x = axis->x - rectangle->gap * rectangle->num;
    half_width = ROUND(rectangle->width / 2);

    assert(present_x >= 0);

    for (i = 0; i < rectangle->num; i++, present_x += rectangle->gap)
    {
        SAFE_READ(&info, sizeof(day_price), 1, fp);

        if (info.close > info.open)
            color = RED;
        else
            color = GREEN;
        setcolor(color);
        setfillpattern(SOLID_FILL, color);

        high_y = CALCULATE_Y(axis, info.high);
        low_y = CALCULATE_Y(axis, info.low);
        open_y = CALCULATE_Y(axis, info.open);
        close_y = CALCULATE_Y(axis, info.close);

        line(present_x, high_y, present_x, low_y);
        bar(present_x - half_width, open_y, present_x + half_width, close_y);
    }

    close_file(fp, stock->code, ".kday or .kweek");
}

void draw_simple_line(FILE* fp, int line_num, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis)
{
    int p;
    for (p = 0; p < line_num; p++)
    {
        float* buffer = (float*)safe_calloc(rectangle->num, sizeof(float));
        int* xy_buffer;

        fseek(fp, sizeof(float) * stock->days * p, SEEK_SET);
        fseek(fp, -sizeof(float) * rectangle->num, SEEK_CUR);
        SAFE_READ(buffer, sizeof(float), rectangle->num, fp);

        xy_buffer = (int*)safe_malloc(rectangle->num * 2 * sizeof(int));
        calculate_xy(buffer, xy_buffer, rectangle, axis);

        drawpoly(rectangle->num, xy_buffer);
        free(buffer);
        free(xy_buffer);
    }
}

void calculate_xy(float* buffer, int* xy_buffer, const rectangle_info* rectangle, const axis_data* axis)
{
    int present_x;
    int i;

    present_x = axis->x - rectangle->gap * rectangle->num;

    assert(present_x >= 0);

    for (i = 0; i < rectangle->num; i++, present_x += rectangle->gap)
    {
        xy_buffer[i * 2] = present_x;
        xy_buffer[i * 2 + 1] = CALCULATE_Y(axis, buffer[i]);
    }
}

void draw_macd(FILE* fp, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis)
{
    float* buffer;
    int* xy_buffer;
    int zero_y;
    enum COLORS color;
    int i;

    draw_simple_line(fp, 2, stock, rectangle, axis);

    buffer = (float*)safe_calloc(rectangle->num, sizeof(float));
    fseek(fp, sizeof(float) * stock->days * 3, SEEK_SET);
    fseek(fp, -sizeof(float) * rectangle->num, SEEK_CUR);
    SAFE_READ(buffer, sizeof(float), rectangle->num, fp);

    xy_buffer = (int*)safe_malloc(rectangle->num * 2 * sizeof(int));
    calculate_xy(buffer, xy_buffer, rectangle, axis);
    free(buffer);

    zero_y = CALCULATE_Y(axis, 0);
    for (i = 0; i < rectangle->num; i++)
    {
        if (xy_buffer[i * 2 + 1] > 0)
            color = RED;
        else
            color = GREEN;
        setcolor(color);

        line(xy_buffer[i * 2], zero_y, xy_buffer[i * 2], xy_buffer[i * 2 + 1]);
    }
    free(xy_buffer);
}


//填充预测界面左侧的数据
void draw_gene_pred(const char* code)
{
    char pro[2], str[5][5];
    float probability;
    FILE* fp = open_file( code, GENE, "rb");
    individual_data best;
    feature_data last;
    SAFE_READ(&best, sizeof(individual_data), 1, fp);
    SAFE_READ(&last, sizeof(feature_data), 1, fp);
    SAFE_READ(&probability, sizeof(float), 1, fp);
    close_file(fp, stock->code, ".gene");

    //将数字转化为可以输出的字符串
    sprintf(pro, "%d", probability * 100);
    sprintf(str[0], "%.2f", last.MA_cross);
    sprintf(str[1], "%.2f", last.EXPMA_cross);
    sprintf(str[2], "%.2f", last.XS_channel);
    sprintf(str[3], "%.2f", last.KDJ_status);
    sprintf(str[4], "%.2f", last.MACD_change);

    //打印左侧表格数据
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(115 - 3, 200, str[0]);
    outtextxy(115 - 3, 220, str[1]);
    outtextxy(115 - 3, 245, str[2]);
    outtextxy(115 - 3, 265, str[3]);
    outtextxy(115 - 3, 287, str[4]);

    //打印上涨或下跌概率
    setcolor(LIGHTCYAN);
    outtextxy(110, 350, ":");
    settextstyle(SMALL_FONT, HORIZ_DIR, 8);
    outtextxy(120, 347, pro);//概率值坐标(120，347)字体为8号
    outtextxy(150, 348, "%");
    if (probability > 0.5) {
        puthz(10, 350, "上涨概率", 24, 24, LIGHTCYAN);
    }
    else {
        puthz(10, 350, "下跌概率", 24, 24, LIGHTCYAN);
    }
}
void draw_ar_pred(const char* code, rectangle_info* rectangle, axis_data* axis)
{
    FILE* predfp;
    int real_days = 3;
    float* pred_buffer;
    most_value most;
    float* xy_buffer;

    predfp = open_file(code, PRED, "rb");

    fseek(predfp, -sizeof(float) * (FORECAST_DAYS + real_days) + sizeof(most_value), SEEK_END);

    pred_buffer = (float*)safe_calloc(FORECAST_DAYS + real_days, sizeof(float));
    SAFE_READ(pred_buffer, sizeof(float), FORECAST_DAYS + real_days, predfp);

    most.max = -FLT_MAX;
    most.min = FLT_MAX;
    {
        int i;
        for (i = 0; i < real_days + FORECAST_DAYS; i++)
        {
            most.max = most.max > pred_buffer[i] ? most.max : pred_buffer[i];
            most.min = most.min < pred_buffer[i] ? most.min : pred_buffer[i];
        }
    }
    write_axis_number(&most, axis);

    close_file(predfp, code, ".pred");

    xy_buffer = (float*)safe_malloc(sizeof(int) * 2 * (FORECAST_DAYS + real_days));
    calculate_xy(pred_buffer, xy_buffer, rectangle, axis);

    setlinestyle(SOLID_LINE, 0, 1);
    drawpoly(real_days, xy_buffer);
    setlinestyle(DOTTED_LINE, 0, 1);
    drawpoly(FORECAST_DAYS, xy_buffer + real_days * 2);

    free(pred_buffer);
    free(xy_buffer);
}

