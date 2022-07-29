#include<stdio.h>
int main()
{
	int a[3][2];
	printf("%p\t%p\n",a,a+1);
	printf("%p\t%p\n",a[0],a[0]+1);
	printf("%p\t%p\n",&a[0],&a[0]+1);
	printf("%p\t%p\n",&a[0][0],&a[0][0]+1);
	return 0;
}

