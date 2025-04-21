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



//绘制主菜单栏
void draw_home()
{
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(0, 0, 640, 20);
    floodfill(1, 1, 1);
    puthz(10, 2, "通达信金融端", 16, 16, 8);
    puthz(130, 2, "行情", 16, 16, 8);
    puthz(180, 2, "市场", 16, 16, 8);
    puthz(230, 2, "问小达", 16, 16, 8);
    puthz(295, 2, "资讯", 16, 16, 8);
    puthz(550, 2, "周四", 16, 16, 8);
    puthz(600, 2, "退出", 16, 16, 8);
}



//������ѡ�ɽ���
void draw_stock() {
    draw_home();
    setcolor(8);
    setfillstyle(SOLID_FILL, 8);
    rectangle(0, 20, 640, 480);
    floodfill(50, 50, 8);
    setcolor(RED);
    rectangle(0, 20, 640, 40);
    puthz(585, 21, "添加", 16, 16, LIGHTCYAN);
    setcolor(LIGHTCYAN);
    settextstyle(SMALL_FONT, HORIZ_DIR, 8);
    outtextxy(620, 14, "+");
    puthz(22, 21, "代码", 16, 16, LIGHTGRAY);
    puthz(104, 21, "名称", 16, 16, LIGHTGRAY);
    puthz(183, 21, "今开", 16, 16, LIGHTGRAY);
    puthz(242, 21, "最高", 16, 16, LIGHTGRAY);
    puthz(305, 21, "最低", 16, 16, LIGHTGRAY);
    puthz(372, 21, "昨收", 16, 16, LIGHTGRAY);
    puthz(430, 21, "细分行业", 16, 16, LIGHTGRAY);
    puthz(520, 21, "地区", 16, 16, LIGHTGRAY);
}


