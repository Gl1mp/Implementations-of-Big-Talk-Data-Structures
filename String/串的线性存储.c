#include <stdio.h>
#include <string.h>
#define MAXSIZE 100

typedef char String[MAXSIZE+1];
typedef int Status;
typedef int ElemtType;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* 生成一个其值等于chars的串T */
Status StrAssign(String T, char* chars)
{
	if (chars == NULL)
		return ERROR;
	int len = strlen(chars);
	if (len > MAXSIZE)
		return ERROR;
	T[0] = len;
	for (int i = 0; i < T[0]; i++)
	{
		T[i+1] = *(chars + i);
	}
	return OK;
}

/* 由串S复制得串T */
Status StrCopy(String T, String S)
{
	if (T == S)
		return OK;
	for (int i = 0; i <= S[0]; i++)
	{
		T[i] = S[i];
	}
	return OK;
}

/* 若S为空串,则返回TRUE,否则返回FALSE */
Status StrEmpty(String S)
{
	if(S[0] == 0)
		return TRUE;
	return FALSE;
}

/*  初始条件: 串S和T存在 */
/*  操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
Status StrCompare(String S, String T)
{
	for (int i = 1; i <= S[0] && i<= T[0]; i++)
	{
		if (S[i] != T[i])
			return S[i] - T[i];
	}
	return S[0] - T[0];
}

/* 返回串的元素个数 */
int StrLength(String S)
{
	return S[0];
}

/* 初始条件:串S存在。操作结果:将S清为空串 */
Status ClearString(String S)
{
	S[0] = 0;
	return OK;
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
Status Concat(String T,String S1,String S2)
{
	int i;
	for(i = 1; i <= S1[0]; i++)
	{
		T[i] = S1[i];
	}
	for(; i <= MAXSIZE && i <= (S1[0] + S2[0]); i++)
	{
		T[i] = S2[i - S1[0]];
	}
	if (S1[0] + S2[0] > MAXSIZE)
	{
		T[0] = MAXSIZE;
		return FALSE;
	}
	T[0] = S1[0] + S2[0];
	return TRUE;
}

/* 用Sub返回串S的第pos个字符起长度为len的子串。 */
Status SubString(String Sub,String S,int pos,int len)
{
	if (pos <= 0 || pos > S[0] || len < 0 || S[0] - pos + 1 < len)
		return ERROR;
	Sub[0] = len;
	for (int i = pos; i < pos + len; i++)
	{
		Sub[i - pos + 1] = S[i];
	}
	return OK;
}

/* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */
// BF算法，Brute-Force（朴素匹配算法）
int Index(String S, String T, int pos)
{
	if (S[0] - pos + 1 < T[0])
		return 0;
	int flag = 0;
	for (int i = pos; i <= S[0] - T[0] + 1; i++)
	{
		if (S[i] == T[1])
		{
			flag = 1;
			for (int j = 2; j <= T[0]; j++)
			{
				if (S[i + j - 1] != T[j])
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				return i;
			}
		}
	}
	return 0;
}

/*  T为非空串。若主串S中第pos个字符之后存在与T相等的子串， */
/*  则返回第一个这样的子串在S中的位置，否则返回0 */
int Index2(String S, String T, int pos) 
{
	String Sub;
	if (pos > 0)
	{
		for (int i = pos; i <= S[0] - T[0] + 1; i++)
		{
			SubString(Sub, S, i, T[0]);
			if(StrCompare(Sub, T) == 0)
				return i;
		}
	}
	return 0;
}


/*  初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
/*  操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */

Status StrInsert(String S,int pos,String T)
{
	int i;
	if (T[0] == 0) return OK;
	if (pos < 1 || pos > S[0] + 1)
		return ERROR;
	if (S[0] + T[0] <= MAXSIZE)
	{
		for (i = S[0]; i >= pos; i--)
		{
			S[i + T[0]] = S[i];
		}
		for (i = 1; i <= T[0]; i++)
		{
			S[pos + i - 1] = T[i];
		}
		S[0] += T[0];
		return TRUE;
	}
	else
	{
		int insertLen = MAXSIZE - S[0];
		if (insertLen <= 0)
		{
			S[0] = MAXSIZE;
			return FALSE;
		}
		for (i = S[0]; i >= pos; i--)
		{
			S[i + insertLen] = S[i];
		}
		for (i = 1; i <= insertLen; i++)
		{
			S[pos + i - 1] = T[i];
		}
		S[0] += insertLen;
		return FALSE;
	}
}


/*  初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/*  操作结果: 从串S中删除第pos个字符起长度为len的子串 */
Status StrDelete(String S,int pos,int len)
{
	if (pos < 1 || pos > S[0] || len > S[0] - pos + 1 || len <= 0)
		return ERROR;
	int i;
	for (i = pos + len; i <= S[0]; i++)
	{
		S[i - len] = S[i];
	}
	S[0] -= len;
	return OK;
}

/*  初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/*  操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
Status Replace(String S,String T,String V)
{
	int i = 1;
	if(StrEmpty(T))
	{
		return ERROR;
	}
	do{
		i = Index(S, T, i);
		if (i)
		{
			StrDelete(S, i, StrLength(T));
			StrInsert(S, i, V);
			i += StrLength(V);
		}
	}while(i);
	return OK;
}

/*  输出字符串T */
void StrPrint(String T)
{ 
	int i;
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
}
