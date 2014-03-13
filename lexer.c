#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lexerDef.h"
int line_num=1;
int curr=0;
FILE *getStream(FILE *fp,buffer *B, buffersize k)
{
	//int i;
	//B=malloc((k+2)*sizeof(char));
	//fgets(B,k,fp);
	
	
	fread(*B,1,k,fp);
	char* A=*B;
	A[((int)strlen(A))-1]='$';
	printf("%s\n",A);
	*B=A;
	printf("A number is %c\n",A[9]);
	return fp;
}

char * searchTok(char pattern)
{
	int i;
	char* Tokens[]={"SQO","SQC","OP","CL","SEMICOLON","COMMA","PLUS","MINUS","MUL","DIV","SIZE"};
	char Patterns[]={'[',']','(',')',';',',','+','-','*','/','@'};
	for(i=0;i<sizeof(Patterns);i++)
	{
		if(pattern==Patterns[i])
		{
			return Tokens[i];
		}
	}
	return "abcd";
}
tokenInfo getNextToken(FILE *fp,buffer *B,buffersize k)
{
	char* A=*B;
	//fp=fopen("abcd","r");
	
	
	tokenInfo ti;
	//char lexeme[100];
	//int forward;

	//ignores white spaces and comments
	while(A[curr]==' '||A[curr]=='\t'||A[curr]=='\n'||A[curr]=='#')
	{
		printf("I am removing whitesp\n");
		if(A[curr]==' '|| A[curr]=='\t')
		{
			curr++;
		}
		if(A[curr]=='\n')
		{
			curr++;
			line_num++;
		}
		if(A[curr]=='#')
		{
			while(A[curr]!='\n')
			{
				curr++;
			}
			curr++;
			line_num++;
		}
	}
	if(strcmp("abcd",searchTok(A[curr]))!=0)//search for single character tokens
	{
		
		ti.line_numb=line_num;
		//memset(ti.pattern,0,sizeof(ti.pattern));
		printf("%c in a  buffer\n",A[curr]);
		printf("in ti %c",ti.pattern[0]);
		ti.pattern[0]=A[curr];
		printf("into the function\n\n");
		ti.token=searchTok(A[curr]);
		curr++;
		printf("I am in searching tok\n%d\n",ti.line_numb);
	}
	return ti;
}


int main()
{
	FILE *fp=fopen("abcd","r");
	buffersize k=600;
	buffer B;
	B=(buffer)malloc(k*sizeof(char));
	printf("here");
	memset(B,0,k);
	getStream(fp,&B,k);
	printf("I am here\n");
	
	tokenInfo ti=getNextToken(fp,&B,k);
	printf("%s\n%s\n",ti.pattern,ti.token);
	ti=getNextToken(fp,&B,k);
	printf("%s is buffer",B);
	printf("%d is buffer",strlen(B));
	printf("%s\n%s\n",ti.pattern,ti.token);
	printf("%s is buffer",B);
	//int i = 0;
	
	
	//buffersize k=600;
	//buffer B;
	
	////printf("%s",B);
	
	//while(B[i]!='$')
	//{
		//printf("%d %c\n",i,B[i]);
		//i++;
	//}
	//printf("%s",B);
	//memset(B,0,k);
	//printf("\nNext\n");
	//getStream(fp,B,k);
	
	//i=0;
	//while(B[i]!='$')
	//{
		//printf("%d %c\n",i,B[i]);
		//i++;
	//}
	//printf("%s",B);
	//fclose(fp);
	//printf("\nend");
	
	return 0;
}
