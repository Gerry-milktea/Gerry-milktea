#include<stdio.h> 
#include<stdlib.h>
int main()
{	double a,b;
	printf("请输入你的工资：");
	scanf("%lf",&a);
	b=(a-800) *0.03;
	printf("你的个人所得税为：%f\n",b);
	system("pause");
	return 0;
}
