#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct accountInfo
{
	char ID[20];
	char pwd[20];
	int role;		//1-ϵͳ����Ա	2-ϵͳ����Ա	3-ѧ��
	int loginFlag;	//1-�ѵ�¼��	0-δ��½��
} acInfo;

typedef struct accountNode
{
	acInfo val;
	struct accountNode* next;
} ACNode;
typedef struct _acList
{
	ACNode* head;
	ACNode* tail;
} ACList;

ACList* InitAcHeadNode();
void InsertAcNode(ACList* aclist, acInfo val);
void readAcInfo(char* FileName, ACList* aclist);
void writeAcInfo(char* FileName, ACList* aclist);

ACNode* acInfoJudge(ACList* aclist, char* ID, char* pwd);
void addAcInfo(ACList* aclist);
