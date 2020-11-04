/**
 * Prgram Filename: command.c
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: main fufunctionality of smallsh command processing
 * Input: 
 * Output:
 *
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./cmd_line.h"
#include "./globals.h"
#include "./command.h"
#include "./child_proc.h"

/* Work in this order
Parse line(done) -> replace $$ with pid(done) -> handle comments(done) -> 
handle exit(done?), status(possible done?) -> handle cd(done) -> 
executing programs(done) -> 
redirection(done!) -> fg/bg(done) -> signals(done)
*/

/* For testing */
#include <limits.h>


/**
 * Function: _redir_in()
 * Description: redirects stdin the specificed file name
 * Parameters: pointer to command line sturct 
 * Pre-Conditions:
 * Post-Conditions: stdin changed
 */
/* Retruns true if file could be opened (same as null case), 
false otherwise  */
int _redir_in(struct cmd_line* l){
	
	if(l->in != NULL){
		// Open source file
  	int sourceFD = open(l->in, O_RDONLY);
  	if (sourceFD == -1) { 
  	    perror("source open()"); 
  	    exit(1); 
  	}
  	// Written to terminal
  	// printf("sourceFD == %d\n", sourceFD); 

  	// Redirect stdin to source file
  	int result = dup2(sourceFD, 0);
  	if (result == -1) { 
  	  perror("source dup2()"); 
  	  exit(2); 
  	}
		// cmd_line_proc_from_file(l);
		// fprintf(stdout, "RETURN T\n");
		return true;
	}
		// fprintf(stdout, "RETURN F\n");
	return false;
} 



/**
 * Function: _redir_out()
 * Description: redirects stdout the specificed file name
 * Parameters: pointer to command line sturct 
 * Pre-Conditions:
 * Post-Conditions: stdout changed
 */
/* Retruns true if file could be opened, false otherwise and null case */
int _redir_out(struct cmd_line* l){

	if(l->out !=NULL){
		// fprintf(stdout, "l->out: %s\n", l->out);
		int targetFD = open(l->out, O_WRONLY | O_CREAT | O_TRUNC, 0640);
  	if (targetFD == -1) {
  	  perror("open()");
  	  exit(1);
  	}
  	 // Currently printf writes to the terminal
  	// fprintf(stdout, "The file descriptor for targetFD is %d\n", targetFD);

  	// Use dup2 to point FD 1, i.e., standard output to targetFD
  	int result = dup2(targetFD, 1);
  	if (result == -1) {
  	  perror("dup2");
			// return false;  
  	  exit(2); 
  	}
		return true;
	}
	else{return false;}

	return true;
} 


/**
 * Function: clear_proces()
 * Description: Clears any finished child proceses
 * Parameters: head of child process list
 * Pre-Conditions:
 * Post-Conditions:chi
 */

void clear_procs(struct child_proc* head){

	int childStatus;
	// int childPid;

	/*Ignore the first because of the bug*/
	if(head->next == NULL){
		return;
	}else{
		for(struct child_proc* tmp = head->next;
				tmp!=NULL; tmp=tmp->next)
		{
		switch(waitpid(tmp->pid, &childStatus, WNOHANG)){
			// fprintf(stdout, "bacgrkoud pid: %d\n", tmp->pid);
				case -1:
					// perror("caught error\n");
					// fprintf(stdout, "case -1\n");
					break;
				case 0: 
					// fprintf(stdout, "case 0\n");
					break;
				default:	 
				// fprintf(stdout, "DEAFULT\n");
					if(WIFEXITED(childStatus)){
						// if(WEXITSTATUS(childStatus)){
							printf("background pid %d is done with exit status: %d\n", 
											tmp->pid, WEXITSTATUS(childStatus));
						// } 
						// else{
						//   printf("background pid %d is done with exit status: %d\n",
						// 					tmp->pid, WTERMSIG(childStatus));
						// }
					}
					/* Has it terminated abnormally yet? */
					else if(WIFSIGNALED(childStatus)){
							printf("background pid %d terminated with signal: %d\n",
							tmp->pid, WTERMSIG(childStatus));
					}
					break;
			}			
		}
	}
	return;
}

/**
 * Function: _io_handling()
 * Description: Changes and handles input and output redirection
 * Parameters: pointer to command line struct 
 * Pre-Conditions:
 * Post-Conditions: file input or output redirected
 */

void _io_handling(struct cmd_line* l){
	if (_redir_out(l) == true){
		// fprintf(stdout,"redirected out\n");
		/* remove > and file name from command line */
		cmd_line_strip(l, ">");
		cmd_line_strip(l, l->out);		
	}
	if(_redir_in(l) == true){
		// fprintf(stdout,"redirected in\n");
		/* remove < and file name from command line */
		cmd_line_strip(l, "<");
		cmd_line_strip(l, l->in);
	}
	return;
}

