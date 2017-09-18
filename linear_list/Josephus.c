/*************************************************************************
	> File Name: Josephus.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月18日 星期一 23时39分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

typedef struct NodeList{
	int id;
	int password;
	struct NodeList *next;
}LNode,*linklist;
void CreatList(LNode **pphead,int n);
LNode *GetNode(int iId,int ipassword);
void PrintList(linklist phead);
int IsEmptyList(linklist phead);
void JosephusOperate(linklist *L,int passord);

void CreatList(LNode **pphead,int n)
{
	int i = 0;
	int ipassword = 0;
	LNode *pNew = NULL;
	LNode *pCur = NULL;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&ipassword);
		pNew = GetNode(i,ipassword);
		if(*pphead == NULL)
		{
			*pphead = pCur =pNew;
			pCur->next = *pphead;
		 } 
		else
		{
			pNew->next=pCur->next;
			pCur->next=pNew;
			pCur = pNew;
		}
	}
 } 
 
 LNode *GetNode(int iId,int ipassword)
 {
 	LNode *pNew = NULL;
	pNew = (LNode *)malloc(sizeof(LNode));
	if(!pNew)
	{
	 	printf("Error,the memory is not enough\n");
	 	exit(-1);
	 	
	}
	pNew->id=iId;
	pNew->password = ipassword;
	pNew->next = NULL;
	return pNew; 
 }
 
 
 void PrintList(linklist phead)
 {
	linklist pCur = phead;
	if(!IsEmptyList(phead))
	{
		do
		{
			printf("%3d %7d\n",pCur->id,pCur->password);
			pCur = pCur->next; 
		} while(pCur!=phead);
	}
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
 
 
 void JosephusOperate(linklist *L,int passord)
{
    int icount = 0;
    int flag = 1;
    linklist pPrv=NULL,pCur=NULL,pDel=NULL;
    pPrv=pCur = *L;
    while(pPrv->next != *L)
        pPrv = pPrv->next;
    while(flag)
    {
        for(icount = 1;icount<passord;icount++)
        {
            pPrv = pCur;
            pCur = pCur ->next;
        }
        if(pPrv == pCur)
            flag=0;
        pDel = pCur;
        pPrv->next = pCur->next;
        pCur = pCur->next;
        passord = pDel->password;
        
        if(flag == 1)
			printf("%d ",pDel->id);
        else
        	printf("%d\n",pDel->id);
		free(pDel);
    }
    L=NULL;
    getchar();
}

int main(void)
{
	int n,m;
	linklist phead=NULL;
	scanf("%d",&n);
	scanf("%d",&m);
	CreatList(&phead,n);
	JosephusOperate(&phead,m);
	return 1;
}
