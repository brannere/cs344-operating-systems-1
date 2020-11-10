
#include "./globals.h"


struct input_ctx{

	char in_lines[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN+1];
	char* processed; /* Just print them out 80 at a time */
};