#include "global.h"

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


bool check_info( const user_data* user )
{
    char filename[FILE_LEN];
    strcpy( filename, DIRECTORY);
    strcat( filename, user->name);
    strcat( filename, ".cho");

    bool flag = false;
    FILE* fp = fopen( user->name, "rb");
    if( fp != NULL )
    {
        user_data temp;
        SAFE_READ( &temp, sizeof(user_data), 1, fp);
        if ( strcmp(user->password, temp.password) == 0)
            flag = true;
        close_file( fp, user->name, ".cho");
    }
    return flag;
}


void save_account(const user_data* user)
{
    FILE* fp = open_file( user->name, CHOICE, "wb");
    int* choice = safe_calloc( STOCK_NUM, sizeof(int) );
    SAFE_WRITE( user, sizeof(user_data), 1, fp);
    SAFE_WRITE( choice, sizeof(int), STOCK_NUM, fp);
    close_file( fp, user->name, ".cho");

}