/*************************************************************************
	> File Name: Nodenum.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 15时23分00秒
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
int leafnum;
int num1;
int num2;

void Create(BiTree *root);
int leaf(BiTree root);
void printleaf(BiTree root);
void sum1(BiTree root);
void sum2(BiTree root);

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

int leaf(BiTree root)
{
    int nl,nr;
    if(root == NULL)    
        return 0;
    if((root->Lchild == NULL) && (root->Rchild == NULL))
        return 1;
    nl = leaf(root->Lchild);
    nr = leaf(root->Rchild);
    return nl + nr;
}


void printleaf(BiTree root)
{
    if(root){
        if(root->Lchild == NULL && root->Rchild == NULL)
        {
            putchar(root->data);
        }
        printleaf(root->Lchild);
        printleaf(root->Rchild);
    }
}

void sum1(BiTree root)
{
    if(root){
        if((root->Lchild == NULL && root->Rchild != NULL ) || (root->Rchild == NULL && root->Lchild != NULL))
        {
            num1++;
        }
        sum1(root->Lchild);
        sum1(root->Rchild);
    }
}


void sum2(BiTree root)
{
    if(root){
        if(root->Lchild != NULL && root->Rchild != NULL)
        {
            num2++;
        }
        sum2(root->Lchild);
        sum2(root->Rchild);
    }
}

int main(void)
{
    BiTree root;
    Create(&root);
    sum1(root);
    sum2(root);
    leafnum = leaf(root);
    printf("%d %d %d\n",leafnum,num1,num2);
    printleaf(root);
    printf("\n");
    return 0;
}

