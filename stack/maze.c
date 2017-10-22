/*************************************************************************
	> File Name: maze.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月28日 星期四 19时20分37秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int maze[101][101];
int road[101][3];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int m,n;
int endstep;
int flag;

int check(int x,int y)
{
    if(x>=1 && x<=m && y>=1 && y<=n && maze[x][y] == '0' && !flag)//在没有结果时判断
        return 1;
    return 0;
}

void dfs(int x ,int y,int step)
{
    road[step][0] = x;
    road[step][1] = y;
    
    if(x==m && y==n)
    {
        flag = 1;//表明找到结果
        endstep = step;
        return ;
    }

    int i,xx,yy;
    for(i=0; i < 4; i++)
    {
        xx = x + dir[i][0];
        yy = y + dir[i][1];
        
        if(check(xx,yy))
        {
            maze[xx][yy] = '1';
            road[step][2] = i + 1;
            dfs(xx,yy,step+1);
            maze[xx][yy] = '0';
        }
    }
}

int main(void)
{
    flag=0;
    scanf("%d%d",&m,&n);
    getchar();
    int i,j;
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++)
        {
            scanf("%c",&maze[i][j]);
        }
        getchar();
    }
    maze[1][1]='1';
    dfs(1,1,1);
    if(endstep > 0)
    {
        for(i=1;i<=endstep;i++)
        {
            printf("(%d,%d,%d)",road[i][0],road[i][1],road[i][2]);
        }
    }
    printf("\n");
    return 0;
}
