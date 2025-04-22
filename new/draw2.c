#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <graphics.h>
#include <dos.h>
#include "use.h"
#include "file.h"
#include "draw.h"
#include "hzo.h"


//��ӡ�������塰ͨ���š�
void draw_tongdaxin() {
    puthz(200, 40, "ͨ", 48, 48, BLUE);

    setlinestyle(0, 0, 3);
    setcolor(BLUE);
    circle(300, 50, 2);
    floodfill(300, 50, BLUE);
    line(299, 50, 381 - 80, 50);
    line(373 - 80, 60, 379 - 80, 60);
    line(373 - 80, 61, 379 - 80, 61);
    circle(373 - 80, 60, 1);
    line(379 - 80, 59, 379 - 80, 82);
    line(380 - 80, 59, 380 - 80, 82);
    line(380 - 80, 82, 418 - 80, 82);
    line(380 - 80, 83, 418 - 80, 83);
    circle(418 - 80, 82, 1);
    line(389 - 80, 55, 415 - 80, 55);
    line(405 - 80, 60, 410 - 80, 75);
    line(410 - 80, 75, 420 - 80, 75);
    setcolor(RED);
    line(376 - 80, 86, 388 - 80, 76);
    line(375 - 80, 85, 387 - 80, 75);
    line(388 - 80, 76, 394 - 80, 76);
    line(387 - 80, 75, 394 - 80, 75);
    line(394 - 80, 76, 405 - 80, 42);
    line(403 - 80, 45, 399 - 80, 45);
    line(399 - 80, 45, 405 - 80, 42);
    line(400 - 80, 46, 398 - 80, 46);
    //�����

    puthz(400, 40, "��", 48, 48, BLUE);
}


//���Ƶ�¼����
void draw_welcome()
{
    setbkcolor(WHITE);
    draw_tongdaxin();

    setcolor(LIGHTRED);
    rectangle(160, 230, 160 + 320, 230 + 32);
    rectangle(160, 278, 160 + 320, 278 + 32);

    setcolor(LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 0);
    puthz(164, 160, "ģ���Ʊ����Ԥ��ϵͳ", 32, 32, LIGHTCYAN);
    puthz(165, 240, "�˻�", 16, 16, LIGHTGRAY);
    outtextxy(200, 242, ":");
    puthz(165, 288, "����", 16, 16, LIGHTGRAY);
    outtextxy(200, 290, ":");

    setfillstyle(SOLID_FILL, 8);
    bar(576, 432, 636, 462);
    puthz(584, 438, "�˳�", 24, 24, WHITE);

    bar(160, 342, 480, 374);
    puthz(294, 348, "��¼", 16, 16, WHITE);


    bar(250, 380, 370, 415);
    puthz(278, 390, "ע���˺�", 16, 16, WHITE);
}

//����ע�����
void draw_register()
{
    setbkcolor(WHITE);
    draw_tongdaxin();
    setcolor(LIGHTRED);

    rectangle(160, 230, 160 + 320, 230 + 32);
    rectangle(160, 278, 160 + 320, 278 + 32);

    setcolor(LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 0);
    puthz(165, 240, "�˻�", 16, 16, LIGHTGRAY);
    outtextxy(200, 240, ":");
    puthz(165, 275 + 14, "����", 16, 16, LIGHTGRAY);
    outtextxy(200, 289, ":");

    puthz(210, 140, "������ս��", 16, 16, LIGHTGRAY);
    puthz(310, 140, "�������ʲƸ��߷�", 16, 16, LIGHTGRAY);
    puthz(240, 188, "��ע���˻�", 32, 32, LIGHTCYAN);

    setfillstyle(SOLID_FILL, 8);
    bar(576, 432, 636, 462);
    puthz(585, 440, "����", 24, 24, WHITE);

    bar(160, 278 + 64, 160 + 320, 278 + 64 + 32);
    puthz(295, 278 + 71, "ע��", 16, 16, WHITE);
}

}

//�������˵���
void draw_home()
{
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(0, 0, 640, 20);
    floodfill(1, 1, 1);
    puthz(10, 2, "ͨ���Ž��ڶ�", 16, 16, 8);
    puthz(130, 2, "����", 16, 16, 8);
    puthz(180, 2, "�г�", 16, 16, 8);
    puthz(230, 2, "��С��", 16, 16, 8);
    puthz(295, 2, "��Ѷ", 16, 16, 8);
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(470, 2, "19:21:26");
    puthz(550, 2, "����", 16, 16, 8);
    puthz(600, 2, "�˳�", 16, 16, 8);
}



