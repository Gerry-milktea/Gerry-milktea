#include<stdio.h>
#include<stdlib.h> 
int max(int,int);
int main()
{
	int a;
	int b;
	int ret;
	printf("请输入两个数：");
	scanf("%d%d",&a,&b) ;
	ret=max(a,b);
	printf("max value is:%d\n",ret);
	system("pause");
	return 0;
}
int max(int num1,int num2)
{
	int result;
	if (num1>num2)
	result=num1;
	else
	result=num2;
	return result;
}
