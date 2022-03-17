#include "stuInfo.h"

char* colInfo[] = { "ͨ��ѧԺ", "�����ѧԺ", "���ѧԺ", "�Զ���ѧԺ", "����ѧԺ", "�о���ѧԺ",
				   "����ѧԺ", "����ѧԺ", "����ѧԺ", "��ýѧԺ", "�Ƚ�����ѧԺ", "���˼����ѧԺ" };
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
//ɾ���ɹ�����1��ʧ�ܷ���0
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
		"ѧ��", "����", "ѧԺ", "���", "����", "�Ƿ����", "����״��", "������1", "������2", "רҵ��1", "רҵ��1", "�ܷ�");
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
		year = (tempData.stuID[0] - '0') * 1000 + (tempData.stuID[1] - '0') * 100 + 
			(tempData.stuID[2] - '0') * 10 + (tempData.stuID[3] - '0');
		collegeID = (tempData.stuID[4] - '0') * 10 + (tempData.stuID[5] - '0');
		if (tempData.stuID[9] == '\0' && year >= 2016 && year <= 2019 && collegeID >= 1 && collegeID <= 12 )
		{
			break;
		}
		printf("��ѧ����Ϣ��Ч�����������룡\n");
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
	strcpy(tempData.college, colInfo[collegeID - 1]);

	int ret = InsertNode(headNode, tempData);
	if (ret)
	{
		printf("��ӳɹ�!\n");
	}
	else
	{
		printf("���ʧ��!\n");
	}
}

void delStuInfoByID(node* headNode)
{
	int temp;
	char ID[20];
	printf("��������Ҫɾ��ѧ��ѧ�ţ�");
	scanf("%s", ID);
	temp = DelNodeByID(headNode, ID);
	if (temp)
	{
		printf("ɾ���ɹ���\fn");
	}
	else
	{
		printf("ɾ��ʧ�ܣ�\n");
	}
}
void upDataInfo(node* headNode)
{
	char ID[20];
	node* pos;
	while (1)
	{
		printf("��������Ҫ�޸ĵ�ѧ��ѧ�ţ���0�˳�����");
		scanf("%s", ID);
		if (ID[0] == '0' && ID[1] == '\0')
		{
			printf("�˳��ɹ���");
			return;
		}
		pos = SearchNodeByID(headNode, ID);
		if (pos != NULL)
		{
			int year;
			int collegeID;
			printf("�����������Ϣ��\n");
			while (1)
			{
				printf("ѧ��ѧ�ţ�");
				scanf("%s", pos->val.stuID);
				year = (pos->val.stuID[0] - '0') * 1000 + (pos->val.stuID[1] - '0') * 100 +
					(pos->val.stuID[2] - '0') * 10 + (pos->val.stuID[3] - '0');
				collegeID = (pos->val.stuID[4] - '0') * 10 + (pos->val.stuID[5] - '0');
				//ID = (pos->val.stuID[6] - '0') * 100 + (pos->val.stuID[7] - '0') * 10 + (pos->val.stuID[8] - '0');
				if (pos->val.stuID[9] == '\0' && year >= 2016 && year <= 2019 && collegeID >= 1 && collegeID <= 12)
				{
					break;
				}
				printf("��ѧ����Ϣ��Ч�����������룡\n");
			}
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
			{
				pos->val.health = 0;
			}
			else
			{
				pos->val.health = 1;
			}
			//�����ܷ�
			pos->val.total = pos->val.score1 + pos->val.score2 + pos->val.score3 + pos->val.score4;
			//�ж�ѧԺ
			strcpy(pos->val.college, colInfo[collegeID - 1]);
			printf("�޸ĳɹ�!\n");
			break;
		}
		printf("ѧ�������޸�ʧ�ܣ�\n");
	}
}

void searchStuInfoByID(node* headNode)
{
	char ID[20];
	node* p;
	printf("��������Ҫ��ѯ��ѧ��ѧ�ţ�");
	scanf("%s", ID);
	p = SearchNodeByID(headNode, ID);
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
void searchStuInfoByName(node* headNode)
{
	char name[10];
	node* p = headNode->next;
	printf("��������Ҫ��ѯ��ѧ��������");
	scanf("%s", name);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-12s%-10s%-16s%-10s%-8s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
		"ѧ��", "����", "ѧԺ", "���", "����", "�Ƿ����", "����״��", "������1", "������2", "רҵ��1", "רҵ��1", "�ܷ�");
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
//ð������
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
//ͳ������
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