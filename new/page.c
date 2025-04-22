#include "global.h"

int main(void) 
{
    float dummy = sin(0.0);
    load();

    {
        int gd = VGA;
        int gm = VGAHI;
        initgraph(&gd, &gm, "C:\\borlandc\\BGI");
        mouseinit();
    }

    {
        char pred_code[7];
        user_data user;
        stock_data stock;
        enum page pattern = WELCOME;
        while (1)
        {
            switch (pattern)
            {
                case WELCOME:
                    pattern = page_welcome(&user);
                    break;
                case REGISTER:
                    pattern = page_register(&user);
                    break;
                case INDICATOR:
                    pattern = page_indicator(&stock);
                    break;
                case STATUS:
                    pattern = page_status(&user, &stock);
                    break;
                case MARKET:
                    pattern = page_market(&user);
                    break;
                case SEARCH:
                    pattern = page_search( pred_code );
                    break;
                case PREDICT:
                    pattern = page_predict( pred_code);
                    break;
                case EXIT:
                    closegraph();
                    exit( EXIT_SUCCESS );
                    return 0;
            }
        }
    }
}

int page_welcome(user_data* user)
{
    int but;
    int name_check = 0, password_check = 0;

    clrmous(MouseX, MouseY);
    cleardevice();
    draw_welcome();

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if( buton_simple( 160, 230, 160 + 320, 230 + 32 ) )
        {
            get_input( 160 + 75, 230 + 12, user->name, 8, 3);
            name_check = true;
        }
        if( buton_simple( 160, 278, 160 + 320, 278 + 32 ) )
        {
            get_input(160 + 75, 278 + 12, user->password, 8, 3);
            password_check = true;
        }
        if( buton_simple(  160, 342, 480, 374 ) )
        {
            if (name_check && password_check)
            {
                if (check_info(user))
                {
                    puthz( 250, 432, "login success", 32, 32, LIGHTGREEN);
                    return STATUS;
                }
                else
                {
                    puthz( 150-8, 432, "longin fail", 32, 32, RED);
                    return WELCOME;
                }
            }
        }
        if( buton_simple( 250, 380 ,370, 415 ) == 1)
            return REGISTER;
        if( buton_simple( 576, 432, 636, 462 ) == 1)
            return EXIT;

        delay(50);
     }
}

int page_register(user_data* user)
{
    int name_check = 0, password_check = 0;

    cleardevice();
    mouseinit();
    draw_register();

    while (1) 
    {
        newmouse(&MouseX, &MouseY, &press);

        if( buton_simple( 160, 230, 160 + 320, 230 + 32 ) == 1)
        {
            get_input( 160, 230, user->name, 8, 3);
            name_check = 1;
        }
        if( buton_simple( 160, 278, 160 + 320, 278 + 32 ) == 1)
        {
            get_input( 160, 278, user->password, 8, 3);
            password_check = 1;
        }
        if( buton_simple( 160, 278 + 64, 160 + 320, 278 + 64 + 32 ) == 1)
        {
            if (name_check && password_check) 
            {
                if( save_account(user) )
                    puthz( 253, 400, "rigister success", 32, 32, LIGHTGREEN);
                else
                    puthz( 253, 400, "username already exist", 32, 32, RED);
                return WELCOME;
            }
        }
        if( buton_simple( 640 - 16 - 48, 480 - 16 - 32, 640 - 16, 480 - 16 ) == 1)
        {
            return WELCOME;
        }

        delay(50);
    }
}
enum page home_button( void )
{

