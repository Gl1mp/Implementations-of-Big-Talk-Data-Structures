#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int ElemtType;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

// 标准教材堆分配串：完全依靠length管理，不依赖\0
typedef struct
{
	char* ch;
	int length;
}HString;

// 初始化空串：ch=NULL length=0
void InitString(HString* S)
{
	S->length = 0;
	S->ch = NULL;
}

// 字符串赋值（纯DS标准，无\0）
Status StrAssign(HString* S, char* chars)
{
	if (chars == NULL)
		return ERROR;
	int len = strlen(chars);

	// 安全释放旧空间
	if (S->ch != NULL)
	{
		free(S->ch);
		S->ch = NULL;
	}

	if (len == 0)
	{
		S->ch = NULL;
		S->length = 0;
		return OK;
	}

	// 严格按需分配，无多余+1、无\0
	S->ch = (char*)malloc(len * sizeof(char));
	if (S->ch == NULL)
		return ERROR;

	for (int i = 0; i < len; i++)
		S->ch[i] = chars[i];
	S->length = len;
	return OK;
}

// 串复制
Status StrCopy(HString* S, HString T)
{
	// 安全释放旧空间
	if (S->ch != NULL)
	{
		free(S->ch);
		S->ch = NULL;
	}

	if (T.ch == NULL && T.length == 0)
	{
		S->ch = NULL;
		S->length = 0;
		return OK;
	}

	S->ch = (char*)malloc(T.length * sizeof(char));
	if (S->ch == NULL)
		return ERROR;

	for (int i = 0; i < T.length; i++)
	{
		S->ch[i] = T.ch[i];
	}
	S->length = T.length;
	return OK;
}

// 自定义打印（适配无\0串，依靠length遍历，纯DS规范）
void StrPrint(HString T)
{
	if (T.length == 0 || T.ch == NULL)
	{
		printf("(空串)\n");
		return;
	}
	for (int i = 0; i < T.length; i++)
	{
		putchar(T.ch[i]);
	}
	putchar('\n');
}

// 清空串
Status ClearString(HString* S)
{
	if (S == NULL)
		return ERROR;
	
	if (S->ch != NULL)
	{
		free(S->ch);
		S->ch = NULL;
	}
	S->length = 0;
	return OK;
}

// 串比较
int StrCompare(HString S, HString T)
{
	int i = 0;
	int minLen = S.length < T.length ? S.length : T.length;
	while (i < minLen && S.ch[i] == T.ch[i])
		i++;
	if (i >= minLen)
		return S.length - T.length;
	return S.ch[i] - T.ch[i];
}

// 串拼接（纯DS标准，无\0、无多余内存）
Status Concat(HString* T, HString S1, HString S2)
{
	int i;
	if (T == NULL)
		return ERROR;

	// 安全释放旧空间
	if (T->ch != NULL)
	{
		free(T->ch);
		T->ch = NULL;
	}

	if (S1.length == 0 && S2.length == 0)
	{
		T->length = 0;
		T->ch = NULL;
		return OK;
	}

	int totalLen = S1.length + S2.length;
	T->ch = (char*)malloc(totalLen * sizeof(char));
	if (T->ch == NULL)
		return ERROR;

	for (i = 0; i < S1.length; i++)
		T->ch[i] = S1.ch[i];
	for (; i < totalLen; i++)
		T->ch[i] = S2.ch[i - S1.length];

	T->length = totalLen;
	return OK;
}

// 串删除（纯教材标准，newbase统一、安全释放）
Status StrDelete(HString* S, int pos, int len)
{
	int i;
	if (S == NULL)
		return ERROR;
	if (pos < 1 || pos > S->length)
		return ERROR;
	if (len < 0 || pos + len - 1 > S->length)
		return ERROR;
	if (len == 0)
		return OK;

	int newLen = S->length - len;

	// 删除后为空串，安全释放
	if (newLen == 0)
	{
		if (S->ch != NULL)
		{
			free(S->ch);
			S->ch = NULL;
		}
		S->length = 0;
		return OK;
	}

	char* newbase = (char*)malloc(newLen * sizeof(char));
	if (newbase == NULL)
		return ERROR;

	// 前段保留
	for (i = 0; i < pos - 1; i++)
		newbase[i] = S->ch[i];
	// 后段前移
	for (int j = pos + len - 1; j < S->length; j++, i++)
		newbase[i] = S->ch[j];

	// 安全释放旧内存
	if (S->ch != NULL)
	{
		free(S->ch);
		S->ch = NULL;
	}

	S->ch = newbase;
	S->length = newLen;
	return OK;
}

// 朴素模式匹配
int IndexBP(HString S, HString T, int pos)
{
	int i = pos - 1;
	int j = 0;
	while (i < S.length && j < T.length)
	{
		if (S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= T.length)
	{
		return i - T.length + 1;
	}
	return 0;
}

// 串插入（纯教材标准版，无\0，无冗余内存）
Status StrInsert(HString* S, int pos, HString T)
{
	int i;
	if (S == NULL)
		return ERROR;
	if (pos < 1 || pos > S->length + 1)
		return ERROR;
	if (T.ch == NULL || T.length == 0)
		return ERROR;

	int newLen = S->length + T.length;
	char* newbase = (char*)malloc(newLen * sizeof(char));
	if (newbase == NULL)
		return ERROR;

	// 三段拷贝，纯标准逻辑
	for (i = 0; i < pos - 1; i++)
		newbase[i] = S->ch[i];
	for (; i < pos - 1 + T.length; i++)
		newbase[i] = T.ch[i - (pos - 1)];
	for (; i < newLen; i++)
		newbase[i] = S->ch[i - T.length];

	// 安全释放旧空间
	if (S->ch != NULL)
	{
		free(S->ch);
		S->ch = NULL;
	}

	S->ch = newbase;
	S->length = newLen;
	return OK;
}

int main()
{
	HString S, T;
	
	InitString(&S);
	InitString(&T);
	
	// 赋值测试
	StrAssign(&S, "Hello");
	printf("S = "); StrPrint(S);
	
	// 复制测试
	StrCopy(&T, S);
	printf("T = "); StrPrint(T);
	
	// 空串测试
	StrAssign(&S, "");
	printf("S = "); StrPrint(S);
	
	StrCopy(&T, S);
	printf("T = "); StrPrint(T);
	
	// 安全释放
	ClearString(&S);
	ClearString(&T);
	
	return 0;
}
