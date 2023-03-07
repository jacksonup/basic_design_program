#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

/**
 * 宏定义
 */
#define MAP_HEIGHT 20       // 定义地图高度
#define MAP_WIDTH 40        // 定义地图宽度
#define UP 'w'              // 定义上移键
#define DOWN 's'            // 定义下移键
#define LEFT 'a'            // 定义左移键
#define RIGHT 'd'           // 定义右移键
#define NODE 1000           // 定义节点数
#define MAX_OBSTACLE_NUM 5  // 定义最大障碍物数
#define OBSTACLE_GENERATE_INTERVAL 8

 /**
  * 结构体定义
  */
typedef struct {        // 定义食物和蛇节点位置的结构体
    int x;              // x坐标位置
    int y;              // y坐标位置
}SnakeNode, Obstacle;

typedef struct {
    SnakeNode snakeNode[NODE];     // 蛇长最多包含1000个节点
    int length;                    // 蛇长度
    int speed;                     // 蛇移动速度
}Snake;

struct Food {
    int x;
    int y;
    int type;   // 食物类型，1代表普通食物、2代表中等食物、3代表高等食物
    int grow;   // 生长速度，普通食物为+1、中等食物为+2、高等食物为+3
};

/**
 * 函数定义
 */
void GotoXY(int, int);      // 光标定位函数
void Hide();                // 隐藏光标函数
int Menu();                 // 主菜单函数
void Help();                // 帮助信息
void About();               // 关于信息
void InitMap();             // 地图初始化
void PrintFood();           // 生成食物
int MoveSnake();            // 蛇移动
int IsCorrect();            // 自撞或撞墙检测
void SpeedControl();        // 速度控制
void PrintObstacle();       // 生成障碍物
int IsPrintfObstacle();    // 是否生成障碍物
void ClearObstacle();       // 清除障碍物
