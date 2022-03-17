#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct accountInfo
{
	char ID[20];
	char pwd[20];
	int role;		//1-系统管理员	2-系统操作员	3-学生
	int loginFlag;	//1-已登录过	0-未登陆过
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
