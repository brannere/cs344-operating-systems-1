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

	if(strcmp(line, "\n") != 0){
  	for(	i = 0, flagptr = line;
					token != NULL; flagptr = NULL, i++)
		{

			token = strtok_r(flagptr, " \n", &saveptr);
			if(token != NULL){
				output->args[i] = calloc(strlen(token)+1, sizeof(char));
				strcpy(output->args[i], token);
				output->len++;
				// output->args[i+1] = NULL;
				// fprintf(stdout, "args[%d]: %s\n", i, output->args[i]);
			}
			output->args[output->len] = NULL;
		}
	}
	return output;
}


/* Expand instances of $$ with current process id */
struct cmd_line* cmd_line_expand(struct cmd_line* l){
  // char* pch; // for use with strstr

	fprintf(stdout, "curr proc id: %d\n", getpid());
	for(int i = 0; i < l->len; i++){	
		for(int j = 1; j < strlen(l->args[i]); j++){
			if(l->args[i][j] == 36 && l->args[i][j-1] == 36){
				fprintf(stdout, "Found $$ pair\n");
			}
		}
	}
  return l;
}


void cmd_line_free(struct cmd_line* c){

	for(int i = 0; i < c->len; i++){
		if(c->args[i] != NULL) free(c->args[i]);
	}
	if(c != NULL) free(c);
	return; 
}
