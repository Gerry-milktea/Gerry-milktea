#include<stdio.h>
int main()
{
	double score[5]={90.5,91.0,92.0,93.5,94.0};
	int i;
	double sum=0.0;
	printf("The address of the array :%10p\n",score) ;
	printf("The address and value of each element:\n");
	for (i=0;i<5;i++)
	printf("score[%d]:\t%p\t%5.2f\n",i,&score[i],score[i]);
	for(i=0;i<5;i++)
	sum+=*(score+i);
	printf("the average lf score is:%5.2f\n",sum/5);
	return 0;
	
}
