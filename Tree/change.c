/*************************************************************************
	> File Name: change.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 20时57分59秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct Node{
    char data;
    struct Node * Lchild;
    struct Node * Rchild;
}BiTNode, * BiTree;

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

void change(BiTree root)
{
    if(root)
    {
        BiTree tmp;
        tmp = root->Lchild;
        root->Lchild = root->Rchild;
        root->Rchild = tmp;
        change(root->Lchild);
        change(root->Rchild);
    }
}

void PreOrder(BiTree root)
{
    if(root){
        putchar(root->data);
        PreOrder(root->Lchild);
        PreOrder(root->Rchild);
    }
}

void InOrder(BiTree root)
{
    if(root){
        InOrder(root->Lchild);
        putchar(root->data);
        InOrder(root->Rchild);
    }
}

void PostOrder(BiTree root)
{
    if(root){
        PostOrder(root->Lchild);
        PostOrder(root->Rchild);
        putchar(root->data);
    }
}

int main(void){
    BiTree root;
    Create(&root);
    change(root);
    PreOrder(root);
    printf("\n");

    InOrder(root);
    printf("\n");

    PostOrder(root);
    printf("\n");
    return 0;
}


