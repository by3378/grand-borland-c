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
	//		page = page_welcome();//��¼����
	//	}
	//	case 2: {
	//		page = page_register();//ע�����
	//	}/*
	//	case 3: {
	//		page = page_stock();//������棬�ɲ鿴��ѡ��
	//	}
	//	case 4: {
	//		page = page_market();//�г����棬�������ѡ��
	//	}*/
	//	case 5: {
	//		page = page_search();//��С����������
	//	}
	//	/*case 6: {
	//		page = page_predict();//��С��Ԥ�����
	//	}
	//	case 7: {
	//		page = page_indicator();//��Ʊָ�����
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