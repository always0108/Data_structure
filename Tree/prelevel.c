/*************************************************************************
	> File Name: prelevel.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 20时09分03秒
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

void Create(BiTree *root);
void PreOrder(BiTree root,int level);

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

void PreOrder(BiTree root,int level)
{
    if(root){
        printf("(%c,%d)",root->data,level);
        PreOrder(root->Lchild,level+1);
        PreOrder(root->Rchild,level+1);
    }
}

int main(void){
    BiTree root;
    Create(&root);
    PreOrder(root,1);
    printf("\n");
    return 0;
}
