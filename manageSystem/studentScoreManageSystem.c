/*************************************************
* Project：学生成绩管理系统
* Function：输入学生成绩记录、增删查改、计算排序等
* Author：chenyb
* time：2023/03/15
* version：V0.1
**************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

#define STU_NUM 50		// 教学班学生人数上限
#define COURSE_NUM 10	// 一学期的课程门数上限
#define NAME_LEN 10		// 学生姓名（字符串）最大长度
#define POS_X1 35		// 1.菜单页，第一列所有功能输出起始位置的x坐标值 // 2.排序之后输出提示起点的x坐标值

#define POS_X2 40		// 输入模块的提示语句起点的x坐标值
#define POS_X3 50		// 第一次调用输入模块或磁盘数据读入模块功能以外的其他功能，提示“系统中尚无学生成绩信息，请先输入！”的起始位置的x坐标值
#define POS_X4 65		// 菜单页，第二列所有功能输出起始位置的x坐标值
#define POS_Y 3			// 排序之后输出提示起点的y坐标值

typedef struct student
{
	long num;	// 学号
	char name[NAME_LEN]; // 姓名
	float score[COURSE_NUM]; // 各门课程成绩
	float sum; // 各门课程的总分
	float aver; // 各门课程的平均分
}STU;

// 自定义函数声明
int Menu(void);
// 操作菜单
void SetPosition(int x, int y);
// 设置输出内容在控制台窗口中的起始位置
void InputRecord(int* n, int* m, STU* stu);
void CalculateScoreOfStudent(int n, int m, STU stu[]);
void CalculateScoreOfCourse(int n, int m, STU* stu);
void WritetoFile(int n, int m, STU stu[]);
int ReadfromFile(int* n, int* m, STU stu[], int* first);
void AppendRecord(int* n, int m, STU stu[]);
void SearchByNumber(int n, int m, STU* stu);
void SearchByName(int n, int m, STU* stu);
void DeleteRecord(int* n, int m, STU stu[]);
void ModifyRecord(int n, int m, STU stu[]);
void PrintRecord(int n, int m, STU* stu);
void SortByName(int n, int m, STU stu[]);
void SortByNum(int n, int m, STU* stu);
void SortByScore(int n, int m, STU* stu, int (*compare)(float a, float b));
int Descending(float a, float b);
int Ascending(float a, float b);
void StatisticAnalysis(int n, int m, STU* stu);

int main()
{
	int n = 0;
	int m = 0;
	int i, j;
	char ch;
	int first = 1;
	STU stu[STU_NUM];

	system("mode con cols = 130 lines = 60");
	system("color 0E");
	while (1) {
		system("cls");
		ch = Menu();
		switch (ch)
		{
		case 1:
			system("cls");
			InputRecord(&n, &m, stu);
			first = 0;
			break;
		case 2:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，清先输入!\n");
				system("pause");
				break;
			}
			AppendRecord(&n, m, stu);
			system("pause");
			break;
		case 3:
			system("cls");
			if (first) {
				printf("系统中尚无学生成绩信息，清先输入!\n");
				system("pause");
				break;
			}
			DeleteRecord(&n, m, stu);
			system("pause");
			break;
		case 4:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			SearchByNumber(n, m, stu);
			system("pause");
			break;
		case 5:
			system("cls");
			if (first) {
				printf("系统中尚无学生信息，请先输入!\n");
				system("pause");
				break;
			}
			SearchByName(n, m, stu);
			system("pause");
			break;
		case 6:
			system("cls");
			if (first) {
				printf("系统中尚无学生信息，请先输入!\n");
				system("pause");
				break;
			}
			ModifyRecord(n, m, stu);
			system("pause");
			break;
		case 7:
			system("cls");
			if (first) {
				printf("系统中尚无学生信息，请先输入!\n");
				system("pause");
				break;
			}
			CalculateScoreOfStudent(n, m, stu);
			system("pause");
		case 8:
			system("cls");
			if (first) {
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				_getch();
				break;
			}
			CalculateScoreOfCourse(n, m, stu);
			_getch();
			break;
		case 9:
			system("cls");
			if (first) {
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortByNum(n, m, stu);
			getch();
			break;
		case 10:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortByName(n, m, stu);
			getch();
			break;
		case 11:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortByScore(n, m, stu, Descending);
			_getch();
			break;
		case 12:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				_getch();
				break;
			}
			SortByScore(n, m, stu, Ascending);
			_getch();
			break;
		case 13:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				_getch();
				break;
			}
			StatisticAnalysis(n, m, stu);
			getch();
			break;
		case 14:
			system("cls");
			if (first) {
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				_getch();
				break;
			}
			PrintRecord(n, m, stu);
			_getch();
			break;
		case 15:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				_getch();
				break;
			}
			WritetoFile(n, m, stu);
			_getch();
			break;
		case 16:
			system("cls");
			if (ReadfromFile(&n, &m, stu, &first) || first)
			{
				SetPosition(POS_X1, 10);
				printf("尚未输入学生信息或文件打开失败，请先检查!\n");
				_getch();
				break;
			}
			_getch();
			break;
		default:
			break;
		}
	}
}

/**
 * 设置文字输出的起始位置
 *
 * @param x x坐标
 * @param y y坐标
 * @return void
 */
