/*************************************************************************
	> File Name: publicchildstring.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月12日 星期四 14时37分10秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAXLEN 50
typedef struct{
    char data[MAXLEN+1];
    int length;
}SString;

SString Maxpublic(SString s,SString t)  
{  
    SString str;  
    int i,j,m,n;  
    int length=0;  
    int index=0;  
    for(i=0;i<s.length;i++)  
    {  
        for(j=0;j<t.length;j++)  
        {  
            for(m=j,n=i; m<t.length && n<s.length && s.data[n]==t.data[m]; m++,n++);  
                if(length<(m-j))  
                {  
                    length = m-j;  
                    index = i;  
                }  
        }  
    }  
    for(i=0;i<length;i++)  
        str.data[i]=s.data[index+i];  
    str.length=length;
    return str;  
}

int main(void)
{
    SString s,t,r;
    gets(s.data);
    s.length = strlen(s.data);
    gets(t.data);
    t.length = strlen(t.data);
    r = Maxpublic(s,t);
    if(r.length == 0)
    {
        printf("not exist\n");
    }else{
        printf("the max public string:\n");
        printf("%s\n",r.data);
    }
    return 0;
}

