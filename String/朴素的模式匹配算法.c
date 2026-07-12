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

// BF算法，Brute-Force（朴素匹配算法）
/* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */

// 双重for循环
int Index1(String S, String T, int pos)
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

// 双指针，单while+回溯
int Index2(String S, String T, int pos)
{
	int i = pos;
	int j = 1;
	while (i <= S[0] && j <= T[0])
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T[0])
	{
		return i - T[0];
	}
	return 0;
}
