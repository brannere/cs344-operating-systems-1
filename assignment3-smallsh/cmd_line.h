#ifndef CMD_LINE_H
#define CMD_LINE_H
// #define MAX_ARGS 513 /* +1 from max to add null*/
#include "./globals.h"


struct cmd_line{
	char* args[MAX_ARGS];	
	int len;
};

struct cmd_line* cmd_line_process(char* line);
void cmd_line_free(struct cmd_line* c);

#endif