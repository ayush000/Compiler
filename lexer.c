
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
	//~ printf("file that is read is%s\n",A);
	*B=A;
	//printf("A number is %c\n",A[9]);
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
	char currLex[100];
	int cli,nxt;
	//fp=fopen("abcd","r");
	
	
	tokenInfo ti;
	getStream(fp,&A,k);
	//char lexeme[100];
	//int forward;

	//ignores white spaces and comments
	
	while(A[curr]==' '||A[curr]=='\t'||A[curr]=='\n'||A[curr]=='#')
	{
		//~ int nxt=curr+1;
		//printf("I am removing whitesp\n");
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
		 //~ printf("\nIncurr is %c, %d\n",A[curr],curr);
		
	}
	if(A[curr]=='$')
	{
		strcpy(ti.token,"EOF");
		return ti;
	}
	if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')||(strcmp(searchTok(A[curr]),"abcd")!=0)||A[curr]=='_'||A[curr]=='='||A[curr]=='<'||A[curr]=='"'||A[curr]=='>'||A[curr]=='$'))
	{
		cli=0;
		memset(currLex,0,100);
		currLex[cli]=A[curr];
		printf("current is %d %c and next is %d %c and next is %d %c",curr,A[curr],curr+1,A[curr+1],curr+2,A[curr+2]);
		cli++;
		curr++;
		printf("Error: Unknown Token:%s at line number %d\n",currLex,line_num);
		if(A[curr]=='$')
		{
			exit(0);
		}
		if(!(A[curr]=='$'||A[curr]=='\n'))
		{
			printf("char is %c\n",A[curr]);
			ti=getNextToken(fp,B,k);
			return ti;
		}
	}
	if(strcmp("abcd",searchTok(A[curr]))!=0)//search for single character tokens
	{
		//~ printf("\nIncurr is %c, %d\n",A[curr],curr);
		
		//ti.line_numb=line_num;
		//memset(ti.pattern,0,sizeof(ti.pattern));
		//printf("%c in a  buffer\n",A[curr]);
		//printf("in ti %c",ti.pattern[0]);
		ti.pattern[0]=A[curr];
		ti.pattern[1]='\0';
	//	printf("into the function\n\n");
		strcpy(ti.token,searchTok(A[curr]));
		
		curr++;
		ti.line_numb=line_num;
		return ti;
	//	printf("I am in searching tok\n%d\n",ti.line_numb);
	}
	
	
	if(A[curr]=='>')
	{
		curr++;
		if(A[curr]=='=')
		{
			strcpy(ti.token,"GE");
			//ti.line_numb=line_num;
			strcpy(ti.pattern,">=");
			ti.line_numb=line_num;
			curr++;
			return ti;
		}
		else
		{
			strcpy(ti.token,"GT");
			//ti.line_numb=line_num;
			strcpy(ti.pattern,">");
			ti.line_numb=line_num;
			return ti;
		}
	}
	if(A[curr]=='<')
	{
		curr++;
		if(A[curr]=='=')
		{
			strcpy(ti.token,"LE");
			strcpy(ti.pattern,"<=");
			curr++;
			ti.line_numb=line_num;
			return ti;
		}
		else
		{
			strcpy(ti.token,"LT");
			strcpy(ti.pattern,"<");
			ti.line_numb=line_num;
			return ti;
		}
	}
	if(A[curr]=='=')
	{
		curr++;
		if(A[curr]=='=')
		{
			strcpy(ti.token,"EQ");
			strcpy(ti.pattern,"==");
			curr++;
			ti.line_numb=line_num;
			return ti;
		}
		else if(A[curr]=='/')
		{
			curr++;
			if(A[curr]=='=')
			{
				strcpy(ti.token,"NE");
				strcpy(ti.pattern,"=/=");
				curr++;
				ti.line_numb=line_num;
				return ti;
			}
			else
			{
				strcpy(ti.token,"ASSIGNOP");
				strcpy(ti.pattern,"=");
				curr--;
				ti.line_numb=line_num;
				return ti;
			}
		}
		else
		{
			strcpy(ti.token,"ASSIGNOP");
			strcpy(ti.pattern,"=");
			ti.line_numb=line_num;
			return ti;
		}
	}
	if(A[curr]=='.')
	{
		
		//~ printf("\nHere in dot\n");
		cli=0;
		memset(currLex,0,100);
		curr++;
		if(A[curr]=='a')
		{
			curr++;
			if(A[curr]=='n')
			{
				curr++;
				if(A[curr]=='d')
				{
					curr++;
					if(A[curr]=='.')
					{
						//~ printf("1Here\n");
						strcpy(ti.token,"AND");
						strcpy(ti.pattern,".and.");
						curr++;
						ti.line_numb=line_num;
						return ti;
					}
				}
			}
		}
		if(A[curr]=='n')
		{
			curr++;
			if(A[curr]=='o')
			{
				curr++;
				if(A[curr]=='t')
				{
					curr++;
					if(A[curr]=='.')
					{
						//~ printf("Here2\n");
						strcpy(ti.token,"NOT");
						strcpy(ti.pattern,".not.");
						curr++;
						ti.line_numb=line_num;
						return ti;
					}
				}
			}
		}
		if(A[curr]=='o')
		{
			curr++;
			if(A[curr]=='r')
			{
				curr++;
				if(A[curr]=='.')
				{
					strcpy(ti.token,"OR");
					//~ printf("Here3\n");
					//~ printf("Real 2nd is %s",ti.token);
					strcpy(ti.pattern,".or.");
					curr++;
					ti.line_numb=line_num;
					return ti;
					//~ printf("\n%c\n",A[curr]);
				}
			}
		}			
	}
	
	if(A[curr]=='"')
	{
		cli=0;
		memset(currLex,0,100);
		currLex[cli]=A[curr];
		curr++;
		cli++;
		while(A[curr]!='"')
		{
			if((A[curr]>='a'&& A[curr]<='z')||A[curr]==' ')
			{
				currLex[cli]=A[curr];
				curr++;
				cli++;
			}
			else
			{
				printf("Error. Invalid string");
			}
		}
		currLex[cli]=A[curr];
		curr++;
		cli++;
		strcpy(ti.token,"STR");
		strcpy(ti.pattern,currLex);
		ti.line_numb=line_num;
		return ti;
		curr++;		
	}
	if(A[curr]>='0' && A[curr]<='9')
	{
		cli=0;
		
		memset(currLex,0,100);
		currLex[cli]=A[curr];
		curr++;
		cli++;
		while(A[curr]>='0' && A[curr]<='9')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
		}
		if(A[curr]=='.')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
			while(A[curr]>='0' && A[curr]<='9')
			{
				currLex[cli]=A[curr];
				curr++;
				cli++;
			}
			strcpy(ti.token,"RNUM");
			strcpy(ti.pattern,currLex);
			ti.line_numb=line_num;
			return ti;
		}
		else
		{
			strcpy(ti.token,"NUM");
			strcpy(ti.pattern,currLex);
			ti.line_numb=line_num;
			return ti;
		}
	}
	
	
	//Begin Code fragment 1
		//int lookahead=curr;
	
	
	
	
	// _main and funid
	
	
	
	
	if(A[curr]=='_'){
		cli=0;
		memset(currLex,0,100);
		currLex[cli]=A[curr];
		curr++;
		cli++;
		if(A[curr]>='0' && A[curr]<='9')
		{
			while(A[curr]>='0' && A[curr]<='9')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
			}
			//~ strcpy(ti.pattern,currLex);
			//~ strcpy(ti.token,"ERROR");
			printf("Error: Unknown pattern '%s' on line Num %d\n",currLex,line_num);
			if(A[curr]=='$')
			{
				exit(0);
			}
			if(A[curr]!='$')
			{
				ti=getNextToken(fp,B,k);
				return ti;
			}
		}
		if(A[curr]=='m'){
			currLex[cli]=A[curr];
			//printf("After %c\n %d",currLex[cli],cli);
			cli++;
			curr++;//can be main or function
			if(A[curr]=='a'){
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(A[curr]=='i'){
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(A[curr]=='n'){
						//~ printf("After %c\n",A[curr]);
						currLex[cli]=A[curr];
						cli++;
						curr++;
						if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
						{
							//~ printf("here");
							//printf("pattern is %s",currLex);
							strcpy(ti.pattern,currLex);
							strcpy(ti.token,"MAIN");
							ti.line_numb=line_num;
							return ti;
						}
					}
				}
			}
		}
		while((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9'))
		{
			currLex[cli]=A[curr];
			cli++;
			curr++;
		}
		//~ printf("pattern is %s",currLex);
		strcpy(ti.pattern,currLex);
		strcpy(ti.token,"FUNID");
		ti.line_numb=line_num;
		return ti;
	}
	
	/*
	 * end endif else if int read real print string matrix
	 * */
	cli=0;
	memset(currLex,0,100);
	int flag=0;
	if(A[curr]=='e')
	{
		currLex[cli]=A[curr];
		curr++;
		cli++;
		if(A[curr]=='n')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
			if(A[curr]=='d')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(A[curr]=='i')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(A[curr]=='f')
					{
						currLex[cli]=A[curr];
						cli++;
						curr++;
						if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
						{
							//~ printf("here");
							//~ printf("pattern is %s",currLex);
							strcpy(ti.pattern,currLex);
							strcpy(ti.token,"ENDIF");
							ti.line_numb=line_num;
							flag=1;
							return ti;
						}
					}
				}
				else if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
				{
					//~ printf("here");
					//~ printf("pattern is %s",currLex);
					strcpy(ti.pattern,currLex);
					strcpy(ti.token,"END");
					ti.line_numb=line_num;
					flag=1;
					return ti;
				}
			}
		}
		else if(A[curr]=='l')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
			if(A[curr]=='s')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(A[curr]=='e')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
					{
						//~ printf("here");
						//~ printf("pattern is %s",currLex);
						strcpy(ti.pattern,currLex);
						strcpy(ti.token,"ELSE");
						ti.line_numb=line_num;
						flag=1;
						return ti;
					}
				}
			}
		}
	}
	
	else if(A[curr]=='i')
	{
		currLex[cli]=A[curr];
		cli++;
		curr++;
		if(A[curr]=='n')
		{
			currLex[cli]=A[curr];
			cli++;
			curr++;
			if(A[curr]=='t')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
				{
					//~ printf("here");
					//~ printf("pattern is %s",currLex);
					strcpy(ti.pattern,currLex);
					strcpy(ti.token,"INT");
					ti.line_numb=line_num;
					flag=1;
					return ti;
				}
			}
		}
		if(A[curr]=='f')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
				{
					//~ printf("here");
					//~ printf("pattern is %s",currLex);
					strcpy(ti.pattern,currLex);
					strcpy(ti.token,"IF");
					ti.line_numb=line_num;
					flag=1;
					return ti;
				}
			}
	}
	else if(A[curr]=='r')
	{
		currLex[cli]=A[curr];
		curr++;
		cli++;
		if(A[curr]=='e')
		{
			currLex[cli]=A[curr];
			cli++;
			curr++;
			if(A[curr]=='a')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(A[curr]=='l')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
					{
						//~ printf("here");
						//~ printf("pattern is %s",currLex);
						strcpy(ti.pattern,currLex);
						strcpy(ti.token,"REAL");
						ti.line_numb=line_num;
						flag=1;
						return ti;
					}
				}
				else if(A[curr]=='d')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
					{
						//~ printf("here");
						//~ printf("pattern is %s",currLex);
						strcpy(ti.pattern,currLex);
						strcpy(ti.token,"READ");
						ti.line_numb=line_num;
						flag=1;
						return ti;
					}
				}
			}
		}
	}
	else if(A[curr]=='p')
	{
		currLex[cli]=A[curr];
		curr++;
		cli++;
		if(A[curr]=='r')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
			if(A[curr]=='i')
			{
				currLex[cli]=A[curr];
				cli++;
				curr++;
				if(A[curr]=='n')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(A[curr]=='t')
					{
						currLex[cli]=A[curr];
						cli++;
						curr++;
						if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
						{
							//~ printf("here");
							//~ printf("pattern is %s",currLex);
							strcpy(ti.pattern,currLex);
							strcpy(ti.token,"PRINT");
							ti.line_numb=line_num;
							flag=1;
							return ti;
						}
					}
				}
			}
		}
	}
	else if(A[curr]=='s')
	{
		//~ printf("go gere");
		currLex[cli]=A[curr];
		curr++;
		cli++;
		if(A[curr]=='t')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
			if(A[curr]=='r')
			{
				currLex[cli]=A[curr];
				curr++;
				cli++;
				if(A[curr]=='i')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(A[curr]=='n')
					{
						currLex[cli]=A[curr];
						cli++;
						curr++;
						if(A[curr]=='g')
						{
							currLex[cli]=A[curr];
							cli++;
							curr++;
							if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
							{
								//~ printf("here");
								//~ printf("pattern is %s",currLex);
								strcpy(ti.pattern,currLex);
								strcpy(ti.token,"STRING");
								ti.line_numb=line_num;
								flag=1;
								return ti;
							}
						}
					}
				}
			}
		}
	}
	else if(A[curr]=='m')
	{
		currLex[cli]=A[curr];
		curr++;
		cli++;
		if(A[curr]=='a')
		{
			currLex[cli]=A[curr];
			curr++;
			cli++;
			if(A[curr]=='t')
			{
				currLex[cli]=A[curr];
				curr++;
				cli++;
				if(A[curr]=='r')
				{
					currLex[cli]=A[curr];
					cli++;
					curr++;
					if(A[curr]=='i')
					{
						currLex[cli]=A[curr];
						cli++;
						curr++;
						if(A[curr]=='x')
						{
							currLex[cli]=A[curr];
							cli++;
							curr++;
							if(!((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9')))
							{
								//~ printf("here");
								//~ printf("pattern is %s",currLex);
								strcpy(ti.pattern,currLex);
								strcpy(ti.token,"MATRIX");
								ti.line_numb=line_num;
								flag=1;
								return ti;
							}
						}
					}
				}
			}
		}
	}
	if((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z')||(A[curr]>='0'&&A[curr]<='9'))
	{
		printf("ID sensed\n");
		while((A[curr]>='a'&&A[curr]<='z')||(A[curr]>='A'&&A[curr]<='Z'))
		{
			currLex[cli]=A[curr];
			cli++;
			curr++;
		}
		//~ printf("%s",currLex);
		if(A[curr]>='0'&&A[curr]<='9')
		{
			int i=0;
			while(A[curr]>='0'&&A[curr]<='9')
			{
				i++;
				currLex[cli]=A[curr];
				cli++;
				curr++;
			}
			if(i>1)
			{
				printf("Error: Unknown pattern '%s' on line Num %d\n",currLex,line_num);
				if(A[curr]=='$')
				{
					exit(0);
				}
				if(A[curr]!='$')
					{
						ti=getNextToken(fp,B,k);
						return ti;
					}
			}
				
		}
		if(cli>20)
		{
			printf("Error:Token ID:%s at line number %d is of Length %d which is more than 20\n",currLex,line_num, cli);
			if(A[curr]=='$')
			{
				exit(0);
			}
			if(A[curr]!='$')
				{
					ti=getNextToken(fp,B,k);
					return ti;
				}
		}
		else
		{
			strcpy(ti.pattern,currLex);
			strcpy(ti.token,"ID");
			ti.line_numb=line_num;
			return ti;
		}
	}
	else if(flag==0)
	{
		strcpy(ti.pattern,currLex);
		strcpy(ti.token,"ID");
		ti.line_numb=line_num;
		return ti;
	}
	
	//~ strcpy(ti.token,"Here");
	return ti;
}
	//End code fragment 1
	//ti.line_numb=line_num;
	


int main()
{
	FILE *fp=fopen("testcase1.txt","r");
	buffersize k=10000;
	buffer B;
	B=(buffer)malloc(k*sizeof(char));
	memset(B,0,k);
	getStream(fp,&B,k);
	//~ while(B[curr]!='$')
	tokenInfo ti;
	memset(ti.token,0,100);
	memset(ti.pattern,0,100);
	while(1)
	{
		//~ printf("%d\n",strcmp(ti.token,"EOF"));
		ti=getNextToken(fp,&B,k);
		if(strcmp(ti.token,"EOF")==0)
		{
			//~ printf("HPattern is %s\nToken is p%sq\nLine number is %d\n\n",ti.pattern,ti.token,ti.line_numb);
			break;
		}
		printf("Pattern is %s\nToken is p%sq\nLine number is %d\n\n",ti.pattern,ti.token,ti.line_numb);
	}
	//~ printf("%s, %d\n",ti.token,strcmp(ti.token,"EOF"));
	return 0;
}
