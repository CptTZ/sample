#include <stdio.h>
#include <stdlib.h>
int sum(int a)
{
	printf("a is %d\n", a);
	if(a==0)
	{
		return a;
	}
	else
	{
		return a+sum(a-1);
	}
}
void main()
{
	printf("sum is %d\n", sum(10));
}
