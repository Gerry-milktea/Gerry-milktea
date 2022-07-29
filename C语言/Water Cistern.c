#include<stdio.h>
#include<math.h>
void sort (double arr[],int len);
int main()
{
	int r=0, h=0, s=0, d=0, g=0, outputint=0,i=0,a=0;
	double pi = 3.1415926, output1=0.0,x=0.0,y=1.0;
	double output2[10000]={0};
	scanf("%d,%d,%d", &r, &h, &s);
	scanf("%d,%d", &d, &g);
	if (d >= 0)
	{
		if (g <= 180)
			output1 = sqrt((2.0 * pi * (double)r * ((double)g / 360.0)) * (2.0 * pi * (double)r * ((double)g / 360.0)) + ((double)s - (double)d) * ((double)s - (double)d));


		if (g > 180)
			g = g - 180;
			output1 = sqrt((2.0 * pi * (double)r * ((double)g / 360.0)) * (2.0 * pi * (double)r * ((double)g / 360.0)) + ((double)s - (double)d) * ((double)s - (double)d));
	}
	if(d<0)
	{  
		d=0-d;
		do
		{	
			do
			{
				x=x+y;
				a++;		
			}while(x<=180);
			x=0.0;		
			do
			{
				output2[i]=sqrt((double)d*(double)d+(double)r*(double)r-2*(double)d*(double)r*cos(2*pi*(((double)g-x)/360.0)))+sqrt((2.0 * pi * (double)r * (x / 360.0))*(2.0 * pi * (double)r * (x / 360.0))+(double)s*(double)s);
				x=x+y;
				i++;		
			}while(x<=180);
			sort (output2,a);
			y=y/2;
			x=0.0;
			i=0;
		}while(!((output2[1]-output2[0])<0.1));

		printf("%f",output2[0]);
	}
	//outputint = (int)(output + 0.5);

//	printf("%d", outputint);


	return 0;
}
void sort (double arr[],int len)
{
	int i=0,j=0;
	double temp=0.0;
	for(j=0;j<len;j++)
	{
		for(i=0;i<len-1;i++)
		{
			if (arr[i]>arr[i+1])
			{
				temp=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=temp;				
			}

		}
	}
}










