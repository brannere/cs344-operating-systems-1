#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Handler for SIGNINT
void handle_SIGINT(int signo){
	char* message = "Caught SIGINT, sleeping for 10 seconds\n";
	write(STDOUT_FILENO, message, 39);
  // Raise SIGUSR2. However, since this signal is blocked until handle_SIGNIT finishes, it will be delivered only when handle_SIGINT finishes
	raise(SIGUSR2);
  // Sleep for 10 seconds
	sleep(10);
}

// Handler for SIGUSR2
void handle_SIGUSR2(int signo){
	char* message = "Caught SIGUSR2, exiting!\n";
	write(STDOUT_FILENO, message, 25);
	exit(0);
}

int main(){
	struct sigaction SIGINT_action = {0}, SIGUSR2_action = {0}, ignore_action = {0};

  // Fill out the SIGINT_action struct
  // Register handle_SIGINT as the signal handler
	SIGINT_action.sa_handler = handle_SIGINT;
  // Block all catchable signals while handle_SIGINT is running
	sigfillset(&SIGINT_action.sa_mask);
  // No flags set
	SIGINT_action.sa_flags = 0;
  sigaction(SIGINT, &SIGINT_action, NULL);

  // Fill out the SIGUSR2_action struct
  // Register handle_SIGUSR2 as the signal handler
	SIGUSR2_action.sa_handler = handle_SIGUSR2;
  // Block all catchable signals while handle_SIGUSR2 is running
	sigfillset(&SIGUSR2_action.sa_mask);
  // No flags set
	SIGUSR2_action.sa_flags = 0;
  sigaction(SIGUSR2, &SIGUSR2_action, NULL);

  // The ignore_action struct as SIG_IGN as its signal handler
	ignore_action.sa_handler = SIG_IGN;

  // Register the ignore_action as the handler for SIGTERM, SIGHUP, SIGQUIT. So all three of these signals will be ignored.
	sigaction(SIGTERM, &ignore_action, NULL);
	sigaction(SIGHUP, &ignore_action, NULL);
	sigaction(SIGQUIT, &ignore_action, NULL);


  pid_t pid = getpid();
  printf("This process PID is %d\n", pid);
  printf("Send signals to the process using the kill command, e.g., kill -SIGTERM %d\n", pid);
  printf("SIGTERM, SIGHUP, and SIGQUIT are disabled, so will be ignored.\n");
	printf("SIGUSR2 signal will kill this program.\n");
	printf("SIGINT signal will cause the program to sleep 10 seconds, then will then kill this program by raising SIGUSR2.\n");

	while(1)
		pause();
  return 0;
}
