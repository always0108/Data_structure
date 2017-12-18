/*************************************************************************
	> File Name: Topo.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年12月18日 星期一 20时35分37秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>



#define ElemType int
#define MAXVEX 20              //最大顶点个数
typedef struct
{
    int arcs[MAXVEX][MAXVEX];  //边（或弧）信息
    char vex[MAXVEX];           //顶点信息
    int vexnum;                //顶点数目
    int arcnum;                //边（或弧）数目
}AdjMatrix;                    //临接矩阵

typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

int InitStack(SqStack *s){
	s->base = (ElemType *)malloc(100*sizeof(ElemType));
	if(!s->base)		return 0;
	s->top = s->base;
	s->stacksize = 100;
	return 1;
}

void Push(SqStack *s,ElemType elem)
{
	*s->top++ = elem;
}

int Pop(SqStack *s,ElemType *elem)
{
	if(s->top == s->base)
		return 0;
	*elem = *--s->top;
	return 1;
}

int StackEmpty(SqStack *s)
{
	if(s->top == s->base)		return 1;
	else	return 0;
}



/*#define N 100   //定义队列最大多少个
#define datatype int  //定义队列的数据类型

struct queue
{
    datatype data[N];//保存数据的数组
    int front;  //数据的开头
    int rear;  //数据的结尾
};

typedef struct queue Q; //给已经有的类型简化一下


void Queueinit(Q *myqueue)
{
    myqueue->front = myqueue->rear = 0;
}

int isempty(Q *myqueue)
{
    if (myqueue->front==myqueue->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int enQueue(Q *myqueue, datatype num)
{
    if (myqueue->rear == N)
    {
        printf("失败");
        return -1;
    }
    else
    {
        myqueue->data[myqueue->rear] = num;//赋值
        myqueue->rear += 1;//增加一个
        return 0;
    }
}

datatype DeQueue(Q *myqueue)
{
    if (myqueue->front==myqueue->rear)
    {
        printf("失败");
        return -1;
    }
    else
    {
        myqueue->front += 1;
        return myqueue->data[myqueue->front-1];
    }
}*/

int LocateVex(AdjMatrix *G, char v)
{
    int i;
    for(i=1;i <= G->vexnum;i++){
        if(G->vex[i] == v)
            return i;
    }
    return 0;
}


void Create(AdjMatrix *G)
{
    int i,j,k,weight;
    char vex1,vex2;
    scanf("%d%d",&G->vexnum,&G->arcnum);
    getchar();
    for(i = 1;i <= G->vexnum;i++){
        for(j = 1;j <=G->vexnum;j++){
            G->arcs[i][j] = 0;
        }
    }
    
    for(i = 1;i <= G->vexnum;i++){
        scanf("%c",&G->vex[i]);
    }
    getchar();

    for(k=0;k<G->arcnum;k++){
        scanf("<%c,%c>",&vex1,&vex2);

        i = LocateVex(G,vex1);
        j = LocateVex(G,vex2);
        G->arcs[i][j] = 1;
    }
}

void FindInDegree(AdjMatrix *G,int indegree[MAXVEX])
{
    int i,j;
    for(i=1;i<=G->vexnum;i++)
        indegree[i] = 0;
    
    for(i=1;i<=G->vexnum;i++){
        for(j=1;j<=G->vexnum;j++){
            if(G->arcs[j][i]!=0)
                indegree[i]++;
        }
    }
}

int main(void)
{
    /*Q q;
    Queueinit(&q);*/
    SqStack s;
    InitStack(&s);
    AdjMatrix G;
    int indegree[MAXVEX];
    Create(&G);
    FindInDegree(&G,indegree);
    int i;
    for(i=1;i<=G.vexnum;i++){
        if(indegree[i]==0){
            Push(&s,i);
            //enQueue(&q,i);
        }
    }
    int count = 0;
    //while(!isempty(&q)){
    while(!StackEmpty(&s)){
        //int index = DeQueue(&q);
        int index;
        Pop(&s,&index);
        printf("%c",G.vex[index]);
        count++;
        for(int j=1;j<=G.vexnum;j++){
            if(G.arcs[index][j]){
                indegree[j]--;
                if(indegree[j]==0)
                    //enQueue(&q,j);
                    Push(&s,j);
            }
        }
    }

    if(count<G.vexnum)
        printf("Topo fail");
    printf("\n");
    return 0;
}

