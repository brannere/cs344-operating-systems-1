


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./prog.h"

#define BUFF_SIZE 2048
#define MAX_ARGS 513 /* +1 from max to add null*/

struct cmd_line{
	char* args[MAX_ARGS];	
	int len;

};


/* Create and return a cmd line struct */
/* Null terminated string */
// might need one more command line arg space (for null)
struct cmd_line* cmd_line_process(char* line){
	struct cmd_line* output = malloc(sizeof(struct cmd_line));
	output->len = 0;
	// maybe set output->args to null
	// For use with strtok_r
  char* saveptr = NULL;
	char* flagptr = line; 
	char* token;
	int i; 
	
	// the first token is the title
	/* 	Set flagptr to null after first iteration to ensure strtok 
			works for the remaining interations*/
  for(	i = 0, flagptr = line;
				token != NULL; flagptr = NULL, i++)
	{
		
		token = strtok_r(flagptr, " \n", &saveptr);
		if(token != NULL){
			output->args[i] = calloc(strlen(token)+1, sizeof(char));
			strcpy(output->args[i], token);
			output->len++;
			// fprintf(stdout, "args[%d]: %s\n", i, output->args[i]);
		}
	}
	fprintf(stdout, "len: %d\n", output->len);
	return output;
}

void cmd_line_free(struct cmd_line* c){

	for(int i = 0; i < c->len; i++){
		if(c->args[i] != NULL) free(c->args[i]);
	}
	if(c != NULL) free(c);
	return; 
}

void main_proc(){
	char PS1[] = ": ";
	char* buff = malloc(sizeof(char)*BUFF_SIZE);
	size_t buffsize = BUFF_SIZE;
	struct cmd_line* foo; 
	int ex = 0;
	
	while(ex != 1){
		memset(buff, '\0', BUFF_SIZE);
		fprintf(stdout, PS1);
		getline(&buff, &buffsize, stdin);
		foo = cmd_line_process(buff);
		if(strcmp(foo->args[0], "exit") == 0) ex = 1;
		cmd_line_free(foo);
	}
	
	free(buff);
	return;
}
