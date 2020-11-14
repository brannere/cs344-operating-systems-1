#ifndef INPUT_H
#define INPUT_H
#include "./globals.h"

struct input{
	int len;
	char* line;
	char* processed;
	int stop_reading;
};


struct input* input_init();
void input_store_line(struct input* in, char* line);

#endif