void SetPosition(int x, int y) {
	HANDLE handle;
	COORD pos;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

/**
 * 主菜单
 *
 * @return int 功能编号
 */
int Menu(void) {
	int posy = 5;
	int option;
	int i, j;
	SetPosition(POS_X3, posy);
	printf("学生成绩管理系统\n");

	// 输出系统名字和功能说明之间的两行短横线
	for (i = 0; i < 2; i++) {
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++) {
			printf("-");
		}
	}

	// 输出系统支持的功能和对应的功能代号
	SetPosition(POS_X1, ++posy);
	printf("1.输入学生信息");
	SetPosition(POS_X4, posy);
	printf("2.增加学生成绩");
	SetPosition(POS_X1, posy += 2);
	printf("3.删除学生信息");
	SetPosition(POS_X4, posy);
	printf("4.按学号查找记录");
	SetPosition(POS_X1, posy += 2);
	printf("5.按照姓名查找记录");
	SetPosition(POS_X4, posy);
	printf("6.修改学生信息");
	SetPosition(POS_X1, posy += 2);
	printf("7.计算学生成绩");
	SetPosition(POS_X4, posy);
	printf("8.计算课程成绩");
	SetPosition(POS_X1, posy += 2);
	printf("9.按学号排序");
	SetPosition(POS_X4, posy);
	printf("10.按姓名排序");
	SetPosition(POS_X1, posy += 2);
	printf("11.按总成绩降序排序");
	SetPosition(POS_X4, posy);
	printf("12.按总成绩升序排序");
	SetPosition(POS_X1, posy += 2);
	printf("13.学生成绩统计");
	SetPosition(POS_X4, posy);
	printf("14.打印学生记录");
	SetPosition(POS_X1, posy += 2);
	printf("15.学生记录存盘");
	SetPosition(POS_X4, posy);
	printf("16.从磁盘读取学生记录");
	SetPosition(POS_X1, posy += 2);

	// 输出系统支持的功能与输入提示语之间的两行短横线
	for (i = 0; i < 2; i++) {
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++) {
			printf("-");
		}
	}

	// 提示用户输入所要执行的功能代号
	SetPosition(POS_X1, ++posy);
	printf("请选择你想要进行的操作[0~16]：[  ]\b\b\b");
	scanf("%d", &option);
	return option;
}

/**
 * 输入学生信息
 *
 * @param n
 * @param m
 * @param stu
 */
void InputRecord(int* n, int* m, STU* stu) {
	int i, j;
	int posy = 6;
	SetPosition(POS_X2, posy);
	printf("输入学生人数(n < %d):", STU_NUM);
	scanf("%d", n);
	SetPosition(POS_X2, posy += 2);
	printf("输入课程门数(m < %d):", COURSE_NUM);
	scanf("%d", m);
	for (i = 0; i < 2; i++)
	{
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++) {
			printf("-");
		}
	}

	SetPosition(POS_X2, ++posy);
	printf("输入学生的学号、姓名和各门课程成绩：");
	for (i = 0; i < *n; i++)
	{
		SetPosition(POS_X2, ++posy);
		printf("输入第%d个学生信息:\t", i + 1);
		scanf("%ld%s", &stu[i].num, stu[i].name, sizeof(stu[i].name));
		for (j = 0; j < *m; j++) {
			scanf("%f", &stu[i].score[j]);
		}
	}

}

