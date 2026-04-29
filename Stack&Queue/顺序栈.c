#include <stdio.h>

#define MAXSIZE 666
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType;

typedef struct
{
	SElemType data[MAXSIZE];
	int top;
} SqStack;

Status Push(SqStack* S, SElemType e)
{
	if (S->top == MAXSIZE - 1)
	{
		return ERROR;
	}
	S->top++;
	S->data[S->top] = e;
	return OK;
}

Status Pop(SqStack* S, SElemType* e)
{
	if (S->top == -1)
	{
		return ERROR;
	}
	*e = S->data[S->top];
	S->top--;
	return OK;
}

Status visit(SElemType e)
{
	printf("%d ", e);
	return OK;
}

Status ClearStack(SqStack* S)
{
	S->top = -1;
	return OK;
}

Status StackEmtpy(SqStack S)
{
	if (S.top == -1)
	{
		return TRUE;
	}
	return FALSE;
}

Status GetTop(SqStack S,SElemType *e)
{
	if (S.top == -1)
		return ERROR;
	*e = S.data[S.top];
	return OK;
}

int StackLength(SqStack S)
{
	return S.top + 1;
}

Status InitStack(SqStack* S)
{
	S->top = -1;
	return OK;
}

Status StackTraverse(SqStack S)
{
	int i;
	i=0;
	while(i<=S.top)
	{
		visit(S.data[i]);
		i++;
	}
	printf("\n");
	return OK;
}
