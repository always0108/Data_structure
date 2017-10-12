/*************************************************************************
	> File Name: StrReverse.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月12日 星期四 13时14分33秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXLEN 50
typedef struct{
    char ch[MAXLEN+1];
    int len;
}String;

int Reverse(String *S,String *T){
    int i,j=0;
    for(i=S->len-1;i>=0;i--){
        T->ch[j]=S->ch[i];
        j++;
    }
    T->len = S->len; 
}

int main(void)
{
    String S,T;
    gets(S.ch);
    S.len = strlen(S.ch);
    Reverse(&S,&T);
    printf("%s\n",T.ch);
    return 0;
}

