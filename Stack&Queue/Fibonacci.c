#include <stdio.h>

int Fib(int i)
{
	if (i < 2)
	{
		return i == 1 ? 0 : 1;
	}
	return Fib(i - 1) + Fib(i - 2);
}

int main()
{
	for (int i = 1; i <= 30; i++)
	{
		printf("%d:%d\n", i, Fib(i));
	}
}
