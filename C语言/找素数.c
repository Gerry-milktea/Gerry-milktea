#include<stdio.h> 
#include<stdlib.h>
#include<math.h>
int main()
{
	int a,i,prime,m,count=0;
	for(a=100;a<=999;a++)
	{
		prime=1;
		m=(int)sqrt((double)a);
		for(i=2;prime&&i<=m;i++)
		if(a%i==0)
		prime=0;
		if(prime)
		{
		printf("%7d",a);
		count++;
		if(count%5==0)
		putchar(10);
		}
	}
	printf("\n三位数的质数总共有%d个\n",count);
	system("pause");
	return 0;
	
}
