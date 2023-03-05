/**
 * snake.h实现类
 *
 * @author chenyb46701
 * @date 2022/03/05
 */
#include "snake.h"

 /**
  * 全局变量定义
  */
Snake snake;                  // 定义蛇结构体变量
Food food;                    // 定义食物结构体变量
char nowDirection = RIGHT;    // 当前蛇头方向
char direction = RIGHT;       // 预期蛇头方向

/**
 * 主菜单函数
 *
 * @return result 菜单项
 */
int Menu() {
    // 定义光标位置
    GotoXY(40, 12);
    printf("欢迎来到贪吃蛇小游戏");
    GotoXY(43, 14);
    printf("1.开始游戏");
    GotoXY(43, 16);
    printf("2.帮助");
    GotoXY(43, 18);
    printf("3.关于");
    GotoXY(43, 20);
    printf("其他任意键退出游戏");
    // 隐藏光标
    Hide();
    char ch;
    int result = 0;
    // 接收用户输入的菜单选项
    ch = _getch();

    switch (ch) {
    case '1':
        result = 1;
        break;
    case '2':
        result = 2;
        break;
    case '3':
        result = 3;
        break;
    }
    system("cls");
    return result;
}

/**
 * 光标定位函数，将光标定位到(x,y)坐标位置
 * <p>
 * HANDLE 是 Windows 操作系统中的一种句柄（handle）类型，代表了操作系统内核为应用程序所提供的各种对象，例如文件、进程、线程、窗口、事件等等。
 * 这里的HANDLE指的是控制台句柄
 * </p>
 *
 * @param x x轴
 * @param y y轴
 */
void GotoXY(int x, int y) {
    HANDLE handle;
    // 表示控制台中的坐标，它包含X和Y两个成员
    COORD coord;
    // 获取控制台标准输出的句柄
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    // 将控制台光标移动到指定坐标位置
    SetConsoleCursorPosition(handle, coord);
}

/**
 * 隐藏光标
 */
void Hide() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // 控制台光标信息中的 dwSize 设置为 1，将 bVisible 设置为 0，即将光标大小设置为 1，将光标可见性设置为不可见
    CONSOLE_CURSOR_INFO consoleCursorInfo = { 1, 0 };
    SetConsoleCursorInfo(handle, &consoleCursorInfo);
}

/**
 * 关于菜单实现
 */
void About() {
    GotoXY(30, 12);
    printf("杭州电子科技大学--程序设计综合实践案例");
    GotoXY(43, 14);
    printf("贪吃蛇-控制台游戏");
    GotoXY(43, 16);
    printf("按任意键返回上级菜单");
    Hide();
    char ch = _getch();
    system("cls");
}

/**
 * 帮助菜单实现
 */
void Help() {
    GotoXY(40, 12);
    printf("w 上");
    GotoXY(40, 14);
    printf("s 下");
    GotoXY(40, 16);
    printf("a 左");
    GotoXY(40, 18);
    printf("d 右");
    GotoXY(40, 20);
    printf("当蛇撞到自身或撞墙时游戏结束");
    GotoXY(45, 22);
    printf("按任意键返回上级菜单");
    Hide();
    char ch = _getch();
    system("cls");
}

/**
 * 初始化地图
 */
void InitMap() {
    // 隐藏光标
    Hide();

    // 设置蛇头位置在地图中心
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;

    // 将光标移到蛇头位置
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    // 打印蛇头
    printf("@");
    snake.length = 3;
    snake.speed = 250;
    nowDirection = RIGHT;

    // 打印蛇身
    for (int i = 1; i < snake.length; i++) {
        // 设置蛇身的纵坐标位置和蛇身位置相同
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        // 设置蛇身的横坐标位置，蛇身在蛇头的左边，所以横坐标依次减1
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        // 移动光标到蛇身位置
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
        // 打印蛇身
        printf("o");
    }

    // 生成地图上下边界
    for (int i = 0; i < MAP_WIDTH; i++) {
        GotoXY(i, 0);
        printf("*");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("*");
    }

    // 生成地图左右边界
    for (int i = 1; i < MAP_HEIGHT; i++) {
        GotoXY(0, i);
        printf("*");
        GotoXY(MAP_WIDTH - 1, i);
        printf("*");
    }

    // 生成食物
    PrintFood();
    // 得分说明
    GotoXY(50, 5);
    printf("当前得分：0");
}

/**
 * 生成食物
 */
