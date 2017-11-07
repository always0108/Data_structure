/*************************************************************************
	> File Name: IPcreate.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月06日 星期一 22时36分44秒
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

void Create(BiTree* root,char* inorder, char* postorder, int length)
{
    if(length == 0)
    {
        *root=NULL;
        return;
    }
    char node_value = postorder[length-1];
    int rootIndex;
    for(rootIndex = 0;rootIndex < length;rootIndex++){
        if(inorder[rootIndex] == node_value)
            break;
    }
    *root = (BiTree)malloc(sizeof(BiTNode));
    (*root)->data = node_value;
    //Left
    Create(&((*root)->Lchild),inorder, postorder, rootIndex);
    //Right
    char tmp[1000];
    strncpy(tmp,postorder+rootIndex,length-rootIndex-1);
    tmp[length-rootIndex-1]='\0';
    Create(&((*root)->Rchild),inorder+rootIndex+1,tmp,length-rootIndex-1);
    return;
}

void PreOrder(BiTree root)
{
    if(root){
        putchar(root->data);
        PreOrder(root->Lchild);
        PreOrder(root->Rchild);
    }
}

int main(void){
    BiTree root;
    
    char Post[1000];
    char In[1000];
    gets(In);
    gets(Post);
    if(strlen(Post)!=strlen(In))
        return 0;
    Create(&root,In,Post,strlen(In));
    PreOrder(root);
    printf("\n");
    return 0;
}

