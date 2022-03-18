#include "stuInfo.h"

char* colInfo[] = { "通信学院", "计算机学院", "光电学院", "自动化学院", "经管学院", "研究生学院",
				   "外语学院", "安法学院", "体育学院", "传媒学院", "先进制造学院", "马克思主义学院" };
List* list_init()
{
	List* list = (List*)malloc(sizeof(List));
	list->head = (Node*)malloc(sizeof(Node));
	list->head->next = NULL;
	list->tail = list->head;
	return list;
}

void list_insert(List* list, stuInfo val)
{
	int ret = 0;
	Node* p = (Node*)malloc(sizeof(Node));
	p->val = val;
	p->next = NULL;
	list->tail->next = p;
	list->tail = p;
}
Node* list_search_byID(List* list, char* ID)
{
	Node* p = NULL;
	for (p = list->head->next; p; p = p->next)
	{
		if (!strcmp(p->val.stuID, ID))
		{
			break;
		}
	}
	return p;
}
//删除成功返回1，失败返回0
int list_del_byID(List* list, char* ID)
{
	int ret = 0;
	Node* pFront = NULL;
	Node* p = NULL;
	for (pFront = list->head, p = list->head->next; p; pFront = pFront->next, p = p->next)
	{
		if (!strcmp(p->val.stuID, ID))
		{
			pFront->next = p->next;
			free(p);
			ret = 1;
			break;
		}
	}
	return ret;
}

void printStuInfo(List* list)
{
	Node* p = NULL;
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"学号", "姓名", "学院", "类别", "体温", "是否咳嗽", "健康状况", "基础课1", "基础课2", "专业课1", "专业课1", "总分");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	for (p = list->head->next; p; p = p->next)
	{
		printf("%-12s%-10s%-16s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.group, p->val.t, p->val.ks,
			p->val.health, p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}
int isStuIDLegal(char* stuID)
{
	int ret = 0;
	int year = 0;
	int collegeID = 0;
	char years[5] = { 0 };
	char collegeIDs[3] = { 0 };
	strncpy(years, stuID, 4);
	strncpy(collegeIDs, stuID + 4, 2);
	year = atoi(years);
	collegeID = atoi(collegeIDs);
	if (strlen(stuID) == 9
		&& year >= 2016 && year <= 2019
		&& collegeID >= 1 && collegeID <= 12)
	{
		ret = 1;
	}
	return ret;
}
void addStuInfo(List* list)
{
	stuInfo tempData;
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
		
		if (isStuIDLegal(tempData.stuID))
		{
			if (list_search_byID(list, tempData.stuID) == 0)
			{
				break;
			}
			else
				printf("学号已存在！\n");
			
		}
		else
			printf("学号无效，请重新输入！\n");
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
	int collegeID = 0;
	char collegeIDs[3] = { 0 };
	strncpy(collegeIDs, tempData.stuID + 4, 2);
	collegeID = atoi(collegeIDs);
	strcpy(tempData.college, colInfo[collegeID - 1]);
	list_insert(list, tempData);
	printf("添加成功!\n");
	
}

void delStuInfoByID(List* list)
{
	int temp;
	char ID[20];
	printf("请输入需要删除学生学号：");
	scanf("%s", ID);
	temp = list_del_byID(list, ID);
	if (temp)
	{
		printf("删除成功！\n");
	}
	else
	{
		printf("删除失败！\n");
	}
}
void updateInfo(List* list)
{
	char ID[20];
	Node* pos;
	while (1)
	{
		printf("请输入需要修改的学生学号（按0退出）：");
		scanf("%s", ID);
		if (ID[0] == '0' && ID[1] == '\0')
		{
			printf("退出成功！");
			return;
		}
		pos = list_search_byID(list, ID);
		if (pos)
		{
			strcpy(pos->val.stuID, ID);
			printf("请输入各项信息：\n");
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
				pos->val.health = 0;
			else
				pos->val.health = 1;
			//计算总分
			pos->val.total = pos->val.score1 + pos->val.score2 + pos->val.score3 + pos->val.score4;
			//判断学院
			int collegeID = 0;
			char collegeIDs[3] = { 0 };
			strncpy(collegeIDs, ID + 4, 2);
			collegeID = atoi(collegeIDs);
			strcpy(pos->val.college, colInfo[collegeID - 1]);
			printf("修改成功!\n");
			break;
		}
		else
			printf("学号有误，修改失败！\n");
	}
}

void searchStuInfoByID(List* list)
{
	char ID[20];
	Node* p = NULL;
	printf("请输入需要查询的学生学号：");
	scanf("%s", ID);
	p = list_search_byID(list, ID);
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
void searchStuInfoByName(List* list)
{
	char name[10];
	Node* p = NULL;
	printf("请输入需要查询的学生姓名：");
	scanf("%s", name);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"学号", "姓名", "学院", "类别", "体温", "是否咳嗽", "健康状况", "基础课1", "基础课2", "专业课1", "专业课1", "总分");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	for (p = list->head->next; p; p = p->next)
	{
		if (strstr(p->val.name, name) != NULL)
		{
			printf("%-12s%-10s%-16s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
				p->val.stuID, p->val.name, p->val.college, p->val.group, p->val.t, p->val.ks,
				p->val.health, p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
		}
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

List* classifyGroup(List* list, char* group)
{
	Node* p = NULL;
	List* newList = list_init();
	for (p = list->head->next; p; p = p->next)
	{
		if (!strcmp(p->val.group, group))
		{
			list_insert(newList, p->val);
		}
	}
	return newList;
}
int priorityCmp(Node* p, Node* q)
{
	return p->val.total == q->val.total ? (p->val.score3 == q->val.score3 ? p->val.score4 - q->val.score4 : p->val.score3 - q->val.score3) : p->val.total - q->val.total;
}
//冒泡排序
void sortStuInfo(List* list)
{
	for (Node* i = list->head->next; i->next; i = i->next)
	{
		int flag = 1;
		//(int j = 0; j < len - 1 - i; j++)
		for (Node* j = list->head->next; j->next; j = j->next)
		{
			//降序排列	if( a[j] < a[j + 1] )
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
List* calculateData(List* list, char* fileName)
{
	if (list->head->next == NULL)//空链表，直接返回不操作
		return;
	sortStuInfo(list);
	writeStuInfo(fileName, list);
	return list;
}

void exceptionCount(List* list)
{
	Node* posNode = list->head->next;
	if (posNode == NULL)
	{
		printf("数据为空！\n");
		return;
	}
	List* newList = list_init();
	for (; posNode; posNode = posNode->next)
	{
		if (posNode->val.health == 0)
		{
			list_insert(newList, posNode->val);
		}
	}
	printStuInfo(newList);
	writeStuInfo("data6.txt", newList);
}
void readStuInfo(char* FileName, List* list)
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
		list_insert(list, tempData);
	}
	fclose(fp);
}
void writeStuInfo(char* FileName, List* list)
{
	Node* p = list->head->next;
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