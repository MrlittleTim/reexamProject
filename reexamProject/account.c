#include "account.h"
#include "stuInfo.h"
ACList* InitAcHeadNode()
{
	ACList* aclist = (ACList*)malloc(sizeof(ACList));
	aclist->head = (ACNode*)malloc(sizeof(ACNode));
	aclist->head->next = NULL;
	aclist->tail = aclist->head;
	return aclist;
}

void InsertAcNode(ACList* aclist, acInfo val)
{
	int ret = 0;
	ACNode* p = (ACNode*)malloc(sizeof(ACNode));
	p->val = val;
	p->next = NULL;
	aclist->tail->next = p;
	aclist->tail = p;
}

void readAcInfo(char* FileName, ACList* aclist)

{
	FILE* fp = fopen(FileName, "r");
	if (!fp)
	{
		perror("");
		return;
	}
	acInfo tempData;
	while (!feof(fp))
	{
		fscanf(fp, "%20s%20s%4d%4d\n", tempData.ID, tempData.pwd, &tempData.role, &tempData.loginFlag);
		InsertAcNode(aclist, tempData);
	}
	fclose(fp);
}
void writeAcInfo(char* FileName, ACList* aclist)
{
	ACNode* p = NULL;
	FILE* fp = fopen(FileName, "w");
	for (p = aclist->head->next; p; p = p->next)
	{
		fprintf(fp, "%-20s%-20s%-4d%-4d\n", p->val.ID, p->val.pwd, p->val.role, p->val.loginFlag);
	}
	fclose(fp);
}


//信息正确返回地址，信息有误返回NULL
ACNode* acInfoJudge(ACList* aclist, char* ID, char* pwd)
{
	ACNode* posNode = aclist->head->next;
	if (posNode == NULL)
		return NULL;
	for (; posNode; posNode = posNode->next)
	{
		if (!strcmp(posNode->val.ID, ID) && !strcmp(posNode->val.pwd, pwd))
		{
			break;
		}
	}
	return posNode;
}


void addAcInfo(ACList* aclist)
{
	acInfo tempData;
	tempData.loginFlag = 0;
	while (1)
	{
		printf("请输入各项信息：\n");
		printf("账号类型（1-系统管理员，2-系统操作员，3-学生，0-退出）：");
		scanf("%d", &tempData.role);
		if (tempData.role == 0)
		{
			printf("退出成功！");
			return;
		}
		else if(tempData.role == 3)
		{
			while (1)
			{
				
				printf("学生学号：");
				scanf("%s", tempData.ID);
				if (isStuIDLegal(tempData.ID))
				{
					break;
				}
				else
					printf("该学号信息无效，请重新输入！\n");
			}
			break;
		}
		else if (tempData.role == 1 || tempData.role == 2)
		{
			printf("账号信息：");
			scanf("%s", tempData.ID);
			break;
		}
		else
		{
			printf("输入有误！");
		}

	}
	strcpy(tempData.pwd, tempData.ID);
	InsertAcNode(aclist, tempData);
	writeAcInfo("data1.txt", aclist);
	printf("添加成功！");
}