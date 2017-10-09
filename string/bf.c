/*************************************************************************
	> File Name: bf.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月09日 星期一 22时25分21秒
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
    //printf("%s\n",S.ch);
    //printf("%s\n",T.ch);
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

int main(void)
{
    SString S,T;
    int pos;
    printf("请输入主串S:");
    gets(S.ch+1);
    S.len = strlen(S.ch+1);
    printf("请输入要查找的串:");
    gets(T.ch+1);
    T.len = strlen(T.ch+1);
    printf("请输入开始搜索的位置:");
    scanf("%d",&pos);
    if(pos < 1 || pos > S.len)
    {
        printf("location is illegal\n");
        return -1;
    }
    int result = Index(S,pos,T);
    if(result > 0){
        printf("exist, index is %d\n",result);
    }else{
        printf("not exist\n");
    }
    return 0;
}
