#ifndef USER_H
#define USER_H

#include "global.h"

# define CHAR_WIDTH 16
# define CHAR_HEIGHT 16 /* depend on your font and size */
# define BACKSPACE 0x0E
# define ENTER 13

typedef struct
{
    char name[12];
    char password[12];
}user_data;


bool save_account(const user_data* user);
void get_input(int x, int y, char* str, int max, int min);
static void erase_char(int x, int y, int index);
bool check_info( const user_data* user );

#endif