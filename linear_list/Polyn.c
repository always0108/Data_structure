/*************************************************************************
	> File Name: Polyn.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年09月18日 星期一 21时36分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


/*最后写的乘法，main中是乘法的测试*/
typedef struct Polynomial{
	float coef; 
	int expn;   
	struct Polynomial *next;
}Polynomial,*Polyn;

//创建带头节点的单链表来存取多项式
Polyn CreatePoly(){
	Polynomial *head,*rear,*s;
	int c , e  , num;
	head = (Polynomial *)malloc(sizeof(Polynomial));
	rear = head;
	scanf("%d",&num); 
	getchar();
	while(num--){
		scanf("(%d,%d)",&c,&e);
		s = (Polynomial *)malloc(sizeof(Polynomial));
		s->coef = c;
		s->expn = e;
		rear->next = s;
		rear = s;
	}
	rear->next = NULL;
	return head;	
}

//打印多项式
void PrintPolyn(Polyn P)
{
	Polyn q = P->next;
	int flag = 1;
	if(!q){
		putchar('0');
		printf("\n");
		return ;
	}
	while(q){
		if(q->coef>0&&flag!=1)	putchar('+');
		if(q->coef != 1&& q->coef != -1){
			printf("%g",q->coef);
			if(q->expn == 1)	putchar('X');
			else if(q->expn)	printf("X^%d",q->expn);
		}
		else{
			if(q->coef == 1)
			{
				if(!q->expn) putchar('1');
				else if(q->expn == 1)	putchar('X');
				else printf("X^%d",q->expn);
			}
			if(q->coef == -1)
			{
				if(!q->expn) printf("-1");
				else if(q->expn == 1)	printf("-X");
				else printf("-X^%d",q->expn);
			}
		}
		q = q->next;
		flag++;
	}
	printf("\n");
}


//相加
Polyn AddPolyn(Polyn pa ,Polyn pb)
{
	Polyn qa = pa->next;
	Polyn qb = pb->next;
	Polyn headc,pc,qc;
	pc = (Polynomial *)malloc(sizeof(Polynomial));
	pc->next = NULL;
	headc = pc;
	while(qa != NULL && qb !=NULL){
		qc = (Polynomial *)malloc(sizeof(Polynomial));
		if(qa->expn < qb->expn)
		{
			qc->coef = qa->coef;
			qc->expn = qa->expn;
			qa = qa->next;
		}else if(qa->expn == qb->expn)
		{
			qc->coef = qa->coef + qb->coef;
			qc->expn = qa->expn;
			qa = qa->next;
			qb = qb->next;
		}else{
			qc->coef = qb->coef;
			qc->expn = qb->expn;
			qb = qb->next;
		}
		if(qc->coef != 0)
		{
			qc->next = pc->next;
			pc->next =qc;
			pc = qc;
		}else
			free(qc);
	}
	while(qa != NULL)
	{
		qc = (Polynomial *)malloc(sizeof(Polynomial));
		qc->coef = qa->coef;
		qc->expn = qa->expn;
		qa = qa->next;
		qc->next = pc->next;
		pc->next =qc;
		pc = qc;
	}
	while(qb != NULL)
	{
		qc = (Polynomial *)malloc(sizeof(Polynomial));
		qc->coef = qb->coef;
		qc->expn = qb->expn;
		qb = qb->next;
		qc->next = pc->next;
		pc->next =qc;
		pc = qc;
	}
	return headc;
}

//相减
Polyn Subtract(Polyn pa ,Polyn pb)
{
	Polyn h = pb;
	Polyn p = pb->next;
	Polyn pd;
	while(p){
		p->coef=p->coef*(-1);
		p = p->next;
	}
	pd = AddPolyn(pa,h);
	for(p=h->next;p;p=p->next)
		p->coef=p->coef*(-1);
	return pd;
}


//求值
double getvalue(Polyn p,int x)
{
	double result = 0;
	Polyn q = p->next;
	while(q != NULL)
	{
		result=result + (q->coef)*pow(x,q->expn);
		q = q->next;
	} 
	return result;
}

//求导数
Polyn Differentiate(Polyn p)
{
    Polyn q = p->next;
    Polyn pc,qc,headc;
	pc = (Polynomial *)malloc(sizeof(Polynomial));
	pc->next = NULL;
    headc = pc;
    while(q != NULL )
    {
        
		qc = (Polynomial *)malloc(sizeof(Polynomial));
        
        if(q->expn != 0)
        {
            qc->coef = q->coef*q->expn;
            qc->expn = q->expn-1;
		    qc->next = pc->next;
		    pc->next =qc;
		    pc = qc;
        }else{
            free(qc);
        }   
        q = q->next; 
    }
    return headc;
    
}

//相乘
Polyn multiplication(Polyn a,Polyn b)
{
    Polyn pa = a->next;
    Polyn result;
	result = (Polynomial *)malloc(sizeof(Polynomial));
    result->next = NULL;
    //a中的每一项都与b相乘再求和
    while(pa != NULL){    
	    Polyn pb = b->next;
        Polyn pc,qc,headc;
	    pc = (Polynomial *)malloc(sizeof(Polynomial));
	    pc->next = NULL;
        headc = pc;
        while(pb != NULL){
            qc = (Polynomial *)malloc(sizeof(Polynomial));
            qc->coef = (pa->coef)*(pb->coef);
            qc->expn =  pa->expn + pb->expn;
    
			qc->next = pc->next;
			pc->next = qc;
			pc = qc;
            
            pb=pb->next;
        }
        pa = pa->next;
        result = AddPolyn(result,headc);
    }
    return result;
}


int main(void)
{
	Polyn a = CreatePoly();
    Polyn b = CreatePoly();

    Polyn result = multiplication(a,b);

    PrintPolyn(result);
	return 0;
}