/**
 * Function: _io_handling_bg()
 * Description: handles all i/o redirection, including background processes
 * Parameters: pointer to command line struct
 * Pre-Conditions:
 * Post-Conditions: output or input redirected
 */

void _io_handling_bg(struct cmd_line* l){
	
	/* 	If background or forground haven't been redirected 
			and the command is to be a background process,
			redirect the input and output to FGBG_OUT (/dev/null)*/
	if(l->bg == true){
		if (_redir_out(l) == true){
			// fprintf(stdout,"redirected out\n");
			cmd_line_strip(l, ">");
			cmd_line_strip(l, l->out);		
		}
		else{
			l->out = FGBG_OUT;
			_redir_out(l);
		}

		if(_redir_in(l) == true){
			// fprintf(stdout,"redirected in\n");
			cmd_line_strip(l, "<");
			cmd_line_strip(l, l->in);
		}
		else{
			l->in = FGBG_OUT;
			_redir_in(l);
		}
	}
	else{
		_io_handling(l);
	}

	return;
}

/**
 * Function: fork_t
 * Description: Handles all forking of processes
 * Parameters: command line pointer, list of child processes, 
								pointers to sigaction structs (ignore, sigtstp, sigint)
 * Pre-Conditions:
 * Post-Conditions: New processes created; exactly one created and terminated or
										running in background
 */

int fork_t(	struct cmd_line* l, struct child_proc* head_childs,
						struct sigaction* ignore, struct sigaction* sigtstp,
						struct sigaction* sigint){
	pid_t spawnpid = -5;
	int intVal = 10;
	int childStatus;
  pid_t childPid;

	struct sigaction default_action = {{0}};
	default_action.sa_handler = SIG_DFL;

	// If fork is successful, the value of spawnpid will be 0 in the child, the child's pid in the parent
	spawnpid = fork();
	switch (spawnpid){
		case -1:
			perror("fork() failed!");
			exit(1);
			break;
		case 0:
      // spawnpid is 0. This means the child will execute the code in this branch
			intVal = intVal + 1;
			// fprintf(stdout, "I am the child! intVal = %d\n", intVal);

			/* The child should ignore SIGTSTP, and terminate with SIGINT*/
			sigaction(SIGTSTP, ignore, NULL);
			sigaction(SIGINT, &default_action, NULL);
			_io_handling_bg(l);
			if(l->bg == true){
				/* If the child is to be run in the background, ignore SIGINT */
				sigaction(SIGINT, ignore, NULL);
			}
			if(execvp(l->args[0], l->args) == -1){
				fprintf(stdout, "smallsh: %s: command not found\n", l->args[0]);
				exit(1);
			} 
			break;
		default:
      // spawnpid is the pid of the child. This means the parent will execute the code in this branch
			intVal = intVal - 1;
			// fprintf(stdout, "I am the parent! ten = %d\n", intVal);
			childPid = spawnpid;

			/* If the current command is to be in background mode */
			if(l->bg == true){
				/* Storing children in a linked list to check their status later*/
				head_childs = child_proc_insert(head_childs, childPid);
				childPid = waitpid(childPid, &childStatus, WNOHANG);
				fprintf(stdout, "bacgrkoud pid: %d\n", spawnpid);
			}else{
				childPid = waitpid(childPid, &childStatus, 0);
			}
			break;
	}
	return WEXITSTATUS(childStatus);
}


/* Used for testing */
/* Caller is responsible for freeding memory */
char* curr_dir(){
	/* Make Dynamic */
	char cwd[PATH_MAX];
	char* output = malloc(sizeof(char)*PATH_MAX);
	memset(output, '\0', PATH_MAX);
	memset(cwd, '\0', PATH_MAX);
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
  	// printf("Current working dir: %s\n", cwd);
		strcpy(output, cwd);
		return output;
  } 
	else {
  	perror("getcwd() error");
		free(output);
   	return NULL;	
  }
			// fprintf(stdout, "max: %d\t len: %d\n", PATH_MAX, strlen(cwd));
	return output;
}


/* Not used */
/* Assumes cmd_line length is more than 1*/
char* _change_dir_rel(struct cmd_line* l){
	char* curr = curr_dir();
	char* output = malloc(sizeof(char)*(strlen(curr) + strlen(l->args[1]) +1));
	strcpy(output, curr);
	strcat(output, "/");
	strcat(output, l->args[1]);
	strcat(output, "\0");
	return output; 
}

/**
 * Function: change_dir()
 * Description: cahnges current working directory to specifed path
 * Parameters: pointer to command line struct
 * Pre-Conditions:
 * Post-Conditions: working directory changed
 */
