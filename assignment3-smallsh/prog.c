


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./prog.h"
#include "./cmd_line.h"

#define BUFF_SIZE 2048
// #define MAX_ARGS 513 /* +1 from max to add null*/



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
