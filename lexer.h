#ifndef LEXERDEF_H
#define LEXERDEF_H
#include "lexerDef.h"
extern FILE *getStream(FILE *fp,buffer *B, buffersize k);
extern tokenInfo getNextToken(FILE *fp,buffer *B,buffersize k);
#endif
