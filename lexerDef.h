typedef int buffersize;
typedef char* buffer;
struct tokenInfo
{
	char pattern[100];
	char* token;
	int line_numb;
};
typedef struct tokenInfo tokenInfo;
