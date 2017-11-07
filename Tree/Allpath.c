/*************************************************************************
	> File Name: Allpath.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 20时37分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

char path[1000];

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

void Prepath(BiTree root,int step)
{
    if(root)
    {
        if(root->Lchild==NULL&&root->Rchild==NULL){
            printf("%c:",root->data);
            int i;
            for(i=0;i<step;i++)
                putchar(path[i]);
            printf("\n");
        }
        path[step] = root->data;
        Prepath(root->Lchild,step+1);
        Prepath(root->Rchild,step+1);
    }
}

int main(void)
{
    BiTree root;
    Create(&root);
    Prepath(root,0);
    return 0;
}

