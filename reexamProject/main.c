#define _CRT_SECURE_NO_WARNINGS 1
#include <conio.h>
#include "stuInfo.h"
#include "account.h"

node* list = NULL;
acNode* acList = NULL;
acNode* curAc = NULL;
int chiose = 0;

void menu();
void pause();
void loading();
void keyDown();
void login(acNode* headNode);

int main()
{
	list = InitHeadNode();
	acList = InitAcHeadNode();
	curAc = InitAcHeadNode();
	readStuInfo("data2.txt", list);
	readAcInfo("data1.txt", acList);

	login(curAc);
	loading();
	system("cls");
	system("color 1f");
	while (1)
	{
		keyDown();
	}
	return 0;
}

void menu()
{
	printf("------【学生管理系统】-------\n");
	printf("***** \t1. 创建账号\t*****\n");
	printf("***** \t2. 显示信息\t*****\n");
	printf("***** \t3. 添加信息\t*****\n");
	printf("***** \t4. 删除信息\t*****\n");
	printf("***** \t5. 修改信息\t*****\n");
	printf("***** \t6. 查找信息\t*****\n");
	printf("***** \t7. 数据统计\t*****\n");
	printf("***** \t8. 异常统计\t*****\n");
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

void keyDown()
{
	system("cls");
	menu();
	printf("请输入您要的操作(0~8)：");
	scanf("%d", &chiose);
	if (curAc->val.role == 2 && (chiose == 1 || chiose == 4 || chiose == 5))//系统操作员，删除修改无权限
	{
		printf("抱歉，您没有权限，请联系管理员！\n");
		pause();
		return;
	}
	else if(curAc->val.role == 3 && (chiose == 1 || chiose == 2 || chiose == 3 || chiose == 4 || chiose ==  5 || chiose == 7 || chiose == 8))//学生只有查询权限
	{
		printf("抱歉，您没有权限，请联系管理员！\n");
		pause();
		return;
	}
	switch (chiose)
	{
	case 1:
		system("cls");
		printf("\n\t\t【创建账号】\n\n");
		addAcInfo(acList);
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
		printf("\n\t【添加信息】\n\n");
		addStuInfo(list);
		writeStuInfo("data2.txt", list);
		pause();
		break;
	case 4:
		system("cls");
		printf("\n\t【删除信息】\n\n");
		delStuInfoByID(list);
		writeStuInfo("data2.txt", list);
		pause();
		break;
	case 5:
		system("cls");
		printf("\n\t【修改信息】\n\n");
		upDataInfo(list);
		writeStuInfo("data2.txt", list);
		pause();
		break;
	case 6:
		system("cls");
		int chiose = 0;
		while (1)
		{
			system("cls");
			printf("\n1. 按学号查找\n2. 按姓名查找\n0. 退出\n\n");
			printf("请输入您的选择：");
			scanf("%d", &chiose);
			if (chiose == 1)
			{
				system("cls");
				printf("\n\t\t\t\t\t\t【查找信息】\n\n");
				searchStuInfoByID(list);
				break;
			}
			else if (chiose == 2)
			{
				system("cls");
				printf("\n\t\t\t\t\t\t【查找信息】\n\n");
				searchStuInfoByName(list);
				break;
			}
			else if (chiose == 0)
			{
				goto out;
			}
			printf("选择有误！\n");
			pause();
		}
		pause();
		out:
		break;
	case 7:
		system("cls");
		printf("\n\t\t\t\t\t\t【数据统计】\n\n");
		node* data3 = classifyGroup(list, "学硕");
		node* data4 = classifyGroup(list, "专硕");
		node* data5 = classifyGroup(list, "非全日制");
		data3 = calculateData(data3, "data3.txt");
		data4 = calculateData(data4, "data4.txt");
		data5 = calculateData(data5, "data5.txt");
		printStuInfo(data3);
		printStuInfo(data4);
		printStuInfo(data5);
		printf("统计完成！\n");
		pause();
		break;
	case 8:
		system("cls");
		printf("\n\t\t\t\t\t\t【异常统计】\n\n");
		exceptionCount(list);
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

void login(acNode* headNode)
{
	printf("-------------------------------------------------\n");
	printf("---------------欢迎进入学生管理系统--------------\n");
	printf("-------------------------------------------------\n");
	while (1)
	{
		printf("请输入账号：");
		scanf("%s", headNode->val.ID);
		printf("请输入密码：");
		scanf("%s", headNode->val.pwd);
		acNode* acFlag = acInfoJudge(acList, headNode->val.ID, headNode->val.pwd);
		//账号密码匹配返回地址，不匹配返回NULL
		if (acFlag != NULL)
		{
			headNode->val = acFlag->val;
			//未登陆过，重置密码
			if (acFlag->val.loginFlag == 0)
			{
				printf("请输入新密码：");
				scanf("%s", acFlag->val.pwd);
				acFlag->val.loginFlag = 1;
				writeAcInfo("data1.txt", acList);
			}
			break;
		}

		printf("账号或密码有误，请重新输入！\n");
	}
}