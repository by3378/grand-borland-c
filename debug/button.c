
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
    //��ť״̬Ϊ0������δ�����
    if (*b == 0)
    {

        //�����밴ť�������
        if (mouse_press(x1, y1, x2, y2) == 1)
        {
            MouseS = 0;
            *b = 1;//��ť״̬��Ϊ1�����ѵ����
        }


        //�����밴ť���������
        else if (mouse_press(x1, y1, x2, y2) == 2)
        {
            setcolor(LIGHTRED);
            line(x1 + 3, y2, x2 - 3, y2);
            MouseS = 1;//�����С�ֵ���״
        }


        //����ڰ�ť��
        else
        {
            setcolor(0);
            line(x1 + 3, y2, x2 - 3, y2);
            MouseS = 0;
        }
    }
}


//���÷��ػ��˳���ť
void button_back(int* b, int x1, int y1, int x2, int y2) 
{
    //��ť״̬Ϊ0������δ�����
    if (*b == 0)
    {

        //�����밴ť�������
        if (mouse_press(x1, y1, x2, y2) == 1)
        {
            MouseS = 0;
            *b = 1;//��ť״̬��Ϊ1�����ѵ����
        }

        //�����밴ť���������
        else if (mouse_press(x1, y1, x2, y2) == 2)
        {
            setcolor(LIGHTRED);
            rectangle(x1, y1, x1 + 60, y1 + 30);
            MouseS = 1;//�����С�ֵ���״
        }

        //����ڰ�ť��
        else
        {
            setcolor(8);
            rectangle(x1, y1, x1 + 60, y1 + 30);
            MouseS = 0;
        }
    }
}


//���������ѡ�ɰ�ť
void button_choose(int* b, int x1, int y1, int x2, int y2)
{
    //��ť״̬Ϊ0������δ�����
    if (*b == 0)
    {

        //�����밴ť�������
        if (mouse_press(x1, y1, x2, y2) == 1)
        {
            MouseS = 0;
            *b = 1;//��ť״̬��Ϊ1�����ѵ����
        }

        //�����밴ť���������
        else if (mouse_press(x1, y1, x2, y2) == 2)
        {
            setcolor(BLUE);
            line(x1 + 1, y1 + 8, x1 + 5, y1 + 2);
            line(x1 + 9, y1 + 18, x1 + 18, y1 + 3);
            MouseS = 1;//�����С�ֵ���״
        }

        //����ڰ�ť��
        else
        {
            setcolor(WHITE);
            line(x1 + 3, y1 + 10, x1 + 9, y1 + 18);
            line(x1 + 9, y1 + 18, x1 + 18, y1 + 3);
            MouseS = 0;
        }
    }
}