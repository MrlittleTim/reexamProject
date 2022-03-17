#include "stuInfo.h"

char* colInfo[] = { "通信学院", "计算机学院", "光电学院", "自动化学院", "经管学院", "研究生学院",
				   "外语学院", "安法学院", "体育学院", "传媒学院", "先进制造学院", "马克思主义学院" };
node* InitHeadNode()
{
	node* headNode = (node*)malloc(sizeof(node));
	headNode->next = NULL;
	return headNode;
}

node* CreatMemberNode(stuInfo val)
{
	node* posNode = (node*)malloc(sizeof(node));
	posNode->val = val;
	posNode->next = NULL;
	return posNode;
}
int InsertNode(node* headNode, stuInfo val)
{
	int ret = 0;
	node* posNode = CreatMemberNode(val);
	node* p = headNode;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = posNode;
	posNode->next = NULL;
	ret = 1;
	return ret;
}
node* SearchNodeByID(node* headNode, char* ID)
{
	node* p = headNode->next;
	if (p == NULL)
	{
		return NULL;
	}
	while (p != NULL && strcmp(p->val.stuID, ID))
	{
		p = p->next;
	}
	return p;
}
//删除成功返回1，失败返回0
int DelNodeByID(node* headNode, char* ID)
{
	node* posFront = headNode;
	node* pos = headNode->next;
	if (pos == NULL)
	{
		return 0;
	}
	while (pos != NULL && strcmp(pos->val.stuID, ID))
	{
		posFront = posFront->next;
		pos = pos->next;
	}
	if (pos == NULL)
	{
		return 0;
	}
	posFront->next = pos->next;
	free(pos);
	return 1;
}


