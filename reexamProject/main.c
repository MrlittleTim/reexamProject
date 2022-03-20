#define _CRT_SECURE_NO_WARNINGS 1
#include <conio.h>
#include "stuInfo.h"
#include "account.h"

void menu();
void pause();
void loading();
void keyDown(List* list, ACNode* curNode);
void login(ACList* acList, ACNode* curNode);

int main()
{
	List* list = list_init();
	readStuInfo("./data2.txt", list);
	ACList* acList = InitAcHeadNode();
	readAcInfo("data1.txt", acList);
	ACNode* curNode = (ACNode*)malloc(sizeof(ACNode));

	login(acList, curNode);
	loading();
	system("cls");
	system("color 1f");
	while (1)
	{
		keyDown(list, curNode);
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

void keyDown(List* list, ACNode* curNode)
{
	int choose;
	system("cls");
	menu();
	printf("请输入您要的操作(0~8)：");
	scanf("%d", &choose);
	if (curNode->val.role == 2 && (choose == 1 || choose == 4 || choose == 5))//系统操作员，删除修改无权限
	{
		printf("抱歉，您没有权限，请联系管理员！\n");
		pause();
		return;
	}
	else if(curNode->val.role == 3 && (choose == 1 || choose == 2 || choose == 3 || choose == 4 || choose ==  5 || choose == 7 || choose == 8))//学生只有查询权限
	{
		printf("抱歉，您没有权限，请联系管理员！\n");
		pause();
		return;
	}
	switch (choose)
	{
	case 1:
		system("cls");
		printf("\n\t\t【创建账号】\n\n");
		//addAcInfo(acList);
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
		updateInfo(list);
		writeStuInfo("data2.txt", list);
		pause();
		break;
	case 6:
		system("cls");
		int choose = 0;
		while (1)
		{
			system("cls");
			printf("\n1. 按学号查找\n2. 按姓名查找\n0. 退出\n\n");
			printf("请输入您的选择：");
			scanf("%d", &choose);
			if (choose == 1)
			{
				system("cls");
				printf("\n\t\t\t\t\t\t【查找信息】\n\n");
				searchStuInfoByID(list);
				break;
			}
			else if (choose == 2)
			{
				system("cls");
				printf("\n\t\t\t\t\t\t【查找信息】\n\n");
				searchStuInfoByName(list);
				break;
			}
			else if (choose == 0)
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
		List* data3 = classifyGroup(list, "学硕");
		List* data4 = classifyGroup(list, "专硕");
		List* data5 = classifyGroup(list, "非全日制");
		data3 = calculateData(data3, "data3.txt");
		data4 = calculateData(data4, "data4.txt");
		data5 = calculateData(data5, "data5.txt");
		printStuInfo(data3);
		printStuInfo(data4);
		printStuInfo(data5);
		printf("统计完成！\n");
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

void login(ACList* acList, ACNode* curNode)
{
	printf("-------------------------------------------------\n");
	printf("---------------欢迎进入学生管理系统--------------\n");
	printf("-------------------------------------------------\n");
	while (1)
	{
		acInfo val;
		printf("请输入账号：");
		scanf("%s", val.ID);
		printf("请输入密码：");
		scanf("%s", val.pwd);
		ACNode* acFlag = acInfoJudge(acList, val.ID, val.pwd);
		//账号密码匹配返回地址，不匹配返回NULL
		if (acFlag)
		{
			curNode->val = acFlag->val;
			curNode->next = NULL;
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