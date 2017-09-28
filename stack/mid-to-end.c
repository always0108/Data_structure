/*************************************************************************
	> File Name: mid-to-end.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月28日 星期四 22时14分30秒
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#define ElementType char 
 

typedef struct Node *PtrToNode; 
typedef PtrToNode Stack; 


typedef struct Node{
    char Element;
    struct Node *Next;
}Node;

 
int IsEmpty(Stack S); 
Stack CreateStack(); 
void DisposeStack(Stack S); 
void MakeEmpty(Stack S); 
void Push(ElementType X,Stack S); 
ElementType Top(Stack S); 
void Pop(Stack S); 
 
//判断栈是否为空 
int IsEmpty(Stack S) 
{ 
    return S->Next == NULL; 
} 
//创建链栈 
Stack CreateStack() 
{ 
    Stack S = malloc(sizeof(struct Node)); 
    if(S == NULL) 
    { 
        printf("No enough memory!"); 
        return NULL; 
    } 
    S->Next = NULL; 
    MakeEmpty(S); 
    return S; 
} 
//清空栈 
void MakeEmpty(Stack S) 
{ 
    if(S == NULL) 
    { 
        printf("Use CreateStack First!"); 
    } 
    else 
    { 
        while(!IsEmpty(S)) 
        { 
            Pop(S); 
        } 
    } 
} 
//进栈 
void Push(ElementType X,Stack S) 
{ 
    PtrToNode Tmp; 
    Tmp = malloc(sizeof(struct Node)); 
    if(Tmp != NULL) 
    { 
        Tmp->Element = X; 
        Tmp->Next = S->Next; 
        S->Next = Tmp; 
    } 
    else 
    { 
        printf("Out of space!"); 
    } 
} 
//出栈 
void Pop(Stack S) 
{ 
     
    if(IsEmpty(S)) 
    { 
        printf("The Stack is Empty!"); 
    } 
    else 
    { 
        PtrToNode Tmp = S->Next; 
        S->Next = Tmp->Next; 
        free(Tmp); 
    } 
} 
//返回栈顶元素 
ElementType Top(Stack S) 
{ 
    if(IsEmpty(S)) 
    { 
        printf("The stack is empty!"); 
        return 0; 
    } 
    else 
    { 
        return S->Next->Element; 
    } 
} 
 
/***************************************************************** 
*根据字符该字符是否在栈中，返回该字符的优先级。 
*这里只处理+、-、*、/、(、)这些符号。 
*需要注意的是：如果(在栈中，它的优先级是最低的，不在栈中则是最高的 
*@param c:需要判断的字符 
*@param flag:字符是否在栈中，0表示在栈中，1表示不在栈中 
*****************************************************************/ 
int GetPrecedence(char c,int flag) 
{ 
    if(c=='+' || c=='-') 
    { 
        return 1; 
    } 
    else if(c=='*' || c=='/') 
    { 
        return 2; 
    } 
    else if(c=='(' && flag==0) 
    { 
        return 0; 
    } 
    else if(c=='(' && flag==1) 
    { 
        return 3; 
    } 
    else 
    { 
        fprintf(stderr,"Input char is invalid!\n"); 
        return -1; 
    } 
} 
 
/**************************************************************** 
*判断一个字符是不是运算符 
*如果是合法的运算符+、-、*、/、(、)则返回0，否则返回1 
****************************************************************/ 
int IsOperator(char c) 
{ 
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')') 
    { 
        return 0; 
    } 
    else 
    { 
        return 1; 
    } 
} 
 
char Output[50]; 
//中缀表达式转成后缀表达式 
char* InfixToPostfix(char *ch,Stack S) 
{ 
     
    int index=0; 
    char c; 
    while((c=*ch) != '\0') 
    { 
        //不是运算符，将该字符放进输出字符数组中。 
        if(IsOperator(c)==1) 
        { 
            Output[index++] = c; 
            ch++; 
        } 
        //是运算符 
        else 
        { 
            //如果此时栈为空，运算符进栈 
            if(IsEmpty(S)) 
            { 
                Push(c,S); 
                ch++; 
                continue; 
            } 
            else 
            { 
                if(c==')')   
                { 
                    while(!IsEmpty(S) && Top(S) != '(') 
                    { 
                        Output[index++] = Top(S); 
                        Pop(S); 
                    } 
                    Pop(S); 
                    ch++; 
                    continue; 
                } 
                else 
                { 
                    int outPrecedence = GetPrecedence(c,1); 
                    while(!IsEmpty(S) && GetPrecedence(Top(S),0) >= outPrecedence) 
                    { 
                        Output[index++] = Top(S); 
                        Pop(S); 
                    } 
                    Push(c,S); 
                    ch++; 
                    continue; 
                } 
            } 
        } 
    } 
    while(!IsEmpty(S)) 
    { 
        Output[index++] = Top(S); 
        Pop(S); 
    } 
    Output[index] = '\0'; 
    return Output; 
} 
 
 
 
int main(void) 
{ 
    Stack S = CreateStack(); 
    char str[10001];
    memset(&str,0,sizeof(str));
    gets(str);
    char *charSequence = str; 
    char tmp; 
    char *out = InfixToPostfix(charSequence,S); 
     
     
    while((tmp=*out)!='\0') 
    { 
        printf("%c",tmp); 
        out++; 
    } 
    printf("\n"); 
    return 0; 
} 
