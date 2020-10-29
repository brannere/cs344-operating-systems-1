#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./cmd_line.h"


/* Replace first occurace*/
/* Assumes both args are not null */
/* Returns the original string if not found */
/* This leaks an incredible amount of memory */
char* _str_replace(char* dest, char* word){

	int w_len = strlen(word);
	char* new_d = NULL;
	char* remainder = NULL;
	for(int i = 1; i < strlen(dest); i++){
		if(dest[i] == 36 && dest[i-1] == 36){
			// fprintf(stdout, "Found $$ pair\n");
			new_d = calloc((strlen(dest) + w_len)+1, sizeof(char));
			/* copy to idx(s) where $$ was found */
			for(int j = 0; j < i-1; j++){
				// fprintf(stdout,"jloop\n");
				new_d[j] = dest[j];
			}
			/* Now append the word */
			strcat(new_d, word);
			if(i == strlen(dest) -1){
				// fprintf(stdout, "is at end\n");
				// if(dest!=NULL) free(dest);
				return new_d;
			}else{
				/* The remainder of the string to add is just past (i+1) the $$ pair */
				remainder = &dest[i+1]; 
				strcat(new_d, remainder);
				// fprintf(stdout, "new_d: %s\n", new_d);
				// if(dest!=NULL) free(dest);
				return _str_replace(new_d, word);
			}
			return NULL;
		}
	}
	return dest;
}


/* Create and return a cmd line struct */
/* Null terminated string */
// might need one more command line arg space (for null)
struct cmd_line* cmd_line_process(char* line){
	struct cmd_line* output = malloc(sizeof(struct cmd_line));
	output->len = 0;
	char pid[256];
	sprintf(pid, "%d", getpid());

	// maybe set output->args to null
	// For use with strtok_r
  char* saveptr = NULL;
	char* flagptr = line; 
	char* token;
	char* result = NULL; // for use with _str_replace
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
				result = _str_replace(token, pid);
				// output->args[i] = calloc(strlen(token)+1, sizeof(char));
				output->args[i] = calloc(strlen(result)+1, sizeof(char));
				// strcpy(output->args[i], token);
				strcpy(output->args[i], result);
				output->len++;
				// output->args[i+1] = NULL;
				fprintf(stdout, "args[%d]: %s\n", i, output->args[i]);
				// free(result);
			}
			output->args[output->len] = NULL;
		}
	}
	return output;
}



/* Expand instances of $$ with current process id */
struct cmd_line* cmd_line_expand(struct cmd_line* l){
  // char* pch; // for use with strstr
	// int pairs = 0;
	// char* res = NULL;
	// char* gen = NULL;
	// char pid[256];
	// sprintf(pid, "%d", getpid());
	// for(int i = 0; i < l->len; i++){
	// 	res = _str_replace(l->args[i], pid);
	// 	free(l->args[i]);

	// }
	return l;
}


void cmd_line_free(struct cmd_line* c){

	for(int i = 0; i < c->len; i++){
		if(c->args[i] != NULL) free(c->args[i]);
	}
	if(c != NULL) free(c);
	return; 
}
