/*************************************************************************
	> File Name: mooc1.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月12日 星期四 12时33分08秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{  
    char ch,ch1,ch2;
    char str[1000];
    fgets(str,1000,stdin);
    str[strlen(str)-1]='\0';
    ch = getchar();
    getchar();
    ch1 = getchar();
    getchar();
    ch2 = getchar();
    printf("%s\n",str);
    printf("%c %c %c\n",ch,ch1,ch2);
    //将值为ch1的字符换成ch2的字符
    int len = strlen(str),i;
    for(i=0;i<len;i++){
        if(str[i] == ch1){
            str[i] = ch2;
        }
    }
    len = strlen(str);
    printf("%s\n",str);
    
    //删除值为ch的字符
    int m,j=0;
    char strtmp[1000];
    for(i=0;i<len;i++)
    {
        if(str[i] != ch)
        {
            strtmp[j] = str[i];
            j++;
        } 
    }
    memset(&str,0,sizeof(str));
    memcpy(&str,&strtmp,j+1);
    printf("%s\n",str);
    return 0;
}
