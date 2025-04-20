#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <graphics.h>
#include <dos.h>
#include "use.h"
#include "file.h"
#include "draw.h"
#include "hzo.h"

//打印艺术字体“通达信”
void draw_tongdaxin() {
    puthz(200, 40, "通", 48, 48, BLUE);

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
    //画“达”

    puthz(400, 40, "信", 48, 48, BLUE);
}



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

    setfillstyle(SOLID_FILL, 8);
    bar(576, 432, 636, 462);
    puthz(584, 438, "退出", 24, 24, WHITE);

    bar(160, 342, 480, 374);
    puthz(294, 348, "登录", 16, 16, WHITE);


    bar(250, 380, 370, 415);
    puthz(278, 390, "注册账号", 16, 16, WHITE);
}



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

    setfillstyle(SOLID_FILL, 8);
    bar(576, 432, 636, 462);
    puthz(585, 440, "返回", 24, 24, WHITE);

    bar(160, 278 + 64, 160 + 320, 278 + 64 + 32);
    puthz(295, 278 + 71, "注册", 16, 16, WHITE);
}



//绘制主菜单栏
void draw_home()
{
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(0, 0, 640, 20);
   // floodfill(1, 1, BLACK);
    floodfill(1, 1, 1);
    puthz(10, 2, "通达信金融端", 16, 16, 8);
    puthz(130, 2, "行情", 16, 16, 8);
    puthz(180, 2, "市场", 16, 16, 8);
    puthz(230, 2, "问小达", 16, 16, 8);
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(470, 2, "19:21:26");
    puthz(550, 2, "周四", 16, 16, 8);
    puthz(600, 2, "退出", 16, 16, 8);
}



//绘制自选股界面
void draw_stock() {
    draw_home();
    setcolor(8);
    setfillstyle(SOLID_FILL, 8);
    rectangle(0, 20, 640, 480);
    floodfill(50, 50, 8);
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
}


