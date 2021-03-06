#include "parserDef.h"
//~ int currentStack=0;
//~ int push(char* ch)
//~ {
	//~ if(currentStack<1000)
	//~ {
		//~ stack[currentStack]=(char*)malloc(sizeof(ch));
		//~ strcpy(stack[currentStack],ch);
		//~ printf("%s",stack[currentStack]);
		//~ currentStack++;
		//~ return 1;
	//~ }
	//~ return 0;
//~ }
//~ 
//~ int pop()
//~ {
	//~ if(currentStack!=0)
	//~ {
		//~ currentStack--;
	//~ }
	//~ return 1;
//~ }
void push(char* data)
{
	
	if (top == NULL)
    {
        head =(struct stack *)malloc(sizeof(struct stack));
        top=head;
        strcpy(top->ch,data);
        //~ printf("%s",top->ch);
    }
    else
    {
		stack* temp;
        temp =(struct stack *)malloc(sizeof(struct stack));
        top->next=temp;
        strcpy(temp->ch,data);
        top = temp;
    }
    top->next = NULL;
    //~ printf("%s",top->ch);
    //~ count++;
}
void pop()
{
	stack* temp;
	temp=head;
	
	if(temp->next==NULL)	//one node
	{
		temp=NULL;
		free(head);
		return ;
	}	
	while(temp->next!=top)
	{
		temp=temp->next;
	}
	temp->next=NULL;
	free(top);
	top=temp;
}	
			 
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
	for(i=0;i<47;i++)
	{
		for(j=0;j<39;j++)
		{
			T[i][j]=-1;
		}
	}
	for(i=0;i<numofrules;i++)
	{
		n=getNonTermIndex(G.r[i][0]);
		//~ printf("index of non term is %d\n",n);
		j=0;
		while(strcmp(ffset[i][j],"\0")!=0)
		{
			//~ printf("Herei is %d and j is %d\n",i,j);
			t=getTermIndex(ffset[i][j]);
			j++;
			if(T[n][t]!=-1) 
			{
				printf("!!!!!!!!!!!!!!!!  conflict in parse table!!!!!!!!!!!!\n %d %d",n,t);
			}
			T[n][t]=i;
		}
	}
	//~ printf("Assert Rule is 87 %d",T[24][38]);
}
parseTree* parseInputSourceCode(char *testcaseFile, Table T,grammar G)
{
	FILE* fp1 =fopen(testcaseFile,"r");
	buffersize k=600;
	buffer B;
	int gindex;
	B=(buffer)malloc(k*sizeof(char));
	int rulenu;
	memset(B,0,k);
	push("$");
	printf("Pushed to stack :%s\n",top->ch);
	//~ printf("%s",top->ch);
	tokenInfo ti;
	memset(ti.token,0,100);
	memset(ti.pattern,0,100);
	//~ printf("here1");
	ti=getNextToken(fp1,&B,k);
	//~ //ti=getNextToken(fp1,&B,k);
	//strcpy(ti.token,"PQR");
	//~ printf("token is %s",ti.token);
	node=(struct parseTree*)malloc(sizeof(struct parseTree));
	push(G.r[0][0]);
	printf("Pushed to stack :%s\n",top->ch);
	node->parent=NULL;
	strcpy(node->parentNodeSymbol,"ROOT");
	strcpy(node->token,top->ch);
	strcpy(node->lexemeCurrentNode,"-");
	//~ printf("%s",node->token);
	//~ node->lexeme=NULL;
	node->numchild=0;
	curr1=node;
	int x = strcmp("$","$");
	//~ printf("\nassert top is $%d\n",x);
	//~ printf("%d",getNonTermIndex(top->ch));
	while((strcmp((top->ch),"$"))!=0)
	{
		if(strcmp(top->ch,"EPSILON")==0)
		{
			printf("Popping from stack :%s\n",top->ch);
			pop();
		}
		else if(getNonTermIndex(top->ch)!=-1)
		{
			//~ printf("non term of %s index is %d\ntermindex of %s is %d\n",top->ch,getNonTermIndex(top->ch),ti.token,getTermIndex(ti.token));
			rulenu=T[getNonTermIndex(top->ch)][getTermIndex(ti.token)];
			if(rulenu==-1)
			{
				printf("Syntactic error");
				break;
			}
			else
			{
				gindex=1;
				//~ printf("\n%d\n",strcmp(G.r[3][2],"\0"));
				while(strcmp(G.r[rulenu][gindex],"\0")!=0)
				{
					gindex++;
					//~ printf("gindex is %d\n",gindex);
				}
				int numOfc=gindex-1;
				curr1->numchild=numOfc;
				parseTree* tempnode=curr1;
				printf("Popping from stack :%s\n",top->ch);
				pop();
				while(gindex>1)
				{
					gindex--;
					push(G.r[rulenu][gindex]);
					printf("Pushed to stack :%s\n",top->ch);
					//~ printf("gindex is %d\n",gindex);
					curr1->children[numOfc-gindex]=(struct parseTree*)malloc(sizeof(struct parseTree));
					curr1=curr1->children[numOfc-gindex];
					curr1->childIndex=numOfc-gindex;
					strcpy(curr1->lexemeCurrentNode,"-");
					curr1->parent=tempnode;
					strcpy(curr1->parentNodeSymbol,tempnode->token);
					//~ curr1=(struct parseTree*)malloc(sizeof(struct parseTree));
					strcpy(curr1->token,top->ch);
					curr1=curr1->parent;
					//~ curr1->lexeme=NULL;
					//~ printf("is%d",numOfc-gindex);
				}
				curr1=curr1->children[numOfc-1];
				//~ printf("parent of current node is %s",curr1->parentNodeSymbol);
				printf("pointing to %s\n",curr1->token);
			}
		}
	else if(getTermIndex(top->ch)!=-1)
	{
		if(strcmp((top->ch),ti.token)==0)
		{
			//~ printf("%s",top->ch);
			printf("popping from stack :%s\n",top->ch);
			pop();
			curr1->isLeafNode=1;
			curr1->lineno=ti.line_numb;
			strcpy(curr1->lexemeCurrentNode,ti.pattern);
			//~ printf("%s",top->ch);
			int temp1=curr1->childIndex;
			if(temp1==0)
			{
				curr1=curr1->parent;
			}
			else
			{
				curr1=curr1->parent->children[temp1-1];
			}
			printf("pointing to %s\n",curr1->token);
			//~ printf("curr1->sibling is %s",curr1->token);
			ti=getNextToken(fp1,&B,k);
		}
		else
		{
			printf("Syntactic error");
			break;
		}
	}
	else
	{
		printf("Unknown Pattern %s\n",top->ch);
		printf("%d\n",getNonTermIndex(top->ch));
		break;
		}
	}
	return curr1;
}
void printParseTree(parseTree*  PT, char *outfile)
{
	FILE* f =fopen("output","w");
	int i;
	if(PT->numchild==0)
	{
		printf("lexemeCurrentNode: %s\nlineno %d\ntoken %s\nparentNodeSymbol: %s\nisLeafNode(0=No,1=Yes): %d\n",PT->lexemeCurrentNode,PT->lineno,PT->token,PT->parentNodeSymbol,PT->isLeafNode);//tree not complete, so non terminals are labeled as leaf nodes
		printf("\n");
		fprintf(f,"lexemeCurrentNode: %s\nlineno %d\ntoken %s\nparentNodeSymbol: %s\nisLeafNode(0=No,1=Yes): %d\n",PT->lexemeCurrentNode,PT->lineno,PT->token,PT->parentNodeSymbol,PT->isLeafNode);//tree not complete, so non terminals are labeled as leaf nodes
		fprintf(f,"\n");
		return;
	}
	else
	{
		for(i=0;i<PT->numchild;i++)
		{
			printf("lexemeCurrentNode: %s\nlineno %d\nNodeSymbol %s\nparentNodeSymbol: %s\nisLeafNode(0=No,1=Yes): %d\n",PT->lexemeCurrentNode,PT->lineno,PT->token,PT->parentNodeSymbol,PT->isLeafNode);
			printf("\n");
			fprintf(f,"lexemeCurrentNode: %s\nlineno %d\nNodeSymbol %s\nparentNodeSymbol: %s\nisLeafNode(0=No,1=Yes): %d\n",PT->lexemeCurrentNode,PT->lineno,PT->token,PT->parentNodeSymbol,PT->isLeafNode);
			fprintf(f,"\n");
			printParseTree(PT->children[i],"output");
		}
	}
	//~ fclose(f);
}
int main()
{
	//~ printf("here");
	grammar G;
	FILE* fp =fopen("Grammar","r");
	int i,j;
	char string[1000];
	i=0;
	while(!feof(fp)) {
		if (fgets(string,1000,fp))
		{
			printf("%s",string);
			j=0;
			char* token = strtok(string, " ");
			//printf("I am token%s\n",token);
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
	fclose(fp);
	int s,u;
	u=0;
	//~ for(s=0;s<80;s++)
	//~ {
		//~ while(strcmp(G.r[s][u],"\0")!=0)
		//~ {
			//~ printf("%s\t",G.r[s][u]);
			//~ u++;
		//~ }
		//~ printf("\n");
	//~ }
	int numofrules=i;
	//~ printf("grammar is %s\n",G.r[0][0]);
	
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
	//~ FILE* fpw = fopen("abc.txt","w");
	createParseTable(G,t,ffset,numofrules);
	//~ for(i=0;i<47;i++)
	//~ {
		//~ for(j=0;j<39;j++)
		//~ {
			//~ fprintf(fpw,"%d\t",t[i][j]);
		//~ }
		//~ fprintf(fp,"\n");
	//~ }
	 parseTree* pt=parseInputSourceCode("testg",t,G);
	 pt=node;
	 printParseTree(pt,"output");
	 
	return 0;
}
