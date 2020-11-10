
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "./input.h"

/* 	Responsibility of the calller to free memory associated
		with char* */
struct input* input_init(){

	struct input* n = malloc(sizeof(struct input));
	n->len = 0;
	n->line = NULL;
	// n->overflow = NULL;
	// memset(n->line, '\0', strlen(n->line));
	return n;
}

void input_store_line(struct input* in, char* line){
	in->line = line; 
	in->len = strlen(line);
	return;
	// for(int i = 0; i < strlen(line); i++){
	// 	if(in->len == 0 || in->len % OUTPUT_LEN != 0){
	// 		fprintf(stdout, "line[%d]: %c\n", i, line[i]);
	// 		in->len++; 
	// 		// fprintf(stdout, "write to overflow\n");
	// 	}
	// 	else if (in->len % OUTPUT_LEN == 0){
	// 		/* PROCESS AND WRITE */
	// 		fprintf(stdout, "PROCESS AND WRITE\n");
	// 		in->len++; 

	// 	}
		
	// }
}