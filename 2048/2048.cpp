/*
做游戏：2048
1.做窗口 每行四个格子  宽带100  间隔15 不变的数据用什么表示？ 1、宏定义 2、const修饰
*/
#include<stdio.h>
#include<conio.h>
#include<graphics.h>

#define MAX_GRID 4 //每格子数
#define GRID_WIDTH 100 //格子宽度
#define INTERVAL 15 //间隔

enum Color {        //枚举格子颜色
    zero = RGB(205, 193, 180),      //0的颜色
    twoTo1 = RGB(238,228,218),      //2的颜色
    twoTo2 = RGB(237,224,200),      //4的颜色
    twoTo3 = RGB(242,177,121),      //8的颜色
    twoTo4 = RGB(245,149,99),       //16的颜色
    twoTo5 = RGB(246,124,95),       //32的颜色
    twoTo6 = RGB(246,94,59),        //64的颜色
    twoTo7 = RGB(242,177,121),      //128的颜色
    twoTo8 = RGB(237,204,97),       //256的颜色
    twoTo9 = RGB(255,0,128),        //512的颜色
    twoTo10 = RGB(145,0,72),        //1024的颜色
    twoTo11 = RGB(242,17,258),      //2048的颜色
    back = RGB(187,173,160),        //背景颜色
};
Color arr[13] = {zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back};
int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];    //全局变量自动初始化为0
POINT pos[MAX_GRID][MAX_GRID];  //  为了方便保存每个格子的左上角左边，POINT为结构体保存两个int值
bool flag = false;
//定义函数，随机返回2或者4
int twoOrFour() {
    if (rand() % 10 == 1)//十分之一的概率产生四
        return 4;
    else
        return 2;
}
//在数组的随机位置产生2或者4
void createNumber() {
    while (1) {
        int x = rand() % MAX_GRID;
        int y = rand() % MAX_GRID;
        if (map[x][y] == 0) {
            map[x][y] = twoOrFour();
            break;
        }
    }
}
void gameInit() {
    //设置随机数种子
    srand(GetTickCount());  //GetTickCount()的返回值是自系统启动以来已用过的毫秒数。
    //计算格子坐标
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int j = 0; j < MAX_GRID; j++)
        {
            pos[i][j].x = j * GRID_WIDTH + (j + 1) * INTERVAL;
            pos[i][j].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
        }
    }
    //初始化
    //游戏开始随机生成两个数
    createNumber();
    createNumber();

}
void gameDraw() {
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int j = 0; j < MAX_GRID; j++)
        {
             //判断map的值,判断格子的颜色
            for (int k = 0; k < 12; k++)
            {
                if (map[i][j] == num[k]) {
                    setfillcolor(arr[k]);
                    solidrectangle(pos[i][j].x, pos[i][j].y, pos[i][j].x+GRID_WIDTH, pos[i][j].y+ GRID_WIDTH);
                    if (map[i][j] != 0) {
                        char number[5] = " ";
                        settextstyle(50,0,"楷体");    //设置字体样式
                        setbkmode(TRANSPARENT); //设置背景颜色透明
                        sprintf(number, "%d", num[k]);
                        //为了文字居中显示：格子的一半减去字符串宽度的一半
                        int tempx = GRID_WIDTH / 2 - textwidth(number) / 2;
                        int tempy = GRID_WIDTH / 2 - textheight(number) / 2;
                        outtextxy(pos[i][j].x+tempx,pos[i][j].y+tempy,number);
                    }
                }
            }
            
            
            
        }
    }
}
//上移
void moveUp() {
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; begin++)
        {
            if (map[begin][i] != 0) {
                if (map[temp][i] == 0) {
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                }
                else if (map[temp][i] == map[begin][i]) {
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }
                else {
                    map[temp+1][i] = map[begin][i];
                    if (temp + 1 != begin) {
                        map[begin][i] = 0;
                    }
                }
                temp++;
                flag = true;
            }
        }
    }
    printf("up\n");
}
//下移
void moveDown() {
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = MAX_GRID-1;
        for (int begin = MAX_GRID - 2; begin >= 0; begin--)
        {
            if (map[begin][i] != 0) {
                if (map[temp][i] == 0) {
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                }
                else if (map[temp][i] == map[begin][i]) {
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }
                else {
                    map[temp - 1][i] = map[begin][i];
                    if (temp - 1 != begin) {
                        map[begin][i] = 0;
                    }
                }
                temp--;
                flag = true;
            }
        }
    }
    printf("down\n");
}
//左移
void moveLeft() {
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; begin++)
        {
            if (map[i][begin] != 0) {
                if (map[i][temp] == 0) {
                    map[i][temp] = map[i][begin];
                    map[i][begin] = 0;
                }
                else if (map[i][temp] == map[i][begin]) {
                    map[i][temp] += map[i][begin];
                    map[i][begin] = 0;
                }
                else {
                    map[i][temp + 1] = map[i][begin];
                    if (temp + 1 != begin) {
                        map[i][begin] = 0;
                    }
                }
                temp++;
                flag = true;
            }
        }
    }
    printf("left\n");

}
//右移
void moveRight() {
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = MAX_GRID-1;
        for (int begin = MAX_GRID-2; begin >= 0; begin--)
        {
            if (map[i][begin] != 0) {
                if (map[i][temp] == 0) {
                    map[i][temp] = map[i][begin];
                    map[i][begin] = 0;
                }
                else if (map[i][temp] == map[i][begin]) {
                    map[i][temp] += map[i][begin];
                    map[i][begin] = 0;
                }
                else {
                    map[i][temp - 1] = map[i][begin];
                    if (temp - 1 != begin) {
                        map[i][begin] = 0;
                    }
                }
                temp--;
                flag = true;
            }
        }
    }
    printf("right\n");
}
void gameJudge() {
    if (flag) {
        createNumber();
        flag = false;
    }
}
//键盘控制数字移动
void gameControl() {
    char key = _getch();
    switch (key){
        case  'w':
        case  'W':
        case  72:
            moveUp();
            break;
        case  's':
        case  'S':
        case  80:
            moveDown();
            break;
        case  'a':
        case  'A':
        case  75:
            moveLeft();
            break;
        case  'd':
        case  'D':
        case  77:
            moveRight();
            break;

    }
}

int main() {
    //创建窗口 
    initgraph(MAX_GRID * GRID_WIDTH + INTERVAL * (MAX_GRID + 1), MAX_GRID * GRID_WIDTH + INTERVAL * (MAX_GRID + 1));
    setbkcolor(RGB(187,173,160));
    cleardevice();        
    gameInit();
    while (1) {

        gameDraw();
        gameControl();
        gameJudge();
        
    }
    return 0;
}

