#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct studentInfo {
    char stuID[20];
    char name[10];
    char college[20];
    char group[10];     // Àà±ð
    float t;            // ÎÂ¶È
    int ks;             // ¿ÈËÔ
    int health;         // ½¡¿µ×´Ì¬
    int score1;
    int score2;
    int score3;
    int score4;
    int total;
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
int list_del_byID(List* list, char* ID);

void printStuInfo(List* list);
int isStuIDLegal(char* stuID);
void addStuInfo(List* list);
void delStuInfoByID(List* list);
void searchStuInfoByID(List* list);
void searchStuInfoByName(Node* headNode);
void updateInfo(List* list);
Node* classifyGroup(Node* headNode, char* group);
int priorityCmp(Node* p, Node* q);
void sortStuInfo(Node* headNode);
Node* calculateData(Node* headNode, char* fileName);
void exceptionCount(Node* headNode);

void readStuInfo(char* FileName, List* list);
void writeStuInfo(char* FileName, List* list);