#include<stdio.h>
int IsPrime(int y);
int main()
{
	int a=0,b=0,c=0,i=0,d=0;
	for(a=4;a<=2000;a+=2)
	{
	
		for(i=2;i<a-1;i++)
		{
			b=IsPrime(i);
			c=IsPrime(a-i);
			if(b&&c)
			{
				d++;
				break; 
			}
	
		}
	}	
		printf("%d",d);

}

int IsPrime(int y)
{
	int i,k;
	k=(int)sqrt((double)y);
	for(i=2;i<=k;i++)
		if(y%i==0)
			return 0;
	return 1;
}
