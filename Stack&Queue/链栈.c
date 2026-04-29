#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 666
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType;

typedef struct StackNode {
	SElemType data;
	struct StackNode *next;
} StackNode;

typedef struct {
	StackNode *top;     // 栈顶指针（空栈时为 NULL）
	int count;          // 栈中元素个数
} LinkStack;

Status visit(SElemType c)
{
	printf("%d ", c);
	return OK;
}

Status InitStack(LinkStack *S)
{
	S->top = NULL;
	S->count = 0;
	return OK;
}

Status ClearStack(LinkStack* S)
{
	StackNode *p, *q;
	p = S->top;
	while(p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	
	S->top = NULL;
	S->count = 0;
	return OK;
}

Status StackEmpty(LinkStack S)
{
	return S.count == 0 ? TRUE : FALSE;
}

int StackLength(LinkStack S)
{
	return S.count;
}

Status GetTop(LinkStack S, SElemType *e)
{
	if(S.top == NULL)
		return ERROR;
	*e = S.top->data;
	return OK;
}

Status Push(LinkStack* S, SElemType e)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	if (p == NULL)
		return ERROR;
	p->next = S->top;
	p->data = e;
	S->top = p;
	S->count++;
	return OK;
}

Status Pop(LinkStack* S, SElemType* e)
{
	if (e == NULL)
		return ERROR;
	StackNode* p = S->top;
	*e = p->data;
	S->top = p->next;
	S->count--;
	free(p);
	return OK;
}

Status StackTraverse(LinkStack S)
{
	StackNode* p = S.top;
	while(p != NULL)
	{
		visit(p->data);
		p = p->next;	
	}
	return OK;
}

int main()
{
	LinkStack s;
	int e;
	
	InitStack(&s);
	
	for (int j = 1; j <= 10; j++)
		Push(&s, j);
	
	printf("栈中元素依次为：");
	StackTraverse(s);
	
	Pop(&s, &e);
	printf("弹出的栈顶元素 e=%d\n", e);
	
	printf("栈空否：%d (1:空 0:否)\n", StackEmpty(s));
	
	GetTop(s, &e);
	printf("栈顶元素 e=%d  栈的长度为 %d\n", e, StackLength(s));
	
	ClearStack(&s);
	printf("清空栈后，栈空否：%d (1:空 0:否)\n", StackEmpty(s));
	
	return 0;
}
