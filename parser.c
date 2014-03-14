#include "parserDef.h"
int getTermIndex(char* input)
{
	int i;
	char *terms[]={"MAIN","SQO","SQC","END","EPSILON","SEMICOLON","FUNCTION","ASSIGNOP","FUNID","ID","INT","REAL","STRING","MATRIX","COMMA","SIZE","IF","OP","CL","ELSE","READ","ENDIF","PRINT","PLUS","MINUS","MUL","DIV","NUM","RNUM","STR","AND","OR","LT","LE","EQ","GT","GE","NE","NOT"};
	int numofterms=39;
	for(i=0;i<numofterms;i++)
	{
		if(strcmp(terms[i],input)==0)
		{
			return i;
		}
	}
	return -1;
}
int getNonTermIndex(char* input)
{
	int i;
	int numofnterms=47;
	char* nterms[]={"<mainFunction>","<stmtsAndFunctionDefs>","<stmtOrFunctionDef>","<var_list>","<more_ids>","<stmt>","<functionDef>","<declarationStmt>","<assignmentStmt_type1>","<assignmentStmt_type2>","<ifStmt>","<ioStmt>","<funCallStmt>","<functionDef>","<parameter_list>","<type>","<remainingList>","<leftHandSide_singleVar>","<rightHandSide_type1>","<leftHandSide_listVar","<rightHandSide_type2>","<arithmeticExpression>","<sizeExpression>","<sizeExpression>","<booleanExpression>","<otherStmts>","<elsepart>","<inputParameterList>","<listVar>","<arithmeticTerm>","<x>","<u>","<operator_lowPrecedence>","<factor>","<w>","<operator_highPrecedence>","<var>","<logicalOp>","<constrainedVars>","<relationalOp>","<matrixElement>","<matrix>","<rows>","<row>","<y>","<z>","<remainingColElements>"};
	for(i=0;i<numofnterms;i++)
	{
		if(strcmp(nterms[i],input)==0)
		{
			return i;
		}
	}
	return -1;
}
void createParseTable(grammar G, Table T, char* ffset[][100],int numofrules)
{
	int i;
	int j=0;
	int n=-1;
	int t=-1;
	for(i=0;i<numofrules;i++)
	{
		n=getNonTermIndex(G.r[i][0]);
		printf("index of non term is %d\n",n);
		j=0;
		while(strcmp(ffset[i][j],"\0")!=0)
		{
			printf("Herei is %d and j is %d\n",i,j);
			t=getTermIndex(ffset[i][j]);
			j++;
			T[n][t]=i;
		}
	}
	printf("Asser Rule is 87 %d",T[24][38]);
}
int main()
{
	printf("here");
	grammar G;
	FILE* fp =fopen("Grammar","r");
	int i,j;
	char string[200];
	i=0;
	while(!feof(fp)) {
		if (fgets(string,200,fp))
		{
			j=0;
			char* token = strtok(string, " ");
			//printf("I am the fucking token%s\n",token);
			while (token) 
			{
				if(strcmp("|",token)==0)
				{
					G.r[i][j]=(char*)malloc(2*sizeof(char));
					strcpy(G.r[i][j],"\0");
					//~ printf("%d",j);
					i++;
					//~ printf("here");
					j=0;
					G.r[i][j]=(char*)malloc(40*sizeof(char));
					strcpy(G.r[i][j],G.r[i-1][j]);
					j++;
				}
				else if(strcmp("->",token)!=0)
				{
					G.r[i][j]=(char*)malloc(40*sizeof(char));
					strcpy(G.r[i][j],token);
					j++;
				}
				//printf("token: %s\n", token);
				
				token = strtok(NULL, " ");
			}
			//printf("%s\n", string);
			G.r[i][j]="\0";
			i++;
		}
	}
	int numofrules=i;
	printf("grammar is %s\n",G.r[87][0]);
	
	char* ffset[89][100]={{"MAIN","\0"},
					{"INT","REAL","STRING","MATRIX","SQO","READ","PRINT","ID","FUNID","IF","FUNCTION","\0"},
					{"END","\0"},
					{"INT","REAL","STRING","MATRIX","SQO","READ","PRINT","ID","FUNID","IF","FUNCTION","\0"},
					{"INT","REAL","STRING","MATRIX","SQO","READ","PRINT","ID","FUNID","IF","\0"},
					{"FUNCTION","\0"},
					{"INT","REAL","STRING","MATRIX","\0"},
					{"ID","\0"},
					{"SQO","\0"},
					{"IF","\0"},
					{"READ","PRINT","\0"},
					{"FUNID","\0"},
					{"FUNCTION","\0"},
					{"INT","REAL","STRING","MATRIX","\0"},
					{"INT","\0"},
					{"REAL","\0"},
					{"STRING","\0"},
					{"MATRIX","\0"},
					{"COMMA","\0"},
					{"SQC","\0"},
					{"INT","REAL","STRING","MATRIX","\0"},
					{"ID","\0"},
					{"COMMA","\0"},
					{"SQC","SEMICOLON","\0"},
					{"ID","\0"},
					{"SQO","\0"},
					{"ID","\0"},
					{"SQC	SQO","\0"},
					{"OP","ID","NUM","RNUM","STR","SQO","\0"},
					{"SIZE","\0"},
					{"FUNID","\0"},
					{"SIZE","\0"},
					{"FUNID","\0"},
					{"SIZE","\0"},
					{"IF","\0"},
					{"ELSE","\0"},
					{"ENDIF","\0"},
					{"INT","REAL","STRING","MATRIX","SQO","READ","PRINT","ID","FUNID","IF","\0"},
					{"ENDIF","ELSE","\0"},
					{"READ","\0"},
					{"PRINT","\0"},
					{"FUNID","\0"},
					{"ID","NUM","RNUM","STR","SQO","\0"},
					{"CL","\0"},
					{"COMMA","\0"},
					{"CL","\0"},
					{"OP","ID","NUM","RNUM","STR","SQO","\0"},
					{"CL","SEMICOLON","\0"},
					{"PLUS","MINUS","\0"},
					{"OP","ID","NUM","RNUM","STR","SQO","\0"},
					{"PLUS","MINUS","CL","SEMICOLON","\0"},
					{"MUL","DIV","\0"},
					{"CL	OP","\0"},
					{"ID","NUM","RNUM","STR","SQO","\0"},
					{"PLUS","\0"},
					{"MINUS","\0"},
					{"MUL","\0"},
					{"DIV","\0"},
					{"OP","\0"},
					{"ID","NUM","RNUM","\0"},
					{"ID","\0"},
					{"NUM","\0"},
					{"RNUM","\0"},
					{"ID","\0"},
					{"NUM","\0"},
					{"RNUM","\0"},
					{"ID","\0"},
					{"STR","\0"},
					{"SQO","\0"},
					{"SQO","\0"},
					{"NUM","\0"},
					{"SQC","\0"},
					{"SEMICOLON","\0"},
					{"NUM","\0"},
					{"SEMICOLON","SQC","\0"},
					{"COMMA","\0"},
					{"COMMA","\0"},
					{"SEMICOLON","SQC","\0"},
					{"ID","\0"},
					{"AND","\0"},
					{"OR","\0"},
					{"LT","\0"},
					{"LE","\0"},
					{"EQ","\0"},
					{"GT","\0"},
					{"GE","\0"},
					{"NE","\0"},
					{"NOT","\0"}
	};
	//~ int f=0;
	//~ int yu=0;
	//~ for(yu=0;yu<88;yu++){
		//~ f=0;
	//~ while(strcmp(ffset[yu][f],"\0")!=0)
		//~ {
			//~ printf("ffset is %s\n",ffset[1][f]);
			//~ f++;
		//~ }
	//~ }
	//~ int sizeofterms=39;
	//~ int sizeofnterms=47;
	//printf("ffset is %s",ffset[87][0]);
	Table t;
	createParseTable(G,t,ffset,numofrules);
	return 0;
}
