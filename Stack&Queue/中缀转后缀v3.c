// 此版本支持多位正数 和 +-*/()
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
	if (S->top >= 0)
	{
		S->top--;
	}
}

char Top(Stack S)
{
	return S.data[S.top];
}

int Prior(char e)
{
	if (e == '+' || e == '-') return 1;
	if (e == '*' || e == '/') return 2;
	return -1;
}

void inToPost(char* p, char* ret)
{
	char c;
	int num = 0;
	char buf[20];
	Stack S;
	S.top = -1;
	ret[0] = 0;

	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			num = num * 10 + (*p - '0');
		}
		else
		{
			if (num > 0)
			{
				sprintf(buf, "%d", num);
				strcat(ret, buf);
				num = 0;
			}

			if (*p == '(')
			{
				Push(&S, *p);
			}
			else if (*p == ')')
			{
				while (Top(S) != '(')
				{
					c = Top(S);
					char temp[2] = {c, 0}; // sprintf()的安全替代
					strcat(ret, temp);
					Pop(&S);
				}
				Pop(&S);
			}
			else if (*p == '+' || *p == '-' || *p == '*' || '/')
			{
				while (S.top != -1 && Top(S) != '(' && Prior(Top(S)) >= Prior(*p))
				{
					c = Top(S);
					char temp[2] = {c, 0};
					strcat(ret, temp);
					Pop(&S);
				}
				Push(&S, *p);
			}
		}
		p++;
	}

	if (num > 0)
	{
		sprintf(buf, "%d", num);
		strcat(ret, buf);
	}

	while (S.top >= 0)
	{
		c = Top(S);
		char temp[2] = {c, 0};
		strcat(ret, temp);
		Pop(&S);
	}
}

int main()
{
	char ret[1000];
	ret[0] = '\0';
	char str[1000] = "1+2*3-(4+5)";
	inToPost(str, ret);
	printf("%s", ret);
}