
void button( int* but , int x1, int y1, int x2, int y2)
{
    int click = mouse_press(x1, y1, x2, y2);
    switch( click )
    {
        case 0:
        
    }

}
void button_home(int* b, int x1, int y1, int x2, int y2)
{
    //按钮状态为0（即：未点击）
    if (*b == 0)
    {

        //鼠标进入按钮，并点击
        if (mouse_press(x1, y1, x2, y2) == 1)
        {
            MouseS = 0;
            *b = 1;//按钮状态改为1（即已点击）
        }


        //鼠标进入按钮，但不点击
        else if (mouse_press(x1, y1, x2, y2) == 2)
        {
            setcolor(LIGHTRED);
            line(x1 + 3, y2, x2 - 3, y2);
            MouseS = 1;//鼠标变成小手的形状
        }


        //鼠标在按钮外
        else
        {
            setcolor(0);
            line(x1 + 3, y2, x2 - 3, y2);
            MouseS = 0;
        }
    }
}


//设置返回或退出按钮
void button_back(int* b, int x1, int y1, int x2, int y2) 
{
    //按钮状态为0（即：未点击）
    if (*b == 0)
    {

        //鼠标进入按钮，并点击
        if (mouse_press(x1, y1, x2, y2) == 1)
        {
            MouseS = 0;
            *b = 1;//按钮状态改为1（即已点击）
        }

        //鼠标进入按钮，但不点击
        else if (mouse_press(x1, y1, x2, y2) == 2)
        {
            setcolor(LIGHTRED);
            rectangle(x1, y1, x1 + 60, y1 + 30);
            MouseS = 1;//鼠标变成小手的形状
        }

        //鼠标在按钮外
        else
        {
            setcolor(8);
            rectangle(x1, y1, x1 + 60, y1 + 30);
            MouseS = 0;
        }
    }
}


//设置添加自选股按钮
void button_choose(int* b, int x1, int y1, int x2, int y2)
{
    //按钮状态为0（即：未点击）
    if (*b == 0)
    {

        //鼠标进入按钮，并点击
        if (mouse_press(x1, y1, x2, y2) == 1)
        {
            MouseS = 0;
            *b = 1;//按钮状态改为1（即已点击）
        }

        //鼠标进入按钮，但不点击
        else if (mouse_press(x1, y1, x2, y2) == 2)
        {
            setcolor(BLUE);
            line(x1 + 1, y1 + 8, x1 + 5, y1 + 2);
            line(x1 + 9, y1 + 18, x1 + 18, y1 + 3);
            MouseS = 1;//鼠标变成小手的形状
        }

        //鼠标在按钮外
        else
        {
            setcolor(WHITE);
            line(x1 + 3, y1 + 10, x1 + 9, y1 + 18);
            line(x1 + 9, y1 + 18, x1 + 18, y1 + 3);
            MouseS = 0;
        }
    }
}