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
}acInfo;

typedef struct accountNode
{
	acInfo val;
	struct accountNode* next;
}acNode;

acNode* InitAcHeadNode();
acNode* CreatAcMemberNode(acInfo val);
int InsertAcNode(acNode* headNode, acInfo val);
void readAcInfo(char* FileName, acNode* headNode);
void writeAcInfo(char* FileName, acNode* headNode);

acNode* acInfoJudge(acNode* headNode, char* ID, char* pwd);
void addAcInfo(acNode* headNode);
