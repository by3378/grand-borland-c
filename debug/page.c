#include "global.h"

int main( void ) 
{
	int gd = VGA;
	int gm = VGAHI;
	initgraph(&gd, &gm, "C:\\borlandc\\BGI");
	mouseinit();
	
    user_data user;
    stock_data stock;
    enum page pattern = WELCOME;
    while( 1 )
    {
        switch( pattern )
        {
            case WELCOME:
                pattern = page_welcome( &user );
                break;
            case REGISTER:
                pattern = page_register( &user );
                break;
            case INDICATOR:
                pattern = page_indicator( &stock );
                break;
            case STATUS:
                pattern = page_status( &user );
                break;
            case MARKET:
                pattern = page_search();
                break;
            case PREDICT:
                pattern = page_predict();
                break;
            case EXIT:
                closegraph();
                return 0;
        }
    }
}

int page_welcome( user_data* user )
{
    {
        clrmous(MouseX, MouseY);
        cleardevice();
        draw_welcome();
    }

    int but;
    bool name_check = false, password_check = false;
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        but = 0;
        button( &but, 160, 230, 160 + 320, 230 + 32);
        button( &but, 160, 278, 160 + 320, 278 + 32);
        button( &but, 160, 342, 480, 374);
        button( &but, 250, 380, 370, 415);
        button_back( &but, 576, 432, 636, 462);

        switch( but )
        {
            case 1:
                get_input(160 + 75, 230 + 12, user->name, 10, 3);
                name_check = true;
                break;
            case 2:
                get_input(160 + 75, 278 + 12, user->password, 10, 3);
                password_check = true;
                break;
            case 3:
                if( name_check && password_check )
                {
                    if( check_info( user ) )
                    {
                        puthz();
                        return STATUS;
                    }
                    else
                    {
                        puthz();
                        return WELCOME;
                    }
                }
                break;
            case 4:
                return REGISTER;
            case 5:
                return EXIT;
        }
    }
}




int page_register( user_data* user )
{
    {
        cleardevice();
        mouseinit();
        draw_register();
    }

    int but;
    bool name_check = false, password_check = false;
    while (1) 
    {
        newmouse(&MouseX, &MouseY, &press);

        but = 0;
        button(&but, 160, 230, 160 + 320, 230 + 32);
        button(&but, 160, 278, 160 + 320, 278 + 32);
        button(&but, 160, 278 + 64, 160 + 320, 278 + 64 + 32);
        button_back(&but, 640 - 16 - 48, 480 - 16 - 32, 640 - 16, 480 - 16);

        switch( but )
        {
            case 1:
                get_input(160 + 75, 230 + 12, user->name, 10, 3);
                name_check = true;
                break;
            case 2:
                get_input(160 + 75, 278 + 12, user->password, 10, 3);
                password_check = true;
                break;
            case 3:
                if (name_check && password_check) 
                {
                    save_account( user );
                    puthz();
                    return WELCOME;
                }
                break;
            case 4:
                return WELCOME;
        }
    }
}

