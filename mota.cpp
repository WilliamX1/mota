/*
    1.创建可视化窗口
    2.基本贴图操作
        2.1 IMAGE  img；  //图片变量去代表图片
        2.2 变量和图片绑定在一起loadimage (&img,"IMAGE")
        2.3 显示 putimage(int x, int y, &img)

    3.C语言一些数据类型：数组和结构体
    4.用户交互：按键交互  鼠标交互
*/
#define _CRT_SECURE_NO_WARNINGS    //去掉scanf_s问题
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>    //图形插件
#include <conio.h>       //_getch()头文件
#include <string>
HWND hwnd;
const int N = 25;
int map[13][13] =  //地图设计
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 13, 1, 19, 2, 3, 2, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 17, 1, 5, 14, 1, 0, 17, 19, 17, 0, 1, 0},
    {0, 19, 5, 10, 0, 1, 0, 17, 19, 17, 0, 1, 0},
    {0, 0, 14, 0, 0, 1, 0, 0, 0, 4, 0, 1, 0},
    {0, 19, 6, 1, 0, 1, 14, 7, 2, 22, 0, 1, 0},
    {0, 11, 1, 20, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 14, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 6, 1, 0, 0, 16, 0, 0, 0, 14, 0, 0},
    {0, 17, 18, 19, 0, 1, N, 1, 0, 19, 9, 20, 0},
    {0, 17, 24, 19, 0, 1, 12, 1, 0, 19, 19, 19, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int roleX = 10, roleY = 6;  //英雄初始位置
struct gameRole         //主角色
{
    char name[20];      //角色名
    int blood;          //血量
    int attack;         //攻击力
    int defence;        //防御力
    int blueKey;        //蓝钥匙
    int yellowKey;      //黄钥匙
    int redKey;         //红钥匙
    int grade;          //等级
    int experience;     //经验
    int money;          //金币
}role;                  //整个游戏唯一角色，创建一个全局角色
struct monster          //怪物角色
{
    int blood;
    int attack;
    int defence;
    int money;
    int experience;
};//更多怪物设计
struct monster greenLTG = { 50,20,1,1,1 };  //绿史莱姆
struct monster redLTG = { 70,15,2,2,2 };  //红史莱姆
struct monster blackLTG = { 200,35,10,5,5 };  // 青头怪
struct monster yellowDJS = { 150,40,20,8,6 };  //骷髅士兵
struct monster redDJS = { 400,90,50,15,12 };  //骷髅队长
struct monster purpleSSG = { 125,50,25,10,7 };  //初级法师
struct monster redSSG = { 100,200,110,30,25 };  //高级法师
struct monster yellowWXR = { 300,75,45,13,10 };  //兽面人
struct monster yellowDGZ = { 100,20,5,3,3 };  //小蝙蝠
struct monster redDGZ = { 150,65,30,10,8 };  //大蝙蝠

IMAGE img[26], roleInfo;  //初始化角色信息
void inputRoleName()
{
    printf("Input role name:");
    scanf("%s", role.name);
    //初始化角色其他所有属性
    role.blood = 10000;
    role.attack = 90;
    role.defence = 10;
    role.yellowKey = 10;
    role.blueKey = 10;
    role.redKey = 2;
    role.grade = 1;
    role.experience = 0;
    role.money = 0;
}  //输入用户名  初始化用户的信息
void loadResource()
{
    //初始化存储资源的边缘
    for (int i = 0; i <= 25; ++i)
    {
        char fileName[20] = "";
        sprintf(fileName, "%d.jpg", i);
        //60*60 固定尺寸为60*60
        loadimage(img + i, fileName, 40, 40);
    }
    loadimage(&roleInfo, "01.jpg", 40, 520);
}  //加载资源:批量加载

//工具函数
char str[16] = "";//把整形转换为字符串:类型转换
char* intToChar(int xNum)
{ 
    sprintf(str, "%d", xNum);
    return str;
}  //整形转换字符型
void drawMap(int map[][13])
{
    int i, j;
    int x, y;
    for (i = 0; i < 13; ++i)
    {
        for (j = 0; j < 13; ++j)
        {
            x = 40 * j;
            y = 40 * i;
            //img[0~25]  图片编号0~25  map[i][j] 0~25
            putimage(x, y, &img[map[i][j]]);
        }
        putimage(40 * 13, 0, &roleInfo);
    }
    outtextxy(40 * 13 + 8, 110, intToChar(role.grade));
    outtextxy(40 * 13 + 8, 155, intToChar(role.experience));
    outtextxy(40 * 13 + 8, 222, intToChar(role.blood));
    outtextxy(40 * 13 + 8, 270, intToChar(role.money));
    outtextxy(40 * 13 + 8, 335, intToChar(role.attack));
    outtextxy(40 * 13 + 8, 382, intToChar(role.defence));
    outtextxy(40 * 13 + 8, 450, intToChar(role.yellowKey));
    outtextxy(40 * 13 + 8, 490, intToChar(role.blueKey));
    outtextxy(40 * 13 + 8, 505, intToChar(role.redKey));
}
int bloodConsume(struct monster M)
{
    if (role.attack <= M.defence) return -1;
    if (role.defence >= M.attack) return 0;
    int times = 1 + M.blood / (role.attack - M.defence);
    int hurt = times * (M.attack - role.defence);
    return hurt;
}  //计算攻击怪物所需血量
bool bloodPK(struct monster M)
{
    int hurt = bloodConsume(M);
    if (hurt == -1) return false;
    if (hurt >= role.blood) return false;

    role.blood -= hurt;
    role.experience += M.experience;
    role.money += M.money;
    return true;
}  //对拼实现函数
int xChange(int direction)  //x坐标转换
{
    if (direction == 0) return -1;
    if (direction == 1 || direction == 3) return 0;
    if (direction == 2) return 1;
}
int yChange(int direction)  //y坐标转换
{
    if (direction == 0 || direction == 2) return 0;
    if (direction == 1) return 1;
    if (direction == 3) return -1;
}
void goAhead(int dx, int dy)  //向前走
{
    map[roleX + dx][roleY + dy] = N;
    map[roleX][roleY] = 1;
    roleX += dx; roleY += dy;
}
void aheadVanish(int dx, int dy)   //前方物体消失
{
    map[roleX + dx][roleY + dy] = 1;
}
bool attackLTG(int delt)  //攻击流体怪
{
    switch (delt)
    {
        case 2: return bloodPK(greenLTG);
        case 3: return bloodPK(redLTG);
        case 4: return bloodPK(blackLTG);
    }
}
bool attackDJS(int delt)  //攻击独角兽
{
    if (delt == 5) return bloodPK(yellowDJS);
    if (delt == 6) return bloodPK(redDJS);
}
bool attackSSG(int delt)  //攻击蛇形怪
{
    if (delt == 7) return bloodPK(purpleSSG);
    if (delt == 8) return bloodPK(redSSG);
}
bool attackWXR(int delt)  //攻击黄外星人
{
    if (delt == 9) return bloodPK(yellowWXR);
}
bool attackDGZ(int delt)
{
    if (delt == 22) return bloodPK(yellowDGZ);
    if (delt == 23) return bloodPK(redDGZ);
}
void getGem(int delt, int dx, int dy)  //拾取宝石
{
    if (delt == 10) { role.attack += 3; };
    if (delt == 11) { role.defence += 3; };
    goAhead(dx, dy);
    return;
}
void getKey(int delt, int dx, int dy)  //拾取钥匙
{
    if (delt == 19) { ++role.yellowKey; goAhead(dx, dy); return; };
    if (delt == 20) { ++role.blueKey; goAhead(dx, dy); return; };
    if (delt == 21) { ++role.redKey; goAhead(dx, dy); return; };
}
void getSword(int delt, int dx, int dy)  //拾取剑
{
    if (delt == 24) { role.attack += 10; goAhead(dx, dy); return; };
}
void openDoor(int delt, int dx, int dy) //开门
{
    if (delt == 14)
    {   
        if (role.blueKey > 0) 
            {
                --role.blueKey; 
                aheadVanish(dx, dy);
            }
        return;
    }
        
    if (delt == 15)
    {   
        if (role.yellowKey > 0)
            {
                --role.yellowKey;
                aheadVanish(dx, dy);
            }
        return;
    }
    if (delt == 16)
    {
        if (role.redKey > 0)
            {
                --role.redKey;
                aheadVanish(dx, dy);
            }
        return;
    }
}
void drinkBill(int delt, int dx, int dy)  //喝药水
{
    if (delt == 17) { role.blood += 50; goAhead(dx, dy); return; };
    if (delt == 18) { role.blood += 50; goAhead(dx, dy); return; };
}
void roadChoice(int direction)  //走路函数
{
    int dx = xChange(direction);
    int dy = yChange(direction);
    int delt = map[roleX + dx][roleY + dy];
    switch (delt){
        case 0: return;
        case 1: goAhead(dx, dy); return;
        case 2:case 3:case 4: if (attackLTG(delt)) { goAhead(dx, dy); }return;
        case 5:case 6: if (attackDJS(delt)) { goAhead(dx, dy); }return;
        case 7:case 8: if (attackSSG(delt)) { goAhead(dx, dy); }return;
        case 9: if (attackWXR(delt)) { goAhead(dx, dy); }return;
        case 10:case 11: getGem(delt, dx, dy); return;
        case 12:case 13:return; //传送门待设计
        case 14:case 15:case 16: openDoor(delt, dx, dy); return;
        case 17:case 18: drinkBill(delt, dx, dy); return;
        case 19:case 20:case 21: getKey(delt, dx, dy); return;
        case 22:case 23: if (attackDGZ(delt)) { goAhead(dx, dy); }return;
        case 24: getSword(delt, dx, dy); return;
    }
}
void keyDown()  //按键识别
{
    char userKey;
    userKey = _getch();
    switch (userKey)
    {
        //上
        case 'w':
        case 'W':
        case 72:
            roadChoice(0);
            break;
        //下
        case 's':
        case 'S':
        case 80:
            roadChoice(2);
            break;
        //左
        case 'A':
        case 'a':
        case 75:
            roadChoice(3);
            break;
        //右
        case 'D':
        case 'd':
        case 77:
            roadChoice(1);
            break;      
    }
}
int main()
{
    
    inputRoleName();  //初始化用户名
    loadResource();  //下载图片资源
    hwnd = initgraph(40 * 14, 40 * 13);  //初始化游戏界面
    while (1)
    {
        drawMap(map);
        keyDown();
    }
    _getch();
    closegraph();
    
    //system("pause")
    return 0;
}