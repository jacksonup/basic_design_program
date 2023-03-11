#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

/**
 * 宏定义
 */
#define MAP_HEIGHT 20                   // 定义地图高度
#define MAP_WIDTH 40                    // 定义地图宽度
#define UP 'w'                          // 定义上移键
#define DOWN 's'                        // 定义下移键
#define LEFT 'a'                        // 定义左移键
#define RIGHT 'd'                       // 定义右移键
#define NODE 1000                       // 定义节点数
#define MAX_OBSTACLE_NUM 5              // 定义最大障碍物数
#define OBSTACLE_GENERATE_INTERVAL 8    // 定义随机障碍物间隔时间 s
#define COMPUTER_SNAKE_NUM 3            // 最大电脑蛇数量
#define INIT_COMPUTER_SNAKE_LENGTH 8    // 初始化电脑蛇长度
#define MAX_RECORDS 1000  // 最多存储1000条记录

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

typedef struct {
    SnakeNode snakeNode[NODE];
    int length;
    char direction;
    int speed;
} ComputerSnake;

struct Food {
    int x;
    int y;
    int type;   // 食物类型，1代表普通食物、2代表中等食物、3代表高等食物
    int grow;   // 生长速度，普通食物为+1、中等食物为+2、高等食物为+3
};

struct GameRecord {
    char startTime[80];
    int score;
};

/**
 * 函数定义
 */
void About();                                                       // 关于信息
void ClearObstacle();                                               // 清除障碍物
void DisplayGameRecords();                                          // 展示排行榜
void GotoXY(int, int);                                              // 光标定位函数
void Hide();                                                        // 隐藏光标函数
void Help();                                                        // 帮助信息
void InitMap();                                                     // 地图初始化
void PrintFood();                                                   // 生成食物
void PrintObstacle();                                               // 生成障碍物
void ReadGameRecords(struct GameRecord records[], int* numRecords); // 读得分记录
void SpeedControl();                                                // 速度控制
void WriteGameRecord(struct GameRecord gameRecord);                 // 将得分记录写入文件
int CompareGameRecords(const void* a, const void* b);               // 排序
int IsCorrect();                                                    // 自撞或撞墙检测
int IsPrintfObstacle();                                             // 是否生成障碍物
int Menu();                                                         // 主菜单函数
int MoveSnake();                                                    // 蛇移动