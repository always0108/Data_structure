/*************************************************************************
	> File Name: Kruskal.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年12月18日 星期一 19时29分35秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXVEX 20              //最大顶点个数 
int par[1000], Rank[1000]; 

typedef struct
{
    int arcs[MAXVEX][MAXVEX];  //边（或弧）信息
    char vex[MAXVEX];           //顶点信息
    int vexnum;                //顶点数目
    int arcnum;                //边（或弧）数目
}AdjMatrix;                    //临接矩阵

typedef struct{
    char a,b;
    int weight;
    int flag;
}Array[30],node;

int cmp(const void *a, const void *b)
{
    return ((node*)a)->weight-((node*)b)->weight;
}


void Init(int n){  
    for(int i = 0; i <= n; i++){  
        Rank[i] = 0;  
        par[i] = i;  
    }  
}  
  
int find(int x){  
    int root = x;  
    while(root != par[root]) 
        root = par[root];  
    while(x != root){  
        int t = par[x];  
        par[x] = root;  
        x = t;  
    }  
    return root;  
}  
  
void unite(int x, int y){  
    x = find(x);  
    y = find(y);  
    if(Rank[x] < Rank[y]){  
        par[x] = y;  
    }  
    else{  
        par[y] = x;  
        if(Rank[x] == Rank[y]) Rank[x]++;  
    }  
}  

//n为结点的数量,m为边的数量
int Kruskal(Array a,int n, int m){  
    Init(128);
    int nEdge = 0, res = 0;  
    //将边按照权值从小到大排序  
    qsort(a, m, sizeof(a[0]), cmp);  
    for(int i = 0; i < m && nEdge != n - 1; i++){  
        //判断当前这条边的两个端点是否属于同一棵树  
        if(find(a[i].a) != find(a[i].b)){  
            a[i].flag = 1;
            unite(a[i].a, a[i].b);  
            res += a[i].weight;  
            nEdge++;  
        }  
    }  
    
    //如果加入边的数量小于m - 1,则表明该无向图不连通,等价于不存在最小生成树  
    if(nEdge < n-1) 
        res = -1;
        
    for(int i=0;i <= m-1;i++)
        printf("(%c,%c,%d,%d)",a[i].a,a[i].b,a[i].weight,a[i].flag);
    return res;  
}  

void Create(AdjMatrix *G)
{
    int i,j,k,weight;
    char vex1,vex2;
    Array array;
    
    scanf("%d%d",&G->vexnum,&G->arcnum);
    getchar();

    for(i = 1;i <= G->vexnum;i++){
        scanf("%c",&G->vex[i]);
    }
    getchar();

    for(k=0;k<G->arcnum;k++){
        scanf("(%c,%c,%d)",&array[k].a,&array[k].b,&array[k].weight);
        array[k].flag=0;
    }

    Kruskal(array,G->vexnum,G->arcnum);
    printf("\n");
}

int main(void)
{
    AdjMatrix G;
    Create(&G);
    return 0;
}

