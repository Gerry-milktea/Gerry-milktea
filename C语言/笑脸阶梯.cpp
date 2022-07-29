#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
	int i,j;
	SetConsoleOutputCP(437);
	printf("\1\1\n");
	for(i=1;i<11;i++)
	{
		for(j=1;j<=i;j++)
		printf("%c%c",219,219);
		printf("\n");
	}
	getchar();
	return 0;
}
