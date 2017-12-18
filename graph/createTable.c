/*************************************************************************
	> File Name: create3.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年12月18日 星期一 15时49分11秒
 ************************************************************************/

/*
 *进行图的遍历，进行图的深度遍历与广度遍历
 */
#include<stdio.h>
#include<malloc.h>
#define MaxVerNum 100 /*定义最大节点数*/
int visited[MaxVerNum] ;
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
/*
 *定义以邻接边为存储类型的图
 */
typedef struct
{
    AdjList adjList ; //邻接表
    int n , e ; //顶点数与边数
} ALGraph ;
/*
 *建立队列的数据结构方便进行广度优先遍历
 */
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

/*
 *建立有向图的邻接表存储
 */
 void CreateALGraph(ALGraph *G)
 {
     int i , j , k ;
     EdgeNode *s ;
     //printf("请输入顶点数与边数（输入格式为：顶点数 边数）： ") ;
     scanf("%d%d" , &G->n , &G->e) ;
     getchar();
     //printf("请输入顶点信息（输入格式为：顶点号）：\n") ;
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
/*
 *进行图的深度优先搜索遍历
 */
 void DFSAL(ALGraph *G , int i)
 {
     //以Vi为出发点对图进行遍历
     EdgeNode *p ;
     printf("%c" , G->adjList[i].vertex) ;
     visited[i] = 1 ;
     p = G->adjList[i].firstedge ;
     while(p)
     {
         if(!visited[p->adjvex])
         {
             DFSAL(G , p->adjvex) ;
         }
         p = p->next ;
     }
 }

void DFSTraverseAL(ALGraph *G)
{
    int i ;
    for(i = 0 ; i < G->n ; i++)
    {
        visited[i] = 0 ;
    }
    for(i = 0 ; i < G->n ; i++)
    {
        if(!visited[i])
        {
            DFSAL(G , i) ;
            printf("\n");
        }
    }
}
 /*
  *进行广度优先搜索遍历
  */
void BFSG(ALGraph *G , int k)
{
    int i , j ;
    Quene q ;
    EdgeNode *p ;
    q.head = 0 ;
    q.tail = 0 ; //进行队列的初始化
    printf("%c" , G->adjList[k].vertex) ;
    visited[k] = 1 ;
    q.data[q.tail++] = k ;
    while(q.head  % (MaxVerNum - 1) != q.tail % (MaxVerNum - 1))
    {
        i = q.data[q.head++] ;
        p = G->adjList[i].firstedge ;
        while(p)
        {
            if(!visited[p->adjvex])
            {
                printf("%c" , G->adjList[p->adjvex].vertex) ;
                visited[p->adjvex] = 1 ;
                q.data[q.tail++] = p->adjvex ;
            }
            p = p->next ;
        }
    }
}


void BFSTraverseAL(ALGraph *G)
{
    int i ;
    for(i = 0 ; i < G->n ; i++)
    {
        visited[i] = 0 ;
    }
    for(i = 0 ; i < G->n ; i++)
    {
        if(!visited[i])
        {
            BFSG(G , i) ;
            printf("\n");
        }
    }
}


void print_degree(ALGraph *G)
{
    int i , j;
    for(i=0;i<G->n;i++)
    {
        EdgeNode *p;
        int ind=0,outd=0;
        printf("%c ",G->adjList[i].vertex);
        //出度
        p=G->adjList[i].firstedge;
        while(NULL!=p){
            outd++;
            p=p->next;
        }
        printf("%d ",outd);
        
        //入度
        for(j=0;j<G->n;j++){
            if(i!=j){
                p = G->adjList[j].firstedge;
                while(NULL!=p){
                    if(p->adjvex == i){
                        ind++;
                    }
                    p=p->next;
                }
            }
        }
        printf("%d \n",ind);
    }
}
 /*
  *进行图的测试
  */
void main()
{
  ALGraph *G ;
  EdgeNode *p = NULL ;
  int i ;
  G = (ALGraph*)malloc(sizeof(ALGraph)) ;
  CreateALGraph(G) ;
  print_degree(G);
  //printf("深度优先遍历\n") ;
  DFSTraverseAL(G) ;
  //printf("广度优先遍历\n") ;
  BFSTraverseAL(G) ;
}
