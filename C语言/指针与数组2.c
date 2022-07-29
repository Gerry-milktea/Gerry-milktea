#include<stdio.h>
int main()
{
	double score[5]={90.5,91.0,92.0,93.5,94.0};
	double *p=score;
	int i;
	double sum=0.0;
	printf("The array is:\n");
	for(i=0;i<5;i++)
	printf("score[%d]:\t%5.2f\t%5.2f\n",i,score[i],*p++);
	for(p=score;p<(score+5);p++)
	sum+=*p;
	printf("the average of score is:%5.2f\n",sum/5);
	return 0;
}
