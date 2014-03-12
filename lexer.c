#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lexerDef.h"
FILE *getStream(FILE *fp, buffer B, buffersize k)
{
	//int i;
	//B=malloc((k+2)*sizeof(char));
	//fgets(B,k,fp);
	
	
	fread(B,1,k,fp);
	B[strlen(B)-1]='$';
	//printf("%s",B);
	return fp;
}
int main()
{
	int i = 0;
	FILE *fp=fopen("abcd","r");
	
	buffersize k=600;
	buffer B;
	getStream(fp,B,k);
	//printf("%s",B);
	
	while(B[i]!='$')
	{
		printf("%d %c\n",i,B[i]);
		i++;
	}
	printf("%s",B);
	memset(B,0,k);
	printf("\nNext\n");
	getStream(fp,B,k);
	
	i=0;
	while(B[i]!='$')
	{
		printf("%d %c\n",i,B[i]);
		i++;
	}
	printf("%s",B);
	fclose(fp);
	printf("\nend");
	return 0;
}

tokenInfo getNextToken(FILE *fp)
{
	//char *begin=1;
	//char *forward;
}
