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
	printf("------��ѧ������ϵͳ��-------\n");
	printf("***** \t1. �����˺�\t*****\n");
	printf("***** \t2. ��ʾ��Ϣ\t*****\n");
	printf("***** \t3. �����Ϣ\t*****\n");
	printf("***** \t4. ɾ����Ϣ\t*****\n");
	printf("***** \t5. �޸���Ϣ\t*****\n");
	printf("***** \t6. ������Ϣ\t*****\n");
	printf("***** \t7. ����ͳ��\t*****\n");
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

void keyDown(List* list, ACNode* curNode)
{
	int choose;
	system("cls");
	menu();
	printf("��������Ҫ�Ĳ���(0~8)��");
	scanf("%d", &choose);
	if (curNode->val.role == 2 && (choose == 1 || choose == 4 || choose == 5))//ϵͳ����Ա��ɾ���޸���Ȩ��
	{
		printf("��Ǹ����û��Ȩ�ޣ�����ϵ����Ա��\n");
		pause();
		return;
	}
	else if(curNode->val.role == 3 && (choose == 1 || choose == 2 || choose == 3 || choose == 4 || choose ==  5 || choose == 7 || choose == 8))//ѧ��ֻ�в�ѯȨ��
	{
		printf("��Ǹ����û��Ȩ�ޣ�����ϵ����Ա��\n");
		pause();
		return;
	}
	switch (choose)
	{
	case 1:
		system("cls");
		printf("\n\t\t�������˺š�\n\n");
		//addAcInfo(acList);
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
		printf("\n\t�������Ϣ��\n\n");
		addStuInfo(list);
		writeStuInfo("data2.txt", list);
		pause();
		break;
	case 4:
		system("cls");
		printf("\n\t��ɾ����Ϣ��\n\n");
		delStuInfoByID(list);
		writeStuInfo("data2.txt", list);
		pause();
		break;
	case 5:
		system("cls");
		printf("\n\t���޸���Ϣ��\n\n");
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
			printf("\n1. ��ѧ�Ų���\n2. ����������\n0. �˳�\n\n");
			printf("����������ѡ��");
			scanf("%d", &choose);
			if (choose == 1)
			{
				system("cls");
				printf("\n\t\t\t\t\t\t��������Ϣ��\n\n");
				searchStuInfoByID(list);
				break;
			}
			else if (choose == 2)
			{
				system("cls");
				printf("\n\t\t\t\t\t\t��������Ϣ��\n\n");
				searchStuInfoByName(list);
				break;
			}
			else if (choose == 0)
			{
				goto out;
			}
			printf("ѡ������\n");
			pause();
		}
		pause();
		out:
		break;
	case 7:
		system("cls");
		printf("\n\t\t\t\t\t\t������ͳ�ơ�\n\n");
		List* data3 = classifyGroup(list, "ѧ˶");
		List* data4 = classifyGroup(list, "ר˶");
		List* data5 = classifyGroup(list, "��ȫ����");
		data3 = calculateData(data3, "data3.txt");
		data4 = calculateData(data4, "data4.txt");
		data5 = calculateData(data5, "data5.txt");
		printStuInfo(data3);
		printStuInfo(data4);
		printStuInfo(data5);
		printf("ͳ����ɣ�\n");
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

void login(ACList* acList, ACNode* curNode)
{
	printf("-------------------------------------------------\n");
	printf("---------------��ӭ����ѧ������ϵͳ--------------\n");
	printf("-------------------------------------------------\n");
	while (1)
	{
		acInfo val;
		printf("�������˺ţ�");
		scanf("%s", val.ID);
		printf("���������룺");
		scanf("%s", val.pwd);
		ACNode* acFlag = acInfoJudge(acList, val.ID, val.pwd);
		//�˺�����ƥ�䷵�ص�ַ����ƥ�䷵��NULL
		if (acFlag)
		{
			curNode->val = acFlag->val;
			curNode->next = NULL;
			//δ��½������������
			if (acFlag->val.loginFlag == 0)
			{
				printf("�����������룺");
				scanf("%s", acFlag->val.pwd);
				acFlag->val.loginFlag = 1;
				writeAcInfo("data1.txt", acList);
			}
			break;
		}
		printf("�˺Ż������������������룡\n");
	}
}