/*************************************************************************
	> File Name: Post.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 19时30分07秒
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
    int top;
}SeqStack;

void Create(BiTree *root);

void InitStack(SeqStack **S)
{
    (*S) = malloc(sizeof(SeqStack));
    (*S)->top = -1;
}

int IsEmpty(SeqStack *S)
{
    if(S->top == -1)
        return 1;
    else
        return 0;
}

int Push(SeqStack *S,BiTree x)
{
    if(S->top == MAXSIZE - 1)
        return 0;
    else{
        S->top++;
        S->data[S->top] = x;
        return 1;
    }
}

int Pop(SeqStack *S,BiTree *x)
{
    if(IsEmpty(S))
        return 0;
    else{
        *x = S->data[S->top];
        S->top--;
        return 1;
    }
}

int Top(SeqStack *S,BiTree *x)
{
    if(IsEmpty(S))
        return 0;
    else{
        *x=S->data[S->top];
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

void PostOrder(BiTree root)
{
    SeqStack *S;
    InitStack(&S);
    BiTree p,q;
    p = root;
    q = NULL;
    while(p!=NULL || !IsEmpty(S))
    {
        while(p!=NULL){
            Push(S,p);
            p=p->Lchild;
        }
        if(!IsEmpty(S)){
            Top(S,&p);
            if(p->Rchild == NULL || p->Rchild == q)
            {
                Pop(S,&p);
                putchar(p->data);
                q=p;
                p=NULL;
            }else{
                p=p->Rchild;
            }
        }
    }
}

int main(void)
{
    BiTree S;
    Create(&S);
    PostOrder(S);
    printf("\n");
    return 0;

}
