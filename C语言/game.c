#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void gotoxy(int x, int y);  //光标定位函数
void anxfx();               //棍子移动
void yxcsh();               //游戏界面初始化
void txqhs();               //弹小球函数
void xtpdhs();              //判断小球运动方向函数
void hzxqhs();              //绘制小球函数
void function();            //功能实现**
void HideCursor();          //隐藏光标函数
void pdyxjs();              //游戏结束

int _x = 0, _y = 0;         //小球的x和y坐标
int ab = 1, ab2 = 1;        //用于控制开关
int xdir = 0, ydir = 0;     //小球运动方向   往右
int bs;
char an = '0';              //接收输入的方向键
int x = 36, x2 = 0, x3 = 0; //棍子的x坐标和清除重复字符
int sdf = 1;                //判断棍子是否接住球,接住为1,不可以写成0
int n = 0;                  //游戏得分变量


int main()
{
	getchar();
    yxcsh();                //游戏界面和计分
    function();             //功能主函数

    return 0;
}

void yxcsh()                            //游戏界面
{
    HideCursor();                        //移除光标
    system("title 弹小球游戏");          //控制台标题
    system("mode con cols=80 lines=25"); //控制台界面大小
int i = 0;
    for ( i = 0; i < 80; i++)         //头部边界
        printf("_");
    
    gotoxy(23, x);
    printf("========");                 //绘制初始棍子
}

void anxfx()                    //控制棍子移动
{
        x2 = x + 7;             //根据x的值确定需要在x2的位置输出空格，用来实现清除上一次的棍子的效果
        x3 = x;

        gotoxy(23, x2-1);       //刚开始会有多出一个等号的漏洞，找不出问题
        printf(" ");    

        an = _getch();          //即使接收值的函数
        if (an == 'a')
        {
            x > 0 ? x-=2 :x;    //如果棍子移动的距离小于边界的距离则停下
            gotoxy(23, x2);
            printf("  ");       //用于清除上一次绘制的棍子
        }
        
        if (an == 'd')
        {
            x <= 71 ? x+=2 : x;
            gotoxy(23, x3);
                printf("  ");
        }

        gotoxy(23, x);
        printf("========");     //绘制下一次按键后的棍子
}

void txqhs()                        //小球运动函数
{
    xtpdhs();                       //判断函数

    if (bs == 2)                    //下边一面
        if (_y >= 22) bs = 3;      
    if (bs == 1)
        if (_y >= 22) bs = 4;
    
    if (bs == 1)                    //右边一面
        if (_x >= 79) bs = 2;       
    if (bs == 4)
        if (_x >= 79) bs = 3;

    if (bs == 3)
        if (_y <= 1)  bs = 2;       //上边一面
    if (bs == 4)
        if (_y <= 1)  bs = 1;


    if (bs == 3)
        if (_x <= 0)  bs = 4;       //左边一面
    if (bs == 2)
        if (_x <= 0)  bs = 1;


    hzxqhs();                       //绘制小球函数
}

void xtpdhs()                       //变量sdf控制小球运动方向
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
    if (bs == 1)        //0是右,下
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
    if (sdf == 0 || n >= 20)              //游戏结束条件
    {
        gotoxy(_y + 1, _x + 1);
        printf("o");
        Sleep(500);
        gotoxy(_y + 1, _x + 1);
        printf(" ");

        system("cls");
        gotoxy(10, 34);
        printf("游戏结束");
        gotoxy(12, 32);
        printf("最终得分：%d", n);
        if (n >= 20)
        {
            gotoxy(14, 34);
            printf("您通关了！");
        }
        else
        {
            gotoxy(14, 32);
            printf("您没有弹中！");
        }
        
        gotoxy(21, 0);
        exit(0);
    }
}

void hzxqhs()               //绘制小球函数
{
    gotoxy(_y, _x);
    printf("o");

    Sleep(100);

    gotoxy(_y, _x);
    printf(" ");
}


void function()                         //总结函数
{
    srand((unsigned)time(NULL));        //随机种子
    _x = rand() % 79;                   //每次小球的初始x坐标为一个随机数

    if(_x > 40)  bs = 2; 
	else  bs = 1;          //因为小球初始的x坐标是一个随机数
   //所以这里针对他的x坐标确定他的初始运动方向

    while (1)
    {
        gotoxy(0, 0);
        printf("得分：%d ", n);         //显示每次循环后分值

        if (_kbhit())                   //按下键盘时
        {
            gotoxy(23, 36);
            anxfx();                    //棍子的动画效果
        }
            
        txqhs();                        //小球动画效果
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
