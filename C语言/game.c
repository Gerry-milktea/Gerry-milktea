#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void gotoxy(int x, int y);  //��궨λ����
void anxfx();               //�����ƶ�
void yxcsh();               //��Ϸ�����ʼ��
void txqhs();               //��С����
void xtpdhs();              //�ж�С���˶�������
void hzxqhs();              //����С����
void function();            //����ʵ��**
void HideCursor();          //���ع�꺯��
void pdyxjs();              //��Ϸ����

int _x = 0, _y = 0;         //С���x��y����
int ab = 1, ab2 = 1;        //���ڿ��ƿ���
int xdir = 0, ydir = 0;     //С���˶�����   ����
int bs;
char an = '0';              //��������ķ����
int x = 36, x2 = 0, x3 = 0; //���ӵ�x���������ظ��ַ�
int sdf = 1;                //�жϹ����Ƿ��ס��,��סΪ1,������д��0
int n = 0;                  //��Ϸ�÷ֱ���


int main()
{
	getchar();
    yxcsh();                //��Ϸ����ͼƷ�
    function();             //����������

    return 0;
}

void yxcsh()                            //��Ϸ����
{
    HideCursor();                        //�Ƴ����
    system("title ��С����Ϸ");          //����̨����
    system("mode con cols=80 lines=25"); //����̨�����С
int i = 0;
    for ( i = 0; i < 80; i++)         //ͷ���߽�
        printf("_");
    
    gotoxy(23, x);
    printf("========");                 //���Ƴ�ʼ����
}

void anxfx()                    //���ƹ����ƶ�
{
        x2 = x + 7;             //����x��ֵȷ����Ҫ��x2��λ������ո�����ʵ�������һ�εĹ��ӵ�Ч��
        x3 = x;

        gotoxy(23, x2-1);       //�տ�ʼ���ж��һ���Ⱥŵ�©�����Ҳ�������
        printf(" ");    

        an = _getch();          //��ʹ����ֵ�ĺ���
        if (an == 'a')
        {
            x > 0 ? x-=2 :x;    //��������ƶ��ľ���С�ڱ߽�ľ�����ͣ��
            gotoxy(23, x2);
            printf("  ");       //���������һ�λ��ƵĹ���
        }
        
        if (an == 'd')
        {
            x <= 71 ? x+=2 : x;
            gotoxy(23, x3);
                printf("  ");
        }

        gotoxy(23, x);
        printf("========");     //������һ�ΰ�����Ĺ���
}

void txqhs()                        //С���˶�����
{
    xtpdhs();                       //�жϺ���

    if (bs == 2)                    //�±�һ��
        if (_y >= 22) bs = 3;      
    if (bs == 1)
        if (_y >= 22) bs = 4;
    
    if (bs == 1)                    //�ұ�һ��
        if (_x >= 79) bs = 2;       
    if (bs == 4)
        if (_x >= 79) bs = 3;

    if (bs == 3)
        if (_y <= 1)  bs = 2;       //�ϱ�һ��
    if (bs == 4)
        if (_y <= 1)  bs = 1;


    if (bs == 3)
        if (_x <= 0)  bs = 4;       //���һ��
    if (bs == 2)
        if (_x <= 0)  bs = 1;


    hzxqhs();                       //����С����
}

void xtpdhs()                       //����sdf����С���˶�����
{
    if (_y>=22)
    {
        if (_x >= x && _x <= x2)
        {
            sdf = 1;
            n++;
        }
        else
        {
            sdf = 0;
        }
    }
    
    pdyxjs();
    if (bs == 1)        //0����,��
    {
        _x++; _y++;
    }
    else if (bs == 2)
    {
        _x--; _y++;
    }
    else if (bs == 3)
    {
        _x--; _y--;
    }
    else if (bs == 4)
    {
        _x++; _y--;
    }
    
}

void pdyxjs()
{
    if (sdf == 0 || n >= 20)              //��Ϸ��������
    {
        gotoxy(_y + 1, _x + 1);
        printf("o");
        Sleep(500);
        gotoxy(_y + 1, _x + 1);
        printf(" ");

        system("cls");
        gotoxy(10, 34);
        printf("��Ϸ����");
        gotoxy(12, 32);
        printf("���յ÷֣�%d", n);
        if (n >= 20)
        {
            gotoxy(14, 34);
            printf("��ͨ���ˣ�");
        }
        else
        {
            gotoxy(14, 32);
            printf("��û�е��У�");
        }
        
        gotoxy(21, 0);
        exit(0);
    }
}

void hzxqhs()               //����С����
{
    gotoxy(_y, _x);
    printf("o");

    Sleep(100);

    gotoxy(_y, _x);
    printf(" ");
}


void function()                         //�ܽắ��
{
    srand((unsigned)time(NULL));        //�������
    _x = rand() % 79;                   //ÿ��С��ĳ�ʼx����Ϊһ�������

    if(_x > 40)  bs = 2; 
	else  bs = 1;          //��ΪС���ʼ��x������һ�������
   //���������������x����ȷ�����ĳ�ʼ�˶�����

    while (1)
    {
        gotoxy(0, 0);
        printf("�÷֣�%d ", n);         //��ʾÿ��ѭ�����ֵ

        if (_kbhit())                   //���¼���ʱ
        {
            gotoxy(23, 36);
            anxfx();                    //���ӵĶ���Ч��
        }
            
        txqhs();                        //С�򶯻�Ч��
    }
}


void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void gotoxy(int x, int y)
{
    COORD pos = { y,x };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