/**
 * @brief
 *
 * @param n
 * @param m
 * @param stu
 */
void CalculateScoreOfStudent(int n, int m, STU stu[]) {
	int i, j;
	printf("每个学生各门课程总分和平均分为：\n");
	for (i = 0; i < n; i++) {
		stu[i].sum = 0;
		for (j = 0; j < m; j++) {
			stu[i].sum += stu[i].score[j];
		}
		stu[i].aver = stu[i].sum / m;
		printf("第%d个学生:总分=%.2f,平均分=%.2f\n", i + 1, stu[i].sum, stu[i].aver);
	}
}

/**
 * @brief
 *
 * @param n
 * @param m
 * @param stu
 */
void CalculateScoreOfCourse(int n, int m, STU* stu) {
	int i, j;
	float sum[COURSE_NUM], aver[COURSE_NUM];
	int posy = 7;
	SetPosition(POS_X1, posy);
	printf("各门课程的总分和平均分的计算结果为：");
	for (j = 0; j < m; j++) {
		sum[j] = 0;
		for (i = 0; i < n; i++)
		{
			sum[j] += stu[i].score[j];
		}
		aver[j] = sum[j] / n;
		SetPosition(POS_X1, ++posy);
		printf("第%d门课程:总分=%.2f,平均分=%.2f\n", j + 1, sum[j], aver[j]);
	}
}

void WritetoFile(int n, int m, STU stu[]) {
	int i, j;
	// 定义文件指针
	FILE* fp;
	// 打开文件，指定对文件的处理方式为写入
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		printf("文件 student.txt 无法正常打开！");
		exit(0);
	}

	// 将数据按指定格式写入文件，包括学生人数n，课程门数及每个学生的信息
	fprintf(fp, "%10d%10d\n", n, m);
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%10ld%10s", stu[i].num, stu[i].name);
		for (j = 0; j < m; j++)
		{
			fprintf(fp, "%10.1f", stu[i].score[j]);
		}
		fprintf(fp, "%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
	}

	// 关闭文件
	fclose(fp);
	printf("存盘完毕！\n");
}

int ReadfromFile(int* n, int* m, STU stu[], int* first) {
	FILE* fp;
	int i, j;
	int posy = 8;
	SetPosition(POS_X1, posy);
	if ((fp = fopen("student.txt", "r")) == NULL) {
		printf("磁盘空间student.txt无法打开");
		return 1;
	}

	// 将数据按指定格式从磁盘文件中读出，包括学生人数n、课程门数m以及每位学生的信息
	fscanf(fp, "%10d%10d", n, m);

	for (i = 0; i < *n; i++)
	{
		fscanf(fp, "%10ld", &stu[i].num);
		fscanf(fp, "%10s", stu[i].name);
		for (j = 0; j < *m; j++)
		{
			fscanf(fp, "%10f", &stu[i].score[j]);
		}
		fscanf(fp, "%10f%10f", &stu[i].sum, &stu[i].aver);
	}
	*first = 0;

	fclose(fp);
	printf("数据从磁盘读取完毕！");
	return 0;
}

/**
 * 增加学生记录一条至多条学生记录
 *
 * @param n
 * @param m
 * @param stu
 */
void AppendRecord(int* n, int m, STU stu[]) {
	int i, j;
	int num_record;
	printf("请输入需要增加的学生记录条数：");
	scanf("%d", &num_record);
	while (*n + num_record > STU_NUM) {
		printf("要增加的记录条数太多，请重新输入：");
		scanf("%d", &num_record);
	}

	for (i = *n; i < *n + num_record; i++)
	{
		printf("输入第%d个学生信息：\t", i + 1);
		scanf("%ld%s", &stu[i].num, stu[i].name);
		for (j = 0; j < m; j++)
		{
			scanf("%f", &stu[i].score[j]);
		}
	}

	*n = *n + num_record;
	printf("添加完毕！\n");;
	return;
}

