/*************************************************************************
	> File Name: BSTree.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年12月18日 星期一 22时00分49秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef int KeyType; //假设的关键字类型
typedef struct Node{
    KeyType key;
    struct Node *Lchild,*Rchild;
}BSTNode,*BSTree;

//查找(非递归)
BSTree SearchBST1(BSTree bst,KeyType K){
    BSTree q;
    q = bst;
    while(q){
        if(q->key==K)     return q;
        if(K < q->key)    q=q->Lchild;
        else              q=q->Rchild;
    }
    return NULL;
}

//查找（递归）
BSTree SearchBST2(BSTree bst,KeyType K){
    if(!bst)   return NULL;
    else if(bst->key==K)    return bst;
    else if(K<bst->key)     return SearchBST2(bst->Lchild,K);
    else                    return SearchBST2(bst->Rchild,K);
}

//插入
void InsertBST(BSTree *bst,KeyType K)
{
    BSTree s;
    if(*bst == NULL){
        s = (BSTree)malloc(sizeof(BSTNode));
        s->key = K;
        s->Lchild = NULL;
        s->Rchild = NULL;
        *bst = s;
    }
    else if(K<(*bst)->key)    InsertBST(&((*bst)->Lchild),K);
    else if(K>(*bst)->key)    InsertBST(&((*bst)->Rchild),K);
}

//建立
void CreateBST(BSTree *bst)
{
    KeyType key;
    *bst = NULL;
    while(scanf("%d",&key)!=EOF){
        InsertBST(bst,key);
    }
}

//删除
BSTNode * DelBST(BSTree bst,KeyType K)
{
    BSTNode *p,*f,*s,*q;
    p=bst;
    f=NULL;
    while(p){
        if(p->key==K)   break;
        f = p;
        if(p->key>K)    p=p->Lchild;
        else            p=p->Rchild;
    }
    //没找到
    if(p==NULL)    return bst;
    //左子树为空
    if(p->Lchild == NULL){
        if(f==NULL)    bst=p->Rchild;
        else if(f->Lchild ==  p)    f->Lchild = p->Rchild;
        else                        f->Rchild = p->Lchild;
        free(p);
    }
    else{
        q=p;
        s=p->Lchild;
        while(s->Rchild){
            q=s;
            s=s->Rchild;
        }
        if(q==p)    q->Lchild=s->Rchild;
        else        q->Rchild=q->Lchild;
        p->key = s->key;
        free(s);
    }
    return  bst;
}

