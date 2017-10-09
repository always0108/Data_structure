/*************************************************************************
	> File Name: kmp.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月09日 星期一 20时39分51秒
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

void Get_Next(SString T);
void Get_NextVal(SString T);
int Index_KMP(SString S, int pos, SString T);

int next[51];
int nextval[51];

int Index_KMP(SString S, int pos, SString T)
{
    /*puts(S.ch+1);
    puts(T.ch+1);
    printf("%d\n",S.len);
    printf("%d\n",T.len);*/
    int i = pos, j = 1;                   //主串从第pos开始，模式串从头开始
    while(i <= S.len && i<= T.len){
        if(j == 0 || S.ch[i] == T.ch[j]){ //继续比较后续字符
            ++i;
            ++j;
        }else{
            j = nextval[j];                  //模式串向右滑动
        }
    }
    if(j > T.len)
        return i - T.len;                 //匹配成功，返回匹配的起始位置
    else
        return 0;                         //匹配失败，返回0
}

void Get_Next(SString T)
{
    int j = 1, k = 0;
    next[1] = 0;
    while(j < T.len){
        if(k == 0 || T.ch[j] == T.ch[k]){
            ++j;
            ++k;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
}

void Get_NextVal(SString T)
{
    int j = 2, k = 0;
    Get_Next(T);   //通过Get_NextVal()来获得T的next值
    nextval[1] = 0;
    while(j <= T.len)
    {
        k = next[j];
        if(T.ch[j] == T.ch[k]){
            nextval[j] = nextval[k];
        }else{
            nextval[j] = next[j];
        }
        j++;
    }
}

int main(void)
{
    SString S;
    int pos;
    printf("请输入主串S:");
    gets(S.ch+1);
    S.len = strlen(S.ch+1);
    printf("请输入要查找的串:");
    SString T;
    gets(T.ch+1);
    T.len = strlen(T.ch+1);
    printf("请输入开始搜索的位置:");
    scanf("%d",&pos);
    if(pos < 1 || pos > S.len)
    {
        printf("location is illegal\n");
        return -1;
    }
    memset(&next,0,sizeof(next));
    memset(&nextval,0,sizeof(nextval));
    Get_Next(T);
    Get_NextVal(T);
    int result = Index_KMP(S,pos,T);
    if(result > 0){
        printf("exist, index is %d\n",result);
    }else{
        printf("not exist\n");
    }
    return 0;
}
