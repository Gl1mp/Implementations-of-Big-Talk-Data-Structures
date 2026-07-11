// 此程序实现了中缀转后缀 只支持一位的非负数和+-()
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000

typedef struct
{
	char data[MAXSIZE];
	int top;
}Stack;

void Push(Stack* S, char e)
{
	S->data[++S->top] = e;
}

void Pop(Stack* S)
{
	if(S->top >= 0)
	{
		S->top--;
	}
}

char Top(Stack S)
{
	return S.data[S.top];
}

void inToPost(char* p, char* ret)
{
	char c;
	Stack S;
	S.top = -1;
	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			sprintf(ret + strlen(ret), "%c", *p);
		}
		else if (*p == '(')
		{
			Push(&S, *p);
		}
		else if (*p == ')')
		{
			while (Top(S) != '(')
			{
				c = Top(S);
				sprintf(ret + strlen(ret), "%c", c);
				Pop(&S);
			}
			Pop(&S);
		}
		else if (*p == '+' || *p == '-')
		{
			Push(&S, *p);
		}
		p++;
	}
	while (S.top >= 0)
	{
		c = Top(S);
		sprintf(ret + strlen(ret), "%c", c);
		Pop(&S);
	}
}
int main()
{
	char ret[1000];
	ret[0] = '\0';
	char str[1000] = "1+(2-3)+4";
	inToPost(str, ret);
	printf("%s", ret);
}