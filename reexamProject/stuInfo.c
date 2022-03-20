#include "stuInfo.h"

char* colInfo[] = { "ͨ��ѧԺ", "�����ѧԺ", "���ѧԺ", "�Զ���ѧԺ", "����ѧԺ", "�о���ѧԺ",
				   "����ѧԺ", "����ѧԺ", "����ѧԺ", "��ýѧԺ", "�Ƚ�����ѧԺ", "���˼����ѧԺ" };
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
//ɾ���ɹ�����1��ʧ�ܷ���0
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
		printf("ʱ�䣺");
		scanf("%s", time);
		strncpy(hour, time, 2);
		hour[2] = '\0';
		ch = time[2];
		strncpy(min, time + 3, 2);
		min[2] = '\0';
		if (strlen(time) == 5 && (ch == ':' || ch == '��')
			&& atoi(hour) >= 0 && atoi(hour) <= 24
			&& atoi(min) >= 0 && atoi(min) <= 60)
		{
			time[2] = ':';
			break;
		}
		else
			printf("��ʽ����\n");
	}
}
void getDate(char* date)
{
	char year[5] = { 0 };
	char mon[3] = { 0 };
	char day[3] = { 0 };
	while (1)
	{
		//printf("���ڣ�");
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
		printf("��ʽ����\n");
	}
}

void printStuInfo(List* list)
{
	Node* p = NULL;
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-8s%-10s%-10s%-8s%-12s\n",
		"ѧ��", "����", "ѧԺ", "����", "�Ƿ����", "����״̬", "ʱ��", "����");
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
	printf("�����������Ϣ����0�˳�����\n");
	//�ж�ѧ�źϷ�
	while (1)
	{
		printf("ѧ��ѧ�ţ�");
		scanf("%s", tempData.stuID);
		if (tempData.stuID[0] == '0' && tempData.stuID[1] == '\0')
		{
			printf("�˳��ɹ���");
			return;
		}
		
		if (isStuIDLegal(tempData.stuID))
			break;
		else
			printf("ѧ����Ч�����������룡\n");
	}
	Node* ret = NULL;
	//�ж�ѧ���Ƿ���ڣ������������������֣��ҽ����ж�����
	if ((ret = list_search_byID(list, tempData.stuID)))
	{
		strcpy(tempData.name, ret->val.name);
		printf("��ѧ���Ѵ��ڣ�\n");
		while (1)
		{
			printf("���ڣ�");
			getDate(tempData.date);
			//�ж������Ƿ��ظ���
			if (list_search_byDate(list, tempData.date))
				printf("�����ظ������������룡\n");
			else
			{
				break;
			}
				
		}
		printf("ѧ�����£�");
		scanf("%f", &tempData.t);
		printf("�Ƿ���ԣ�");
		scanf("%d", &tempData.ks);
		getTime(tempData.time);
		//�жϽ�����0Ϊ�쳣��1Ϊ����
		if (tempData.t >= 37.2 || tempData.ks == 1)
		{
			tempData.health = 0;
		}
		else
		{
			tempData.health = 1;
		}
		//�ж�ѧԺ
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
		printf("��ӳɹ�!\n");
	}
	else
	{
		printf("ѧ��������");
		scanf("%s", tempData.name);
		printf("ѧ�����£�");
		scanf("%f", &tempData.t);
		printf("�Ƿ���ԣ�");
		scanf("%d", &tempData.ks);
		getTime(tempData.time);
		printf("���ڣ�\n");
		getDate(tempData.date);
		//�жϽ�����0Ϊ�쳣��1Ϊ����
		if (tempData.t >= 37.2 || tempData.ks == 1)
		{
			tempData.health = 0;
		}
		else
		{
			tempData.health = 1;
		}
		//�ж�ѧԺ
		int collegeID = 0;
		char collegeIDs[3] = { 0 };
		strncpy(collegeIDs, tempData.stuID + 4, 2);
		collegeID = atoi(collegeIDs);
		strcpy(tempData.college, colInfo[collegeID - 1]);
		//���û�
		list_insert(list, tempData);
		printf("��ӳɹ�!\n");
	}
	
}

