#include<stdio.h>
#include<graphics.h>
#include "hzo.h"

void move_search()
{
	cleardevice();
	setbkcolor(WHITE);

	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(230, 160, 410, 260);
	puthz(248, 190, "∑÷Œˆ‘§≤‚÷–£¨«Î…‘∫Û", 16, 16, WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(280, 230, 360, 240);
	setfillstyle(SOLID_FILL, 8);

	for (i = 0; i < 21; i++) {
		setcolor(BLUE);
		circle(70 + i * 25, 60, 20);
		line(80 + i * 25, 76, 90 + i * 25, 92);
		bar(280, 230, 280 + i * 4, 240);
		delay(350);
		setcolor(WHITE);
		circle(70 + i * 25, 60, 20);
		line(80 + i * 25, 76, 90 + i * 25, 92);
	}
		
}