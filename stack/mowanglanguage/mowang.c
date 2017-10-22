/*************************************************************************
	> File Name: mowang.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年10月21日 星期六 21时52分31秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h> //exit
#define MAX 256

//思路：
//先将魔王语言逆序入栈，入栈同时处理大写字母，然后出栈入队列，并且在入队列的同时按规则转换形式。
//最后将队列里的英文翻译为对应汉字即可。

void pushstack(char s[], char origin[], int *top);//入栈
void intoquene(char s[], int *top,char quene[]);//入队
void begin_translate();//开始翻译
void translate(char s[]);//翻译为最终语言
void see_rule();//列出当前规则
void see_language();//列出当前最终语言的解释
int  find_rule(char ch,char s[20]);//查找规则是否已存在
int  find_endlanguage(char ch,char s[20]);//查找最终语言有无解释
void print_help();//打印帮助信息
int clear_rule();//清空规则
int add_rule();//添加规则
int delete_rule();//删除规则
int update_rule();//修改规则
void rule_UI();//管理规则界面
void Main_UI();//主界面

typedef struct Rule{
    char ch;//大写字母
    char s[20];//小写字母组成序列
}rule;

//查找规则是否已存在
int  find_rule(char ch,char s[20]){
    FILE *fp;
    fp = fopen("Rule","r");
    if(!fp){
        //printf("open file fail\n");
        return 0;
    }
    rule tmp;
    int flag = 0;
    while(fscanf(fp,"%c %s\n",&tmp.ch,tmp.s)>0)
    {
        if(ch == tmp.ch){
            strcpy(s,tmp.s);
            flag = 1;
            break;    
        }
    }
    fclose(fp);
    if(flag){
        return 1;
    }else
        return 0;

}


void find_end_rule(char s1[20],char s2[20]){
    int i,j=0;
    char s3[20];
    for(i=0;i<strlen(s1);i++){
        if(s1[i] >= 'A' && s1[i] <= 'Z' && find_rule(s1[i],s3)){
            int k = 0;
            for(k=0;k<strlen(s3);k++){
                s2[j]=s3[k];
                j++;
            }
        }else{
            s2[j] = s1[i];
            j++;
        }
    }
    s2[strlen(s2)] = '\0';
    //printf("-------%s-------\n",s2);
    char k[20];
    
    for(i=0;i<strlen(s2);i++)
    {
        if(s2[i] >= 'A' && s2[i] <= 'Z' && find_rule(s2[i],k))
        {
            find_end_rule(s2,s1);
            //printf("%s\n",s1);
            strcpy(s2,s1);
            break;
        }
    }
    
}
//查找最终语言有无解释
int  find_endlanguage(char ch,char s[20]){
    FILE *fp;
    fp = fopen("endlanguage","r");
    if(!fp){
        //printf("open file fail\n");
        return 0;
    }
    rule tmp;
    int flag = 0;
    while(fscanf(fp,"%c %s\n",&tmp.ch,tmp.s)>0)
    {
        if(ch == tmp.ch){
            strcpy(s,tmp.s);
            flag = 1;
            break;    
        }
    }
    fclose(fp);
    if(flag){
        return 1;
    }else
        return 0;

}

//压栈
void pushstack(char s[], char origin[], int *top)
{
    char k[20],tmp[20];
    int m ,i, j,t;
    t = strlen(origin);
    for(j = 0; j < t; j ++){
        //去文件中找要替换的字符，如果需要替换，就替换
        if(find_rule(origin[t - 1 - j],tmp)){
            find_end_rule(tmp,k);
            m = strlen(k);
            for(i = 0; i < m; i ++){
                if(*top > MAX - 1){
                    printf("上溢！");
                    exit(0); 
                }
                else
                    s[++(*top)] = k[m - 1 - i];
            } 
        }
    else
        s[++(*top)] = origin[t - 1 - j];
    }
    s[++(*top)] = '\0';
}   

//入队
void intoquene(char s[], int *top,char quene[])
{
    char temp;
    int front = -1, rear = -1;
    while((*top) != -1)
    {
        --(*top);
        //新建一个栈来存储括号中的字符串，方便翻译
        if(s[(*top)] == '('){
            temp = s[--(*top)];
            char s3[MAX] = {0};
            int top3 = -1;
            while(s[--(*top)] != ')'){
                s3[++ top3] = s[(*top)];
            }
            while(top3 != -1){
                quene[++ rear] = temp;
                quene[++ rear] = s3[top3 --];
            }
            quene[++ rear] = temp;          
        }
        else if(s[(*top)] == ')') ;
        else 
            quene[++ rear] = s[(*top)]; 
    }
    quene[++ rear] = '\0';
}

//翻译为最终语言
void translate(char s[])
{
    int i,t;
    char k[20];
    t = strlen(s);
    for(i = 0; i < t; i ++){
        if(find_endlanguage(s[i],k))
            printf("%s",k);
        else{
            printf("%c",s[i]);
        }
    }
}

//开始初步解释
void begin_translate(){
    char s1[MAX] = {0}, s2[MAX] = {0},quene[MAX] = {0};
    int i;
    int top1 = -1;
    printf("\t\t\t\033[1;36m请输入魔王语言：\033[0m\n\t\t\t");
    scanf("%s",s2);
    getchar();
    pushstack(s1, s2, &top1);
    intoquene(s1, &top1, quene);
    printf("\t\t\t初步解释为：\n\t\t\t");
    puts(quene);
    while(1){
        printf("\t\t\t\033[31m你想要进一步解释嘛？(Y/N)\033[0m");
        char  ch = getchar();
        getchar();
        if(ch == 'Y'||ch == 'y'){
            printf("\t\t\t人的语言为：\n\t\t\t");
            translate(quene);
            printf("\n");
            break;
        }else if(ch == 'N'|| ch == 'n'){
            break;
        }
    }
    getchar();
}

//打印帮助信息
void print_help(){
    system("clear");
    printf("\t\t\t\033[1;32m***************************************\033[0m\n");
    printf("\t\t\t\033[1;34m*********** \033[35mThe current rule \033[34m**********\033[0m\n");
    printf("\t\t\t\033[1;33m***************************************\033[0m\n\n");
    printf("Base rule:(θδ1δ2 •••δn)→θδnθδn-1 ••• θδ1θ\n");
    printf("\t\t\t\t---Can not change!!!\n");
    see_rule();
    see_language();
    getchar();
}

//列出当前最终语言的解释
void see_language(){
    rule tmp;
    FILE *fp;
    fp = fopen("endlanguage","r");
    if(!fp){
        //printf("open file fail\n");
        getchar();
        return;
    }
    printf("\033[1;35mThe endlanguage you set:\n\033[0m");
    int icount = 0;
    while(fscanf(fp,"%c %s\n",&tmp.ch,tmp.s)>0){
        printf("%c -> %-8s  ",tmp.ch,tmp.s);
        icount++;
        if((icount) %4 == 0)
            printf("\n");
    }
    fclose(fp);
}

//列出当前规则
void see_rule(){
    rule tmp;
    FILE *fp;
    fp = fopen("Rule","r");
    if(!fp){
        //printf("open file fail\n");
        getchar();
        return;
    }
    printf("\033[1;35mThe rule you set:\n\033[0m");
    while(fscanf(fp,"%c %s\n",&tmp.ch,tmp.s)>0)
        printf("%c -> %s\n",tmp.ch,tmp.s);
    fclose(fp);
}

//清空规则
int clear_rule(){
    FILE *fp;
    fp = fopen("Rule","w+");
    if(fp){
        printf("clear sucess\n");
        fclose(fp);
        getchar();
        return 1;

    }
    else{
        printf("clear fail\n");
        getchar();
        return 0;
    }
}

//添加规则
int add_rule(){
    rule tmp;
    printf("请输入要转换的字母:");
    tmp.ch = getchar();
    getchar();
    printf("请输入要转换成的结果:");
    fgets(tmp.s,20,stdin);
    tmp.s[strlen(tmp.s)-1] = '\0';
    int i,flag = 1;
    for(i=0;i<strlen(tmp.s);i++){
        if(tmp.s[i] >= 'a' &&  tmp.s[i] <= 'z'||tmp.s[i] >= 'A'&&tmp.s[i] <= 'Z')  ;
        else{ 
            flag = 0;
            break;
        }
    }
    if(tmp.ch >= 'A' && tmp.ch <= 'Z' && flag == 1){
        char k[20];
        if(find_rule(tmp.ch,k)){
            printf("规则已存在！\n添加失败！\n");
            return 0;
        }
        FILE *fp;
        fp = fopen("Rule","a+");
        if(!fp){
            printf("open file fail,add fail\n");
            getchar();
            return 0;
        }
        if(fprintf(fp,"%c %s\n",tmp.ch,tmp.s)){
            printf("Add success\n");
            fclose(fp);
        }else{
            printf("Add fail\n");
            fclose(fp);
        }
    }else{
        printf("添加的规则不符合规范！\n");
    }
    getchar();
    return 0;
}

//删除规则
int delete_rule(){
    rule tmp;
    printf("请输入要删除的字母:");
    tmp.ch = getchar();
    getchar();
    int i;
    char k[20];
    if(find_rule(tmp.ch,k)){
        FILE *fp1,*fp2;
        fp1 = fopen("Rule","r+");
        fp2 = fopen("Ruletemp","w+");    
        rule tmp1;
        if(fp1 && fp2){
            while(fscanf(fp1,"%c %s\n",&tmp1.ch,tmp1.s)>0)
            {
                if(tmp.ch == tmp1.ch)
                    continue;
                fprintf(fp2,"%c %s\n",tmp1.ch,tmp1.s); 
            }
            fclose(fp1);
            fclose(fp2);
            remove("Rule");
            rename("Ruletemp","Rule");
            printf("\t\t\t删除成功！\n");
            getchar();
            return 1;
        }else{
            printf("open file fail！\n");
        }
    }else{
        printf("要删除的规则不存在！\n");
    }
    getchar();
    return 0;
}

//修改规则
int update_rule(){
    rule tmp;
    printf("请输入要修改的字母:");
    tmp.ch = getchar();
    getchar();
    printf("请输入要转换成的结果:");
    fgets(tmp.s,20,stdin);
    tmp.s[strlen(tmp.s)-1] = '\0';
    int i,flag = 1;
    for(i=0;i<strlen(tmp.s);i++){
        if(tmp.s[i] >= 'a' &&  tmp.s[i] <= 'z'||tmp.s[i] >= 'A'&&tmp.s[i] <= 'Z')  ;
        else{ 
            flag = 0;
            break;
        }
    }
    if(tmp.ch >= 'A' && tmp.ch <= 'Z' && flag == 1){
        char k[20];
        if(find_rule(tmp.ch,k)){
            FILE *fp1,*fp2;
            fp1 = fopen("Rule","r+");
            fp2 = fopen("Ruletemp","w+");    
            rule tmp1;
            if(fp1 && fp2){
                while(fscanf(fp1,"%c %s\n",&tmp1.ch,tmp1.s)>0)
                {
                    if(tmp.ch == tmp1.ch)
                        fprintf(fp2,"%c %s\n",tmp.ch,tmp.s); 
                    else
                        fprintf(fp2,"%c %s\n",tmp1.ch,tmp1.s); 
                }
                fclose(fp1);
                fclose(fp2);
                remove("Rule");
                rename("Ruletemp","Rule");
                printf("\t\t\t修改成功！\n");
                getchar();
                return 1;
            }else{
                printf("open file fail！\n");
            }
        }else{
            printf("要修改的规则不存在！\n");
        }
    }
    getchar();
    return 0;
}

//管理规则的界面
void rule_UI(){
    char choice;
    do{
        system("clear");
        printf("\t\t\t\033[1;32m***************************************\033[0m\n");
        printf("\t\t\t\033[1;34m************ \033[35m管理规则 \033[34m***********\033[0m\n");
        printf("\t\t\t\033[1;33m***************************************\033[0m\n");
        printf("\t\t\t\t\033[1;36m-- 1.查看规则\n\n");
        printf("\t\t\t\t-- 2.添加规则\n\n");
        printf("\t\t\t\t-- 3.删除规则\n\n");
        printf("\t\t\t\t-- 4.修改规则\n\n");
        printf("\t\t\t\t-- 5.清空规则\n\n");
        printf("\t\t\t\t-- R.返回上一级菜单\n\n\033[0m");
        printf("\t\t\t\033[1;35m请输入你的选择：\033[0m");
        choice = getchar();
        getchar();
        switch(choice){
            case '1':
                system("clear");
                see_rule();
                getchar();
                break;
            case '2':
                add_rule();
                break;    
            case '3':
                delete_rule();
                break;
            case '4':
                update_rule();
                break;
            case '5':
                clear_rule();
                break;
        }
    }while(choice != 'R' && choice != 'r');
}

//主界面
void Main_UI(){
    char choice;
    do{
        system("clear");
        printf("\t\t\t\033[1;32m***************************************\033[0m\n");
        printf("\t\t\t\033[1;34m************ \033[35m魔王语言解释器 \033[34m***********\033[0m\n");
        printf("\t\t\t\033[1;33m***************************************\033[0m\n");
        printf("\n");
        printf("\t\t\t\t\033[1;36m-- 1.查看帮助\n\n");
        printf("\t\t\t\t-- 2.管理规则\n\n");
        printf("\t\t\t\t-- 3.开始解释\n\n");
        printf("\t\t\t\t-- q.退出程序\n\n\033[0m");
        printf("\t\t\t\033[1;35m请输入你的选择：\033[0m");
        choice = getchar();
        getchar();
        switch(choice){
            case '1':
                print_help();
                break;
            case '2':
                rule_UI();
                break;
            case '3':
                begin_translate();
                break;
        }
    }while(choice != 'q' && choice != 'Q');
}

//主函数
int main()
{
    Main_UI();
    printf("\n\n\t\t\tBye , Bye !\n");
    return 0;   
}