/**
 * 按学号查找学生记录
 *
 * @param n
 * @param m
 * @param stu
 */
void SearchByNumber(int n, int m, STU* stu) {
	long id;
	int i, j;
	printf("请输入你要查找的学生的学号：");
	scanf("%ld", &id);
	for (i = 0; i < n; i++)
	{
		if (stu[i].num == id)
		{
			printf("找到了，该学号对应的学生信息为：\n");
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}
			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
			return;
		}
	}
	printf("未找到这个学号对应的学生记录\n");
	return;
}

/**
 * 按姓名查找学生记录
 *
 * @param n
 * @param m
 * @param stu
 */
void SearchByName(int n, int m, STU* stu) {
	int flag = 1;
	int i, j;
	int k = 0;
	char name[NAME_LEN];
	printf("请输入你要查找的学生的姓名：");
	scanf("%s", name);
	for (i = 0; i < n; i++)
	{
		if (strcmp(stu[i].name, name) == 0)
		{
			printf("找到了，第%d学生信息为：\n", ++k);
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}
			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
			flag = 0;
		}
	}
	if (flag)
	{
		printf("未找到这个姓名对应的学生记录\n");
	}
	return;
}

void DeleteRecord(int* n, int m, STU stu[]) {
	int i, j;
	long id;
	char ch;
	printf("请输入你要删除学生信息对应的学号：");
	scanf("%ld", &id);
	for (i = 0; i < *n; i++)
	{
		if (stu[i].num == id)
		{
			printf("找到了该生记录，信息为：\n");
			printf("%10lf%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}

			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
			printf("请确认是否需要删除这条记录？(Y/y)或(N/n)：");
			getchar();
			scanf("%c", &ch);
			if (ch == 'Y' || ch == 'y')
			{
				for (j = i; j < *n - 1; j++)
				{
					stu[j] = stu[j + 1];
				}
				(*n)--;
				printf("删除完毕\n");
				return;
			}
			else if (ch == 'N' || ch == 'n')
			{
				printf("找到了该学生记录，但不删除\n");
				return;
			}
			else
			{
				printf("输入出错！\n");
				return;
			}
		}
	}
	printf("未找到该生记录！\n");
	return;
}

void ModifyRecord(int n, int m, STU stu[]) {
	int i, j;
	long id;
	char ch;
	printf("请输入需要修改信息对应的学号：");

	scanf("%ld", &id);
	for (i = 0; i < n; i++)
	{
		if (stu[i].num == id)
		{
			printf("找到了该生记录，信息为：\n");
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}

			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
			printf("请确认是否需要修改这条记录？(Y/y)或(N/n)：");
			getchar();
			scanf("%c", &ch);

			if (ch == 'Y' || ch == 'y')
			{
				printf("请输入要修改的学生信息：");
				scanf("%ld%s", &stu[i].num, stu[i].name);
				stu[i].sum = 0;
				for (j = 0; j < m; j++)
				{
					scanf("%f", &stu[i].score[j]);
					stu[i].sum += stu[i].score[j];
				}
				stu[i].aver = stu[i].sum / n;
				printf("修改完毕！\n");
				return;
			}
			else if (ch == 'N' || ch == 'n')
			{
				printf("找到了该生记录，但不修改！\n");
				return;
			}
			else {
				printf("输入错误！\n");
				return;
			}
		}
	}
	printf("未找到该生记录！\n");
	return;
}

/**
 * 输出所有学生记录
 *
 * @param n
 * @param m
 * @param stu
 */
void PrintRecord(int n, int m, STU* stu) {
	int i, j;
	printf("学号\t\t姓名\t\t");
	for (j = 0; j < m; j++)
	{
		printf("课程%d\t\t", j + 1);
	}
	printf("总分\t\t平均分\n");

	for (i = 0; i < n; i++)
	{
		printf("%-16ld%-16s", stu[i].num, stu[i].name);
		for (j = 0; j < m; j++) {
			printf("%-16.1lf", stu[i].score[j]);
		}
		printf("%-16.1lf%-16.1lf\n", stu[i].sum, stu[i].aver);
	}
	return;
}

