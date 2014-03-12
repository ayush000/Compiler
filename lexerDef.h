typedef int buffersize;
typedef char buffer[1000];
struct tokenInfo
	{
		char pattern;
		char token;
		struct tokenInfo* next;
	};
