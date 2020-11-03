

#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./prog.h"
#include "./cmd_line.h"
#include "./command.h"
#include "./globals.h"
#include "./child_proc.h"
// #include "./signal.h"

// #define BUFF_SIZE 2048
// #define MAX_ARGS 513 /* +1 from max to add null*/

void main_proc(){
	char PS1[] = ": ";
	char* buff = malloc(sizeof(char)*BUFF_SIZE);
	size_t buffsize = BUFF_SIZE;
	struct cmd_line* foo; 
	int ex = 0;
	int prev_stat = 0;
	struct child_proc* children = NULL;
	children = child_proc_create();
	int catch = -1;
	/* so if getline returns -1, you want to check if 
	errno is EINTR, if it is re-print the prompt and try again*/
	while(ex != true){
		while(catch == -1){
			clear_procs(children);
			memset(buff, '\0', BUFF_SIZE);
			fflush(stdout);
			fprintf(stdout, PS1);
			catch = getline(&buff, &buffsize, stdin);
			if (catch == -1){
				clearerr(stdin);
			}
			fflush(stdout);
		}
		catch = -1;
		foo = cmd_line_process(buff);
		// foo = cmd_line_expand(cmd_line_process(buff));
		// if(strcmp(foo->args[0], "exit") == 0) ex = 1;

		ex = handle_input(foo, &prev_stat, children);
		cmd_line_free(foo);
	}
	//free the children IF are still alive in some exit function
	free(buff);
	// child_proc_print_all(children);
	exit_ka(children);
	child_proc_free_all(children);
	return;
}
