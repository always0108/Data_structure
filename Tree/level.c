/*************************************************************************
	> File Name: level.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 19时44分55秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXSIZE 1000
typedef struct Node{
    char data;
    struct Node * Lchild;
    struct Node * Rchild;
}BiTNode, * BiTree;

typedef struct{
    BiTree data[MAXSIZE];
    int rear,front;
}SeQueue;

void Create(BiTree *root);

void InitQueue(SeQueue **q)
{
    (*q) = malloc(sizeof(SeQueue));
    (*q)->rear = MAXSIZE-1;
    (*q)->front = MAXSIZE -1;
}

int IsEmpty(SeQueue *q)
{
    if(q->front == q->rear)
        return 1;
    else
        return 0;
}

int EnterQueue(SeQueue *q,BiTree x)
{
    if((q->rear+1)%MAXSIZE == q->front)//full
        return 0;
    else{
        q->rear = (q->rear+1)%MAXSIZE;
        q->data[q->rear]=x;
        return 1;
    }
}

int OutQueue(SeQueue *q,BiTree *x)
{
    if(IsEmpty(q))
        return 0;
    else{
        q->front = (q->front+1) % MAXSIZE;
        *x = q->data[q->front];
        return 1;
    }
}


void Create(BiTree *root)
{
    char ch;
    ch = getchar();
    if(ch == '#') *root = NULL;
    else{
        *root = (BiTree)malloc(sizeof(BiTNode));
        (*root)->data = ch;
        Create(&((*root)->Lchild));
        Create(&((*root)->Rchild));
    }
}

void LevelOrder(BiTree root)
{
    SeQueue *Q;
    BiTree p;
    InitQueue(&Q);
    EnterQueue(Q,root);
    while(!IsEmpty(Q)){
        OutQueue(Q,&p);
        putchar(p->data);
        if(p->Lchild!=NULL)
            EnterQueue(Q,p->Lchild);
        if(p->Rchild!=NULL)
            EnterQueue(Q,p->Rchild);
    }
}

int main(void)
{
    BiTree S;
    Create(&S);
    LevelOrder(S);
    printf("\n");
    return 0;
}
