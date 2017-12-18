/*************************************************************************
	> File Name: liantong.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年12月18日 星期一 18时06分38秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MaxVerNum 100 /*定义最大节点数*/
int visited[MaxVerNum] ;
int icount=0;
typedef char VertexType ;
typedef struct node
{
    int adjvex ;
    struct node *next ; //指向下一个邻接节点域
} EdgeNode ;

typedef struct vnode
{
    VertexType vertex ; //顶点域
    EdgeNode *firstedge ; //边表头指针
} VertexNode ;

typedef VertexNode AdjList[MaxVerNum] ;

typedef struct
{
    AdjList adjList ; //邻接表
    int n , e ; //顶点数与边数
} ALGraph ;


typedef struct
{
    int data[1000] ;
    int head , tail ; //队头与队尾
} Quene ;

int LocateVex(ALGraph *G, char v)
{
    int i;
    for(i=0;i < G->n;i++){
        if(G->adjList[i].vertex == v)
            return i;
    }
    return -1;
}

void CreateALGraph(ALGraph *G)
{
    int i , j , k ;
    EdgeNode *s ;
    scanf("%d%d" , &G->n , &G->e) ;
    getchar();
    for( i = 0 ; i < G->n ; i++)
    {
        scanf("%c" , &G->adjList[i].vertex) ;
        G->adjList[i].firstedge = NULL ; //将顶点的边表头指针设置为空
    }
    getchar();
     
    for(k = 0 ; k < G->e ; k++)
    {
        char a,b;
        scanf("%c%c" , &a , &b) ;
        getchar();
         
        i=LocateVex(G,a);
        j=LocateVex(G,b);
         
        s = malloc(sizeof(EdgeNode)) ;
        s->adjvex = j ;
        //头插
        //s->next = G->adjList[i].firstedge ;
        //G->adjList[i].firstedge = s ;
        EdgeNode *p=G->adjList[i].firstedge;
        //尾插
        s->next = NULL;
        if(p==NULL){
            G->adjList[i].firstedge = s;
        }else{
            while(p->next!=NULL){
            p=p->next;
        }
        p->next = s;
        }
    } 
}

void DFSAL(ALGraph *G , int i)
{
    //以Vi为出发点对图进行遍历
    EdgeNode *p ;
    visited[i] = 1 ;
    p = G->adjList[i].firstedge ;
    while(p){
        if(!visited[p->adjvex]){
            DFSAL(G , p->adjvex) ;
        }
        p = p->next ;
    }
}

void DFSTraverseAL(ALGraph *G)
{
    int i ;
    for(i = 0 ; i < G->n ; i++){
        visited[i] = 0 ;
    }
    for(i = 0 ; i < G->n ; i++){
        if(!visited[i]){
            DFSAL(G , i) ;
            icount++;
        }
    }
}

int  main(void)
{
    ALGraph *G ;
    G = (ALGraph*)malloc(sizeof(ALGraph)) ;
    CreateALGraph(G) ;
    DFSTraverseAL(G) ;
    printf("%d\n",icount);
    return 0;
}

