/*************************************************************************
	> File Name: SeqList.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月11日 星期一 23时48分45秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXSIZE 1000
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef struct 
{
    ElemType elem[MAXSIZE];
    int length;//线性表的长度
}SeqList;


//顺序表初始化
void Init_SeqList(SeqList *L)
{
    L->length = 0;
}

//按下标插入
int  Insert_SeqList(SeqList *L , int i ,ElemType x)
{
    if(L->length == MAXSIZE - 1)
    {
        printf("SeqList is full\n");
        return ERROR;
    }
    if(i < 1 || i > L->length + 1)
    {
        printf("error in location\n");
    }
    int j;
    for(j = L->length; j >= i;j--)
        L->elem[j+1] = L->elem[j];
    L->elem[i] = x;
    L->length++;
    return OK;
}


//按下标删除
int Delete_SeqList(SeqList *L , int i)
{
    if(L->length == 0)
    {
        printf("SeqList is empty\n");
        return ERROR;
    }
    if(i < 1 || i > L->length)
    {
        printf("the i data does not exist\n");
        return ERROR;
    }
    int j;
    for(j = i;j <= L->length - 1; j++)
        L->elem[j] = L->elem[j+1];
    L->length--;
    return OK;
}


//顺序表中按值查找元素的位置，找到第一个符合条件的值即返回
int Location_SeqList(SeqList *L , ElemType x)
{
    int i = 1;
    while(i <= L->length && L->elem[i]!=x)
        i++;
    if(i > L->length){
        printf("%d does not exist in the SeqList\n");
        return ERROR;
    }
    else
        return i;
}

//顺序表按下标打印出值
int Print_in_SeqList(SeqList *L ,int i)
{
    if(i < 1 || i > L->length)
    {
        printf("the i data does not exist\n");
        return ERROR;
    }
    else
    {
        printf("%d\n",L->elem[i]);
        return OK;
    }
}

//打印顺序表中所有的值
int Print_all(SeqList *L)
{
    int i;
    printf("-------------------------------\n");
    for(i = 1; i <= L->length; i++)
        printf("%d\n",L->elem[i]);
    printf("-------------------------------\n");
}


int main(void)
{
    SeqList List;
    //初始化
    Init_SeqList(&List);
    
    //插入1～10的平方
    int i;
    for(i=1;i<=10;i++){
        if(!Insert_SeqList(&List,i,i*i))
            printf("Insert fail\n");
    }

    //循环输出每一个元素
    printf("\n-----------------------------\n");
    for(i=1;i<=List.length;i++){
        Print_in_SeqList(&List , i);
    }
    printf("\n-----------------------------\n");
    
    //删除下标为5的数
    printf("删除下标为5的数\n");
    Delete_SeqList(&List,5); 
    
    //打印顺序表中所有的值
    Print_all(&List);

    //在顺序表中查找值为9的下标
    printf("The index of '9' is %d\n",Location_SeqList(&List , 9));
    
    printf("\n-----------------------------\n");

    return 0;
}