/**
 * 按照学生姓名字典顺序对所有学生记录从小到大排序
 *
 * @param n
 * @param m
 * @param stu
 */
void SortByName(int n, int m, STU stu[]) {
	int i, j;
	STU temp;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (strcmp(stu[j].name, stu[j + 1].name) > 0)
			{
				temp = stu[j];
				stu[j] = stu[j + 1];
				stu[j + 1] = temp;
			}
		}
	}
	printf("按姓名字典对学生记录排序完毕");
	return;
}

/**
 * 按照学号对所有学生记录从小到大排序
 *
 * @param n
 * @param m
 * @param stu
 */
void SortByNum(int n, int m, STU* stu) {
	int i, j;
	int k;
	STU temp;

	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (stu[j].num < stu[k].num)
			{
				k = j;
			}
		}
		if (k != i)
		{
			temp = stu[k];
			stu[k] = stu[i];
			stu[i] = temp;
		}
	}
	printf("按学号从小到大对学生记录排序完毕");
}

/**
 * 按照总成绩对所有学生记录升序排序
 *
 * @param n
 * @param m
 * @param stu
 */
void SortByScore(int n, int m, STU* stu, int (*compare)(float a, float b)) {
	int i, j;
	int k;
	STU temp;

	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if ((*compare)(stu[j].sum, stu[k].sum))
			{
				k = j;
			}
		}
		if (k != i)
		{
			temp = stu[k];
			stu[k] = stu[i];
			stu[i] = temp;
		}
	}
	printf("按总分对学生记录升序排序完毕");
}

/**
 * 规定降序排序规则
 *
 * @param a
 * @param b
 * @return int
 */
int Descending(float a, float b) {
	return a > b;
}

/**
 * 规定升序排序规则
 *
 * @param a
 * @param b
 * @return int
 */
int Ascending(float a, float b) {
	return a < b;
}

void StatisticAnalysis(int n, int m, STU* stu) {
	int i, j, t[6];

	for (j = 0; j < m; j++) {
		printf("\n课程%d成绩统计结果为：\n", j + 1);
		printf("分数段\t人数\t占比\n");

		memset(t, 0, sizeof(t));
		for (i = 0; i < n; i++)
		{
			if (stu[i].score[j] >= 0 && stu[i].score[j] < 60)
			{
				t[0]++;
			}
			else if (stu[i].score[j] < 70)
			{
				t[1]++;
			}
			else if (stu[i].score[j] < 80)
			{
				t[2]++;
			}
			else if (stu[i].score[j] < 90)
			{
				t[3]++;
			}
			else if (stu[i].score[j] < 100)
			{
				t[4]++;
			}
			else if (stu[i].score[j] == 100)
			{
				t[5]++;
			}
		}

		for (i = 0; i < 6; i++)
		{
			if (i == 0)
			{
				printf("<60\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
			}
			else if (i == 5)
			{
				printf("100\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
			}
			else
			{
				printf("%d-%d\t%d\t%.2f%%\n", (i + 5) * 10, (i + 5) * 10 + 9, t[i], (float)t[i] / n * 100);
			}
		}
		printf("\n学生成绩平均分统计结果为：\n");
		printf("分数段\t人数\t占比\n");
		memset(t, 0, sizeof(t));
		for (i = 0; i < n; i++)
		{
			if (stu[i].aver >= 0 && stu[i].aver < 60)
			{
				t[0]++;
			}
			else if (stu[i].aver < 70)
			{
				t[1]++;
			}
			else if (stu[i].aver < 80)
			{
				t[2]++;
			}
			else if (stu[i].aver < 90)
			{
				t[3]++;
			}
			else if (stu[i].aver < 100)
			{
				t[4]++;
			}
			else if (stu[i].aver == 10)
			{
				t[5]++;
			}
		}

		for (i = 0; i < 6; i++)
		{
			if (i == 0)
			{
				printf("<60\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
			}
			else if (i == 5)
			{
				printf("100\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
			}
			else
			{
				printf("%d-%d\t%d\t%.2f%%\n", (i + 5) * 10, (i + 5) * 10 + 9, t[i], (float)t[i] / n * 100);
			}
		}
	}
}