#include <dos.h>
#include <stdio.h>
#include "page.h"
#include "stock.h"
#include "calculate.h"
#include "global.h"
#include "file.h"
#include "draw.h"
#include "mouse.h"

void indicator_page( const stock_data* stock )
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

void predict_page( const stock_data* stock )
{
    /* draw_page */

    axis_data pred_axis ={ x, y, length, max, min, unit_num};/* replace it with real data */
    rectangle_info rectangle = { 2+FORECAST_DAYS, 0,  };

    draw_ar_pred( stock, &rectangle, &pred_axis );
    draw_gene_pred( stock );

    while( 1 )
    {
        if( mouse_press( /*exit*/ ) == 1 )
            break;
    }

}


void choose_page( const user_data* user, bool isnew )
{
    int* choice = safe_calloc( STOCK_NUM, sizeof(int) );

    FILE* fp;
    if( isnew )
    {
        fp = open_file( user->name, CHOICE, "wb");
        SAFE_WRITE( user, sizeof(user_data), 1, fp);
        SAFE_WRITE( choice, sizeof(int), STOCK_NUM, fp);
    }
    else
    {
        fp = open_file( user->name, CHOICE, "rb");
        fseek( fp, sizeof(user_data), SEEK_SET);
        SAFE_READ( choice, sizeof(int), STOCK_NUM, fp);
    }
 

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