/**
 * Prgram Filename: cmd_line.c
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: main functionality of smallsh
 * Input:
 * Output:
 *
*/

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

/* Returns outputfile name, null if none exists */
char* _inf(struct cmd_line* l){
	char* file = NULL;
	for(int i = 0; i < l->len; i++){
		if(strcmp(l->args[i], "<") == 0){
			// fprintf(stdout, "Found <:\n");
			if(i == l->len-1 || i == 0){
				file = NULL;
			}else {
				file = l->args[i+1];
			}
		}
	}
	return file;
}

/* Returns inputfile name, null if none exists */
char* _outf(struct cmd_line* l){
	char* file = NULL;
	for(int i = 0; i < l->len; i++){
		if(strcmp(l->args[i], ">") == 0){
			// fprintf(stdout, "Found >:\n");
			if(i == l->len-1 || i == 0){
				file = NULL;
			}else {
				file = l->args[i+1];
			}
		}
	}
	return file;
}

void _remove(struct cmd_line* l, char* word){
	int removed = 0;
	/* For each letter in each word, remove the word  */	
	for(int i = 0; i < l->len; i++){
		if(strcmp(l->args[i], word) == 0){
			removed++;
			// fprintf(stdout ,"i: %d\n", i);
			for(int j = i; j < l->len; j++){
				if(l->args[j+1] != NULL){
					// fprintf(stdout, "on %d changed %s to ",i, l->args[j]);
					free(l->args[j]);
					l->args[j] = calloc(strlen(l->args[j+1])+1, sizeof(char));
					strcpy(l->args[j], l->args[j+1]);
					fprintf(stdout, "%s\n", l->args[j]);
				}else l->args[j] = NULL;
			}
		}
		l->len = l->len - removed;
	}
	return; 
}

/* Create and return a cmd line struct */
/* Null terminated string */
// might need one more command line arg space (for null)
struct cmd_line* cmd_line_process(char* line, int* fg_mode){
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
				// fprintf(stdout, "args[%d]: %s\n", i, output->args[i]);
				// free(result);
				// output->in = NULL;
			}
			output->args[output->len] = NULL;
			 
		}
		output->in = _inf(output);
		// fprintf(stdout, "in file: %s\n", output->in);
		output->out = _outf(output);
		// fprintf(stdout, "outf: %s\n", output->out);

		/* If not foreground only mode */
		if(*fg_mode == false){
			if(output->len != 0){
				// fprintf(stdout, "len: %d\n", output->len);
				if(strcmp(output->args[output->len-1], "&") == 0){
					// fprintf(stdout, "bg mode\n");
					_remove(output, "&");
					output->bg = true;
				}else{
					// fprintf(stdout, "not bg mode\n");
					output->bg = false;
				}
			}
		}
		else{ /* remove '&' (ignore it)*/
			if(strcmp(output->args[output->len-1], "&") == 0){
				_remove(output, "&");
			}
			output->bg = false; 
		}
	}
	return output;
}


/**
 * Function: cmd_line_strip()
 * Description: Interface function that calls helper function to 
		remove a specified word from the cmd line
 * Parameters: a command line, word to remove 
 * Pre-Conditions: 
 * Post-Conditions: updates length, args string
 */
void cmd_line_strip(struct cmd_line* l, char* word){
	_remove(l, word);
	return;
}

/**
 * Function: cmd_line_free() 
 * Description: Frees all memory associated with a command line struct
 * Parameters:
 * Pre-Conditions:
 * Post-Conditions: Memory freed
 */

void cmd_line_free(struct cmd_line* c){

	for(int i = 0; i < c->len; i++){
		if(c->args[i] != NULL) free(c->args[i]);
	}
	if(c != NULL) free(c);
	return; 
}
