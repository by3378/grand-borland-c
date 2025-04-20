#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <float.h>
#include <graphics.h>
#include "use.h"
#include "button.h"
#include "page.h"
#include "draw.h"
#include "mouse.h"
#include "hzo.h"


//��¼����1
int page_welcome()
{
    struct info user = { 0 };
    enum bool name_check = false, password_check = false;
    int but1 = 0, but2 = 0, but3 = 0, but4 = 0, but5 = 0;
    cleardevice();
    mouseinit();
    //clrmous(MouseX, MouseY);
    cleardevice();
    draw_welcome();

    while (1) {
        newmouse(&MouseX, &MouseY, &press);

        button(&but1, 160, 230, 160 + 320, 230 + 32);//�����˺�
        button(&but2, 160, 278, 160 + 320, 278 + 32);//��������
        button(&but3, 160, 342, 480, 374);//��¼
        button(&but4, 250, 380, 370, 415);//ע��
        button_back(&but5, 576, 432, 636, 462);//�˳�

        if (but1 == 1) {
            get_input(160 + 75, 230 + 12, user.name, 10, 3);
            name_check = true;
            but1 = 0;
            continue;
        }
        if (but2 == 1) {
            get_input(160 + 75, 278 + 12, user.password, 10, 3);
            password_check = true;
            but2 = 0;
            continue;
        }

        if (name_check && password_check && but3 == 1) {

            if (check_info(&user))
            {
                show_guide();
                puthz(250, 432, "��¼�ɹ�", 32, 32, LIGHTGREEN);
                delay(2000);
                return 3;//�����������
            }
            else
            {
                show_guide();
                puthz(150, 432, "�û��������ڻ��������", 32, 32, RED);
                delay(2000);
                return 1;
            }   
        }

        if (but4 == 1) {
            return 2;//����ע�����
        }
        if (but5 == 1) {
            closegraph();//�˳�ϵͳ
        }

    }
}




//ע�����2
int page_register()
{
    struct info user = { 0 };
    enum bool name_check = false, password_check = false;
    int but1 = 0, but2 = 0, but3 = 0,but4 = 0;
    cleardevice();
    mouseinit();
    draw_register();


    while (1) {
        newmouse(&MouseX, &MouseY, &press);
        button(&but1, 160, 230, 160 + 320, 230 + 32);//�����˺�
        button(&but2, 160, 278, 160 + 320, 278 + 32);//��������
        button(&but3, 160, 278 + 64, 160 + 320, 278 + 64 + 32);//ע��
        button_back(&but4, 640 - 16 - 48, 480 - 16 - 32, 640 - 16, 480 - 16);//���ص�¼����

        if (but1 == 1) {
            get_input(160 + 75, 230 + 12, user.name, 10, 3);
            name_check = true;
            but1 = 0;
            continue;
        }
        if (but2 == 1) {
            get_input(160 + 75, 278 + 12, user.password, 10, 3);
            password_check = true;
            but2 = 0;
            continue;
        }
        if (name_check && password_check && but3 == 1) {
            saveaccount(&user);
            puthz(253, 400, "ע��ɹ�", 32, 32, LIGHTGREEN);
            delay(1500);
            return 1;
        }
        if (but4 == 1) {
            return 1;
        }

    }
}


//�������3
int page_stock() {

    int but1 = 0, but2 = 0, but3 = 0;
    mouseinit();
    //clrmous();
    draw_stock();
    
    while (1) {
        newmouse(&MouseX, &MouseY, &press);

        button_home(&but1, 180, 1, 210, 20);//�г�
        button_home(&but2, 230, 1, 270, 20);//��С��
        button_home(&but3, 600, 1, 630, 20);//�˳�
        if (but1 == 1) {
            return 4;//�����г�����
        }
        if (but2 == 1) {
            return 5;//������С��-��������
        }
        if (but3 == 1) {
            closegraph();//�˳�ϵͳ
        }
    }
}


//�г�����4
int page_market() {
    int but1 = 0, but2 = 0, but3 = 0, but4 = 0, but5 = 0;
    cleardevice();
    mouseinit();
    draw_market();

    while (1) {
        newmouse(&MouseX, &MouseY, &press);

        button_home(&but1, 130, 1, 160, 20);//����
        button_home(&but2, 230, 1, 270, 20);//��С��
        button_home(&but3, 600, 1, 630, 20);//�˳�
        button_choose(&but4, 125, 46, 135, 56);//�����Ƽ�
        button_choose(&but5, 125, 66, 135, 76);//��������

        if (but1 == 1) {
            return 3;
        }
        if (but2 == 1) {
            return 5;
        }
        if (but3 == 1) {
            closegraph();
        }
        if (but4 == 1) {
            //����
        }
        if (but5 == 1) {
            //����
        }
    }
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


//��С��-Ԥ�����6
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


/*
//��Ʊָ�����7
int page_indicator( const stock_data* stock )
{
    draw_analysis();

    axis_data main_axis ={ x, y, length, max, min, unit_num};// replace it with real data 
    axis_data sub_axis  ={ x, y, length, max, min, unit_num};

    // default gear 
    enum gear_type gear = MEDIUM;
    rectangle_info rectangle;
    choose_rectangle( &rectangle , gear);

    // main screen: default kline 
    draw_line( stock, &rectangle, KDAY, &main_axis);
    // sub screen: default kdj 
    draw_line( stock, &rectangle, KDJ, &sub_axis);

    enum line_type main_line = KDAY;
    enum line_type sub_line = KDJ;
    enum line_type button = NA;

    enum bool gear_changed;
    enum bool main_changed;
    enum bool sub_changed;

    while( 1 )
    {
        main_changed = false;
        sub_changed = false;
        gear_changed = false;
        button = NA;  // no button pressed 

        if( mouse_press( //exit ) == 1 )
            break;

        // choose gear 
        if( mouse_press( // +) == 1 && gear<LARGE )
        {
            gear_changed = true;
            gear++;
        }
        else if( mouse_press( //- ) == 1 && gear>SMALL )
        {
            gear_changed = true;
            gear--;
        }
        if( gear_changed )
        {
            choose_rectangle( &rectangle , gear);
            // clear main screen 
            draw_line( stock, &rectangle, main_line, &main_axis);
            //clear sub screen 
            draw_line( stock, &rectangle, sub_line, &sub_axis);
            continue;
        }
        
        // choose indicator 
        if( mouse_press( //kday ) == 1 )
            button = KDAY;
        else if( mouse_press( /*kweek ) == 1 )
            button = KWEEK;
        else if( mouse_press( /*ma*) == 1 )
            button = MA;
        else if( mouse_press( /*expma* ) == 1 )
            button = EXPMA;
        else if( mouse_press( /*xuechi ) == 1 )
            button = XUECHI;
        else if( mouse_press( /*macd*) == 1 )
            button = MACD;
        else if( mouse_press( /*kdj* ) == 1 )
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
            /* clear main screen 
            draw_line( stock, &rectangle, main_line, &main_axis);
        }
        if( sub_changed )
        {
            /* clear sub screen 
            draw_line( stock, &rectangle, sub_line, &sub_axis);
        }

    }
}
*/


