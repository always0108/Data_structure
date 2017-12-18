/*************************************************************************
	> File Name: create.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月27日 星期一 15时02分38秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXVEX 20              //最大顶点个数
#define INFINITY 32767         //表示极大值

typedef struct
{
    int arcs[MAXVEX][MAXVEX];  //边（或弧）信息
    char vex[MAXVEX];           //顶点信息
    int vexnum;                //顶点数目
    int arcnum;                //边（或弧）数目
}AdjMatrix;                    //临接矩阵

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
    printf("请输入无向网中的顶点数和边数：\n");
    scanf("%d%d",&G->vexnum,&G->arcnum);
    getchar();
    for(i = 1;i <= G->vexnum;i++){
        for(j = 1;j <=G->vexnum;j++){
            G->arcs[i][j] = INFINITY;
        }
    }
    
    printf("请输入无向网中%d个顶点:\n",G->vexnum);
    for(i = 1;i <= G->vexnum;i++){
        printf("No.%d个顶点:顶点V    ",i);
        scanf("%c",&G->vex[i]);
        getchar();
    }

    for(k=0;k<G->arcnum;k++){
        printf("\nNo.%d条边:\n      顶点V  ",k+1);
        scanf("%c",&vex1);
        getchar();
        printf("<---> 顶点V  ");
        scanf("%c",&vex2);
        getchar();
        printf("Weight:  ");
        scanf("%d",&weight);
        getchar();
        i = LocateVex(G,vex1);
        j = LocateVex(G,vex2);
        G->arcs[i][j] = weight;    //如果不是网，赋值为1
        G->arcs[j][i] = weight;    //如果是有向网，删掉此句
    }
}

void Print_map(AdjMatrix *G){
    int i,j;
    for(i=1;i<=G->vexnum;i++){
        printf("\t%c",G->vex[i]);
    }
    printf("\n\n");
    for(i=1;i<=G->vexnum;i++){
        printf("%c\t",G->vex[i]);
        for(j=1;j<=G->vexnum;j++){
            if(G->arcs[i][j] == INFINITY)
                printf("∞\t");
            else
                printf("%d\t",G->arcs[i][j]);

        }
        printf("\n");
    }
}

int main(void)
{
    AdjMatrix G;
    Create(&G);
    Print_map(&G);
    return 0;
}




