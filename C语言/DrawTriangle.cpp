#include<stdio.h>
void DrawTriangle (int n,char c);
int main()
{	
//	DrawTriangle (59,'*');
//	DrawTriangle (10,'#');
	DrawTriangle (100,'*');
	
	return 0;
}
void DrawTriangle (int n,char c)
	{
		int i,j;
		for(j=0;j<=n;j++)
		{
		
			for(i=0;n-i-j>0;i++)
			{
				printf(" ");
			}
			for(i=0;2*j-i>=0;i++)
			{
				printf("%c",c);
			}
			putchar(10);
		}
	}
