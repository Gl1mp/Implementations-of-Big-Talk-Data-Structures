#include <stdio.h>
#include <string.h>

#define MAXSIZE 1000
typedef char String[MAXSIZE + 1]; // 0号存长度，字符从1开始

//本程序采用1-based
void get_next(String T, int* next)
{
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T[0])
	{
		// j为0时是走到头了不能再走了，而T[i]和T[j]相同的时候同样找到了最长的前后缀字串
		if (j == 0 || T[i] == T[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
}

// get_next的改进版，防止对于相同值进行多次无效的重复比较
void get_nextval(String T, int* nextval)
{
	int i = 1, j = 0;
	nextval[1] = 0;
	while (i < T[0])
	{
		if (j == 0 || T[i] == T[j])
		{
			i++;
			j++;
			if (T[i] != T[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}	
}

int IndexKMP(String S, String T, int pos)
{
	int i = pos, j = 1;
	int nextval[MAXSIZE];
	if (pos < 1 || pos > S[0] || T[0] == 0)
		return 0;
	get_next(T, nextval);
	while (i <= S[0] && j <= T[0])
	{
		//j回退到0的时候说明这种情况完全不行，即使有重叠的也完全不行
		if (j == 0 || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
			j = nextval[j];
	}
	if (j > T[0])
		return i - T[0];
	return 0;
}

int main()
{
	String S, T;
	strcpy(S + 1, "aaaab");
	S[0] = 5;
	strcpy(T + 1, "aaab");
	T[0] = 4;
	
	int pos = IndexKMP(S, T, 1);
	printf("%d", pos);
}
