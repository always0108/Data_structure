/*************************************************************************
	> File Name: lowestCommonAncestor.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年11月07日 星期二 14时40分38秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct Node{
    char data;
    struct Node * Lchild;
    struct Node * Rchild;
}BiTNode, * BiTree;

void Create(BiTree *root)
{
    char ch;
    ch = getchar();
    if(ch == '#') *root = NULL;
    else{
        *root = (BiTree)malloc(sizeof(BiTNode));
        (*root)->data = ch;
        Create(&((*root)->Lchild));
        Create(&((*root)->Rchild));
    }
}

BiTNode *lowestCommonAncestor(BiTNode *pRoot, BiTNode  *pNode1, BiTNode  *pNode2){
    //是空树，不用查找了，也就找不到对应节点，则返回NULL
    if( pRoot == NULL ) 
        return  NULL;

    //说明在当前子树的根节点上找到两个节点之一
    if( pRoot == pNode1 || pRoot == pNode2 )
        return pRoot;

    //左子树中的查找两个节点并返回查找结果
    BiTNode   *pLeft = lowestCommonAncestor( pRoot->Lchild, pNode1, pNode2);  
    //右子树中查找两个节点并返回查找结果
    BiTNode   *pRight = lowestCommonAncestor( pRoot->Rchild, pNode1, pNode2);

    //如果在左子树中没有找到，则断定两个节点都在右子树中，可以返回右子树中查询结果；
    //否则，需要结合左右子树查询结果共同断定
    if( pLeft == NULL )
        return pRight;
    
    //如果在右子树中没有找到，则断定两个节点都在左子树中，可以返回左子树中查询结果；
    //否则，需要结合左右子树查询结果共同断定
    if ( pRight == NULL )
        return pLeft;

    //如果在左右子树中都找两个节点之一，则pRoot就是最低公共祖先节点，返回即可。
    return pRoot;
}

BiTNode *find_BiTnode(BiTree root,char x)
{
    if(root){
        if(root->data == x)
            return root;
        BiTree Lchild = find_BiTnode(root->Lchild,x);
        BiTree Rchild = find_BiTnode(root->Rchild,x);
        if(Lchild!=NULL)
            return Lchild;
        if(Rchild!=NULL)
            return Rchild;
    }else{
        return NULL;//出口
    }
}

int main(void)
{
    BiTree root;
    Create(&root);
    getchar();
    char a,b;
    scanf("%c %c",&a,&b);
    BiTree nodeA = find_BiTnode(root,a);
    BiTree nodeB = find_BiTnode(root,b);
    BiTree result = lowestCommonAncestor(root,nodeA,nodeB);
    printf("%c\n",result->data);
    return 0;
}
