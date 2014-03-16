#include  "lexer.h"
typedef char* rules[100][300];
//typedef unsigned long long int Set ;

typedef char* Set[89][100];
struct grammar
{
	rules r;
};
typedef struct grammar grammar;
typedef int Table[47][39];
struct stack
{
	char ch[100];
	struct stack* next;
};
typedef struct stack stack;
stack* top=NULL;
stack* head=NULL;
struct parseTree
{
	struct parseTree* children[20];
	struct parseTree* parent;
	char token[100];
	char lexemeCurrentNode[100];
	int numchild;
	int childIndex;
	int lineno;
	char parentNodeSymbol[100];
	int isLeafNode;
};
typedef struct parseTree parseTree;
parseTree* node;
parseTree* curr1;