//������ѡ�ɽ���
void draw_status() {
    draw_home();
    setcolor(8);
    setfillstyle(SOLID_FILL, 8);
    rectangle(0, 20, 640, 480);
    floodfill(50, 50, 8);
    setcolor(RED);
    rectangle(0, 20, 640, 40);
    puthz(585, 21, "����", 16, 16, LIGHTCYAN);
    setcolor(LIGHTCYAN);
    settextstyle(SMALL_FONT, HORIZ_DIR, 8);
    outtextxy(620, 14, "+");
    puthz(22, 21, "����", 16, 16, LIGHTGRAY);
    puthz(104, 21, "����", 16, 16, LIGHTGRAY);
    puthz(183, 21, "��", 16, 16, LIGHTGRAY);
    puthz(242, 21, "���", 16, 16, LIGHTGRAY);
    puthz(305, 21, "���", 16, 16, LIGHTGRAY);
    puthz(372, 21, "����", 16, 16, LIGHTGRAY);
    puthz(430, 21, "ϸ����ҵ", 16, 16, LIGHTGRAY);
    puthz(520, 21, "����", 16, 16, LIGHTGRAY);
}

//�����г�����
void draw_market() {

    int i,j,k;
    char temp[7];
    stock_data2 stock;
    FILE* fp = open_file("main", STOCK, "rb");

    for( i=0 ; i<STOCK_NUM ; i++ )
    {
        SAFE_READ( &stock, sizeof(stock_data2), 1, fp);
        puthz(100, 40+i*20, stock.name, 16, 16, YELLOW);
        sprintf(temp, "%.2f", stock.rate);
        puthz(180, 40+i*20, temp, 16, 16, YELLOW);
        sprintf(temp, "%.2f", stock.fu);
        puthz(240, 40+i*20, temp, 16, 16, YELLOW);
    }
    close_file(fp, "main", "stock");


    draw_home();
    //�����
    setcolor(RED);
    rectangle(0, 21, 639, 479);
    floodfill(50, 70, 0);
    rectangle(0, 21, 320, 479);
    rectangle(0, 21, 639, 40);
    line(0, 262 - 20, 639, 262 - 20);
    line(0, 262, 639, 262);

    puthz(10, 23, "��ѡ��Ʊ", 16, 16, LIGHTGRAY);
    puthz(100, 23, "������ѡ", 16, 16, LIGHTGRAY);
    puthz(190, 23, "�ǵ���", 16, 16, LIGHTGRAY);
    puthz(265, 23, "�ǵ���", 16, 16, LIGHTGRAY);

    puthz(330, 23, "��֤", 16, 16, LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    setcolor(LIGHTGRAY);
    outtextxy(365, 21, "A");
    puthz(374, 23, "��", 16, 16, LIGHTGRAY);
    puthz(420, 23, "������ѡ", 16, 16, LIGHTGRAY);
    puthz(420, 220 + 23, "������ѡ", 16, 16, LIGHTGRAY);
    puthz(515, 23, "����", 16, 16, LIGHTGRAY);
    puthz(515, 220 + 23, "����", 16, 16, LIGHTGRAY);
    puthz(595, 23, "�Ƿ�", 16, 16, LIGHTGRAY);
    puthz(595, 220 + 23, "�Ƿ�", 16, 16, LIGHTGRAY);

    puthz(10, 243, "����", 16, 16, LIGHTGRAY);//220��320
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    setcolor(LIGHTGRAY);
    outtextxy(45, 241, "A");
    puthz(54, 243, "��", 16, 16, LIGHTGRAY);
    puthz(100, 243, "������ѡ", 16, 16, LIGHTGRAY);
    puthz(200, 243, "����", 16, 16, LIGHTGRAY);
    puthz(275, 243, "����", 16, 16, LIGHTGRAY);

    //��֤A��
    puthz(330, 243, "��֤", 16, 16, LIGHTGRAY);//220��320
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    setcolor(LIGHTGRAY);
    outtextxy(365, 241, "A");
    puthz(374, 243, "��", 16, 16, LIGHTGRAY);


    puthz(10, 263, "��������", 16, 16, YELLOW);
    puthz(10, 283, "��ó����", 16, 16, YELLOW);
    puthz(10, 303, "��ԭ�Ҿ�", 16, 16, YELLOW);
    puthz(10, 323, "�����ɷ�", 16, 16, YELLOW);
    puthz(10, 343, "���Ƹ�", 16, 16, YELLOW);
    puthz(10, 363, "���Ĺɷ�", 16, 16, YELLOW);
    puthz(10, 383, "��Դ�Ƽ�", 16, 16, YELLOW);
    puthz(10, 403, "������", 16, 16, YELLOW);
    puthz(10, 423, "�����Ƽ�", 16, 16, YELLOW);
    puthz(10, 443, "���ڿƼ�", 16, 16, YELLOW);
    puthz(10, 463, "���ƾ���", 16, 16, YELLOW);

    //��֤A��
    puthz(330, 43, "��������", 16, 16, YELLOW);
    puthz(330, 63, "˶����", 16, 16, YELLOW);
    puthz(330, 83, "�³���", 16, 16, YELLOW);
    puthz(330, 103, "��嫹ɷ�", 16, 16, YELLOW);
    puthz(330, 123, "������", 16, 16, YELLOW);
    puthz(330, 143, "��Դ����", 16, 16, YELLOW);
    puthz(330, 163, "����ɷ�", 16, 16, YELLOW);
    puthz(330, 183, "����ΰҵ", 16, 16, YELLOW);
    puthz(330, 203, "��ά��Ϣ", 16, 16, YELLOW);
    puthz(330, 223, "����Ӣ", 16, 16, YELLOW);

    puthz(330, 263, "������", 16, 16, YELLOW);
    puthz(330, 283, "��̬�ɷ�", 16, 16, YELLOW);
    puthz(330, 303, "���ڻ�ѧ", 16, 16, YELLOW);
    puthz(330, 323, "���ֿƼ�", 16, 16, YELLOW);
    puthz(330, 343, "���ӱ�", 16, 16, YELLOW);
    puthz(330, 363, "����ɷ�", 16, 16, YELLOW);
    puthz(330, 383, "�Ͼ���", 16, 16, YELLOW);
    puthz(330, 403, "����Ƽ�", 16, 16, YELLOW);
    puthz(330, 423, "�Ϸ�����", 16, 16, YELLOW);
    puthz(330, 443, "����ɷ�", 16, 16, YELLOW);
    puthz(330, 463, "���ϴ�ý", 16, 16, YELLOW);


    setfillstyle(SOLID_FILL, WHITE);
    for (i = 0; i < 10; i++) {
        bar(125, 46 + 20 * i, 135, 56 + 20 * i);
    }
    for (i = 11; i < 22; i++) {
        bar(125, 46 + 20 * i, 135, 56 + 20 * i);
    }
    for (i = 0; i < 10; i++) {
        bar(445, 46 + 20 * i, 455, 56 + 20 * i);
    }
    for (i = 11; i < 22; i++) {
        bar(445, 46 + 20 * i, 455, 56 + 20 * i);
    }

    setcolor(RED);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);

    //��ָ֤������
    outtextxy(512, 41, "1.86%");
    outtextxy(512, 61, "1.65%");
    outtextxy(512, 81, "1.60%");
    outtextxy(512, 101, "1.52%");
    outtextxy(512, 121, "1.49%");
    outtextxy(512, 141, "1.43%");
    outtextxy(512, 161, "1.40%");
    outtextxy(512, 181, "1.38%");
    outtextxy(512, 201, "1.35%");
    outtextxy(512, 221, "1.30%");

    //��ָ֤���Ƿ�
    outtextxy(583, 41, "20.02%");
    outtextxy(583, 61, "20.02%");
    outtextxy(583, 81, "12.68%");
    outtextxy(583, 101, "10.10%");
    outtextxy(583, 121, "10.05%");
    outtextxy(589, 141, "8.79%");
    outtextxy(589, 161, "8.65%");
    outtextxy(589, 181, "8.34%");
    outtextxy(589, 201, "8.01%");
    outtextxy(589, 221, "7.56%");


    setcolor(GREEN);
    outtextxy(188, 261, "-8.76%");
    outtextxy(188, 281, "-1.77%");
    outtextxy(188, 301, "-1.22%");
    outtextxy(188, 321, "-1.08%");
    outtextxy(188, 341, "-1.07%");
    outtextxy(188, 361, "-1.05%");
    outtextxy(188, 381, "-1.01%");
    outtextxy(188, 401, "-0.95%");
    outtextxy(188, 421, "-0.92%");
    outtextxy(188, 441, "-0.91%");
    outtextxy(188, 461, "-0.85%");

    //��ָ֤������
    outtextxy(255, 261, "-10.88%");
    outtextxy(255, 281, "-10.05%");
    outtextxy(255, 301, "-10.03%");
    outtextxy(255, 321, "-10.03%");
    outtextxy(255, 341, "-10.02%");
    outtextxy(255, 361, "-10.00%");
    outtextxy(260, 381, "-9.85%");
    outtextxy(260, 401, "-9.82%");
    outtextxy(260, 421, "-9.76%");
    outtextxy(260, 441, "-9.72%");
    outtextxy(260, 461, "-9.67%");

    //��ָ֤������
    setcolor(RED);
    outtextxy(512, 261, "1.99%");
    outtextxy(512, 281, "1.90%");
    outtextxy(512, 301, "1.60%");
    outtextxy(512, 321, "1.42%");
    outtextxy(512, 341, "1.26%");
    outtextxy(512, 361, "1.21%");
    outtextxy(512, 381, "1.13%");
    outtextxy(512, 401, "1.10%");
    outtextxy(512, 421, "0.95%");
    outtextxy(512, 441, "0.94%");
    outtextxy(512, 461, "0.89%");

    //��ָ֤������
    outtextxy(583, 261, "19.57%");
    outtextxy(583, 281, "13.42%");
    outtextxy(583, 301, "12.38%");
    outtextxy(583, 321, "11.90%");
    outtextxy(583, 341, "11.81%");
    outtextxy(583, 361, "11.15%");
    outtextxy(583, 381, "10.93%");
    outtextxy(583, 401, "10.87%");
    outtextxy(583, 421, "10.26%");
    outtextxy(589, 441, "9.98%");
    outtextxy(589, 461, "9.95%");

}