    if( button_home( 180, 1, 210, 20 ) )
        return MARKET;
    else if( button_home( 230, 1, 270, 20 ) )
        return SEARCH;
    else if( button_home( 600, 1, 630, 20 ) )
        return EXIT;
    else if( button_home( 130, 1, 160, 20 ) )
        return STATUS;
    else if( button_home( 295, 1, 325, 20 ) )
        return NEWS;
    else
        return NOBUT;
    

}
int page_status(const user_data* user, stock_data* stock) 
{
    FILE* fp;/**/
    FILE* stockfp;/**/
    int* choice;/**/
    int total;
    int i, j, k;
    stock_data2 temp;
    enum page pattern = NOBUT;

    clrmous(MouseX, MouseY);
    cleardevice();
    draw_status();

    choice = safe_calloc(STOCK_NUM, sizeof(int));/**/
    fp = open_file(user->name, CHOICE, "rb");/**/
    fseek(fp, sizeof(user_data), SEEK_SET);
    SAFE_READ(choice, sizeof(int), STOCK_NUM, fp);
    close_file(fp, user->name, ".cho");/**/

    total = 0;
    draw_choosed_stock(choice, &total);

    stockfp = open_file("main", STOCK, "rb");/**/

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        pattern = home_button();
        if( pattern != NOBUT )
        {
            close_file( stockfp, "main", ".stock" );/**/
            free(choice);/**/
            return pattern;
        }

        for( k=1; k<=total; k++ )
        {
            if( button_simple( 10, 40 + k * 20, 160,  40 + (k+1) * 20 ) )
            {
                for (i = 0, j = 0; i < STOCK_NUM; i++)
                {
                    if (choice[i] == 1)
                        j++;
                    if (j == k)
                        break;
                }

                fseek(stockfp, sizeof(stock_data2) * i, SEEK_SET);
                SAFE_READ(&temp, sizeof(stock_data2), 1, stockfp);
                close_file(stockfp, "main", ".stock");/**/
            
                strcpy(stock->code, temp.code);
                strcpy(stock->name, temp.name);
            
                free(choice);/**/
                return INDICATOR;
            }
        }
        delay(50);
    }
}

void draw_choosed_stock(int* choice, int* total)
{
    FILE* stockfp;
    stock_data2 stock;
    int num, i;
    enum COLORS color;

    stockfp = open_file("main", STOCK, "rb");
    num = 0;
    for (i = 0; i < STOCK_NUM; i++)
    {
        SAFE_READ(&stock, sizeof(stock_data2), 1, stockfp);
        if (choice[i] == 1)
        {
            
            char str[4][5] = { 0 };
            num++;

            sprintf(str[0], "%.2f", stock.open);
            sprintf(str[1], "%.2f", stock.close);
            sprintf(str[2], "%.2f", stock.high);
            sprintf(str[3], "%.2f", stock.low);

            settextstyle(SMALL_FONT, HORIZ_DIR, 8);
            setcolor(YELLOW);
            outtextxy(10, 42 + num * 20, stock.code); //����
            puthz(90, 44 + num * 20, stock.name, 16, 16, YELLOW); //����
            puthz(430, 44 + num * 20, stock.industry, 16, 16, YELLOW); //��ҵ
            puthz(520, 44 + num * 20, stock.region, 16, 16, YELLOW); //����
            outtextxy(235, 43 + num * 20, str[2]); //���
            outtextxy(302, 43 + num * 20, str[3]); //���

            if (stock.open >= stock.close) 
                color = RED;
            else
                color = GREEN;

            setcolor(color);
            outtextxy(176, 43 + num * 20, str[0]); //��
            outtextxy(368, 43 + num * 20, str[1]); //����

        }
    }
    *total = num;
    close_file(stockfp, "main", ".stock");
}

