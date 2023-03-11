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
Snake snake;                                      // 定义蛇结构体变量
struct Food food;                                       // 定义食物结构体变量
Obstacle obstacle[MAX_OBSTACLE_NUM];                    // 定义障碍结构体数组变量
char nowDirection = RIGHT;                              // 当前蛇头方向
char direction = RIGHT;                                 // 预期蛇头方向
time_t obstacleTimeStamp;                               // 生成上一次障碍物时间戳


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
    printf("4.排行榜");
    GotoXY(43, 22);
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
    case '4':
        result = 4;
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
    // 生成障碍物
    PrintObstacle();
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
        // 生成随机的食物类型
        food.type = rand() % 3 + 1;
        // 循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        for (int i = 0; i <= snake.length - 1; ++i) {
            if (snake.snakeNode[i].x == food.x && snake.snakeNode[i].y == food.y) {
                flag = 1;
                break;
            }
        }
        // 循环判断食物位置是否和障碍物的位置重叠，如果重叠则需要重新设置食物位置
        for (int i = 0; i <= MAX_OBSTACLE_NUM - 1; ++i) {
            if (obstacle[i].x == food.x && obstacle[i].y == food.y) {
                flag = 1;
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    // 类型为 1 的食物输出字符为 $
    if (food.type == 1) {
        printf("$");
        food.grow = 1;
    }
    // 假设类型为 2 的食物输出字符为 @
    else if (food.type == 2) {
        printf("@");
        food.grow = 2;
    }
    // 假设类型为 3 的食物输出字符为 &
    else {
        printf("&");
        food.grow = 3;
    }
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
        snake.length += food.grow;
        flag = 1;
        for (int i = snake.length - food.grow; i < snake.length; ++i) {
            snake.snakeNode[i] = snakeTailNode;
        }
    }

    // 输出蛇此时的状态，若没有吃到食物，在原先蛇尾的地方输出一个空格，去掉原来的蛇尾
    if (flag) {
        PrintFood();
        GotoXY(50, 5);
        printf("当前得分：%d   ", snake.length - 3);
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

        // 保存当前成绩至文件中
        struct GameRecord gameRecord;

        time_t t = time(NULL);

        struct tm* localTime = localtime(&t);
        char formattedTime[80];
        strftime(gameRecord.startTime, 80, "%Y-%m-%d %H:%M:%S", localTime);
        gameRecord.score = snake.length - 3;
        WriteGameRecord(gameRecord);

        printf("请按任意键返回主菜单");
        char c = _getch();
        system("cls");
        return 0;
    }

    // 随机刷新障碍物
    if (IsPrintfObstacle()) {
        // 重新生成障碍物
        ClearObstacle();
        PrintObstacle();
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

    // 判断是否碰到障碍物
    for (int i = 0; i <= MAX_OBSTACLE_NUM - 1; i++) {
        if (snake.snakeNode[0].x == obstacle[i].x && snake.snakeNode[0].y == obstacle[i].y) {
            return 0;
        }
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
    printf("当前得分：%d   ", snake.length - 3);
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

/**
 * 生成障碍物函数
 */
void PrintObstacle() {
    // 随机生成1-5个障碍物
    int obstacleCount = rand() % 5 + 1;
    int flag = 1;
    while (obstacleCount > 0) {
        flag = 1;
        // 设置随机的障碍物坐标位置
        obstacle[obstacleCount - 1].x = rand() % (MAP_WIDTH - 2) + 1;
        obstacle[obstacleCount - 1].y = rand() % (MAP_HEIGHT - 2) + 1;
        // 循环判断障碍物位置是否和蛇或食物的位置重叠，如果重叠则需要重新设置障碍物位置
        for (int i = 0; i <= snake.length - 1; ++i) {
            if (snake.snakeNode[i].x == obstacle[obstacleCount - 1].x && snake.snakeNode[i].y == obstacle[obstacleCount - 1].y) {
                flag = 0;
                break;
            }
        }
        if (flag && food.x == obstacle[obstacleCount - 1].x && food.y == obstacle[obstacleCount - 1].y) {
            flag = 0;
        }
        for (int i = 0; i <= MAX_OBSTACLE_NUM - 1; ++i) {
            if (i != obstacleCount - 1 && obstacle[i].x == obstacle[obstacleCount - 1].x && obstacle[i].y == obstacle[obstacleCount - 1].y) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            GotoXY(obstacle[obstacleCount - 1].x, obstacle[obstacleCount - 1].y);
            printf("#");
            obstacleCount--;
        }
    }
}

/**
 * 判断是否重新生成障碍物
 *
 * @return int
 */
int IsPrintfObstacle() {
    time_t currentTimeStamp = time(NULL);
    double timeDiff = difftime(currentTimeStamp, obstacleTimeStamp);
    if (timeDiff > OBSTACLE_GENERATE_INTERVAL) {
        obstacleTimeStamp = currentTimeStamp;
        return 1;
    }
    return 0;
}

/**
 * 清除障碍物
 */
void ClearObstacle() {
    for (int i = 0; i < MAX_OBSTACLE_NUM; i++) {
        GotoXY(obstacle[i].x, obstacle[i].y);
        printf(" ");
    }
}

/**
 * 读得分记录
 *
 * @param: struct GameRecord 得分数组
 * @param: int* 记录数量
 */
void ReadGameRecords(struct GameRecord records[], int* numRecords) {
    FILE* fp;
    fp = fopen("game_records.txt", "r");
    if (fp == NULL) {
        printf("Error opening game_records.txt\n");
        return;
    }

    *numRecords = 0;
    while (*numRecords < MAX_RECORDS && fscanf(fp, "%19[^\n] %d\n", &records[*numRecords].startTime, &records[*numRecords].score) == 2) {
        (*numRecords)++;
    }

    fclose(fp);
}

/**
 * 将得分记录写入文件
 *
 * @param struct GameRecord 游戏记录结构体
 */
void WriteGameRecord(struct GameRecord record) {
    FILE* fp;
    fp = fopen("game_records.txt", "a");
    if (fp == NULL) {
        printf("Error opening game_records.txt\n");
        return;
    }

    fprintf(fp, "%s %d\n", record.startTime, record.score);
    fclose(fp);
}

/**
 * 比较排序
 *
 * @param: *a 记录1
 * @param: *b 记录2
 * @return: int
 */
int CompareGameRecords(const void* a, const void* b) {
    struct GameRecord* recordA = (struct GameRecord*)a;
    struct GameRecord* recordB = (struct GameRecord*)b;

    if (recordA->score == recordB->score) {
        return recordB->startTime - recordA->startTime;
    }
    else {
        return recordB->score - recordA->score;
    }
}

/**
 * 显示游戏排行榜
 */
void DisplayGameRecords() {
    struct GameRecord records[MAX_RECORDS];
    int numRecords = 0;
    system("cls");
    ReadGameRecords(records, &numRecords);

    qsort(records, numRecords, sizeof(struct GameRecord), CompareGameRecords);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

    const int RECORDS_PER_PAGE = 10;
    int numPages = (numRecords + RECORDS_PER_PAGE - 1) / RECORDS_PER_PAGE;
    int currentPage = 1;

    while (1) {
        system("cls");
        printf("排行榜:\n");
        printf("|===============================================|\n");
        printf("|   排名   |   得分   |   开始时间              |\n");
        printf("|===============================================|\n");
        int startIndex = (currentPage - 1) * RECORDS_PER_PAGE;

        int startY = (consoleHeight - 5) / 2 + 1; // 排行榜第一行的位置

        for (int i = startIndex; i < startIndex + RECORDS_PER_PAGE && i < numRecords; i++) {
            printf("|%10d|%10d|%25s|\n", i + 1, records[i].score, records[i].startTime);
            if (i == startIndex) { // 第一次迭代，计算排行榜的实际位置
                startY -= i % RECORDS_PER_PAGE; // 计算排行榜的实际位置
            }
        }
        printf("|===============================================|\n");

        int startX = (consoleWidth - 37) / 2;
        GotoXY(startX, startY + 4);
        printf("第 %d 页 / 共 %d 页\n", currentPage, numPages);

        GotoXY(startX, startY + RECORDS_PER_PAGE + 6);
        printf("按 [上箭头] 或 [下箭头] 翻页，按 [Esc] 返回主菜单");

        int ch = _getch();
        system("cls");
        if (ch == 27) { // Esc
            break;
        }
        else if (ch == 224) { // 非常规按键
            ch = _getch();
            if (ch == 72 && currentPage > 1) { // 上箭头
                currentPage--;
            }
            else if (ch == 80 && currentPage < numPages) { // 下箭头
                currentPage++;
            }
        }
    }
}