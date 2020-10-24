#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./cmd_line.h"

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
	return output;
}

void cmd_line_free(struct cmd_line* c){

	for(int i = 0; i < c->len; i++){
		if(c->args[i] != NULL) free(c->args[i]);
	}
	if(c != NULL) free(c);
	return; 
}