void printStuInfo(node* headNode)
{
	node* p = headNode->next;

	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"学号", "姓名", "学院", "类别", "体温", "是否咳嗽", "健康状况", "基础课1", "基础课2", "专业课1", "专业课1", "总分");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	while (p)
	{
		printf("%-12s%-10s%-16s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.group, p->val.t, p->val.ks,
			p->val.health, p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
		p = p->next;
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

void addStuInfo(node* headNode)
{
	stuInfo tempData;
	int year;
	int collegeID;
	printf("请输入各项信息（按0退出）：\n");
	while (1)
	{
		printf("学生学号：");
		scanf("%s", tempData.stuID);
		if (tempData.stuID[0] == '0' && tempData.stuID[1] == '\0')
		{
			printf("退出成功！");
			return;
		}
		year = (tempData.stuID[0] - '0') * 1000 + (tempData.stuID[1] - '0') * 100 + 
			(tempData.stuID[2] - '0') * 10 + (tempData.stuID[3] - '0');
		collegeID = (tempData.stuID[4] - '0') * 10 + (tempData.stuID[5] - '0');
		if (tempData.stuID[9] == '\0' && year >= 2016 && year <= 2019 && collegeID >= 1 && collegeID <= 12 )
		{
			break;
		}
		printf("该学号信息无效，请重新输入！\n");
	}
	printf("学生姓名：");
	scanf("%s", tempData.name);
	printf("学生类别：");
	scanf("%s", tempData.group);
	printf("学生体温：");
	scanf("%f", &tempData.t);
	printf("是否咳嗽：");
	scanf("%d", &tempData.ks);
	printf("学生基础课1成绩：");
	scanf("%d", &tempData.score1);
	printf("学生基础课2成绩：");
	scanf("%d", &tempData.score2);
	printf("学生专业课1成绩：");
	scanf("%d", &tempData.score3);
	printf("学生专业课2成绩：");
	scanf("%d", &tempData.score4);
	//判断健康。0为异常，1为正常
	if (tempData.t >= 37.2 || tempData.ks == 1)
	{
		tempData.health = 0;
	}
	else
	{
		tempData.health = 1;
	}
	//计算总分
	tempData.total = tempData.score1 + tempData.score2 + tempData.score3 + tempData.score4;
	//判断学院
	strcpy(tempData.college, colInfo[collegeID - 1]);

	int ret = InsertNode(headNode, tempData);
	if (ret)
	{
		printf("添加成功!\n");
	}
	else
	{
		printf("添加失败!\n");
	}
}

void delStuInfoByID(node* headNode)
{
	int temp;
	char ID[20];
	printf("请输入需要删除学生学号：");
	scanf("%s", ID);
	temp = DelNodeByID(headNode, ID);
	if (temp)
	{
		printf("删除成功！\fn");
	}
	else
	{
		printf("删除失败！\n");
	}
}
void upDataInfo(node* headNode)
{
	char ID[20];
	node* pos;
	while (1)
	{
		printf("请输入需要修改的学生学号（按0退出）：");
		scanf("%s", ID);
		if (ID[0] == '0' && ID[1] == '\0')
		{
			printf("退出成功！");
			return;
		}
		pos = SearchNodeByID(headNode, ID);
		if (pos != NULL)
		{
			int year;
			int collegeID;
			printf("请输入各项信息：\n");
			while (1)
			{
				printf("学生学号：");
				scanf("%s", pos->val.stuID);
				year = (pos->val.stuID[0] - '0') * 1000 + (pos->val.stuID[1] - '0') * 100 +
					(pos->val.stuID[2] - '0') * 10 + (pos->val.stuID[3] - '0');
				collegeID = (pos->val.stuID[4] - '0') * 10 + (pos->val.stuID[5] - '0');
				//ID = (pos->val.stuID[6] - '0') * 100 + (pos->val.stuID[7] - '0') * 10 + (pos->val.stuID[8] - '0');
				if (pos->val.stuID[9] == '\0' && year >= 2016 && year <= 2019 && collegeID >= 1 && collegeID <= 12)
				{
					break;
				}
				printf("该学号信息无效，请重新输入！\n");
			}
			printf("学生姓名：");
			scanf("%s", pos->val.name);
			printf("学生类别：");
			scanf("%s", pos->val.group);
			printf("学生体温：");
			scanf("%f", &pos->val.t);
			printf("是否咳嗽：");
			scanf("%d", &pos->val.ks);
			printf("学生基础课1成绩：");
			scanf("%d", &pos->val.score1);
			printf("学生基础课2成绩：");
			scanf("%d", &pos->val.score2);
			printf("学生专业课1成绩：");
			scanf("%d", &pos->val.score3);
			printf("学生专业课2成绩：");
			scanf("%d", &pos->val.score4);
			//判断健康。0为异常，1为正常
			if (pos->val.t >= 37.2 || pos->val.ks == 1)
			{
				pos->val.health = 0;
			}
			else
			{
				pos->val.health = 1;
			}
			//计算总分
			pos->val.total = pos->val.score1 + pos->val.score2 + pos->val.score3 + pos->val.score4;
			//判断学院
			strcpy(pos->val.college, colInfo[collegeID - 1]);
			printf("修改成功!\n");
			break;
		}
		printf("学号有误，修改失败！\n");
	}
}

void searchStuInfoByID(node* headNode)
{
	char ID[20];
	node* p;
	printf("请输入需要查询的学生学号：");
	scanf("%s", ID);
	p = SearchNodeByID(headNode, ID);
	if (p)
	{
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
		printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
			"学号", "姓名", "学院", "类别", "体温", "是否咳嗽", "健康状况", "基础课1", "基础课2", "专业课1", "专业课1", "总分");
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
		printf("%-12s%-10s%-16s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.group, p->val.t, p->val.ks,
			p->val.health, p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
	}
	else
	{
		printf("查找失败！\n");
	}
	
}
void searchStuInfoByName(node* headNode)
{
	char name[10];
	node* p = headNode->next;
	printf("请输入需要查询的学生姓名：");
	scanf("%s", name);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"学号", "姓名", "学院", "类别", "体温", "是否咳嗽", "健康状况", "基础课1", "基础课2", "专业课1", "专业课1", "总分");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (strstr(p->val.name, name) != NULL)
		{
			printf("%-12s%-10s%-16s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
				p->val.stuID, p->val.name, p->val.college, p->val.group, p->val.t, p->val.ks,
				p->val.health, p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
		}
		p = p->next;
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

node* classifyGroup(node* headNode, char* group)
{
	node* posNode = headNode->next;
	node* newList = InitHeadNode();
	if (posNode == NULL)
	{
		return newList;
	}
	while (posNode != NULL)
	{
		if (!strcmp(posNode->val.group, group))
		{
			InsertNode(newList, posNode->val);
		}
		posNode = posNode->next;
	}
	return newList;
}
int priorityCmp(node* p, node* q)
{
	return p->val.total == q->val.total ? (p->val.score3 == q->val.score3 ? p->val.score4 - q->val.score4 : p->val.score3 - q->val.score3) : p->val.total - q->val.total;
}
//冒泡排序
void sortStuInfo(node* headNode)
{
	for (node* i = headNode->next; i->next->next != NULL; i = i->next)
	{
		int flag = 1;
		for (node* j = headNode->next; j->next != NULL; j = j->next)
		{
			if (priorityCmp(j, j->next) < 0)
			{
				stuInfo temp = j->val;
				j->val = j->next->val;
				j->next->val = temp;
				flag = 0;
			}
		}
		if (flag)
		{
			return;
		}
	}
}
//统计数据
node* calculateData(node* headNode, char* fileName)
{
	if (headNode->next == NULL)
	{
		return;
	}
	sortStuInfo(headNode);
	writeStuInfo(fileName, headNode);
	return headNode;
}

void exceptionCount(node* headNode)
{
	node* posNode = headNode->next;
	if (posNode == NULL)
	{
		return;
	}
	node* newList = InitHeadNode();
	while (posNode)
	{
		if (posNode->val.health == 0)
		{
			InsertNode(newList, posNode->val);
		}
		posNode = posNode->next;
	}
	printStuInfo(newList);
	writeStuInfo("data6.txt", newList);
}
void readStuInfo(char* FileName, node* headNode)
{
	FILE* fp = fopen(FileName, "r");
	if (!fp)
	{
		fp = fopen(FileName, "w");
		return;
	}
	stuInfo tempData;
	while (!feof(fp))
	{
		fscanf(fp, "%12s%10s%20s%10s%8f%10d%10d%10d%10d%10d%10d%10d\n",
			tempData.stuID, tempData.name, tempData.college, tempData.group,
			&tempData.t, &tempData.ks, &tempData.health,
			&tempData.score1, &tempData.score2, &tempData.score3, &tempData.score4, &tempData.total);
		InsertNode(headNode, tempData);
	}
	fclose(fp);
}
void writeStuInfo(char* FileName, node* headNode)
{
	node* p = headNode->next;
	FILE* fp = fopen(FileName, "w");
	while (p)
	{
		fprintf(fp, "%-12s%-10s%-20s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.group,
			p->val.t, p->val.ks, p->val.health,
			p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
		p = p->next;
	}
	fclose(fp);
}