void draw_indicator( char* code ) {

    int i;
    draw_home();  
    setcolor(WHITE);
    rectangle(0, 20, 640, 480);
    floodfill(50, 50, BLACK);
    setcolor(LIGHTRED);
    rectangle(0, 20, 639, 40);
    rectangle(0, 40, 600, 280);
    rectangle(0, 280, 600, 479);
    rectangle(600, 40, 639, 280);
    rectangle(600, 280, 639, 479);
    
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    for (i = 1; i < 7; i++) {
        line(0, 40 + 40 * i, 600, 40 + 40 * i);
    }
    for (i = 1; i < 5; i++) {
        line(0, 280 + 50 * i, 600, 280 + 50 * i);
    }
    
    
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(600, 50, 605, 50);
    line(600, 270, 605, 270);
    line(600, 290, 605, 290);
    line(600, 470, 605, 470);
    for (i = 1; i < 7; i++) {
        line(600, 40 + 40 * i, 605, 40 + 40 * i);
    }
    for (i = 1; i < 9; i++) {
        line(600, 280 + 50 * i, 605, 280 + 50 * i);
    }
    
    
    puthz(10, 21, "����", 16, 16, LIGHTGRAY);
    puthz(50, 21, "����", 16, 16, LIGHTGRAY);
    setcolor(LIGHTBLUE);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(95, 21, "MA");
    puthz(110, 21, "����", 16, 16, LIGHTBLUE);
    outtextxy(155, 21, "EXPMA");
    puthz(195, 21, "����", 16, 16, LIGHTBLUE);
    puthz(238, 21, "Ѧ˹ͨ��", 16, 16, LIGHTBLUE);
    setcolor(YELLOW);
    settextstyle(SMALL_FONT, HORIZ_DIR, 7);
    outtextxy(315, 18, "KDJ");
    outtextxy(360, 18, "MACD");
    puthz(425, 21, "�Ŵ�", 16, 16, GREEN);
    puthz(470, 21, "��С", 16, 16, GREEN);
    
    settextstyle(SMALL_FONT, HORIZ_DIR, 7);
    setcolor(MAGENTA);
    outtextxy(517, 19, code);
    puthz(600, 21, "����", 16, 16, CYAN);
}


