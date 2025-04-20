#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <bios.h>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <ctype.h>
#include <math.h>
#include "mouse.h"
#include "use.h"
#include "file.h"
#include "mouse.h"


# define CHAR_WIDTH 16
# define CHAR_HEIGHT 16 /* depend on your font and size */
# define BACKSPACE 0x0E
# define ENTER 13


void get_input(int x, int y, char* str, int max, int min)
{
    unsigned int ch;
    unsigned char ascii, scancode;
    char temp[2] = { 0 };
    int index = 0;

    clrmous(MouseX, MouseY);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    moveto(x, y);

    while (1)
    {
        while (!bioskey(1))
            continue;

        ch = bioskey(0);
        ascii = ch & 0xFF;
        scancode = ch >> 8;

        if (scancode == BACKSPACE)
        {
            if (index == 0)
                continue;

            str[--index] = 0;
            erase_char(x, y, index);
        }
        else if (ascii == ENTER)
        {
            if (index > min)
                break;

        }
        else if (isalnum(ascii))
        {
            if (index == max - 1)
                continue;

            temp[0] = ascii;
            str[index++] = ascii;
            outtext(temp);

        }

    }
    str[index] = 0;

}


static void erase_char(int x, int y, int index)
{
    x += index * CHAR_WIDTH;

    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y, x + CHAR_WIDTH, y + CHAR_HEIGHT);

    moveto(x, y);

}


enum bool check_info(const struct info* user)
{
    FILE* fp;
    struct info temp = { 0 };
    enum bool flag = false;

    if ((fp = fopen("user.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Error: Cannot open file 'user.dat'\n");
        exit(EXIT_FAILURE);
    }

    while (fread(&temp, sizeof(struct info), 1, fp) == 1)
    {
        if (strcmp(user->name, temp.name) == 0 && strcmp(user->password, temp.password) == 0)
            flag = true;
    }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Error in closing files\n");
        exit(EXIT_FAILURE);
    }

    return flag;

}


void show_guide(void)
{
    clrmous(MouseX, MouseY);
    cleardevice();
    setbkcolor(WHITE);
    setcolor(DARKGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 0);
}


//”√”⁄◊¢≤· ±¥Ê¥¢’À∫≈
void saveaccount(const struct info* user)
{
    FILE* fp;
    size_t written;
    fp = fopen("user.dat", "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "Error in opening the file\n");
        exit(EXIT_FAILURE);
    }

    written = fwrite(user, sizeof(struct info), 1, fp);
    if (written)
    {
        show_guide();
        outtextxy(300, 230, "Registration successful.");
        outtextxy(250, 250, "You will be redirected to the login page shortly.");
        delay(2000);

    }
    else
    {
        fprintf(stderr, "Error in writing to file\n");
        exit(EXIT_FAILURE);
    }


    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Error in closing files\n");
        exit(EXIT_FAILURE);
    }

}


