/*************************************************************************
	> File Name: Delete_in_A_Insert_in_B.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月22日 星期五 10时05分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

typedef struct NodeList{
	int data;
	struct NodeList *next;
}LNode,*linklist;
void CreatList(LNode **pphead,int n);
LNode *GetNode(int idata);
void PrintList(linklist phead);
int IsEmptyList(linklist phead);
void JosephusOperate(linklist *L,int passord);

void CreatList(LNode **pphead,int n)
{
	int i = 0;
	int idata = 0;
	LNode *pNew = NULL;
	LNode *pCur = NULL;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&idata);
		pNew = GetNode(idata);
		if(*pphead == NULL)
		{
			*pphead = pCur =pNew;
			pCur->next = NULL;
		} 
		else
		{
			pNew->next=NULL;
			pCur->next=pNew;
			pCur = pNew;
		}
    }
} 
 
LNode *GetNode(int idata)
{
 	LNode *pNew = NULL;
	pNew = (LNode *)malloc(sizeof(LNode));
	if(!pNew)
	{
	 	printf("Error,the memory is not enough\n");
	 	exit(-1);
	 	
	}
    pNew->data = idata; 	
	pNew->next = NULL;
    return pNew; 
}

int Length_linklist(linklist phead)
{
    LNode *p = phead;
    if(!phead)
        return 0;
    int j=1;
    while(p->next!=NULL)
    {
        p=p->next;
        j++;
    }
    return j;
}
 
 
void PrintList(linklist phead)
{
	linklist pCur = phead;
	if(!IsEmptyList(phead))
	{
	    printf("\n");
		do
		{
			printf("%d ",pCur->data);
			pCur = pCur->next; 
		} while(pCur!=NULL);
	    printf("\n");
    }

}
 
linklist get_linklist(linklist phead,int k)
{
    if(!phead)
        return NULL;
    LNode *p = phead;
    int j = 1;
    while(p->next != NULL && j<k)
    {
        p = p->next;
        j++;
    }
    if(j == k)
    {
        return p;
    }
    else return NULL;
}

int IsEmptyList(linklist phead)
{
 	if(!phead)
    {
 		printf("The list is empty\n");
 		return 1;
	}
	return 0;
}

int  Del_linklist(linklist phead,int i)
{
    linklist p,q;
    p = phead;
    for(int j=1;j<i-1;j++)
        p=p->next;
    if(p == NULL)
    {
        return 0;
    }else{
        if(p->next == NULL)
        {
            return 0;
        }else{
            q = p->next;
            p->next = q->next;
            free(q);
            return 1;
        }
    }

}
int  Insert_tail(linklist phead,int x)
{
    LNode *p,*s;
    p = get_linklist(phead,Length_linklist(phead));
    if(p == NULL)
    {
        printf("can not insert\n");
        return 0;
    }else{
        s = (linklist)malloc(sizeof(LNode));
        s->data = x;
        s->next = NULL;
        p->next = s;
        return 1;
    }
}
 
int Insert_linklist(linklist phead, int i, int x)
{
    LNode *p,*s;
    p = get_linklist(phead,i-1);
    if(p == NULL)
    {
        printf("插入位置i错");
        return 0;
    }else{
        s = (linklist)malloc(sizeof(LNode));
        s->data = x;
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

int main(void)
{
	int n,m;
    linklist list1 = NULL;
    linklist list2 = NULL;
    
    //create list1 & list2
    printf("input the length of list1:");
    scanf("%d",&n);
	CreatList(&list1,n);
    
    printf("input the length of list2:");
    scanf("%d",&m);
    CreatList(&list2,m);
    
    PrintList(list1);
    PrintList(list2);

    //input i and len.   
    int i,len;
    printf("input i and len:");
    scanf("%d%d",&i,&len);

    int list1len = Length_linklist(list1);
    //judge i and len
    if(i<=0 || i>list1len)
    {
        printf("i is illegal\n");
        return 0;
    }
    if(list1len-i+1 < len)
    {
        printf("len is too large!\n");
        return 0;
    }else{
        int j;
        for(j=0;j<len;j++)
        {
            LNode *p = get_linklist(list1,i);
            Insert_tail(list2,p->data);
            Del_linklist(list1,i);
        }
    }
    
    PrintList(list1);
    PrintList(list2);
    return 1;
}