//���������֡���С�
void draw_wenxiaoda() {

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    setcolor(LIGHTGRAY);
    rectangle(0, 22, 640, 480);
    floodfill(50, 50, LIGHTGRAY);//���ñ�����ɫ

    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    circle(250, 64, 20);
    setcolor(LIGHTGRAY);
    rectangle(237, 74, 263, 89);
    floodfill(250, 84, LIGHTGRAY);
    rectangle(246, 40, 249, 46);
    floodfill(248, 43, LIGHTGRAY);
    rectangle(233, 52, 237, 47);
    floodfill(235, 49, LIGHTGRAY);
    setcolor(BLUE);
    circle(250, 64, 9);
    setlinestyle(0, 0, 3);
    line(257, 70, 263, 79);
    line(263, 79, 264, 78);
    //�����ʡ�

    puthz(300, 40, "С", 48, 48, BLUE);

    circle(380, 50, 1);
    floodfill(380, 50, BLUE);
    line(379, 50, 381, 50);
    line(373, 60, 379, 60);
    line(373, 61, 379, 61);
    circle(373, 60, 1);
    line(379, 59, 379, 82);
    line(380, 59, 380, 82);
    line(380, 82, 418, 82);
    line(380, 83, 418, 83);
    circle(418, 82, 1);
    line(389, 55, 415, 55);
    line(405, 60, 410, 75);
    line(410, 75, 420, 75);
    setcolor(RED);
    line(376, 86, 388, 76);
    line(375, 85, 387, 75);
    line(388, 76, 394, 76);
    line(387, 75, 394, 75);
    line(394, 76, 405, 42);
    line(403, 45, 399, 45);
    line(399, 45, 405, 42);
    line(400, 46, 398, 46);
    //�����

    puthz(210, 110, "����Ͷ�ʹ���", 16, 16, 14);
    puthz(320, 110, "�����Ƹ��º���", 16, 16, 14);
}


