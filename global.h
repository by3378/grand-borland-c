#ifndef USE_H
#define USE_H

enum bool{ false, true };
void get_input(int x, int y, char* str, int max, int min);
static void erase_char(int x, int y, int index);
enum bool check_info(const struct info* user);
void show_guide(void);
struct info
{
    char name[12];
    char password[12];
};
void saveaccount(const struct info* user);

#endif