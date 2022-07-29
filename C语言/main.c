#include<stdio.h>
#include<stdlib.h> 
#include"circle.h"
#include"rectangle.h"
int main()
{
	double r,w,h;
	printf("Input radius:\n");
	scanf("%lf",&r);
	printf("Circle area=%f\n",circle_area(r));
	printf("Circle perimeter=%f\n",circle_perimeter(r));
	printf("Input width and height:\n");
	scanf("%lf%lf",&w,&h);
	printf("Rectangle area=%f\n",rectangle_area(w,h));
	printf("Rectangle perimeter=%f\n",rectangle_perimeter(w,h));
	system("pause");
	return 0;
}
