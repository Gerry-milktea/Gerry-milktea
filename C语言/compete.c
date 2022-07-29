#include <stdio.h>
#include <math.h>
int select(int m)
{
	int i;
	int k;
	if ( m>1)
	{

	 k = (int)sqrt((double)m);
	 for( i =2;i<=k;i++)
	 	if(m%i == 0)
	 	break;
	if(i>k)

		return 1;
	else 

	  	return 0;
	  }
	if ( m==1)
		return 0;
}
int main()
{
int a = 0;
int b = 0;
int b2 = 0;
int c = 0;
int i = 0;
//printf("%d",a);
//a = select(7);
// 
//printf("%d",a);
scanf("%d",&b);
while(b>1)
{

	b = b-a;
	b2  =b;
	a =0;
	for (; b2>0;b2--)
	{


		if ( select(b2))
		{
				a++;
			//printf("%d\n",a);
		}
	}

	c++;
}
	printf("%d",c);
return 0;
} 