//������С����������
void draw_search() {
    draw_home();
    draw_wenxiaoda();

    setcolor(RED);
    circle(180, 230, 40);
    setcolor(LIGHTGRAY);
    bar(180, 190, 450, 270);
    setcolor(RED);
    rectangle(180, 190, 430, 270);
    setcolor(LIGHTGRAY);
    line(180, 192, 180, 268);
    setcolor(BLUE);
    rectangle(431, 190, 480, 270);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(450, 200, BLUE);
    circle(480, 230, 40);
    floodfill(483, 230, BLUE);
    setcolor(WHITE);
    circle(465, 225, 18);
    line(478, 238, 488, 248);
    puthz(181, 220, "�������Ʊ����", 16, 16, 8);
    setfillstyle(SOLID_FILL, 15);
    floodfill(181, 220, RED);
}




//������С��Ԥ�����
void draw_predict() {
    draw_home();
    draw_wenxiaoda();

    puthz(10, 35, "��Ʊ����", 16, 16, 8);//�������꣺��87��32������6��
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(78, 32, ":");
    outtextxy(78, 57, ":");
    setcolor(8);
    puthz(10, 60, "��Ʊ����", 16, 16, 8);//�������꣺��85��60������16��

    //�����ָ�����
    setcolor(8);
    puthz(34, 179, "ָ��", 16, 16, 8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(40, 200, "MA");
    outtextxy(30, 220, "EXPMA");
    puthz(20, 245, "Ѧ��ͨ��", 16, 16, 8);
    outtextxy(35, 265, "KDJ");
    outtextxy(32, 287, "MACD");
    puthz(119, 179, "Ȩ��", 16, 16, 8);
    outtextxy(137+5, 200, "%");//�������꣺��115��200������Ϊ6��
    outtextxy(137+5, 220, "%");//�������꣺��115��220��
    outtextxy(137+5, 245, "%");//�������꣺��115��245��
    outtextxy(137+5, 265, "%");//�������꣺��115��265��
    outtextxy(137+5, 287, "%");//�������꣺��115��287��
    setlinestyle(0, 0, 1);
    rectangle(10, 170, 180, 310);
    line(95, 170, 95, 310);
    line(10, 200, 180, 200);
    line(10, 219, 180, 219);
    line(10, 240, 180, 240);
    line(10, 264, 180, 264);
    line(10, 283, 180, 283);
    setlinestyle(1, 0, 1);
    line(190, 145, 190, 390);
    setlinestyle(0, 0, 1);

    //���Ҳ�������
    line(590, 300, 590, 170);
    line(590, 300, 440, 300);
    line(590, 170, 585, 180);
    line(590, 170, 595, 180);
    line(440, 300, 450, 295);
    line(440, 300, 450, 305);

    //���Ҳ�ʱ��۸����
    puthz(248, 160, "����", 16, 16, 8);
    puthz(349, 160, "�۸�", 16, 16, 8);
    rectangle(215, 150, 413, 335);
    line(319, 150, 319, 335);
    line(215, 185, 413, 185);
    line(215, 215, 413, 215);
    line(215, 245, 413, 245);
    line(215, 275, 413, 275);
    line(215, 305, 413, 305);//��һ�У��������꣨224��191�����۸����꣨331��191����RMB���꣨389��193����ÿ��y����30����������

    puthz(10, 400, "ͨ����������", 16, 16, 8);
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(110, 398, ":");
    puthz(10, 430, "��ϵͳԤ���������ο��������з��գ�Ͷ���������", 16, 16, 8);

    setfillstyle(SOLID_FILL, 8);
    bar(570, 30, 630, 60);
    puthz(576, 33, "����", 24, 24, 8);
}
