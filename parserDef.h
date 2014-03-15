#include  "lexer.h"
typedef char* rules[100][200];
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
	char* ch;
	struct stack* next;
};
typedef struct stack stack;
stack* top=NULL;
stack* head=NULL;
struct parseTree
{
	struct parseTree* children[20];
	char* child;
	int numchild;
};
typedef struct parseTree parseTree;