/* Ignores following arguments */
int change_dir(struct cmd_line* l){
	// char* relative = NULL;
	switch(l->len){
		case 0: 
			fprintf(stdout, "Too few arguments.. ");
			fprintf(stdout, "This shouldn't even be possible\n");
			exit(1); /* The caller of this function did something wrong if we get
									here -- stop everything */
			break;
		case 1:
		/* Go to home directory */
			// fprintf(stdout, "Home dir\n");
			// fprintf(stdout, "HOME: %s\n", getenv("HOME"));
			return chdir(getenv("HOME"));
			break;
		default: 
			/* Go to path supplied */
			// relative = _change_dir_rel(l);
			// fprintf(stdout, "rel returned: %s\n", relative);
			// fprintf(stdout, "Enough arguments\n");
			// if (chdir(l->args[1]) == -1){
			// 	fprintf(stdout, "Trying relative\n");
			// 	return chdir(relative);
			// }
			// fprintf(stdout, "returning\n");
			return chdir(l->args[1]);
			
			// return chdir(l->args[1]);
	}	

	return -1;
}

/**
 * Function: is_comment()
 * Description: Checks if current line is a comment or empty
 * Parameters: pointer to command line struct
 * Pre-Conditions: none
 * Post-Conditions: returns true if empty or comment, returns false otherwise
 */
/* also checks if is empty */
int is_comment(struct cmd_line* l){
	// fprintf(stdout, "args[0][0]: %s\n",l->args[0] );
	/* This ordering is possibly dangerous */
	// fprintf(stdout, "LEN: %d\n", l->len);
	if(l->len == 0){
		return true;
	}
	else if(l->args[0][0] == 35){
		return true; 
	} 
	else {
		return false;
	} 
	return false;
}


/**
 * Function: handle_input()
 * Description: Main constrol structure after commmand line has processed
 * Parameters: pointer to command line, child processes, pointer to status, 
	pointers to sigactions (ignore, sigitn, and sigtstp)
 * Pre-Conditions:
 * Post-Conditions: Returns exit status
 */

/* Returns true (1) if exit */
int handle_input(	struct cmd_line* line, 
									int* prev_stat, struct child_proc* head_childs,
									struct sigaction* ignore, struct sigaction* sigtstp,
									struct sigaction* sigint)
{
	int status = -2; 
	char* tmp = NULL;
	if(is_comment(line) == true){
		/* This is a comment, do nothing */
	} else {
		/* Is not a comment */
		if(strcmp(line->args[0], "exit") == 0){
			return true; /* return true or 1 to indicate we want to exit
											and call repsective exit functions */
		}//built in cd
		else if(strcmp(line->args[0], "cd") == 0){
			// fprintf(stdout, "change dirs\n");
			status = change_dir(line);
			if(status == -1){
				fprintf(stdout, "-smallsh: cd: %s: No such file or directory\n",
								line->args[1]);
			}
			tmp = curr_dir();
			// fprintf(stdout, "curr dir: %s\n", tmp);

		} // built in  status
		else if(strcmp(line->args[0], "status") == 0){
			if(*prev_stat){
      	printf("%d\n", *prev_stat);
    	} else{
    	  printf("%d\n", WTERMSIG(*prev_stat));
    	}
		}
		else{ // non built in functions
			// fprintf(stdout, "not built in\n");
			status = fork_t(line, head_childs, ignore, sigtstp, sigint);
			*prev_stat = status; 
		}
		/* clean up memory used */
		if(tmp!=NULL){ 
			free(tmp);
			tmp = NULL;
		}
	}
	return -1; // indicates to calling loop that user has not reuqested to exit
}

/**
 * Function: exit_ka()
 * Description: Kills all created processes if not terminated yet
 * Parameters: head of child process list
 * Pre-Conditions:
 * Post-Conditions: Child processes killed
 */
void exit_ka(struct child_proc* head){
	/*Ignore the first because of the bug*/
	int childStatus; 
	if(head->next == NULL){
		return;
	}else{
		for(struct child_proc* tmp = head->next;
				tmp!=NULL; tmp=tmp->next)
		{
			switch(waitpid(tmp->pid, &childStatus, WNOHANG)){
			// fprintf(stdout, "bacgrkoud pid: %d\n", tmp->pid);
				case -1:
					// perror("caught error\n");
					// fprintf(stdout, "case -1\n");
					break;
				case 0: 
					/* Kill them if they haven't ended yet*/
					fprintf(stdout, "smallsh: killing process: %d\n", tmp->pid);
					kill(tmp->pid, SIGTERM);
					break;
					/* Otherwise, Process has ended */
			}
		}
	}
	return;
}