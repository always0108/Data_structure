/*************************************************************************
	> File Name: huiwen.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月08日 星期日 13时47分25秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Stack
{
    int top;
    char str[100];
}STACK;

int main()
{
    int len,i,mid,next;
    char str[100];
    STACK s;
    s.top=0;
    gets(str);
    len=strlen(str);
    mid=len/2;
    for(i=0;i<mid;i++){
        s.str[s.top]=str[i];
        s.top++;
    }
    if(len%2!=0){
        next=mid+1;
    }else{
        next=mid;
    }
    while(s.top!=0){
        if(s.str[s.top-1]==str[next]){
            s.top--;
            next++;
        }
        else{
            break;
        }
    }
    if(s.top==0){
        printf("是回文\n");
    }
    else{
        printf("不是回文\n");
    }
    return 0;
}
