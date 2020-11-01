#ifndef CMD_LINE_H
#define CMD_LINE_H
// #define MAX_ARGS 513 /* +1 from max to add null*/
#include "./globals.h"


struct cmd_line{
	char* args[MAX_ARGS];
	char* infile_args[MAX_ARGS];
	// char* args_strip[MAX_ARGS];	
	// char args[MAX_ARGS][BUFF_SIZE];	
	int len;
	int inf_len;
	int status;
	char* out;
	char* in;
};

struct cmd_line* cmd_line_process(char* line);
void cmd_line_free(struct cmd_line* c);
struct cmd_line* cmd_line_expand(struct cmd_line* l);
void cmd_line_strip(struct cmd_line* l, char* word);
void cmd_line_proc_from_file(struct cmd_line* l);

// char* _str_repalce(char* dest, char* word);

#endif
