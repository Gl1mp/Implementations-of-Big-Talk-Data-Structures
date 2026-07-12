#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int ElemtType;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct
{
	char* ch;
	int length;
}HString;

void InitString(HString* S)
{
	//在此处我们选择将：长度为0、ch为NULL定为空的标准
	S->length = 0;
	S->ch = NULL;
}

Status StrAssign(HString* S, char* chars)
{
	if (chars == NULL)
		return ERROR;
	int len = strlen(chars);
	if (S->ch != NULL)
		free(S->ch);
	if (len == 0)
	{
		S->ch = NULL;
		S->length = 0;
		return OK;
	}
	S->ch = (char*)malloc((len + 1) * sizeof(char)); //这里加1是为了给'\0'留位置，因为底层要经常和字符串打交道，这样会方便一些
	for (int i = 0; i < len; i++)
		S->ch[i] = chars[i];
	S->ch[len] = '\0';
	S->length = len;
	return OK;
}

Status StrCopy(HString* S, HString T)
{
	if (S->ch != NULL)
	{
		free(S->ch);
	}
	if (T.ch == NULL && T.length == 0)
	{
		S->ch = NULL;
		S->length = 0;
		return OK;
	}
	S->ch = (char*)malloc(sizeof(char) * (1 + T.length));
	if (S->ch == NULL) return ERROR;
	// memcpy(S->ch, T.ch, T.length + 1);
	for (int i = 0; i <= T.length; i++)
	{
		S->ch[i] = T.ch[i];
	}
	S->length = T.length;
	return OK;
}

void StrPrint(HString T)
{
	if (T.length == 0 || T.ch == NULL)
	{
		printf("(空串)\n");
		return;
	}
	printf("%s\n", T.ch);
}

int main()
{
	HString S, T;
	
	InitString(&S);
	InitString(&T);
	
	// 赋值
	StrAssign(&S, "Hello");
	printf("S = "); StrPrint(S);
	
	// 复制
	StrCopy(&T, S);
	printf("T = "); StrPrint(T);
	
	// 测试空串
	StrAssign(&S, "");
	printf("S = "); StrPrint(S);
	
	StrCopy(&T, S);
	printf("T = "); StrPrint(T);
	
	// 释放内存
	free(S.ch);
	free(T.ch);
	
	return 0;
}
