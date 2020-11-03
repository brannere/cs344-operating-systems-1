/**
 * Prgram Filename: main.c
 * Author: Erick Branner
 * Date: 20 October 2020
 * Description: Contains main function/process for assginment
 * Input: Strings of text relating to file names
 * Output: Files, directoires
 * 
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include "./prog.h"
#include "./globals.h"




void handle_SIGINT(int signo){
	char* message = "smallsh caught SIGINT; ignoring\n";
  // We are using write rather than printf
	write(STDOUT_FILENO, message, strlen(message));
	fflush(stdout);
	// sleep(10);
}


/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */

int main(int argc, char *argv[]){

	struct sigaction SIGINT_action = {{0}};

  // Fill out the SIGINT_action struct
  // Register handle_SIGINT as the signal handler
	SIGINT_action.sa_handler = handle_SIGINT;
  // Block all catchable signals while handle_SIGINT is running
	sigfillset(&SIGINT_action.sa_mask);
  // No flags set
	SIGINT_action.sa_flags = 0;

  // Install our signal handler
	sigaction(SIGINT, &SIGINT_action, NULL);


	main_proc();
	return EXIT_SUCCESS;                   
}