//绘制市场界面
void draw_market() {
    int i;
    draw_home();

    //画框架
    setcolor(RED);
    rectangle(0, 21, 639, 479);
    floodfill(50, 70, 0);
    rectangle(0, 21, 320, 479);
    rectangle(0, 21, 639, 40);
    line(0, 262, 639, 262);

    puthz(10, 23, "上证", 16, 16, LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    setcolor(LIGHTGRAY);
    outtextxy(45, 21, "A");
    puthz(54, 23, "股", 16, 16, LIGHTGRAY);
    puthz(100, 23, "添加自选", 16, 16, LIGHTGRAY);
    puthz(190, 23, "涨跌速", 16, 16, LIGHTGRAY);
    puthz(265, 23, "涨跌幅", 16, 16, LIGHTGRAY);
 
    puthz(330, 23, "深证", 16, 16, LIGHTGRAY);
    outtextxy(365, 21, "A");
    puthz(374, 23, "股", 16, 16, LIGHTGRAY);
    puthz(420, 23, "添加自选", 16, 16, LIGHTGRAY);
    puthz(510, 23, "涨跌速", 16, 16, LIGHTGRAY);
    puthz(585, 23, "涨跌幅", 16, 16, LIGHTGRAY);

    //上证A股
    puthz(10, 43, "华工科技", 16, 16, YELLOW);
    puthz(10, 63, "华中数控", 16, 16, YELLOW);
    puthz(10, 83, "中润光学", 16, 16, YELLOW);
    puthz(10, 103, "文峰股份",16,16, YELLOW);
    puthz(10, 123, "保锐科技", 16,16,YELLOW);
    puthz(10, 143, "国芳集团", 16,16,YELLOW);
    puthz(10, 163, "重庆银行", 16,16,YELLOW);
    puthz(10, 183, "中南传媒", 16,16,YELLOW);
    puthz(10, 203, "中毅达", 16,16,YELLOW);
    puthz(10, 223, "大名城", 16,16,YELLOW);
    puthz(10, 243, "紫燕食品", 16,16,YELLOW);
    puthz(10, 263, "碧兴物联", 16,16,YELLOW);
    puthz(10, 283, "华贸物流", 16, 16, YELLOW);
    puthz(10, 303, "中原家具", 16, 16, YELLOW);
    puthz(10, 323, "新赛股份", 16, 16, YELLOW);
    puthz(10, 343, "连云港", 16, 16, YELLOW);
    puthz(10, 363, "华纺股份", 16, 16, YELLOW);
    puthz(10, 383, "力源科技", 16, 16, YELLOW);
    puthz(10, 403, "智洋创新", 16, 16, YELLOW);
    puthz(10, 423, "世华科技", 16, 16, YELLOW);
    puthz(10, 443, "灿勤科技", 16, 16, YELLOW);

    //深证A股
    puthz(330, 43, "达利凯普", 16, 16, YELLOW);
    puthz(330, 63, "硕贝德", 16, 16, YELLOW);
    puthz(330, 83, "新城市", 16, 16, YELLOW);
    puthz(330, 103, "慧瀚股份", 16, 16, YELLOW);
    puthz(330, 123, "金凯生科", 16, 16, YELLOW);
    puthz(330, 143, "兴源环境", 16, 16, YELLOW);
    puthz(330, 163, "矽电股份", 16, 16, YELLOW);
    puthz(330, 183, "澄天伟业", 16, 16, YELLOW);
    puthz(330, 203, "拓维信息", 16, 16, YELLOW);
    puthz(330, 223, "凯莱英", 16, 16, YELLOW);
    puthz(330, 243, "铭科精技", 16, 16, YELLOW);
    puthz(330, 263, "飞力达", 16, 16, YELLOW);
    puthz(330, 283, "三态股份", 16, 16, YELLOW);
    puthz(330, 303, "华融化学", 16, 16, YELLOW);
    puthz(330, 323, "飞沃科技", 16, 16, YELLOW);
    puthz(330, 343, "安居宝", 16, 16, YELLOW);
    puthz(330, 363, "怡达股份", 16, 16, YELLOW);
    puthz(330, 383, "南京港", 16, 16, YELLOW);
    puthz(330, 403, "吉峰科技", 16, 16, YELLOW);
    puthz(330, 423, "南方精工", 16, 16, YELLOW);
    puthz(330, 443, "名雕股份", 16, 16, YELLOW);
    
    setfillstyle(SOLID_FILL, WHITE);
    for (i = 0; i < 21; i++ ) {
        bar(125, 46 + 20 * i, 135, 56 + 20 * i);
    }
    for (i = 0; i < 21; i++) {
        bar(445, 46 + 20 * i, 455, 56 + 20 * i);
    }
    
    setcolor(RED);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    //上证指数涨速
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
    //深证指数涨速
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
    //上证指数涨幅
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
    //深证指数涨幅
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
    //上证指数跌速
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
    //深证指数跌速
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
    //上证指数跌幅
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
    //深证指数跌幅
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


/*
//绘制股票分析界面
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

    puthz(10, 21, "日线", 16, 16, LIGHTGRAY);
    puthz(50, 21, "周线", 16, 16, LIGHTGRAY);
    setcolor(LIGHTBLUE);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(95, 21, "MA");
    puthz(110, 21, "均线", 16, 16, LIGHTBLUE);
    outtextxy(155, 21, "EXPMA");
    puthz(195, 21, "均线", 16, 16, LIGHTBLUE);
    puthz(238, 21, "薛斯通道", 16, 16, LIGHTBLUE);
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



//绘制艺术字“问小达”
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

    puthz(210, 110, "智能投资顾问", 16, 16, 14);
    puthz(320, 110, "开启财富新航线", 16, 16, 14);
}




//绘制问小达搜索界面
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
    puthz(181, 220, "请输入股票代码", 16, 16, 8);
    setfillstyle(SOLID_FILL, 15);
    floodfill(181, 220, RED);
}



//绘制问小达预测界面
void draw_predict() {
    draw_home();
    draw_wenxiaoda();

    puthz(10, 35, "股票代码", 16, 16, 8);//代码坐标：（87，32）字体6号
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(78, 32, ":");
    outtextxy(78, 57, ":");
    setcolor(8);
    puthz(10, 60, "股票名称", 16, 16, 8);//名称坐标：（85，60）字体16号

    //画左侧指标表格
    setcolor(8);
    puthz(34, 179, "指标", 16, 16, 8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(40, 200, "MA");
    outtextxy(30, 220, "EXPMA");
    puthz(20, 245, "薛氏通道", 16, 16, 8);
    outtextxy(35, 265, "KDJ");
    outtextxy(32, 287, "MACD");
    puthz(119, 179, "权重", 16, 16, 8);
    outtextxy(137+5, 200, "%");//数字坐标：（115，200）字体为6号
    outtextxy(137+5, 220, "%");//数字坐标：（115，220）
    outtextxy(137+5, 245, "%");//数字坐标：（115，245）
    outtextxy(137+5, 265, "%");//数字坐标：（115，265）
    outtextxy(137+5, 287, "%");//数字坐标：（115，287）
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
    puthz(248, 160, "日期", 16, 16, 8);
    puthz(349, 160, "价格", 16, 16, 8);
    rectangle(215, 150, 413, 335);
    line(319, 150, 319, 335);
    line(215, 185, 413, 185);
    line(215, 215, 413, 215);
    line(215, 245, 413, 245);
    line(215, 275, 413, 275);
    line(215, 305, 413, 305);//第一行：日期坐标（224，191），价格坐标（331，191），RMB坐标（389，193），每行y递增30，六号字体

    puthz(10, 400, "通达信提醒您", 16, 16, 8);
    setcolor(8);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(110, 398, ":");
    puthz(10, 430, "本系统预测结果仅供参考，股市有风险，投资需谨慎！", 16, 16, 8);

    setfillstyle(SOLID_FILL, 8);
    bar(570, 30, 630, 60);
    puthz(576, 33, "返回", 24, 24, 8);
}


//填充预测界面左侧的数据
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

    //将数字转化为可以输出的字符串
    sprintf(pro, "%d", probability * 100);
    sprintf(str[0], "%.2f", MA_cross);
    sprintf(str[1], "%.2f", EXPMA_cross);
    sprintf(str[2], "%.2f", XS_channel);
    sprintf(str[3], "%.2f", KDJ_status);
    sprintf(str[4], "%.2f", MACD_change);

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



void write_axis_number(const most_value* most, axis_data* axis)
{
    int gap;
    float unit_gap;
    float marks[] = { 0.1f, 0.5f, 1, 2, 5, 10, 20, 50, 100 };
    int mark_num;
    int i;
    int unit_length;
    char buffer[6];
    int mark_y;
    float mark_value;

    gap = most->max - most->min;
    mark_num = sizeof(marks) / sizeof(marks[0]);
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



/* choose_gear function 
void choose_rectangle( rectangle_info* rectangle , enum gear_type gear)
{
    switch( gear )
    {
        case SMALL:
        {
            rectangle->width = ;
            rectangle->gap = ;
            rectangle->num = 63;
            break;
        } /* 63 rectangles 
        case MEDIUM:
        {
            rectangle->width = ;
            rectangle->gap = ;
            rectangle->num = 35;
            break;
        } /* 35 rectangles 
        case LARGE:
        {
            rectangle->width = ;
            rectangle->gap = ;
            rectangle->num = 14;
            break;
        } /* 14 rectangles 
    }
}




FILE* choose_line( const char* code , enum line_type type , int* line_num , enum bool* ismain )
{
    FILE* fp;
    switch( type )
    {
        case KDAY:
        {
            *line_num = 1;
            *ismain = false;/* 
            fp = open_file( code , ".kday", "rb+");
        }
        case KWEEK:
        {
            *line_num = 1;
            *ismain = false;/* 
            fp = open_file( code , ".kweek", "rb+");
        }
        case MA:
        {
            *line_num = 3;
            *ismain = true;
            fp = open_file( code , ".ma", "rb+");
        }
        case EXPMA:
        {
            *line_num = 2;
            *ismain = true;
            fp = open_file( code , ".expma", "rb+");
        }
        case XUECHI:
        {
            *line_num = 4;
            *ismain = true;
            fp = open_file( code , ".xuechi", "rb+");
        }
        case KDJ:
        {
            *line_num = 3;
            *ismain = false;
            fp = open_file( code , ".kdj", "rb+");
        }
        case MACD:
        {
            *line_num = 3;
            *ismain = false;
            fp = open_file( code , ".macd", "rb+");
        }
        case PRED:
        {
            *line_num = 1;
            *ismain = false;
            fp = open_file( code , ".pred", "rb+");
        }
    }
    return fp;

}




/* get the most value of the last "num" data  
void get_most( const stock_data* stock, enum line_type type , int num, most_value* most)
{
    int line_num;
    enum bool ismain;
    FILE* fp = choose_line( stock->code, type , &line_num , &ismain);

    most->max = -FLT_MAX;
    most->min = FLT_MAX;

    most_value* buffer = (most_value* )safe_malloc( num * sizeof(most_value));

    fseek( fp, -sizeof(most_value)*num, SEEK_END );
    SAFE_READ( buffer, sizeof(most_value), num, fp );

    close_file( fp, stock->code, ".who cares" );
    for( int i=0; i<num; i++ )
    {
        most->max = buffer[i].max > most->max ? buffer[i].max : most->max;
        most->min = buffer[i].min < most->min ? buffer[i].min : most->min;
    }
    free(buffer);

    if( !ismain )
        return;
    else
    {
        most_value most2;
        get_most( stock, KDAY , num, &most2);
        most->max = most2.max > most->max ? most2.max : most->max;
        most->min = most2.min < most->min ? most2.min : most->min;
        return;
    }

}





void draw_line( const stock_data* stock, const rectangle_info* rectangle, enum line_type type, const axis_data* axis )
{
    most_value most;
    get_most( stock, type, rectangle->num/stock->period_length, &most);
    write_axis_number( &most, axis);

    int line_num;
    enum bool ismain;
    FILE* fp = choose_line( stock->code, type , &line_num , &ismain);

    if( type == KDAY || type == KWEEK ) 
        draw_kline( fp, type, stock, rectangle, axis);
    else if( type == MACD )  /* column type sub indicator
        draw_macd( fp, stock, rectangle, axis);
    else if( !ismain )       /* line type sub indicator
        draw_simple_line( fp, line_num, stock, rectangle, axis);        
    else if( ismain )        /* draw main indicator with KDAY 
    {
        draw_simple_line( fp, line_num, stock, rectangle, axis);
        draw_kline( fp, KDAY, stock, rectangle, axis);
    }

    close_file( fp, stock->code, ".whatever" );
}*/



/*
void draw_ar_pred( const stock_data* stock, rectangle_info* rectangle, axis_data* axis )
{
    FILE* predfp = open_file( stock->code , ".pred", "rb");
    most_value most;
    int real_days = 3;
    fseek( predfp, -sizeof(float)*(FORECAST_DAYS+real_days)+sizeof(most_value), SEEK_END );

    float* pred_buffer = (float* )safe_calloc( FORECAST_DAYS+real_days, sizeof(float));
    SAFE_READ( pred_buffer, sizeof(float), FORECAST_DAYS+real_days, predfp );

    SAFE_READ( &most, sizeof(most_value), 1, predfp );
    write_axis_number( &most, axis);

    close_file( predfp, stock->code, ".pred" );

    float* xy_buffer = (float*)safe_malloc( sizeof(int) * 2 * (FORECAST_DAYS+real_days) );
    calculate_xy( pred_buffer, xy_buffer, &rectangle, &axis );
    
    setlinestyle( SOLID_LINE, 0, 1 );
    drawpoly( real_days, xy_buffer );
    setlinestyle( DOTTED_LINE, 0, 1 );
    drawpoly( FORECAST_DAYS, xy_buffer+real_days*2 );

    free(pred_buffer);
    free(xy_buffer);
    
}*



/*
void draw_kline( FILE* fp , enum line_type type, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis )
{

    // has defined: typedef day_price week_data; 
    if( type == KDAY )
        fseek( fp, sizeof(day_price)*stock->days, SEEK_SET );
    else /* KWEEK 
        fseek( fp, sizeof(week_data)*stock->weeks, SEEK_SET );

    fseek( fp, -sizeof(day_price)*rectangle->num, SEEK_CUR );

    day_price info;
    enum COLORS color;
    int high_y, low_y, open_y, close_y;  // Y coordinates 
    int present_x = axis->x - rectangle->gap*rectangle->num;
    int half_width = ROUND(rectangle->width/2);

    assert( present_x >= 0 ); //check if the num is too large 

    for( int i = 0; i < rectangle->num ; i++ , present_x += rectangle->gap )
    {

        SAFE_READ( &info, sizeof(day_price), 1, fp );

        if( info.close > info.open )
            color = RED;
        else
            color = GREEN;
        setcolor( color );
        setfillpattern( SOLID_FILL, color );

        high_y = CALCULATE_Y( axis, info.high );
        low_y = CALCULATE_Y( axis, info.low );
        open_y = CALCULATE_Y( axis, info.open );
        close_y = CALCULATE_Y( axis, info.close );

        // draw kline 
        line( present_x, high_y, present_x, low_y );
        bar( present_x-half_width, open_y, present_x+half_width, close_y );
    }

    close_file( fp, stock->code, ".kday or .kweek" );
}
*/


/*
void draw_simple_line( FILE* fp , int line_num, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis )
{
    for( int p = 0; p < line_num; p++ )
    {
        float* buffer = (float* )safe_calloc( rectangle->num , sizeof(float));
        fseek( fp, sizeof(float)*stock->days*p, SEEK_SET );
        fseek( fp, -sizeof(float)*rectangle->num, SEEK_CUR );
        SAFE_READ( buffer, sizeof(float), rectangle->num, fp );

        int* xy_buffer = (int* )safe_malloc( rectangle->num*2 * sizeof(int));
        calculate_xy( buffer, xy_buffer, &rectangle, axis );

        drawpoly( rectangle->num, xy_buffer );
        free(buffer);
        free(xy_buffer);
    }
}




void calculate_xy( float* buffer, int* xy_buffer, const rectangle_info* rectangle , const axis_data* axis )
{
    int present_x = axis->x - rectangle->gap*rectangle->num;

    assert( present_x >= 0 ); /* check if the num is too large 

    for( int i = 0; i < rectangle->num; i++, present_x += rectangle->gap )
    {
        xy_buffer[i*2] = present_x;
        xy_buffer[i*2+1] = CALCULATE_Y( axis, buffer[i] );
    }
}




void draw_macd( FILE* fp, const stock_data* stock, const rectangle_info* rectangle, const axis_data* axis )
{
    draw_simple_line( fp, 2, stock, rectangle, axis);

    float* buffer = (float* )safe_calloc( rectangle->num , sizeof(float));
    fseek( fp, sizeof(float)*stock->days*3, SEEK_SET );
    fseek( fp, -sizeof(float)*rectangle->num, SEEK_CUR );
    SAFE_READ( buffer, sizeof(float), rectangle->num, fp );

    int* xy_buffer = (int* )safe_malloc( rectangle->num*2 * sizeof(int));
    calculate_xy( buffer, xy_buffer, &rectangle, axis );
    free(buffer);

    enum COLORS color;
    for( int i=0; i<rectangle->num; i++ )
    {
        if( buffer[i*2+1] > 0 )
            color = RED;
        else
            color = GREEN;
        setcolor( color );

        line( buffer[i*2], axis->y+axis->length , buffer[i*2], buffer[i*2+1] );
    }
    free(xy_buffer);
}*/


