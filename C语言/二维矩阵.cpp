#include<stdio.h> 
#include<stdlib.h>
#define N 3
int main()
{
	int A[N][N]={{1,4,7,},{2,5,8},{3,6,9}};
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++) 
		printf("%5d",A[i][j]);
		printf("\n");
	}
	system("pause");
	return 0;
}
