#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct studentInfo {
    char stuID[20];
    char name[10];
    char college[20];
    float t;            // 温度
    int ks;             // 咳嗽
    int health;         // 健康状态
    char time[10];      //时间
    char date[20];           //日期 
}stuInfo;

typedef struct LinkListNode
{
    stuInfo val;
    struct LinkListNode* next;
} Node;

typedef struct _list
{
    Node* head;
    Node* tail;
} List;


List* list_init();
void list_insert(List* list, stuInfo val);
Node* list_search_byID(List* list, char* ID);
Node* list_search_byDate(List* list, char* date);
Node* list_search_byIDandDate(List* list, char* ID, char* date);
int list_del_byID(List* list, char* ID);

void printStuInfo(List* list);
int isStuIDLegal(char* stuID);
void addStuInfo(List* list);
void delStuInfoByID(List* list);
void searchStuInfoByID(List* list);
void searchStuInfoByName(List* list);
void searchStuInfo(List* list);
void updateInfo(List* list);

void getTime(char* time);
void getDate(char* date);

int priorityCmp(Node* p, Node* q);
void sortStuInfo(List* list);
void exceptionCount(List* list);
void exceptionWarning(List* list);

void readStuInfo(char* FileName, List* list);
void writeStuInfo(char* FileName, List* list);