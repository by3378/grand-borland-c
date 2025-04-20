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
#include "page.h"
#include "mouse.h"



void main() {
	
	//nt page = 1;
	int gd = VGA;
	int gm = VGAHI;
	initgraph(&gd, &gm, "C:\\borlandc\\BGI");
	mouseinit();
	

	//while (1) {
	//	switch (page) {

	//	case 1: {
	//		page = page_welcome();//登录界面
	//	}
	//	case 2: {
	//		page = page_register();//注册界面
	//	}/*
	//	case 3: {
	//		page = page_stock();//行情界面，可查看自选股
	//	}
	//	case 4: {
	//		page = page_market();//市场界面，可添加自选股
	//	}*/
	//	case 5: {
	//		page = page_search();//问小达搜索界面
	//	}
	//	/*case 6: {
	//		page = page_predict();//问小达预测界面
	//	}
	//	case 7: {
	//		page = page_indicator();//股票指标界面
	//	}*/
	//	}
	//}
	
	while (1) {
		if (page == 1) {
			page = page_welcome();
		}
		else if (page == 2) {
			page = page_register();
		}
		else if (page == 3) {
			page = page_stock();
		}
		else if (page == 4) {
			page = page_market();
		}
		else if (page == 5) {
			page = page_search();
		}
		else if (page == 6) {
			page = page_predict();
		}
	}
	
}