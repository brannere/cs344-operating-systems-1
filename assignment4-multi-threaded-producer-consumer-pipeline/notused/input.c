
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
	n->start_flag = false;
	//memset history to null..?
	n->stop_reading = false; 
	// n->overflow = NULL;
	// memset(n->line, '\0', strlen(n->line));
	return n;
}

int _search_stop(struct input* in){

	// char* ret = NULL;

	// ret = strstr(in->line, STOP_SEQ);
	if(strcmp(in->line, STOP_SEQ) == 0){
		// fprintf(stdout, "stop found\n");
		return true;
	}
	else{
		// fprintf(stdout, "stop not found\n");
		return false;
	}
	return false;
}

void input_append_history(struct input* in){

	if(in->stop_reading == false){
		strcat(in->history, in->processed);
	}
	// fprintf(stdout, "history: %s\n", in->history);

	return;
}

void input_store_line(struct input* in, char* line){
	in->line = line; 
	in->len = strlen(line);
	in->stop_reading = _search_stop(in);
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