int page_status( const user_data* user , stock_data* stock ) 
{
    {
        clrmous(MouseX, MouseY);
        cleardevice();
        draw_stock();
    }

    /* read choice */
    FILE* fp = open_file( user->name, CHOICE, "rb");
    int* choice = safe_calloc( STOCK_NUM, sizeof(int) );
    fseek( fp, sizeof(user_data), SEEK_SET);
    SAFE_READ( choice, sizeof(int), STOCK_NUM, fp);
    close_file( fp, user->name, ".cho");

    int total = 0;
    draw_choosed_stock( choice , &total );
    
    /* get click position */
    int result = 0;
    while( 1 )
    {
        if( mouse_press( /**/ ) == 1 )
            result = 1;
        if( mouse_press( /**/ ) == 1 )
            result = 2;
        if( mouse_press( /**/ ) == 1 )
            result = 3;
        /* ...... */

        if( result > total )
            break;
    }

    int i,j;
    for( i=0,j=0; i < STOCK_NUM; i++ )
    {
        if( choice[i] == 1 )
            j++;
        if( j == result )
            break;
    }

    stock_data2 temp;
    FILE* stockfp = open_file( "main", STOCK, "rb");
    fseek( stockfp, sizeof(stock_data2)*i, SEEK_SET);
    SAFE_READ( &temp, sizeof(stock_data2), 1, stockfp);
    close_file( stockfp, "main", ".stock");

    strcpy( stock->code, temp.code );
    strcpy( stock->name, temp.name );

    return INDICATOR;
}
void draw_choosed_stock( int* choice , int* total )
{   /* 101000*/
    FILE* stockfp = open_file( "main", STOCK, "rb");
    stock_data2 stock;
    int num = 0;
    for( int i = 0; i < STOCK_NUM; i++ )
    {
        SAFE_READ( &stock, sizeof(stock_data2), 1, stockfp);
        if( choice[i] == 1 )
        {
            char str[4][5] = { 0 };
	    num++;
            sprintf(str[0], "%.2f", stock->open);
            sprintf(str[1], "%.2f", stock->close);
	    sprintf(str[2], "%.2f", stock->high);
            sprintf(str[3], "%.2f", stock->low);
 

           settextstyle(SMALL_FONT, HORIZ_DIR, 8);
           setcolor(YELLOW);
           outtextxy(10, 42 + num * 20, stock->code);//代码
           puthz(90, 44 + num * 20, stock->name16, 16, YELLOW);//名称
           puthz(430, 44 + num * 20, stock->industry, 16, 16, YELLOW);//行业
           puthz(520, 44 + num * 20, stock->region, 16, 16, YELLOW);//地区
           outtextxy(235, 43 + num * 20, str[2]);//最高
           outtextxy(302, 43 + num * 20, str[3]);//最低

           if (stock->open > stock->close) {
               setcolor(RED);
               outtextxy(176, 43 + num * 20, str[0]);//今开
               outtextxy(368, 43 + num * 20, str[1]);//昨收
          }
          else {
               setcolor(GREEN);
               outtextxy(176, 43 + num * 20, str[0]);//今开
               outtextxy(368, 43 + num * 20, str[1]);//昨收
         }
      }
    *total = num;
    close_file( stockfp, "main", ".stock");
}

int page_indicator( const stock_data* stock )
{
    /* draw_page */

    axis_data main_axis ={ x, y, length, max, min, unit_num};/* replace it with real data */
    axis_data sub_axis  ={ x, y, length, max, min, unit_num};

    /* default gear */
    enum gear_type gear = MEDIUM;
    rectangle_info rectangle;
    choose_rectangle( &rectangle , gear);

    /* main screen: default kline */
    draw_line( stock, &rectangle, KDAY, &main_axis);
    /* sub screen: default kdj */
    draw_line( stock, &rectangle, KDJ, &sub_axis);

    enum line_type main_line = KDAY;
    enum line_type sub_line = KDJ;
    enum line_type button = NA;

    bool gear_changed;
    bool main_changed;
    bool sub_changed;

    while( 1 )
    {
        main_changed = false;
        sub_changed = false;
        gear_changed = false;
        button = NA;  /* no button pressed */

        if( mouse_press( /*exit*/ ) == 1 )
            break;

        /* choose gear */
        if( mouse_press( /*+*/ ) == 1 && gear<LARGE )
        {
            gear_changed = true;
            gear++;
        }
        else if( mouse_press( /*-*/ ) == 1 && gear>SMALL )
        {
            gear_changed = true;
            gear--;
        }
        if( gear_changed )
        {
            choose_rectangle( &rectangle , gear);
            /* clear main screen */
            draw_line( stock, &rectangle, main_line, &main_axis);
            /* clear sub screen */
            draw_line( stock, &rectangle, sub_line, &sub_axis);
            continue;
        }
        
        /* choose indicator */
        if( mouse_press( /*kday*/ ) == 1 )
            button = KDAY;
        else if( mouse_press( /*kweek*/ ) == 1 )
            button = KWEEK;
        else if( mouse_press( /*ma*/ ) == 1 )
            button = MA;
        else if( mouse_press( /*expma*/ ) == 1 )
            button = EXPMA;
        else if( mouse_press( /*xuechi*/ ) == 1 )
            button = XUECHI;
        else if( mouse_press( /*macd*/ ) == 1 )
            button = MACD;
        else if( mouse_press( /*kdj*/ ) == 1 )
            button = KDJ;
        else
            button = NA;

        switch( button )
        {
            case KDAY:
            case KWEEK:
            {
                if( main_line != button )
                {
                    main_changed = true;
                    main_line = button;
                }
                break;
            }
            case MA:
            case EXPMA:
            case XUECHI:
            {
                if( main_line != button )
                {
                    main_changed = true;
                    main_line = button;
                }
                else 
                {
                    main_line = KDAY;
                }
                break;
            }
            case KDJ:
            case MACD:
            {
                if( sub_line != button )
                {
                    sub_changed = true;
                    sub_line = button;
                }
                break;
            }
            case NA:
            {
                delay( 50 );
                continue;
            }
        }

        if( main_changed )
        {
            /* clear main screen */
            draw_line( stock, &rectangle, main_line, &main_axis);
        }
        if( sub_changed )
        {
            /* clear sub screen */
            draw_line( stock, &rectangle, sub_line, &sub_axis);
        }

    }
}

int page_predict(const stock_data* stock)
{
    int but1 = 0, but2 = 0��but3 = 0, but4 = 0, but5 = 0;
    mouseinit();
    draw_predict();

    axis_data pred_axis = { 590,170, 130, 0, 0, 5 };
    rectangle_info rectangle = { 6,0,21 };

    draw_ar_pred(stock, &rectangle, &pred_axis);
    draw_gene_pred(stock);
    while (1)
    {
        button_back(&but1, 570, 30, 630, 60);//����
        button_home(&but2, 600, 1, 630, 20);//�˳�
        button_home(&but3, 230, 1, 270, 20);//��С��
        button_home(&but4, 130, 1, 160, 20);//����
        button_home(&but5, 180, 1, 210, 20);//�г�
        if (but1 == 1 || but3 == 1) {
            return 5;//������С���ѽ���
        }
        if (but2 == 1) {
            closegraph();//�˳�ϵͳ
        }
        if (but4 == 1) {
            return 3;//�����������
        }
        if (but5 == 1) {
            //return 4;//�����г�����
        }
    }
}

button_home(&but1, 130, 1, 160, 20);//����
button_home(&but2, 230, 1, 270, 20);//��С��
button_home(&but3, 600, 1, 630, 20);//�˳�
button_choose(&but4, 125, 46, 135, 56);//�����Ƽ�
button_choose(&but5, 125, 66, 135, 76);//��������
int page_market( const user_data* user )
{
    int* choice = safe_calloc( STOCK_NUM, sizeof(int) );

    FILE* fp = open_file( user->name, CHOICE, "rb");
    fseek( fp, sizeof(user_data), SEEK_SET);
    SAFE_READ( choice, sizeof(int), STOCK_NUM, fp);
    
    /* draw choose page accordingly */
    
    while(1)
    {
        int button = 0;
        if( mouse_press( /*stock1*/)==1 )
            button = 1;
        if( mouse_press( /*stock2*/)==1 )
            button = 2;
        if( mouse_press( /*stock3*/)==1 )
            button = 3;
        /* ......*/
        if( mouse_press( /*stock10*/)==1 )
            button = 10;

        if( mouse_press( /* exit */)==1 )
            break;

        if( button != 0 )
           choice[button-1] = ( choice[button-1] == 0 ) ? 1 : 0;
    
    }

    fseek( fp, sizeof(user_data), SEEK_SET);
    SAFE_WRITE( choice, sizeof(int), STOCK_NUM, fp);
    close_file( fp, user->name, ".choice");

    free( choice );

}

//��С��-��������5
int page_search() {
    int but1 = 0, but2 = 0, but3 = 0, but4 = 0, but5 = 0;
    cleardevice();
    mouseinit();
    draw_search();

    while (1) {
        newmouse(&MouseX, &MouseY, &press);

        button_home(&but1, 130, 1, 160, 20);//����
        button_home(&but2, 180, 1, 210, 20);//�г�
        button_home(&but3, 600, 1, 630, 20);//�˳�
        //button(&but4, 180, 190, 430, 270);//�����Ʊ����
        //button(&but5, 431, 190, 480, 270);//����

        if (but1 == 1) {
            return 3;//�����������
        }
        if (but2 == 1) {
            return 4;//�����г�����
        }
        if (but3 == 1) {
            closegraph();//�˳�ϵͳ
        }
        if (but4 == 1) {
            //�û������Ʊ����
        }
        if (but5 == 1) {
            //return 6;//������С��Ԥ�����
        }
    }
}
