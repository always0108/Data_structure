/*************************************************************************
	> File Name: dfs-stack.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月09日 星期一 15时41分53秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};  
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};  

int vis[9][9];
int result[9][9];
int p,q;
int flag;

struct Step{
    int  x, y;
} path[100];

typedef struct{  //location
	int x;
	int y;
}PosType;

typedef struct{  //STACK
	PosType seat; //point
    int step;
}ElemType;

typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

SqStack s;

int InitStack(){
	s.base = (ElemType *)malloc(100*sizeof(ElemType));
	if(!s.base)		return 0;
	s.top = s.base;
	s.stacksize = 100;
	return 1;
}

ElemType GetTop()
{
	if(s.top == s.base)
		exit(0);
	return *(s.top-1);
}

void Push(ElemType elem)
{
	*s.top++ = elem;
}

int Pop(ElemType *elem)
{
	if(s.top == s.base)
		return 0;
	*elem = *--s.top;
	return 1;
}

int StackEmpty()
{
	if(s.top == s.base)		return 1;
	else	return 0;
}

int check(int x,int y)
{
    if(vis[x][y]== 0 && x>0 && y>0 && x<=8 && y<=8 && !flag)
        return 1;
    return 0;
}

void dfs_stack(int x,int y,int step)
{ 
    int xx,yy,t;
    ElemType tmp;
    tmp.seat.x = x;
    tmp.seat.y = y;
    tmp.step = step;
    Push(tmp); 
    path[tmp.seat.x].y = tmp.seat.x;   
    path[tmp.seat.y].x = tmp.seat.y;
    
    while(!StackEmpty())
    {
        tmp = GetTop();
        
        if(tmp.step == 64)
        {
            flag=1;
            return ;
        }
        int flag2 = 0;
        for(t=0;t<8;t++)
        {
            xx = tmp.seat.x+dx[t];
            yy = tmp.seat.y+dy[t];
            if(check(xx,yy))
            {
                vis[xx][yy]=1;
                ElemType temp;
                temp.seat.x=xx;
                temp.seat.y=yy;
                temp.step = tmp.step + 1;
                Push(temp);
                
                flag = 1;
                path[temp.seat.x].y = temp.seat.x;   
                path[temp.seat.y].x = temp.seat.y;
                break ; 
            }
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
    dfs_stack(p,q,1);
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

