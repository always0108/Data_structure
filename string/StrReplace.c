/*************************************************************************
	> File Name: StrReplace.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月12日 星期四 13时34分49秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXLEN 50
typedef struct{
    char ch[MAXLEN+1];
    int len;
}SString;

int Index(SString S, int pos, SString T)
{
    int i = pos, j = 1;             //主串从第pos开始，模式串从头开始
    while(i <= S.len && j <= T.len){
        if(S.ch[i] == T.ch[j]){     //当对应字符相等，比较后续字符
            i++;
            j++;
        }else{                      //当对应字符不相等
            i = i-j+2;              //主串回溯到i-j+2的位置重新比较
            j = 1;                  //模式串从头开始重新比较
        }
    }
    if(j > T.len)
        return i-T.len;             //匹配成功时，返回匹配的起始位置
    else
        return 0;                   //匹配失败时，返回0
}

int StrDelete(SString *S,int pos,int len)
{
    int i = 1;
    if(NULL == S || NULL == S->ch || len < 0 || pos < 1 || pos > S->len-len+1)
        return 0;
    for(i = pos ; i <= S->len - len;i++)
        S->ch[i] = S->ch[i+len];
    S->len = S->len - len;
    S->ch[S->len+1]='\0';
    return 1;
}

int StrInsert(SString *S,int pos ,SString T)
{
    int i;
    if(NULL == S || NULL == S->ch || NULL == T.ch || pos<1 ||pos > S->len+1)
        return 0;
    if(S->len + T.len <= MAXLEN)
    {
        for(i=S->len+T.len; i>=pos+T.len;i--)
            S->ch[i] = S->ch[i-T.len];
        for(i = pos; i< pos+T.len;i++)
            S->ch[i] = T.ch[i-pos+1];
        S->len = S->len + T.len;
        S->ch[S->len+1]='\0';
    }
    else if(pos + T.len <= MAXLEN)
    {
        for(i=MAXLEN;i >=pos+T.len;i--)
            S->ch[i] = S->ch[i-T.len];
        for(i = pos; i< pos+T.len;i++)
            S->ch[i] = T.ch[i-pos+1];
        S->len = MAXLEN;
    }
    else{
        for(i = pos;i<=MAXLEN;i++)
            S->ch[i] = T.ch[i-pos+1];
        S->len = MAXLEN;
    }
    return 1;
}

int StrReplace(SString *S,SString *T,SString *V)
{
    //先寻找要替换的字符串的位置
    int pos = Index(*S,1,*T);
    printf("%d\n",pos);
    if(pos > 0)
    {
        //把要替换的字符串先删掉
        StrDelete(S,pos,T->len);
        //将目标的字符串插入进去
        StrInsert(S,pos,*V) ; 
        printf("%s\n",S->ch+1);
    }
    else{
        printf("can not find string\n");
    }
}


int main(void)
{
    SString S,V,T;
    gets(S.ch+1);
    S.len = strlen(S.ch+1);
    gets(T.ch+1);
    T.len = strlen(T.ch+1);
    gets(V.ch+1);
    V.len = strlen(V.ch+1);
    StrReplace(&S,&T,&V);
    return 0;
}
