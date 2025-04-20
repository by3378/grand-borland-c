#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <bios.h>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include"hzo.h"
//void draw_analysis();
void draw_home();
//void draw_wenxiaoda();
//void draw_search();
//void draw_stock();
//void draw_welcome();
//void draw_register();
//void draw_tongdaxin();
void draw_predict();
void main() {
    int gd = VGA;
    int gm = VGAHI;
    initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");
    //draw_register();
    //draw_welcome();
    //mouseinit();
    //draw_all_analysis();
    //draw_home();
    //draw_stock();
   // draw_wenxiaoda();
    //draw_search();
    draw_predict();
    getchar();
}

/*
//绘制注册界面
void draw_register()
{
    setbkcolor(WHITE);
    draw_tongdaxin();
    setcolor(LIGHTRED);

    rectangle(160, 230, 160 + 320, 230 + 32);
    rectangle(160, 278, 160 + 320, 278 + 32);

    setcolor(LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 0);
    puthz(165, 240, "账户", 16, 16, LIGHTGRAY);
    outtextxy(200, 240, ":");
    puthz(165, 275 + 14, "密码", 16, 16, LIGHTGRAY);
    outtextxy(200, 289, ":");

    puthz(210, 140, "股市如战场", 16, 16, LIGHTGRAY);
    puthz(310, 140, "智者勇攀财富高峰", 16, 16, LIGHTGRAY);
    puthz(240, 188, "请注册账户", 32, 32, LIGHTCYAN);

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(640 - 16 - 48, 480 - 16 - 32, 640 - 16, 480 - 16);
    puthz(640 - 16 - 48 + 9, 480 - 16 - 32 + 8, "退出", 16, 16, WHITE);

    bar(160, 278 + 64, 160 + 320, 278 + 64 + 32);
    puthz(295, 278 + 71, "注册", 16, 16, WHITE);

    
}



//打印艺术字体“通达信”
void draw_tongdaxin() {
    puthz(200, 40, "通", 48, 48, BLUE);

    setlinestyle(0, 0, 3);
    setcolor(BLUE);
    circle(380 - 80, 50, 2);
    floodfill(380 - 80, 50, BLUE);
    line(379 - 80, 50, 381 - 80, 50);
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
    //画“达”

    puthz(400, 40, "信", 48, 48, BLUE);
}*/

/*
//绘制登录界面
void draw_welcome()
{
    setbkcolor(WHITE);
    draw_tongdaxin();

    setcolor(LIGHTRED);
    rectangle(160, 230, 160 + 320, 230 + 32);
    rectangle(160, 278, 160 + 320, 278 + 32);

    setcolor(LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 0);
    puthz(164, 160, "模拟股票行情预测系统", 32, 32, LIGHTCYAN);
    puthz(165, 240, "账户", 16, 16, LIGHTGRAY);
    outtextxy(200, 242, ":");
    puthz(165, 288, "密码", 16, 16, LIGHTGRAY);
    outtextxy(200, 290, ":");

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(576, 432, 624, 464);
    puthz(640 - 16 - 48 + 8, 480 - 16 - 32 + 6, "退出", 16, 16, WHITE);

    bar(160, 342, 480, 374);
    puthz(294, 348, "登录", 16, 16, WHITE);


    bar(250, 380, 370, 415);
    puthz(278, 390, "注册账号", 16, 16, WHITE);

}



/*void analysis_page(int* pattern) {/*640*480*/
    /*cleardevice();
    clrmous(MouseX, MouseY);
    draw_analysis();
    /*while (bioskey(1))
        bioskey(0);

    while (1)
    {



    }


}*//*
void draw_analysis() {
    int i;
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

    puthz(10, 21, "日线", 16, 16, LIGHTGRAY);
    puthz(50, 21, "周线", 16, 16, LIGHTGRAY);
    setcolor(LIGHTBLUE);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(95, 21, "MA");
    puthz(110, 21, "均线", 16, 16, LIGHTBLUE);
    outtextxy(155, 21, "EXPMA");
    puthz(195, 21, "均线", 16, 16, LIGHTBLUE);
    puthz(238, 21, "薛斯通道",16,16,LIGHTBLUE);
    setcolor(YELLOW);
    settextstyle(SMALL_FONT, HORIZ_DIR, 7);
    outtextxy(315, 18, "KDJ");
    outtextxy(360, 18, "MACD");
    puthz(420, 21, "加入自选", 16, 16, GREEN);
    setcolor(MAGENTA);
    outtextxy(500, 18, "01");
    puthz(524, 22, "华中数控", 16, 16, MAGENTA);
    puthz(600, 21, "返回", 16, 16, CYAN);
}*/

void draw_home() 
{
    setcolor(WHITE);
    rectangle(0, 0, 640, 20);
    floodfill(1, 1, WHITE);
    puthz(10, 1, "通达信金融端", 16, 16, 0);
    puthz(130, 1, "行情",16,16,0);
    puthz(180, 1, "市场", 16, 16, 0);
    puthz(230, 1, "问小达", 16, 16, 0);
    setcolor(BLACK);
    outtextxy(470, 7, "19:21:26");
    puthz(550, 1, "周四", 16, 16, 0);
    puthz(600, 1, "退出", 16, 16, 0);
}

