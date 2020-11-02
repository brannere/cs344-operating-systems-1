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
	/* For each letter in each word, change > or < to " "  */	
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


/* Assume dup2 has been called and workd for changing stdout */
// void cmd_line_proc_from_file(struct cmd_line* l){
// 	char* buff = malloc(sizeof(char)*BUFF_SIZE);
// 	size_t buffsize = BUFF_SIZE;
// 	getline(&buff, &buffsize, stdin);
// 	fprintf(stdout, "we got: %s\n", buff);

// 	/* Copy data of first argument */
// 	l->infile_args[0] = calloc(strlen(l->args[0])+1, sizeof(char));
// 	strcpy(l->infile_args[0],l->args[0]);
// 	l->inf_len++;

// 	/* Read from file */
//   char* curr_line = NULL;
//   size_t len = 0;
//   ssize_t nread; 
//   char* token;
//   unsigned int counter = 0;

// 	char* saveptr = NULL;
// 	char* flagptr = NULL; 
// 	// char* token;
// 	char* result = NULL; // for use with _str_replace
// 	int i; 
	
  
// 	/* For each line, make a movie */
//   while((getline(&curr_line, &len, stdin)) != -1){
// 		/* For each line and for each word in that line */
// 	  for(	i = 1, flagptr = curr_line;
// 					token != NULL; flagptr = NULL, i++)
// 		{
// 			token = strtok_r(flagptr, " \n", &saveptr);
// 			if(token != NULL){
// 				l->infile_args[i] = calloc(strlen(token)+1, sizeof(char));
// 				// l->args[i] = calloc(strlen(result)+1, sizeof(char));
// 				// strcpy(output->args[i], token);
// 				strcpy(l->infile_args[i], result);
// 				l->len++;
// 				// output->args[i+1] = NULL;
// 				fprintf(stdout, "args[%d]: %s\n", i, l->infile_args[i]);
// 				// free(result);
// 				// output->in = NULL;
// 			}
// 			l->infile_args[l->inf_len] = NULL;
// 		}
// 		counter++;
// 	}
//   free(curr_line);

// 	return;
// }
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
		if(strcmp(output->args[output->len-1], "&") == 0){
			// fprintf(stdout, "bg mode\n");
			_remove(output, "&");
			output->bg = true;
		}else{
			// fprintf(stdout, "not bg mode\n");
			output->bg = false;
		}
	}
	return output;
}

void cmd_line_strip(struct cmd_line* l, char* word){
	_remove(l, word);
	return;
}


void cmd_line_free(struct cmd_line* c){

	for(int i = 0; i < c->len; i++){
		if(c->args[i] != NULL) free(c->args[i]);
	}
	if(c != NULL) free(c);
	return; 
}