//�����г�����
void draw_market() {
    int i;
    draw_home();

    //�����
    setcolor(RED);
    rectangle(0, 21, 639, 479);
    floodfill(50, 70, 0);
    rectangle(0, 21, 320, 479);
    rectangle(0, 21, 639, 40);
    line(0, 262, 639, 262);

    puthz(10, 23, "��֤", 16, 16, LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    setcolor(LIGHTGRAY);
    outtextxy(45, 21, "A");
    puthz(54, 23, "��", 16, 16, LIGHTGRAY);
    puthz(100, 23, "������ѡ", 16, 16, LIGHTGRAY);
    puthz(190, 23, "�ǵ���", 16, 16, LIGHTGRAY);
    puthz(265, 23, "�ǵ���", 16, 16, LIGHTGRAY);
 
    puthz(330, 23, "��֤", 16, 16, LIGHTGRAY);
    outtextxy(365, 21, "A");
    puthz(374, 23, "��", 16, 16, LIGHTGRAY);
    puthz(420, 23, "������ѡ", 16, 16, LIGHTGRAY);
    puthz(510, 23, "�ǵ���", 16, 16, LIGHTGRAY);
    puthz(585, 23, "�ǵ���", 16, 16, LIGHTGRAY);

    //��֤A��
    puthz(10, 43, "�����Ƽ�", 16, 16, YELLOW);
    puthz(10, 63, "��������", 16, 16, YELLOW);
    puthz(10, 83, "�����ѧ", 16, 16, YELLOW);
    puthz(10, 103, "�ķ�ɷ�",16,16, YELLOW);
    puthz(10, 123, "����Ƽ�", 16,16,YELLOW);
    puthz(10, 143, "��������", 16,16,YELLOW);
    puthz(10, 163, "��������", 16,16,YELLOW);
    puthz(10, 183, "���ϴ�ý", 16,16,YELLOW);
    puthz(10, 203, "�����", 16,16,YELLOW);
    puthz(10, 223, "������", 16,16,YELLOW);
    puthz(10, 243, "����ʳƷ", 16,16,YELLOW);
    puthz(10, 263, "��������", 16,16,YELLOW);
    puthz(10, 283, "��ó����", 16, 16, YELLOW);
    puthz(10, 303, "��ԭ�Ҿ�", 16, 16, YELLOW);
    puthz(10, 323, "�����ɷ�", 16, 16, YELLOW);
    puthz(10, 343, "���Ƹ�", 16, 16, YELLOW);
    puthz(10, 363, "���Ĺɷ�", 16, 16, YELLOW);
    puthz(10, 383, "��Դ�Ƽ�", 16, 16, YELLOW);
    puthz(10, 403, "������", 16, 16, YELLOW);
    puthz(10, 423, "�����Ƽ�", 16, 16, YELLOW);
    puthz(10, 443, "���ڿƼ�", 16, 16, YELLOW);

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
    puthz(330, 243, "���ƾ���", 16, 16, YELLOW);
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
    
    setfillstyle(SOLID_FILL, WHITE);
    for (i = 0; i < 21; i++ ) {
        bar(125, 46 + 20 * i, 135, 56 + 20 * i);
    }
    for (i = 0; i < 21; i++) {
        bar(445, 46 + 20 * i, 455, 56 + 20 * i);
    }
    
    setcolor(RED);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    //��ָ֤������
    outtextxy(192, 41, "2.72%");
    outtextxy(192, 61, "1.40%");
    outtextxy(192, 81, "1.31%");
    outtextxy(192, 101, "1.26%");
    outtextxy(192, 121, "1.18%");
    outtextxy(192, 141, "1.10%");
    outtextxy(192, 161, "1.05%");
    outtextxy(192, 181, "0.92%");
    outtextxy(192, 201, "0.90%");
    outtextxy(192, 221, "0.85%");
    outtextxy(192, 241, "0.79%");
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
    outtextxy(512, 241, "1.29%");
    //��ָ֤���Ƿ�
    outtextxy(263, 41, "20.01%");
    outtextxy(263, 61, "20.00%");
    outtextxy(263, 81, "19.96%");
    outtextxy(263, 101, "19.23%");
    outtextxy(263, 121, "17.25%");
    outtextxy(263, 141, "12.73%");
    outtextxy(263, 161, "11.98%");
    outtextxy(263, 181, "10.54%");
    outtextxy(263, 201, "10.23%");
    outtextxy(269, 221, "8.74%");
    outtextxy(268, 241, "7.56%");
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
    outtextxy(589, 241, "7.34%");

    setcolor(GREEN);
    //��ָ֤������
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
    //��ָ֤������
    outtextxy(508, 261, "-1.99%");
    outtextxy(508, 281, "-1.90%");
    outtextxy(508, 301, "-1.60%");
    outtextxy(508, 321, "-1.42%");
    outtextxy(508, 341, "-1.26%");
    outtextxy(508, 361, "-1.21%");
    outtextxy(508, 381, "-1.13%");
    outtextxy(508, 401, "-1.10%");
    outtextxy(508, 421, "-0.95%");
    outtextxy(508, 441, "-0.94%");
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
    //��ָ֤������
    outtextxy(574, 261, "-19.57%");
    outtextxy(574, 281, "-13.42%");
    outtextxy(574, 301, "-12.38%");
    outtextxy(574, 321, "-11.90%");
    outtextxy(574, 341, "-11.81%");
    outtextxy(574, 361, "-11.15%");
    outtextxy(574, 381, "-10.93%");
    outtextxy(574, 401, "-10.87%");
    outtextxy(574, 421, "-10.26%");
    outtextxy(580, 441, "-9.98%");
}


void draw_news() {
	char str[20][50];
	{
		FILE* fp1 = fopen("C:\\1.txt", "r");
		FILE* fp2 = fopen("C:\\2.txt", "r");
		FILE* fp3 = fopen("C:\\3.txt", "r");
		FILE* fp4 = fopen("C:\\4.txt", "r");
		FILE* fp5 = fopen("C:\\5.txt", "r");
		fgets(str[0], 25, fp1);
		fgets(str[1], 25, fp2);
		fgets(str[2], 25, fp3);
		fgets(str[3], 25, fp4);
		fgets(str[4], 25, fp5);
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		fclose(fp4);
		fclose(fp5);
	}

	{
		FILE* fp6 = fopen("C:\\6.txt", "r");
		FILE* fp7 = fopen("C:\\7.txt", "r");
		FILE* fp8 = fopen("C:\\8.txt", "r");
		FILE* fp9 = fopen("C:\\9.txt", "r");
		FILE* fp10 = fopen("C:\\10.txt", "r");
		fgets(str[5], 25, fp6);
		fgets(str[6], 25, fp7);
		fgets(str[7], 25, fp8);
		fgets(str[8], 25, fp9);
		fgets(str[9], 25, fp10);
		fclose(fp6);
		fclose(fp7);
		fclose(fp8);
		fclose(fp9);
		fclose(fp10);
	}

	{
		FILE* fp11 = fopen("C:\\11.txt", "r");
		FILE* fp12 = fopen("C:\\12.txt", "r");
		FILE* fp13 = fopen("C:\\13.txt", "r");
		FILE* fp14 = fopen("C:\\14.txt", "r");
		FILE* fp15 = fopen("C:\\15.txt", "r");
		fgets(str[10], 25, fp11);
		fgets(str[11], 25, fp12);
		fgets(str[12], 25, fp13);
		fgets(str[13], 25, fp14);
		fgets(str[14], 25, fp15);
		fclose(fp11);
		fclose(fp12);
		fclose(fp13);
		fclose(fp14);
		fclose(fp15);
	}

	{
		FILE* fp16 = fopen("C:\\16.txt", "r");
		FILE* fp17 = fopen("C:\\17.txt", "r");
		FILE* fp18 = fopen("C:\\18.txt", "r");
		FILE* fp19 = fopen("C:\\19.txt", "r");
		FILE* fp20 = fopen("C:\\20.txt", "r");
		fgets(str[15], 25, fp16);
		fgets(str[16], 25, fp17);
		fgets(str[17], 25, fp18);
		fgets(str[18], 25, fp19);
		fgets(str[19], 25, fp20);
		fclose(fp16);
		fclose(fp17);
		fclose(fp18);
		fclose(fp19);
		fclose(fp20);
	}

	{
		int i;
		cleardevice();
		setbkcolor(LIGHTGRAY);
		draw_home();

		setcolor(RED);
		rectangle(3, 28, 6, 31);
		rectangle(9, 28, 12, 31);
		rectangle(3, 34, 6, 37);
		setfillstyle(SOLID_FILL, RED);
		bar(9, 34, 12, 37);
		puthz(16, 25, "财经新闻", 16, 16, RED);

		line(0, 44, 640, 44);
		puthz(16, 48, "国际财经", 16, 16, LIGHTGREEN);
		line(310, 44, 310, 480);
		puthz(336, 48, "国内财经", 16, 16, LIGHTGREEN);

		setcolor(BLUE);
		setfillstyle(SOLID_FILL, BLUE);
		for (i = 0; i < 10; i++) {

			circle(8, 75 + 23 * i, 2);
			floodfill(8, 75 + 23 * i, BLUE);
			puthz(16, 67 + 23 * i, str[i], 16, 16, 8);
			outtextxy(215, 69 + 23 * i, "...");

			circle(328, 75 + 23 * i, 2);
			floodfill(328, 75 + 23 * i, BLUE);
			puthz(336, 67 + 23 * i, str[i + 10], 16, 16, 8);
			outtextxy(536, 69 + 23 * i, "...");
		}
	}
}


/*
//���ƹ�Ʊ��������
void draw_analysis() {
    int i;
    draw_home();
    setcolor(BLACK);
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
    puthz(420, 21, "������ѡ", 16, 16, GREEN);
    setcolor(MAGENTA);
    outtextxy(500, 18, "01");
    puthz(524, 22, "��������", 16, 16, MAGENTA);
    puthz(600, 21, "����", 16, 16, CYAN);
}*/



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


//���Ԥ�������������
void draw_gene_pred(const stock_data* stock)
{
    char pro[2], str[5][5];
    float probability;
    FILE* fp = open_file(stock->code, GENE, "rb");
    individual_data best;
    feature_data last;
    SAFE_READ(&best, sizeof(individual_data), 1, fp);
    SAFE_READ(&last, sizeof(feature_data), 1, fp);
    SAFE_READ(&probability, sizeof(float), 1, fp);
    close_file(fp, stock->code, ".gene");

    //������ת��Ϊ����������ַ���
    sprintf(pro, "%d", probability * 100);
    sprintf(str[0], "%.2f", MA_cross);
    sprintf(str[1], "%.2f", EXPMA_cross);
    sprintf(str[2], "%.2f", XS_channel);
    sprintf(str[3], "%.2f", KDJ_status);
    sprintf(str[4], "%.2f", MACD_change);

    //��ӡ����������
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(115 - 3, 200, str[0]);
    outtextxy(115 - 3, 220, str[1]);
    outtextxy(115 - 3, 245, str[2]);
    outtextxy(115 - 3, 265, str[3]);
    outtextxy(115 - 3, 287, str[4]);

    //��ӡ���ǻ��µ�����
    setcolor(LIGHTCYAN);
    outtextxy(110, 350, ":");
    settextstyle(SMALL_FONT, HORIZ_DIR, 8);
    outtextxy(120, 347, pro);//����ֵ����(120��347)����Ϊ8��
    outtextxy(150, 348, "%");
    if (probability > 0.5) {
        puthz(10, 350, "���Ǹ���", 24, 24, LIGHTCYAN);
    }
    else {
        puthz(10, 350, "�µ�����", 24, 24, LIGHTCYAN);
    }
}



void draw_ar_pred(const stock_data* stock, rectangle_info* rectangle, axis_data* axis)
{
    FILE* predfp;
    int real_days;
    float* pred_buffer;
    most_value most;
    int i;
    float* xy_buffer;

    predfp = open_file(stock->code, PRED, "rb");
    real_days = 3;
    fseek(predfp, -sizeof(float) * (FORECAST_DAYS + real_days) + sizeof(most_value), SEEK_END);
    pred_buffer = (float*)safe_calloc(FORECAST_DAYS + real_days, sizeof(float));
    SAFE_READ(pred_buffer, sizeof(float), FORECAST_DAYS + real_days, predfp);
    most.max = -FLT_MAX;
    most.min = FLT_MAX;
    for (i = 0; i < real_days + FORECAST_DAYS; i++)
    {
        most.max = most.max > pred_buffer[i] ? most.max : pred_buffer[i];
        most.min = most.min < pred_buffer[i] ? most.min : pred_buffer[i];
    }
    write_axis_number(&most, axis);
    close_file(predfp, stock->code, ".pred");
    xy_buffer = (float*)safe_malloc(sizeof(int) * 2 * (FORECAST_DAYS + real_days));
    calculate_xy(pred_buffer, xy_buffer, &rectangle, &axis);
    setlinestyle(SOLID_LINE, 0, 1);
    drawpoly(real_days, xy_buffer);
    setlinestyle(DOTTED_LINE, 0, 1);
    drawpoly(FORECAST_DAYS, xy_buffer + real_days * 2);
    free(pred_buffer);
    free(xy_buffer);
}


