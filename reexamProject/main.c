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
	printf("\n ��2020ѧ����У��������ϵͳ��\n\n");
	printf("-----------------------------\n");
	printf("***** \t1. �����Ϣ\t*****\n");
	printf("***** \t2. ��ʾ��Ϣ\t*****\n");
	printf("***** \t3. ɾ����Ϣ\t*****\n");
	printf("***** \t4. �޸���Ϣ\t*****\n");
	printf("***** \t5. ��ѯͳ��\t*****\n");
	printf("***** \t6. �쳣��¼\t*****\n");
	printf("***** \t7. �쳣Ԥ��\t*****\n");
	printf("***** \t0. �˳�    \t*****\n");
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
	printf("��������Ҫ�Ĳ���(0~8)��");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		system("cls");
		printf("\n\t�������Ϣ��\n\n");
		addStuInfo(list);
		writeStuInfo("data1.txt", list);
		pause();
		break;
	case 2:
		system("cls");
		printf("\n\t\t\t\t\t\t����ʾ��Ϣ��\n\n");
		printStuInfo(list);
		pause();
		break;
	case 3:
		system("cls");
		printf("\n\t��ɾ����Ϣ��\n\n");
		delStuInfoByID(list);
		writeStuInfo("data1.txt", list);
		pause();
		break;
	case 4:
		system("cls");
		printf("\n\t���޸���Ϣ��\n\n");
		updateInfo(list);
		writeStuInfo("data1.txt", list);
		pause();
		break;
	case 5:
		system("cls");
		printf("\n\t\t\t\t\t\t����ѯͳ�ơ�\n\n");
		searchStuInfo(list);
		pause();
		break;
	case 6:
		system("cls");
		printf("\n\t\t\t\t\t\t���쳣��¼��\n\n");
		exceptionCount(list);
		pause();
		break;
	case 7:
		system("cls");
		printf("\n\t\t\t\t\t\t���쳣Ԥ����\n\n");
		exceptionWarning(list);
		pause();
		break;
	case 0:
		exit(0);
		break;
	default:
		printf("������������������(0~8)��");
		system("pause");
		break;
	}
}