int page_indicator(const stock_data* stock)
{
    axis_data main_axis = { 600, 50, 220, 0, 0, 6 };
    axis_data sub_axis  = { 600, 290,180, 0, 0, 4 }; 
    enum gear_type gear = MEDIUM;
    enum line_type main_line = KDAY;
    enum line_type sub_line = KDJ;
    enum line_type button = NA;
    bool changed = false;
    enum page pattern = NOBUT;

    rectangle_info rectangle;
    choose_rectangle(&rectangle, gear);
    cleardevice();
    clrmous(MouseX, MouseY);
    draw_indicator( stock->code );
    draw_line(stock, &rectangle, KDAY, &main_axis);
    draw_line(stock, &rectangle, KDJ, &sub_axis);

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        
        pattern = home_button();
        if( pattern != NOBUT )
            return pattern;

        changed = false;
        button = NA;

        if ( button_simple( 425,21,460,40 ) && gear < LARGE)
        {
            changed = true;
            gear++;
        }
        else if ( button_simple( 470,21,505,40 ) && gear > SMALL)
        {
            changed = true;
            gear--;
        }

        
        if ( button_simple( 10,21,45,40 ) )
            button = KDAY;
        else if ( button_simple( 51,21,85,40 ) )
            button = KWEEK;
        else if ( button_simple(95,21,145,40) )
            button = MA;
        else if ( button_simple( 155,121,230,40 ) )
            button = EXPMA;
        else if ( button_simple( 238,21,305,40 ) )
            button = XUECHI;
        else if ( button_simple( 360,21,415,40 ) )
            button = MACD;
        else if ( button_simple( 315,21,355,40 ) )
            button = KDJ;
        else
            button = NA;
        

        switch (button)
        {
            case KDAY:
            case KWEEK:
                if (main_line != button)
                {
                    changed = true;
                    main_line = button;
                }
                break;
            case MA:
            case EXPMA:
            case XUECHI:
                if (main_line != button)
                {
                    changed = true;
                    main_line = button;
                }
                else 
                {
                    changed = false;
                    main_line = KDAY;
                }
                break;
            case KDJ:
            case MACD:
                if (sub_line != button)
                {
                    changed = true;
                    sub_line = button;
                }
                break;
            case NA:
                delay(50);
                continue;
        }

        if ( changed )
        {
            cleardevice();
            draw_indicator( stock->code );
            choose_rectangle(&rectangle, gear);
            draw_line(stock, &rectangle, main_line, &main_axis);
            draw_line(stock, &rectangle, sub_line, &sub_axis);
        }
    }
    return 0;
}
int page_market(const user_data* user)
{
    int i, j, k;
    int* choice = safe_calloc(STOCK_NUM, sizeof(int));/**/
    enum page pattern = NOBUT;

    FILE* fp = open_file(user->name, CHOICE, "rb+");/**/
    fseek(fp, sizeof(user_data), SEEK_SET);
    SAFE_READ(choice, sizeof(int), STOCK_NUM, fp);
    
    cleardevice();
    clrmous(MouseX, MouseY);
    draw_market();

    setcolor(BLUE);
    for( k=1; k<=STOCK_NUM; k++ )
    {
        if( choice[ k-1 ] )
        {
            line(10 + 1, 40 + k * 20 + 8, 10 + 5, 40 + k * 20 + 2);
            line(10 + 9, 40 + k * 20 + 18, 10 + 18, 40 + k * 20 + 3);
        }
    }

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        pattern = home_button();
        if( pattern != NOBUT )
            break;

        for( k=1; k<=STOCK_NUM; k++ )
        {
            if( button_simple( 10, 40 + k * 20, 160,  40 + (k+1) * 20 ) )
            {
                if( choice[ k-1 ] == 0 )
                {
                    setcolor(BLUE);
                    choice[ k-1 ] = 1;
                }
                else 
                {
                    setcolor(WHITE);
                    choice[ k-1 ] = 0;
                }
                line(10 + 1, 40 + k * 20 + 8, 10 + 5, 40 + k * 20 + 2);
                line(10 + 9, 40 + k * 20 + 18, 10 + 18, 40 + k * 20 + 3);
                break;
            } 
        }

        delay(50);
    }
    fseek(fp, sizeof(user_data), SEEK_SET);
    SAFE_WRITE(choice, sizeof(int), STOCK_NUM, fp);
    close_file(fp, user->name, ".choice");
    free(choice);
    return pattern;
}

int page_predict(const char* code)
{
    enum page pattern = NOBUT;
    axis_data pred_axis = { 590, 170, 130, 0, 0, 5 };
    rectangle_info rectangle = { 6, 0, 21 };

    clrmous(MouseX, MouseY);
    cleardevice();
    draw_predict();

    draw_ar_pred( code, &rectangle, &pred_axis);
    draw_gene_pred( code);

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        pattern = home_button();
        if( pattern != NOBUT )
            return pattern;

    }
}


int page_search( char* code )
{
    enum page pattern = NOBUT;
    bool check = false;
    clrmous(MouseX, MouseY);
    cleardevice();
    draw_search();

    while (1)
    {
        check = false;
        newmouse(&MouseX, &MouseY, &press);

        pattern = home_button();
        if( pattern != NOBUT )
            return pattern;

        if( button_simple( 180, 190, 430, 270 ) )
        {
            get_input( 180, 190, code, 7, 6 );
            check = true;
        }
        if( button_simple( 431, 190, 480, 270 ) && check )
        {
            move_search();
            return PREDICT;
        }

    }
}
