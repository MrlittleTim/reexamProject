#include "account.h"

acNode* InitAcHeadNode()
{
	acNode* headNode = (acNode*)malloc(sizeof(acNode));
	headNode->next = NULL;
	return headNode;
}

acNode* CreatAcMemberNode(acInfo val)
{
	acNode* posNode = (acNode*)malloc(sizeof(acNode));
	posNode->val = val;
	posNode->next = NULL;
	return posNode;
}
int InsertAcNode(acNode* headNode, acInfo val)
{
	int ret = 0;
	acNode* posNode = CreatAcMemberNode(val);
	acNode* p = headNode;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = posNode;
	posNode->next = NULL;
	ret = 1;
	return ret;
}

void readAcInfo(char* FileName, acNode* headNode)

{
	FILE* fp = fopen(FileName, "r");
	if (!fp)
	{
		printf("文件打开错误！\n");
		return;
	}
	acInfo tempData;
	while (!feof(fp))
	{
		fscanf(fp, "%20s%20s%4d%4d\n", tempData.ID, tempData.pwd, &tempData.role, &tempData.loginFlag);
		InsertAcNode(headNode, tempData);
	}
	fclose(fp);
}
void writeAcInfo(char* FileName, acNode* headNode)
{
	acNode* posNode = headNode->next;
	FILE* fp = fopen(FileName, "w");
	while (posNode)
	{
		fprintf(fp, "%-20s%-20s%-4d%-4d\n", posNode->val.ID, posNode->val.pwd, posNode->val.role, posNode->val.loginFlag);
		posNode = posNode->next;
	}
	fclose(fp);
}


//信息正确返回地址，信息有误返回NULL
acNode* acInfoJudge(acNode* headNode, char* ID, char* pwd)
{
	acNode* posNode = headNode->next;
	if (posNode == NULL)
	{
		return NULL;
	}
	while (posNode && (strcmp(posNode->val.ID, ID) || strcmp(posNode->val.pwd, pwd)))
	{
		posNode = posNode->next;
	}
	return posNode;
}


void addAcInfo(acNode* headNode)
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
				int year;
				int collegeID;
				printf("学生学号：");
				scanf("%s", tempData.ID);
				year = (tempData.ID[0] - '0') * 1000 + (tempData.ID[1] - '0') * 100 +
					(tempData.ID[2] - '0') * 10 + (tempData.ID[3] - '0');
				collegeID = (tempData.ID[4] - '0') * 10 + (tempData.ID[5] - '0');
				if (tempData.ID[9] == '\0' && year >= 2016 && year <= 2019 && collegeID >= 1 && collegeID <= 12)
				{
					break;
				}
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
	InsertAcNode(headNode, tempData);
	writeAcInfo("data1.txt", headNode);
	printf("添加成功！");
}