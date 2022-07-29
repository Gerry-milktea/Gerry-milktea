#include<stdio.h>


 int main()


 {

  char X[6];

   int i,a,b;

  for(i=0;i<6;i++)

   X[i]=getchar();

a=(int)X[0]-48;
b=(int)X[2]-48;
printf("%d\n",a+b);
 for(i=0;i<6;i++)

  putchar(X[i]);

   return 0;


 }
