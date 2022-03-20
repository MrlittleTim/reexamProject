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
Node* list_search_byDate(List* list, char* date)
{
	Node* p = NULL;
	for (p = list->head->next; p; p = p->next)
	{
		if (!strcmp(p->val.date, date))
		{
			break;
		}
	}
	return p;
}

Node* list_search_byIDandDate(List* list, char* ID, char* date)
{
	Node* p = NULL;
	for (p = list->head->next; p; p = p->next)
	{
		if (!strcmp(p->val.stuID, ID) && !strcmp(p->val.date, date))
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


void getTime(char* time)
{
	char hour[3] = { 0 };
	char min[3] = { 0 };
	char ch = 0;
	while (1)
	{
		printf("时间：");
		scanf("%s", time);
		strncpy(hour, time, 2);
		hour[2] = '\0';
		ch = time[2];
		strncpy(min, time + 3, 2);
		min[2] = '\0';
		if (strlen(time) == 5 && (ch == ':' || ch == '：')
			&& atoi(hour) >= 0 && atoi(hour) <= 24
			&& atoi(min) >= 0 && atoi(min) <= 60)
		{
			time[2] = ':';
			break;
		}
		else
			printf("格式有误！\n");
	}
}
void getDate(char* date)
{
	char year[5] = { 0 };
	char mon[3] = { 0 };
	char day[3] = { 0 };
	while (1)
	{
		//printf("日期：");
		scanf("%s", date);
		strncpy(year, date, 4);
		year[4] = '\0';
		strncpy(mon, date + 4, 2);
		mon[2] = '\0';
		strncpy(day, date + 6, 2);
		mon[2] = '\0';
		if (strlen(date) == 8 && atoi(year) == 2020)
		{
			if (atoi(mon) == 4 && atoi(day) >= 29 && atoi(day) <= 30)
				break;
			else if (atoi(mon) == 5 && atoi(day) >= 1 && atoi(day) <= 12)
				break;
		}
		printf("格式有误！\n");
	}
}

void printStuInfo(List* list)
{
	Node* p = NULL;
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-8s%-10s%-10s%-8s%-12s\n",
		"学号", "姓名", "学院", "体温", "是否咳嗽", "健康状态", "时间", "日期");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	for (p = list->head->next; p; p = p->next)
	{
		printf("%-12s%-10s%-16s%-8.1f%-10d%-10d%-8s%-12s\n",
			p->val.stuID, p->val.name, p->val.college, p->val.t, p->val.ks,
			p->val.health, p->val.time, p->val.date);
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
		ret = 1
;
	}
	return ret;
}
void addStuInfo(List* list)
{
	stuInfo tempData;
	printf("请输入各项信息（按0退出）：\n");
	//判断学号合法
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
			break;
		else
			printf("学号无效，请重新输入！\n");
	}
	Node* ret = NULL;
	//判断学号是否存在，若存在则不用输入名字，且紧接判断日期
	if ((ret = list_search_byID(list, tempData.stuID)))
	{
		strcpy(tempData.name, ret->val.name);
		printf("该学号已存在！\n");
		while (1)
		{
			printf("日期：");
			getDate(tempData.date);
			//判断日期是否重复。
			if (list_search_byDate(list, tempData.date))
				printf("日期重复，请重新输入！\n");
			else
			{
				break;
			}
				
		}
		printf("学生体温：");
		scanf("%f", &tempData.t);
		printf("是否咳嗽：");
		scanf("%d", &tempData.ks);
		getTime(tempData.time);
		//判断健康。0为异常，1为正常
		if (tempData.t >= 37.2 || tempData.ks == 1)
		{
			tempData.health = 0;
		}
		else
		{
			tempData.health = 1;
		}
		//判断学院
		int collegeID = 0;
		char collegeIDs[3] = { 0 };
		strncpy(collegeIDs, tempData.stuID + 4, 2);
		collegeID = atoi(collegeIDs);
		strcpy(tempData.college, colInfo[collegeID - 1]);
		
		while (ret)
		{
			if (ret->next == NULL)
			{
				list_insert(list, tempData);
				break;
			}
			else if (strcmp(ret->next->val.stuID, tempData.stuID))
			{
				Node* p = (Node*)malloc(sizeof(Node));
				p->val = tempData;
				p->next = ret->next;
				ret->next = p;
				break;
			}
			ret = ret->next;
		}
		printf("添加成功!\n");
	}
	else
	{
		printf("学生姓名：");
		scanf("%s", tempData.name);
		printf("学生体温：");
		scanf("%f", &tempData.t);
		printf("是否咳嗽：");
		scanf("%d", &tempData.ks);
		getTime(tempData.time);
		printf("日期：\n");
		getDate(tempData.date);
		//判断健康。0为异常，1为正常
		if (tempData.t >= 37.2 || tempData.ks == 1)
		{
			tempData.health = 0;
		}
		else
		{
			tempData.health = 1;
		}
		//判断学院
		int collegeID = 0;
		char collegeIDs[3] = { 0 };
		strncpy(collegeIDs, tempData.stuID + 4, 2);
		collegeID = atoi(collegeIDs);
		strcpy(tempData.college, colInfo[collegeID - 1]);
		//新用户
		list_insert(list, tempData);
		printf("添加成功!\n");
	}
	
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
	char date[21];
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
		printf("请输入需要修改日期信息：");
		scanf("%s", date);
		pos = list_search_byIDandDate(list, ID, date);

		if (pos)
		{
			char item[21];
			while (1)
			{
				printf("请输入需要修改的项：");
				scanf("%20s", item);
				if (!strcmp(item, "体温"))
				{
					printf("体温：");
					scanf("%f", &pos->val.t);
					break;
				}
				else if (!strcmp(item, "是否咳嗽"))
				{
					printf("是否咳嗽：");
					scanf("%d", &pos->val.ks);
					break;
				}
				else if (!strcmp(item, "时间"))
				{
					printf("时间：");
					scanf("%s", pos->val.time);
					break;
				}
				else
					printf("输入有误！\n");
			}
			//判断健康。0为异常，1为正常
			if (pos->val.t >= 37.2 || pos->val.ks == 1)
				pos->val.health = 0;
			else
				pos->val.health = 1;
			printf("修改成功!\n");
			break;
		}
		else
			printf("信息有误，修改失败！\n");
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
		printf("%-12s%-10s%-16s%-8s%-10s%-10s%-8s%-12s\n",
			"学号", "姓名", "学院", "体温", "是否咳嗽", "健康状态", "时间", "日期");
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
		printf("%-12s%-10s%-16s%-8.1f%-10d%-10d%-8s%-12d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.t, p->val.ks,
			p->val.health, p->val.time, p->val.date);
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
	printf("%-12s%-10s%-16s%-8s%-10s%-10s%-8s%-12s\n",
		"学号", "姓名", "学院", "体温", "是否咳嗽", "健康状态", "时间", "日期");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	for (p = list->head->next; p; p = p->next)
	{
		if (strstr(p->val.name, name) != NULL)
		{
			printf("%-12s%-10s%-16s%-8.1f%-10d%-10d%-8s%-12s\n",
				p->val.stuID, p->val.name, p->val.college, p->val.t, p->val.ks,
				p->val.health, p->val.time, p->val.date);
		}
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

void searchStuInfo(List* list)
{
	stuInfo data;
	List* searchList = list_init();
	printf("请输入学生学号：\n");
	scanf("%s", data.stuID);
	printf("请输入当前日期：\n");
	getDate(data.date);
	Node* p = list_search_byID(list, data.stuID);
	if (p && strcmp(p->val.date, data.date) <= 0)
	{
		printf("\n学号：%s\n", p->val.stuID);
		printf("姓名：%s\n", p->val.name);
		printf("学院：%s\n", p->val.college);
		printf("--------------------------------------------\n");
		printf("%-8s%-10s%-10s%-8s%-12s\n", "体温", "是否咳嗽", "健康状态", "时间", "日期");
		printf("--------------------------------------------\n");
		for (;p && strcmp(p->val.date, data.date) <= 0 && !strcmp(p->val.stuID, data.stuID); p = p->next)
		{
			printf("%-8.1f%-10d%-10d%-8s%-12s\n", p->val.t, p->val.ks, p->val.health, p->val.time, p->val.date);
			list_insert(searchList, p->val);
		}
		printf("--------------------------------------------\n");
	}
	else
	{
		printf("信息有误！\n");
	}
	writeStuInfo("data2.txt", searchList);
}


//int priorityCmp(Node* p, Node* q)
//{
//	return p->val.total == q->val.total ? (p->val.score3 == q->val.score3 ? p->val.score4 - q->val.score4 : p->val.score3 - q->val.score3) : p->val.total - q->val.total;
//}
//冒泡排序
//void sortStuInfo(List* list)
//{
//	for (Node* i = list->head->next; i->next; i = i->next)
//	{
//		int flag = 1;
//		//(int j = 0; j < len - 1 - i; j++)
//		for (Node* j = list->head->next; j->next; j = j->next)
//		{
//			//降序排列	if( a[j] < a[j + 1] )
//			if (priorityCmp(j, j->next) < 0)
//			{
//				stuInfo temp = j->val;
//				j->val = j->next->val;
//				j->next->val = temp;
//				flag = 0;
//			}
//		}
//		if (flag)
//		{
//			return;
//		}
//	}
//}


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
	writeStuInfo("data3.txt", newList);
}

void exceptionWarning(List* list)
{
	int cnt = 0;
	Node* p = list->head->next;
	stuInfo val = p->val;
	List* warnList = list_init();
	List* warnInfoList = list_init();
	for ( ;p ; p = p->next)
	{
		//标志val,不同则重新赋值
		if (strcmp(val.stuID, p->val.stuID))
		{
			val = p->val;
			cnt = 0;
		}
		if (p->val.health == 0 && !strcmp(val.stuID, p->val.stuID))
		{
			cnt++;
		}
		else if(p->val.health == 0 && strcmp(val.stuID, p->val.stuID))
		{
			cnt = 1;
		}
		else if(p->val.health == 1)
		{
			cnt = 0;
		}
		//预警
		if (cnt == 3 && list_search_byID(warnList, p->val.stuID) == NULL)
		{
			list_insert(warnList, p->val);
		}
	}
	printf("一下学生已连续三天出现身体健康状态异常：\n");
	p = warnList->head->next;
	val = p->val;
	printf("\n学号：%s\n", p->val.stuID);
	printf("姓名：%s\n", p->val.name);
	printf("学院：%s\n", p->val.college);
	for ( ; p; p = p->next)
	{
		if (strcmp(val.stuID, p->val.stuID))
		{
			val = p->val;
			printf("\n学号：%s\n", p->val.stuID);
			printf("姓名：%s\n", p->val.name);
			printf("学院：%s\n", p->val.college);
		}
		printf("--------------------------------------------\n");
		printf("%-8s%-10s%-10s%-8s%-12s\n", "体温", "是否咳嗽", "健康状态", "时间", "日期");
		printf("--------------------------------------------\n");
		for (Node* q = list->head->next; q; q = q->next)
		{
			if (!strcmp(q->val.stuID, p->val.stuID))
			{
				printf("%-8.1f%-10d%-10d%-8s%-12s\n", q->val.t, q->val.ks, q->val.health, q->val.time, q->val.date);
				list_insert(warnInfoList, q->val);
			}
				
		}
		printf("--------------------------------------------\n");
	}
	writeStuInfo("data4.txt", warnInfoList);
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
		fscanf(fp, "%12s%10s%16s%8f%10d%10d%8s%12s\n",
			tempData.stuID, tempData.name, tempData.college,
			&tempData.t, &tempData.ks, &tempData.health,
			tempData.time, tempData.date);
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
		fprintf(fp, "%-12s%-10s%-16s%-8.1f%-10d%-10d%-8s%-12s\n",
			p->val.stuID, p->val.name, p->val.college, 
			p->val.t, p->val.ks, p->val.health,
			p->val.time, p->val.date);
		p = p->next;
	}
	fclose(fp);
}