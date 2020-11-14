#ifndef INPUT_H
#define INPUT_H
#include "./globals.h"

struct input{
	int len;
	char* line;
	char* processed;
	char history[MAX_IPT_LINE_LEN*MAX_IPT_LINE_NUM]; // ordered history of lines
	int stop_reading;
};


struct input* input_init();
void input_store_line(struct input* in, char* line);
void input_append_history(struct input* in);

#endif