#include<stdio.h>
#include<stdlib.h>
const int MAX=3;
int main()
{
	int var[]={10,100,200};
	int i,*ptr;
	ptr=var;
	i=0;
	while(ptr<=&var[MAX-1])
	{
		printf("´æ´¢µØÖ·£ºvar[%d]=%p\n",i,ptr) ;
		printf("´æ´¢Öµ£ºvar[%d]=%d\n",i,*ptr);
		ptr++;
		i++;
	}
	system("pause");
	return 0;
}
