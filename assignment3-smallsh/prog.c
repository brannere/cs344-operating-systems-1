/**
 * Prgram Filename: prog.c
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: Main functionality of smallsh
 * Input:
 * Output:
 *
*/

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

/* Toggle for foreground only mode */
int fg_only = false; 

/* SIGNAL HANDLERS */

/* SIGINT signal handler ignores signal */
void handle_SIGINT(int signo){
	char* message = "smallsh: caught SIGINT; ignoring\n";
  // We are using write rather than printf
	write(STDOUT_FILENO, message, 33);
	fflush(stdout);
	// sleep(10);
}

/* Toggle fg_mode on SIGTSTP */
void handle_SIGTSTP(int signo){
	char* message = NULL; 
	if(fg_only == true){
		fg_only = false;
		message = "smallsh: DISABLED: foreground only mode \n";
	}else{
		fg_only = true;
		message = "smallsh: ENABLED: foreground only mode  \n";
	} 
  // We are using write rather than printf
	write(STDOUT_FILENO, message, 41);
	fflush(stdout);
	// sleep(10);
}


/**
 * Function: main_proc()
 * Description: runs everything needed to process the shell
 * Parameters:
 * Pre-Conditions:
 * Post-Conditions: 
 */

void main_proc(){
	char PS1[] = ": ";
	char* buff = malloc(sizeof(char)*BUFF_SIZE);
	size_t buffsize = BUFF_SIZE;
	struct cmd_line* line; 
	int ex = 0;
	int prev_stat = 0;
	struct child_proc* children = NULL;
	children = child_proc_create();
	int catch = -1;

	/* Install signal handlers */

	/* SIGINT */
	struct sigaction SIGINT_action = {{0}};
	struct sigaction ignore_action = {{0}};
	ignore_action.sa_handler = SIG_IGN;


	SIGINT_action.sa_handler = handle_SIGINT;
	sigfillset(&SIGINT_action.sa_mask);
	// SIGINT_action.sa_flags = 0;
	SIGINT_action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &SIGINT_action, NULL);

	/* SIGSTP */
	struct sigaction SIGTSTP_action = {{0}};
	SIGTSTP_action.sa_handler = handle_SIGTSTP;
	sigfillset(&SIGTSTP_action.sa_mask);
	// SIGTSTP_action.sa_flags = 0;
	SIGTSTP_action.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);


	/****************************/

	while(ex != true){
		while(catch == -1){
			// fg_mode = fg_only;
			clear_procs(children);
			memset(buff, '\0', BUFF_SIZE);
			fflush(stdout);
			fprintf(stdout, PS1);
			/* Catch error if SIGTSTP or SIGINT are sent and reprompt */
			catch = getline(&buff, &buffsize, stdin);
			if (catch == -1){
				clearerr(stdin);
			}
			fflush(stdout);
		}
		catch = -1;
		/* Process command line and handle the arguments */
		line = cmd_line_process(buff, &fg_only);
		ex = handle_input(line, &prev_stat, children,&ignore_action,
											&SIGTSTP_action, &SIGINT_action);
		cmd_line_free(line);
	}
	/* Memory cleanup, kill ended */
	free(buff);
	exit_ka(children);
	clear_procs(children);
	child_proc_free_all(children);
	return;
}
