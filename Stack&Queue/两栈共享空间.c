#include <stdio.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType;

typedef struct
{
	SElemType data[MAXSIZE];
	int top1;
	int top2;
 }SqDoubleStack;

Status visit(SElemType e)
{
	printf("%d ", e);
	return OK;
}

Status InitStack(SqDoubleStack* S)
{
	S->top1 = -1;
	S->top2 = MAXSIZE;
	return OK;
}

Status ClearStack(SqDoubleStack* S)
{
	S->top1 = -1;
	S->top2 = MAXSIZE;
	return OK;	
}

Status StackEmpty(SqDoubleStack S)
{
	if(S.top1 == -1 && S.top2 == MAXSIZE)
	{
		return TRUE;
	}
	return FALSE;
}

Status StackLength(SqDoubleStack S)
{
	return (S.top1 + 1) + MAXSIZE - S.top2;
}

Status Push(SqDoubleStack* S, SElemType e, int stackNumber)
{
	if (S->top1 == S->top2 - 1)
	{
		return ERROR;
	}
	if (stackNumber == 1)
	{
		S->top1 ++;
		S->data[S->top1] = e;
	}
	else if (stackNumber == 2)
	{
		S->top2 --;
		S->data[S->top2] = e;		
	}
	else return ERROR;
	return OK;
}

Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber)
{
	if (stackNumber == 1)
	{
		if (S->top1 == -1)
			return ERROR;
		*e = S->data[S->top1];
		S->top1--;
	}
	else if(stackNumber == 2)
	{
		if (S->top2 == MAXSIZE)
			return ERROR;
		*e = S->data[S->top2];
		S->top2++;		
	}
	else return ERROR;
	return OK;
}

// 遍历的时候不要修改top指针，应该给副本i。因为实际上没有出栈入栈的操作
Status StackTraverse(SqDoubleStack S)
{
	int i;
	i = 0;
	printf("Stack1:");
	while(i<=S.top1)
	{
		visit(S.data[i]);
		i++;
	}
	printf("\n");
	i =S.top2;
	printf("Stack2:");
	while(i<MAXSIZE)
	{
		visit(S.data[i]);
		i++;
	}
	printf("\n");
	return OK;	
}

int main()
{
	int j;
	SqDoubleStack s;
	int e;
	if(InitStack(&s)==OK)
	{
		for(j=1;j<=5;j++)
			Push(&s,j,1);
		for(j=MAXSIZE;j>=MAXSIZE-2;j--)
			Push(&s,j,2);
	}
	
	printf("栈中元素依次为：");
	StackTraverse(s);
	
	printf("当前栈中元素有：%d \n",StackLength(s));
	
	Pop(&s,&e,2);
	printf("弹出的栈顶元素 e=%d\n",e);
	printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
	
	for(j=6;j<=MAXSIZE-2;j++)
		Push(&s,j,1);
	
	printf("栈中元素依次为：");
	StackTraverse(s);
	
	printf("栈满否：%d(1:否 0:满)\n",Push(&s,100,1));
	
	
	ClearStack(&s);
	printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
	
	return 0;
}
