#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
int main()
{
	int i, a;
	
	srand(time(NULL));
	for(i=0;i<6;i++)
	{
	a=rand()%100+1;
	printf("%d\n",a);
	}
	return 0;
}
