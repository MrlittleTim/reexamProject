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

void printStuInfo(List* list)
{
	Node* p = NULL;
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"ѧ��", "����", "ѧԺ", "���", "����", "�Ƿ����", "����״��", "������1", "������2", "רҵ��1", "רҵ��1", "�ܷ�");
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
	printf("�����������Ϣ����0�˳�����\n");
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
		{
			if (list_search_byID(list, tempData.stuID) == 0)
			{
				break;
			}
			else
				printf("ѧ���Ѵ��ڣ�\n");
			
		}
		else
			printf("ѧ����Ч�����������룡\n");
	}
	printf("ѧ��������");
	scanf("%s", tempData.name);
	printf("ѧ�����");
	scanf("%s", tempData.group);
	printf("ѧ�����£�");
	scanf("%f", &tempData.t);
	printf("�Ƿ���ԣ�");
	scanf("%d", &tempData.ks);
	printf("ѧ��������1�ɼ���");
	scanf("%d", &tempData.score1);
	printf("ѧ��������2�ɼ���");
	scanf("%d", &tempData.score2);
	printf("ѧ��רҵ��1�ɼ���");
	scanf("%d", &tempData.score3);
	printf("ѧ��רҵ��2�ɼ���");
	scanf("%d", &tempData.score4);
	//�жϽ�����0Ϊ�쳣��1Ϊ����
	if (tempData.t >= 37.2 || tempData.ks == 1)
	{
		tempData.health = 0;
	}
	else
	{
		tempData.health = 1;
	}
	//�����ܷ�
	tempData.total = tempData.score1 + tempData.score2 + tempData.score3 + tempData.score4;
	//�ж�ѧԺ
	int collegeID = 0;
	char collegeIDs[3] = { 0 };
	strncpy(collegeIDs, tempData.stuID + 4, 2);
	collegeID = atoi(collegeIDs);
	strcpy(tempData.college, colInfo[collegeID - 1]);
	list_insert(list, tempData);
	printf("��ӳɹ�!\n");
	
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
		pos = list_search_byID(list, ID);
		if (pos)
		{
			strcpy(pos->val.stuID, ID);
			printf("�����������Ϣ��\n");
			printf("ѧ��������");
			scanf("%s", pos->val.name);
			printf("ѧ�����");
			scanf("%s", pos->val.group);
			printf("ѧ�����£�");
			scanf("%f", &pos->val.t);
			printf("�Ƿ���ԣ�");
			scanf("%d", &pos->val.ks);
			printf("ѧ��������1�ɼ���");
			scanf("%d", &pos->val.score1);
			printf("ѧ��������2�ɼ���");
			scanf("%d", &pos->val.score2);
			printf("ѧ��רҵ��1�ɼ���");
			scanf("%d", &pos->val.score3);
			printf("ѧ��רҵ��2�ɼ���");
			scanf("%d", &pos->val.score4);
			//�жϽ�����0Ϊ�쳣��1Ϊ����
			if (pos->val.t >= 37.2 || pos->val.ks == 1)
				pos->val.health = 0;
			else
				pos->val.health = 1;
			//�����ܷ�
			pos->val.total = pos->val.score1 + pos->val.score2 + pos->val.score3 + pos->val.score4;
			//�ж�ѧԺ
			int collegeID = 0;
			char collegeIDs[3] = { 0 };
			strncpy(collegeIDs, ID + 4, 2);
			collegeID = atoi(collegeIDs);
			strcpy(pos->val.college, colInfo[collegeID - 1]);
			printf("�޸ĳɹ�!\n");
			break;
		}
		else
			printf("ѧ�������޸�ʧ�ܣ�\n");
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
		printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
			"ѧ��", "����", "ѧԺ", "���", "����", "�Ƿ����", "����״��", "������1", "������2", "רҵ��1", "רҵ��1", "�ܷ�");
		printf("-----------------------------------------------------------------------------------------------------------------------\n");
		printf("%-12s%-10s%-16s%-10s%-8.1f%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",
			p->val.stuID, p->val.name, p->val.college, p->val.group, p->val.t, p->val.ks,
			p->val.health, p->val.score1, p->val.score2, p->val.score3, p->val.score4, p->val.total);
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
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"ѧ��", "����", "ѧԺ", "���", "����", "�Ƿ����", "����״��", "������1", "������2", "רҵ��1", "רҵ��1", "�ܷ�");
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
//ð������
void sortStuInfo(List* list)
{
	for (Node* i = list->head->next; i->next; i = i->next)
	{
		int flag = 1;
		//(int j = 0; j < len - 1 - i; j++)
		for (Node* j = list->head->next; j->next; j = j->next)
		{
			//��������	if( a[j] < a[j + 1] )
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
//ͳ������
List* calculateData(List* list, char* fileName)
{
	if (list->head->next == NULL)//������ֱ�ӷ��ز�����
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