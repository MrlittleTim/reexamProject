#define _CRT_SECURE_NO_WARNINGS 1
#include <conio.h>
#include "stuInfo.h"

void menu();
void pause();
void loading();
void keyDown(List* list);

int main()
{
	List* list = list_init();
	readStuInfo("./data1.txt", list);
	
	loading();
	system("cls");
	system("color 1f");
	while (1)
	{
		keyDown(list);
	}
	return 0;
}

void menu()
{
	printf("\n 【2020学生返校健康管理系统】\n\n");
	printf("-----------------------------\n");
	printf("***** \t1. 添加信息\t*****\n");
	printf("***** \t2. 显示信息\t*****\n");
	printf("***** \t3. 删除信息\t*****\n");
	printf("***** \t4. 修改信息\t*****\n");
	printf("***** \t5. 查询统计\t*****\n");
	printf("***** \t6. 异常记录\t*****\n");
	printf("***** \t7. 异常预警\t*****\n");
	printf("***** \t0. 退出    \t*****\n");
	printf("-----------------------------\n");

}
void pause()
{
	fflush(stdin);
	getch();
}

void loading()
{
	printf("\n");
	for (int n = 1; n < 50; n++)
	{
		printf("*");
		Sleep(15);
	}
}

void keyDown(List* list)
{
	int choose;
	system("cls");
	menu();
	printf("请输入您要的操作(0~8)：");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		system("cls");
		printf("\n\t【添加信息】\n\n");
		addStuInfo(list);
		writeStuInfo("data1.txt", list);
		pause();
		break;
	case 2:
		system("cls");
		printf("\n\t\t\t\t\t\t【显示信息】\n\n");
		printStuInfo(list);
		pause();
		break;
	case 3:
		system("cls");
		printf("\n\t【删除信息】\n\n");
		delStuInfoByID(list);
		writeStuInfo("data1.txt", list);
		pause();
		break;
	case 4:
		system("cls");
		printf("\n\t【修改信息】\n\n");
		updateInfo(list);
		writeStuInfo("data1.txt", list);
		pause();
		break;
	case 5:
		system("cls");
		printf("\n\t\t\t\t\t\t【查询统计】\n\n");
		searchStuInfo(list);
		pause();
		break;
	case 6:
		system("cls");
		printf("\n\t\t\t\t\t\t【异常记录】\n\n");
		exceptionCount(list);
		pause();
		break;
	case 7:
		system("cls");
		printf("\n\t\t\t\t\t\t【异常预警】\n\n");
		exceptionWarning(list);
		pause();
		break;
	case 0:
		exit(0);
		break;
	default:
		printf("输入有误，请重新输入(0~8)：");
		system("pause");
		break;
	}
}
