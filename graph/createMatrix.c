*************************************************************************
	> File Name: create2.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年12月18日 星期一 14时32分11秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 20

int visited[MAXVEX]={0};
typedef struct 
{
	int arc[MAXVEX][MAXVEX];
	char vex[MAXVEX];
	int vexnum;
	int arcnum;
}AdjMatrix;

void Creat(AdjMatrix *G,int RuDu[ ],int ChuDu[ ])
{
	int i,j,k;
	scanf("%d%d",&G->vexnum,&G->arcnum);
	for(i=1;i<G->vexnum;i++)
		for(j=1;j<G->arcnum;j++)
			G->arc[i][j]=0;
	char words[G->vexnum]; 
	scanf("%s",words);
	for(i=1;i<=G->vexnum;i++)
	{
		G->vex[i]=words[i-1] ;
	}
 	int z,x;
	for(k=1;k<=G->arcnum;k++)
	{
			char s[2]; 
			scanf("%s",s);
 			fflush(stdin);
 		G->arc[s[0]-64][s[1]-64]=1;	
 		//建立的同时计算出入度和出度
        RuDu[s[0]-64]++;
 		ChuDu[s[1]-64]++;
	}
	
	for(k=1;k<=G->vexnum;k++)
	{
		printf("%c %d %d\n",G->vex[k],RuDu[k],ChuDu[k]);
	}
}

int FirstAdjVex(AdjMatrix *G,int v0)
{
	int j;
	for(j=1;j<G->arcnum;j++)
		if(G->arc[v0][j]!=0)
			return j;
	return -1;
}

int NextAdjVex(AdjMatrix *G,int v0,int w)
{
	int j;	
	for(j=w+1;j<G->arcnum;j++)
		if(G->arc[v0][j]!=0)
			return j;	
	return -1;
}

void DFS(AdjMatrix *G,int v0 )
{
	int w;
	printf("%c",G->vex[v0]);
	visited[v0]=1;
	w=FirstAdjVex(G,v0);
	while(w!=-1)
	{
		if(!visited[w])
			DFS(G,w );
		w=NextAdjVex(G,v0,w);
	}
}

void BFS(AdjMatrix *G,int v0)
{
	int w,v;
	int Q[G->vexnum+1];
	int front =0,tail = 0;
		
	printf("%c",G->vex[v0]);
	visited[v0]=-1;
	Q[++tail] = v0;
	
	while(front != tail){
		v = Q[++front];
		w = FirstAdjVex(G,v);
		while(w!=-1){
			if(!visited[w])
			{
				printf("%c",G->vex[w]);
				visited[w]=1;
				Q[++tail] = w;
			}
			w=NextAdjVex(G,v,w);
		}
	} 
}
void  TraverseG1(AdjMatrix *G)
{
	int v;
	for(v=1;v<=G->vexnum;v++)
		visited[v]=0;
	for(v=1;v<=G->vexnum;v++)
		if(!visited[v])
			BFS(G,v);
}
void  TraverseG(AdjMatrix *G)
{
	int v;
	for(v=1;v<=G->vexnum;v++)
		if(!visited[v])
			DFS(G,v);
}

int main(void)
{
	int RuDu[MAXVEX]={0},ChuDu[MAXVEX]={0};
	AdjMatrix *G;
	G = (AdjMatrix *) malloc(sizeof(AdjMatrix));
	Creat(G,RuDu,ChuDu);
	TraverseG(G);
	printf("\n");
	TraverseG1(G);
    return 0;
}