void PrintFood() {
    int flag = 1;
    while (flag) {
        flag = 0;
        // 设置随机的食物坐标位置
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        // 循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        for (int i = 0; i <= snake.length - 1; ++i) {
            if (snake.snakeNode[i].x == food.x && snake.snakeNode[i].y == food.y) {
                flag = 1;
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    printf("$");
}

/**
 * 蛇移动函数实现，返回值为1表示继续移动，为0表示停止移动
 *
 * @return
 */
int MoveSnake() {
    SnakeNode snakeTailNode;
    int flag = 0;

    // 记录蛇尾
    snakeTailNode = snake.snakeNode[snake.length - 1];
    for (int i = snake.length - 1; i >= 1; i--) {
        snake.snakeNode[i] = snake.snakeNode[i - 1];
    }
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    // 前进方向打印一节蛇身，其他蛇身不需要打印
    printf("o");

    // 响应键盘修改
    if (_kbhit()) {
        direction = _getch();
        switch (direction) {
        case UP:
            if (nowDirection != DOWN) {
                nowDirection = direction;
            }
            break;
        case DOWN:
            if (nowDirection != UP) {
                nowDirection = direction;
            }
            break;
        case LEFT:
            if (nowDirection != RIGHT) {
                nowDirection = direction;
            }
            break;
        case RIGHT:
            if (nowDirection != LEFT) {
                nowDirection = direction;
            }
            break;
        }
    }

    switch (nowDirection) {
    case UP:
        snake.snakeNode[0].y--;
        break;
    case DOWN:
        snake.snakeNode[0].y++;
        break;
    case LEFT:
        snake.snakeNode[0].x--;
        break;
    case RIGHT:
        snake.snakeNode[0].x++;
        break;
    }

    // 打印蛇头
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");

    // 判断是否吃到食物
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        snake.length++;
        flag = 1;
        snake.snakeNode[snake.length - 1] = snakeTailNode;
    }

    // 输出蛇此时的状态，若没有吃到食物，在原先蛇尾的地方输出一个空格，去掉原来的蛇尾
    if (flag) {
        PrintFood();
        GotoXY(50, 5);
        printf("当前得分：%d", snake.length - 3);
    }
    else {
        GotoXY(snakeTailNode.x, snakeTailNode.y);
        printf(" ");
    }

    // 判断是否死亡
    if (!IsCorrect()) {
        system("cls");
        GotoXY(45, 14);
        printf("最终得分：%d", snake.length - 3);
        GotoXY(45, 16);
        printf("你输了！");
        GotoXY(45, 18);
        printf("请按任意键返回主菜单");
        char c = _getch();
        system("cls");
        return 0;
    }

    SpeedControl();
    Sleep(snake.speed);
    return 1;
}

/**
 * 判断是否自撞或撞墙
 *
 * @return 0：自撞或撞墙；1：安全
 */
int IsCorrect() {
    if (snake.snakeNode[0].x == 0 ||
        snake.snakeNode[0].y == 0 ||
        snake.snakeNode[0].x == MAP_WIDTH - 1 ||
        snake.snakeNode[0].y == MAP_HEIGHT - 1) {
        return 0;
    }
    int cutIndex = -1; // 初始化为-1，表示不需要截断
    for (int i = 1; i < snake.length; i++) {
        if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y) {
            cutIndex = i;
            break;
        }
    }

    if (cutIndex >= 0) {
        // 长度为3时不截断
        if (cutIndex <= 3) {
            return 1;
        }
        // 清除屏幕上之前的蛇身
        for (int i = cutIndex; i < snake.length; i++) {
            GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
            printf(" ");
        }
        snake.length = cutIndex; // 设置蛇的长度为需要截断的位置
        // 根据新的长度设置蛇的节点
        for (int i = 0; i < snake.length; i++) {
            snake.snakeNode[i] = snake.snakeNode[i + 1];
        }
    }
    GotoXY(50, 5);
    printf("当前得分：%d", snake.length - 3);
    return 1;
}

/**
 * 速度调整函数
 */
void SpeedControl() {
    switch (snake.length) {
    case 6:
        snake.speed = 200;
        break;
    case 9:
        snake.speed = 180;
        break;
    case 12:
        snake.speed = 160;
        break;
    case 15:
        snake.speed = 140;
        break;
    case 18:
        snake.speed = 120;
        break;
    case 21:
        snake.speed = 100;
        break;
    case 24:
        snake.speed = 80;
        break;
    case 27:
        snake.speed = 60;
        break;
    case 30:
        snake.speed = 40;
        break;
    }
}
