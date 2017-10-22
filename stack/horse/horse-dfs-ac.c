/*************************************************************************
	> File Name: horse2.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月25日 星期一 22时02分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};  
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};  

int vis[9][9];
int result[9][9];
int p,q;
int flag;

struct Step{
    int  x, y;
} path[100];

int check(int x,int y)
{
    if(vis[x][y]== 0 && x>0 && y>0 && x<=8 && y<=8 && !flag)
        return 1;
    return 0;
}

void dfs(int x,int y,int step)
{
    path[step].y = y;   
    path[step].x = x;
    
    if(step == 64)
    {
        flag=1;
        return ;
    }
    int xx,yy,t;
    
    for(t=0;t<8;t++)
    {
        xx = x+dx[t];
        yy = y+dy[t];
        if(check(xx,yy))
        {
            vis[xx][yy]=1;
            dfs(xx,yy,step+1);
            vis[xx][yy]=0;
        }
    }
}

int main(void)
{
    int i,j;
    flag=0;
    memset(vis,0,sizeof(vis));
    memset(result,0,sizeof(result));
    scanf("%d %d",&p,&q);
    vis[p][q]=1;
    dfs(p,q,1);
    if(flag){
        for(j=1;j<=64;j++){
                /*printf("(%d,%d)  ",path[j].x,path[j].y);
                if(j%8==0)
                    printf("\n");*/
            result[path[j].x][path[j].y] = j;
        }
        for(i=1;i<=8;i++)
        {
            for(j=1;j<=8;j++)
                printf("%2d ",result[i][j]);
            printf("\n");
        }
    }
    else
        printf("impossible\n");
    return 0;
}
