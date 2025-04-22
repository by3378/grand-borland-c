#include "global.h"

//enum button_type { SIMPLE, HOME, BACK, CHOOSE };

int button_simple(int x1, int y1, int x2, int y2)
{
    int click = mouse_press(x1, y1, x2, y2);
    MouseS = (click == 0) ? 0 : 1; 
    return (click == 1);   
}

int button_home( int x1, int y1, int x2, int y2)
{
    int click = mouse_press(x1, y1, x2, y2);
    MouseS = (click == 0) ? 0 : 1; 
    if( click == 2 )
    {
        setcolor(LIGHTRED);
        line(x1 + 3, y2, x2 - 3, y2);
    }
    if( click == 0 )
    {
        setcolor(0);
        line(x1 + 3, y2, x2 - 3, y2);
    }
    return (click == 1);   

}

int button_back( int x1, int y1, int x2, int y2)
{
    int click = mouse_press(x1, y1, x2, y2);
    MouseS = (click == 0) ? 0 : 1; 
    if( click == 2 )
    {
        setcolor(LIGHTRED);
        rectangle(x1, y1, x1 + 60, y1 + 30);
    }
    if( click == 0 )
    {
        setcolor(0);
        rectangle(x1, y1, x1 + 60, y1 + 30);
    }
    return (click == 1);   
}


int button_choose( int x1, int y1, int x2, int y2)
{
    int click = mouse_press(x1, y1, x2, y2);
    MouseS = (click == 0) ? 0 : 1; 
    if( click == 2 )
    {
        setcolor(BLUE);
        line(x1 + 1, y1 + 8, x1 + 5, y1 + 2);
        line(x1 + 9, y1 + 18, x1 + 18, y1 + 3);
    }
    if( click == 0 )
    {
        setcolor(WHITE);
        line(x1 + 3, y1 + 10, x1 + 9, y1 + 18);
        line(x1 + 9, y1 + 18, x1 + 18, y1 + 3);
    }
    return (click == 1);   
}
