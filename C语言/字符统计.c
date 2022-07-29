#include<stdio.h> 
#include<stdlib.h>
int main()
{
	while(1)
	{
	
	int character=0,digit=0,other=0;
	char *p="Hello!",s[600];
	printf("%s\n",p);
	p=s;
	printf("input string:\n");
	scanf("%s",&s);
	while(*p!='\0')
	{
		if(('A'<=*p&&*p<='Z')||('a'<=*p&&*p<='z'))
		++character;
		else if((*p<='9') &&(*p>='0'))
		++digit;
		else ++other;
		p++;
	}
	printf(" character:%d\n digit:%d\n other: %d\n",character,digit,other);
	}
	system("pause");
	return 0;
}
