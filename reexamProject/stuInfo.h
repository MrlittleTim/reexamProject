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
}node;

typedef struct _list
{
    node* head;
    node* tail;
};


node* InitHeadNode();
node* CreatMemberNode(stuInfo val);
int InsertNode(node* headNode, stuInfo val);
node* SearchNodeByID(node* headNode, char* ID);
int DelNodeByID(node* headNode, char* ID);

void printStuInfo(node* headNode);
void addStuInfo(node* headNode);
void delStuInfoByID(node* headNode);
void upDataInfo(node* headNode);
void searchStuInfoByID(node* headNode);
void searchStuInfoByName(node* headNode);
node* classifyGroup(node* headNode, char* group);
int priorityCmp(node* p, node* q);
void sortStuInfo(node* headNode);
node* calculateData(node* headNode, char* fileName);
void exceptionCount(node* headNode);

void readStuInfo(char* FileName, node* headNode);
void writeStuInfo(char* FileName, node* headNode);