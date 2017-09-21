#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node {  
    int data;  
    struct node *next;  
}Node;  
  
  
//创建链表  
Node *CreatList(void)  
{  
    int val, i, n;  
    Node *phead, *p, *q;  
  
    phead = NULL;  
    printf("请输入您要建立的链表长度:\n");  
    scanf("%d", &n);  
    printf("请输入您要输入的数据:\n");  
    for(i=0; i<n; ++i)  
    {     
        scanf("%d", &val);  
        p = (Node *)malloc(sizeof(Node));  
        p->data = val;  
        if(NULL == phead)  
            q = phead = p;  
        else  
        q->next = p;  
        q = p;  
    }  
    p->next = NULL;  
    return phead;  
}  
  
  
//链表的逆置  
Node *ReverseList(Node *phead)  
{  
    Node *p, *q, *r;  
  
    p = phead;  
    q=r=NULL;  
  
    while(p)  
    {  
        q = p->next;  
        p->next = r;  
        r = p;  
        p = q;  
    }  
    return r;  
}  
  

//输出链表  
void ShowList(Node *phead)  
{  
    Node *p;  
   
    p = phead;  
    while(p)  
    {  
        printf("%d ", p->data);  
        p = p->next;  
    }  
    printf("\n");  
}  
  
  
int main(void)  
{  
    Node *phead;  
  
    phead = CreatList();  
    printf("链表逆置前的数据:\n");  
    ShowList(phead);  
    phead = ReverseList(phead);  
  
    printf("链表逆置后的数据:\n");  
    ShowList(phead);  
      
    return 0;  
}   