/*
void draw_stock(){
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    rectangle(0, 20, 640, 480);
    floodfill(50, 50, BLACK);
    setcolor(RED);
    rectangle(0, 20, 640, 40);
    puthz(5, 21, "添加", 16, 16, LIGHTCYAN);
    setcolor(LIGHTCYAN);
    settextstyle(SMALL_FONT, HORIZ_DIR, 8);
    outtextxy(36, 14, "+");
    puthz(80, 21, "代码", 16, 16, LIGHTGRAY);
    puthz(150, 21, "名称", 16, 16, LIGHTGRAY);
    puthz(230, 21, "今开", 16, 16, LIGHTGRAY);
    puthz(290, 21, "最高", 16, 16, LIGHTGRAY);
    puthz(350, 21, "最低", 16, 16, LIGHTGRAY);
    puthz(410, 21, "昨收", 16, 16, LIGHTGRAY);
    puthz(470, 21, "细分行业", 16, 16, LIGHTGRAY);
    puthz(570, 21, "地区", 16, 16, LIGHTGRAY);


}*/

void draw_wenxiaoda() {

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    setcolor(LIGHTGRAY);
    rectangle(0, 22, 640, 480);
    floodfill(50, 50, LIGHTGRAY);//设置背景颜色
    
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
    //画“问”

    puthz(300, 40, "小", 48, 48, BLUE);

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
    //画“达”

    puthz(210, 110, "智能投资顾问", 16, 16, BLACK);
    puthz(320, 110, "开启财富新航线", 16, 16, BLACK);
}
/*
void draw_search() {

    setcolor(RED);
    circle(180, 230, 40);
    setcolor(LIGHTGRAY);
    bar(180, 190, 450, 270);
    setcolor(RED);
    rectangle(180, 190, 430, 270);
    setcolor(LIGHTGRAY);
    line(180, 192, 180, 268);
    setcolor(BLUE);
    rectangle(431, 190, 480,270);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(450, 200, BLUE);
    circle(480, 230, 40);
    floodfill(483, 230, BLUE);
    setcolor(WHITE);
    circle(465, 225, 18);
    line(478, 238, 488, 248);
    puthz(181, 220, "请输入股票代码", 16, 16, BLACK);
 
}*/


void draw_predict() {
    draw_home();
    draw_wenxiaoda();

    puthz(10, 35, "股票代码",16, 16, BLACK);//代码坐标：（87，32）字体6号
    setcolor(BLACK);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(78, 32, ":");
    outtextxy(78, 57, ":");
    setcolor(BLACK);
    puthz(10, 60, "股票名称", 16, 16, BLACK);//名称坐标：（85，60）字体16号

    //画左侧指标表格
    setcolor(BLACK);
    puthz(34, 179, "指标", 16, 16, BLACK);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(40, 200, "MA");
    outtextxy(30, 220, "EXPMA");
    puthz(20, 245, "薛氏通道", 16, 16, BLACK);
    outtextxy(35, 265, "KDJ");
    outtextxy(32, 287, "MACD");
    puthz(119, 179, "权重", 16, 16, BLACK);
    outtextxy(137, 200, "%");//数字坐标：（115，200）字体为6号
    outtextxy(137, 220, "%");//数字坐标：（115，220）
    outtextxy(137, 245, "%");//数字坐标：（115，245）
    outtextxy(137, 265, "%");//数字坐标：（115，265）
    outtextxy(137, 287, "%");//数字坐标：（115，287）
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

    //画右侧坐标轴
    line(590, 300, 590, 170);
    line(590, 300, 440, 300);
    line(590, 170, 585, 180);
    line(590, 170, 595, 180);
    line(440, 300, 450, 295);
    line(440, 300, 450, 305);

    //画右侧时间价格表格
    puthz(248, 160, "日期", 16, 16, BLACK);
    puthz(349, 160, "价格", 16, 16, BLACK);
    rectangle(215, 150, 413, 335);
    line(319, 150, 319, 335);
    line(215, 185, 413, 185);
    line(215, 215, 413, 215);
    line(215, 245, 413, 245);
    line(215, 275, 413, 275);
    line(215, 305, 413, 305);//第一行：日期坐标（224，191），价格坐标（331，191），RMB坐标（389，193），每行y递增30，六号字体
    

    puthz(10, 350, "上涨概率", 24, 24, LIGHTCYAN);
    setcolor(LIGHTCYAN);
    outtextxy(110, 350, ":");
    settextstyle(SMALL_FONT, HORIZ_DIR, 8);
    outtextxy(150, 348, "%");//概率值坐标(120，347)字体为8号

    puthz(10, 400, "通达信提醒您", 16, 16, BLACK);
    setcolor(BLACK);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(110, 398, ":");
    puthz(10, 430, "本系统预测结果仅供参考，股市有风险，投资需谨慎！", 16, 16, BLACK);

    setfillstyle(SOLID_FILL, LIGHTGREEN);
    bar(570, 30, 630, 60);
    puthz(576, 33, "返回", 24, 24, BLACK);
}
