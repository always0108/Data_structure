/*************************************************************************
	> File Name: HuffmanTree2.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月20日 星期一 15时53分58秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define N 30
#define M 2*N-1
typedef struct{
    int weight;
    int parent,Lchild,Rchild;
}HTNode,HuffmanTree[M+1];

typedef char** huffmanCode;
void Select(HuffmanTree ht,int j,int *s1,int *s2)
{
    int i; 
    //int占4个字节
    int min = 2147483647;
    for(i=1;i<=j;i++){
        if((ht[i].parent == 0) && ht[i].weight < min){
            min = ht[i].weight;
            *s1 = i;
        }

    }
    int lessmin = 2147483647;
    for(i=1;i<=j;i++){
        if((ht[i].parent == 0) && ht[i].weight < lessmin && i != *s1){
            lessmin = ht[i].weight;
            *s2 = i;
        }
    }
}

void Print_huffmanTree(HuffmanTree ht , int n)
{
    int i,m;
    m = 2*n-1;
    printf("%8s%8s%8s%8s%8s\n","Index","Weight","Parent","Lchild","Rchild");
    for(i = 1;i <= m; i++){
        printf("%8d%8d%8d%8d%8d\n",i,ht[i].weight,ht[i].parent,ht[i].Lchild,ht[i].Rchild);
    }
}

//建立哈夫曼树
void CrtHuffmanTree(HuffmanTree ht, int w[], int n)
{

    int m,i;
    m = 2*n-1;
    for(i=1;i<=n;i++){ 
        ht[i].weight = w[i];//初始化前n个元素成为根结点
        ht[i].parent = 0;
        ht[i].Lchild = 0;
        ht[i].Rchild = 0;
    }
    for(i=n+1;i<=m;i++){
        //初始化后n-1个元素
        ht[i].weight = 0;
        ht[i].parent = 0;
        ht[i].Lchild = 0;
        ht[i].Rchild = 0;
    }
    for(i=n+1;i<=m;i++)   //从第n+1个元素开始构造新结点
    {
        int s1,s2;
        //在ht的前i-1项中选择双亲为0且全值较小的两结点s1,s2
        Select(ht,i-1,&s1,&s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;//建立新结点，赋权值
        ht[i].Lchild = s1;
        ht[i].Rchild = s2; //赋新结点左右孩子的指针
        ht[s1].parent = i;
        ht[s2].parent = i;//改s1,s2的双亲指针
    }
}

void CrtHuffmanCode1(HuffmanTree ht,huffmanCode hc,int n)
{
    char *cd;
    int start,i,c,p;
    cd = (char * )malloc(n*sizeof(char ));
    cd[n-1] = '\0';
    for(i=1;i<=n;i++)
    {
        start = n-1;
        c = i;
        p = ht[i].parent;
        while(p!=0){
            --start;
            if(ht[p].Lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = p;
            p = ht[p].parent;
        }
        hc[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy(hc[i],&cd[start]);
    }
}

int find_code(huffmanCode hc,int n,char *dest,int *result)
{
    int i ;
    for(i=1;i<=n;i++){
        if(strcmp(dest,hc[i])==0){
            *result = i;
            return 1;
        }
    }
    return 0;
}


int main(void)
{
    HuffmanTree ht;
    huffmanCode hc;
    int n,i;
    int w[100];
    int chlist[100];
    
    int cal[128] = {0};
    char str[10001];
    char code[10001];
    char tmp;
    while((tmp=getchar())!='#')
    {
        str[i] = tmp;
        i++;
    }
    str[i] = '\0';

    getchar();
    gets(code);

    for(i=0;i<strlen(str);i++)
        cal[str[i]]++;
    
    int j = 1;
    for(i=32;i<=122;i++){
        if(cal[i]>0){
            w[j] = cal[i];
            chlist[j] = i;
            j++;
        }
    }

    n=j-1; 
    CrtHuffmanTree(ht,w,n);
    
    hc = malloc(sizeof(char)*(n+1)*(n+1));
    CrtHuffmanCode1(ht,hc,n);
 
    //编码
    long long codelength = 0;
    for(i=0;i<strlen(str);i++){
        for(int x=1;x<=n;x++){
            if(str[i]== chlist[x]){
                printf("%s",hc[x]);
                codelength +=strlen(hc[x]); 
                break;
            }
        }
    }
    printf("\n");

    //译码 
    char temp[100];
    int result;
    int k = 0;
    for(i=0;i<strlen(code);i++){
        temp[k] = code[i];
        if(find_code(hc,n,temp,&result)){
            putchar(chlist[result]);
            k = 0;
            memset(&temp,0,sizeof(temp));
        }
        else{
            k++;
        }
    }
    printf("\n");

    printf("%0.2f\n",(codelength*1.0)/strlen(str));
    return 0;
}