void delStuInfoByID(List* list)
{
	int temp;
	char ID[20];
	printf("��������Ҫɾ��ѧ��ѧ�ţ�");
	scanf("%s", ID);
	temp = list_del_byID(list, ID);
	if (temp)
	{
		printf("ɾ���ɹ���\n");
	}
	else
	{
		printf("ɾ��ʧ�ܣ�\n");
	}
}
void updateInfo(List* list)
{
	char ID[20];
	char date[21];
	Node* pos;
	while (1)
	{
		printf("��������Ҫ�޸ĵ�ѧ��ѧ�ţ���0�˳�����");
		scanf("%s", ID);
		if (ID[0] == '0' && ID[1] == '\0')
		{
			printf("�˳��ɹ���");
			return;
		}
		printf("��������Ҫ�޸�������Ϣ��");
		scanf("%s", date);
		pos = list_search_byIDandDate(list, ID, date);

		if (pos)
		{
			char item[21];
			while (1)
			{
				printf("��������Ҫ�޸ĵ��");
				scanf("%20s", item);
				if (!strcmp(item, "����"))
				{
					printf("���£�");
					scanf("%f", &pos->val.t);
					break;
				}
				else if (!strcmp(item, "�Ƿ����"))
				{
					printf("�Ƿ���ԣ�");
					scanf("%d", &pos->val.ks);
					break;
				}
				else if (!strcmp(item, "ʱ��"))
				{
					printf("ʱ�䣺");
					scanf("%s", pos->val.time);
					break;
				}
				else
					printf("��������\n");
			}
			//�жϽ�����0Ϊ�쳣��1Ϊ����
			if (pos->val.t >= 37.2 || pos->val.ks == 1)
				pos->val.health = 0;
			else
				pos->val.health = 1;
			printf("�޸ĳɹ�!\n");
			break;
		}
		else
			printf("��Ϣ�����޸�ʧ�ܣ�\n");
	}
}

void searchStuInfoByID(List* list)
{
	char ID[20];
	Node* p = NULL;
	printf("��������Ҫ��ѯ��ѧ��ѧ�ţ�");
	scanf("%s", ID);
	p = list_search_byID(list, ID);
	if (p)
	{
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
		printf("%-12s%-10s%-16s%-8s%-10s%-10s%-8s%-12s\n",
			"ѧ��", "����", "ѧԺ", "����", "�Ƿ����", "����״̬", "ʱ��", "����");
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
		printf("%-12s%-10s%-16s%-8.1f%-10d%-10d%-8s%-12d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.t, p->val.ks,
			p->val.health, p->val.time, p->val.date);
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}
	
}
void searchStuInfoByName(List* list)
{
	char name[10];
	Node* p = NULL;
	printf("��������Ҫ��ѯ��ѧ��������");
	scanf("%s", name);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-8s%-10s%-10s%-8s%-12s\n",
		"ѧ��", "����", "ѧԺ", "����", "�Ƿ����", "����״̬", "ʱ��", "����");
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
	printf("������ѧ��ѧ�ţ�\n");
	scanf("%s", data.stuID);
	printf("�����뵱ǰ���ڣ�\n");
	getDate(data.date);
	Node* p = list_search_byID(list, data.stuID);
	if (p && strcmp(p->val.date, data.date) <= 0)
	{
		printf("\nѧ�ţ�%s\n", p->val.stuID);
		printf("������%s\n", p->val.name);
		printf("ѧԺ��%s\n", p->val.college);
		printf("--------------------------------------------\n");
		printf("%-8s%-10s%-10s%-8s%-12s\n", "����", "�Ƿ����", "����״̬", "ʱ��", "����");
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
		printf("��Ϣ����\n");
	}
	writeStuInfo("data2.txt", searchList);
}


//int priorityCmp(Node* p, Node* q)
//{
//	return p->val.total == q->val.total ? (p->val.score3 == q->val.score3 ? p->val.score4 - q->val.score4 : p->val.score3 - q->val.score3) : p->val.total - q->val.total;
//}
//ð������
//void sortStuInfo(List* list)
//{
//	for (Node* i = list->head->next; i->next; i = i->next)
//	{
//		int flag = 1;
//		//(int j = 0; j < len - 1 - i; j++)
//		for (Node* j = list->head->next; j->next; j = j->next)
//		{
//			//��������	if( a[j] < a[j + 1] )
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
		printf("����Ϊ�գ�\n");
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
		//��־val,��ͬ�����¸�ֵ
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
		//Ԥ��
		if (cnt == 3 && list_search_byID(warnList, p->val.stuID) == NULL)
		{
			list_insert(warnList, p->val);
		}
	}
	printf("һ��ѧ������������������彡��״̬�쳣��\n");
	p = warnList->head->next;
	val = p->val;
	printf("\nѧ�ţ�%s\n", p->val.stuID);
	printf("������%s\n", p->val.name);
	printf("ѧԺ��%s\n", p->val.college);
	for ( ; p; p = p->next)
	{
		if (strcmp(val.stuID, p->val.stuID))
		{
			val = p->val;
			printf("\nѧ�ţ�%s\n", p->val.stuID);
			printf("������%s\n", p->val.name);
			printf("ѧԺ��%s\n", p->val.college);
		}
		printf("--------------------------------------------\n");
		printf("%-8s%-10s%-10s%-8s%-12s\n", "����", "�Ƿ����", "����״̬", "ʱ��", "����");
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