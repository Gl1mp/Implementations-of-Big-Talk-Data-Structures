#include "stdio.h"
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType;

/* ==================== 链栈结构（现代清晰写法） ==================== */
typedef struct StackNode {
	SElemType data;
	struct StackNode *next;
} StackNode;

typedef struct {
	StackNode *top;     // 栈顶指针（空栈时为 NULL）
	int count;          // 栈中元素个数
} LinkStack;


/* 访问元素 */
Status visit(SElemType c)
{
	printf("%d ", c);
	return OK;
}

/* 构造一个空栈 S */
Status InitStack(LinkStack *S)
{
	S->top = NULL;
	S->count = 0;
	return OK;
}

/* 清空栈（释放所有节点） */
Status ClearStack(LinkStack *S)
{
	StackNode *p, *q;
	p = S->top;
	
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	
	S->top = NULL;
	S->count = 0;
	return OK;
}

/* 判断栈是否为空 */
Status StackEmpty(LinkStack S)
{
	return (S.count == 0) ? TRUE : FALSE;
}

/* 返回栈的长度 */
int StackLength(LinkStack S)
{
	return S.count;
}

/* 获取栈顶元素 */
Status GetTop(LinkStack S, SElemType *e)
{
	if (S.top == NULL)
		return ERROR;
	
	*e = S.top->data;
	return OK;
}

/* 入栈 */
Status Push(LinkStack *S, SElemType e)
{
	StackNode *s = (StackNode *)malloc(sizeof(StackNode));
	if (s == NULL)
		return ERROR;               // 内存分配失败
	
	s->data = e;
	s->next = S->top;
	S->top = s;
	S->count++;
	return OK;
}

/* 出栈 */
Status Pop(LinkStack *S, SElemType *e)
{
	if (S->top == NULL)             // 也可以用 StackEmpty(*S)
		return ERROR;
	
	StackNode *p = S->top;
	*e = p->data;
	S->top = p->next;
	free(p);
	S->count--;
	return OK;
}

/* 遍历栈（从栈顶到栈底） */
Status StackTraverse(LinkStack S)
{
	StackNode *p = S.top;
	while (p != NULL)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

/* 主函数测试 */
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
