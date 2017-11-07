/*************************************************************************
	> File Name: PIcreate.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 21时52分18秒
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

void Create(BiTree* root,char* inorder, char* preorder, int length)
{
    if(length == 0)
    {
        *root=NULL;
        return;
    }
    char node_value = preorder[0];
    int rootIndex;
    for(rootIndex = 0;rootIndex < length; rootIndex++){
        if(inorder[rootIndex] == node_value)
            break;
    }
    *root = (BiTree)malloc(sizeof(BiTNode));
    (*root)->data = node_value;
    //Left
    Create(&((*root)->Lchild),inorder, preorder +1, rootIndex);
    //Right
    Create(&((*root)->Rchild),inorder+rootIndex+1,preorder+rootIndex+1,length-(rootIndex+1));
    return;
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
    
    char Pre[1000];
    char In[1000];
    //fgets本机测没有问题，oj没法过，改成gets即可
    /*fgets(Pre,1000,stdin);
    fgets(In,1000,stdin);
    Pre[strlen(Pre)-1]='\0';
    In[strlen(In)-1]='\0';*/
    gets(Pre);
    gets(In);
    if(strlen(Pre)!=strlen(In))
        return 0;
    Create(&root,In,Pre,strlen(Pre));
    PostOrder(root);
    printf("\n");
    return 0;
}
