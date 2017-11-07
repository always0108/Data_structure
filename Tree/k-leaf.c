/*************************************************************************
	> File Name: k-leaf.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 20时21分47秒
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
int k;

void Create(BiTree *root);
void kleaf(BiTree root,int level);

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

void kleaf(BiTree root,int level)
{
    if(root){
        if(root->Lchild == NULL && root->Rchild == NULL && level == k){
            leafnum++;
        }
        kleaf(root->Lchild,level+1);
        kleaf(root->Rchild,level+1);
    }
}

int main(void)
{
    BiTree root;
    Create(&root);
    scanf("%d",&k);
    kleaf(root,1);
    printf("%d\n",leafnum);
}

