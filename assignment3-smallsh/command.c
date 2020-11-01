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
redirection -> fg/bg -> signals
*/

/* For testing */
#include <limits.h>

/****************/
/* 
	S1: https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
*/





/* Retruns true if file could be opened (same as null case), false otherwise  */

int _redir_in(struct cmd_line* l){

	return false;
} 

void _to_stdin(){
  int result = dup2(1, 1);
	if (result == -1) {
  	perror("dup2");
		// return false;  
  	exit(2); 
  }
}

/* Retruns true if file could be opened, false otherwise and null case */
int _redir_out(struct cmd_line* l){

	if(l->out !=NULL){
		fprintf(stdout, "l->out: %s\n", l->out);
		int targetFD = open(l->out, O_WRONLY | O_CREAT | O_TRUNC, 0640);
  	if (targetFD == -1) {
  	  perror("open()");
  	  exit(1);
  	}
  	 // Currently printf writes to the terminal
  	fprintf(stdout, "The file descriptor for targetFD is %d\n", targetFD);

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

/* THEN RESET */

int fork_t(struct cmd_line* l, struct child_proc* head_childs){
	pid_t spawnpid = -5;
	int intVal = 10;
	int childStatus;
  pid_t childPid;
	// int out = _redir_out(l);
	/* INPUT AND OUTPUT REDIRECTION HERE*/

	// If fork is successful, the value of spawnpid will be 0 in the child, the child's pid in the parent
	spawnpid = fork();
	switch (spawnpid){
		case -1:
      // Code in this branch will be exected by the parent when fork() fails and the creation of child process fails as well
			perror("fork() failed!");
			exit(1);
			break;
		case 0:
      // spawnpid is 0. This means the child will execute the code in this branch
			intVal = intVal + 1;
			// fprintf(stdout, "I am the child! intVal = %d\n", intVal);
			if (_redir_out(l) == true){
				fprintf(stdout,"redirected out\n");
				cmd_line_strip(l, ">");
				cmd_line_strip(l, l->out);		
			}else fprintf(stdout,"out not redirected\n");
			if(execvp(l->args[0], l->args) == -1) exit(1);
			break;
		default:
      // spawnpid is the pid of the child. This means the parent will execute the code in this branch
			intVal = intVal - 1;
			// fprintf(stdout, "I am the parent! ten = %d\n", intVal);
			childPid = spawnpid;
			head_childs = child_proc_insert(head_childs, childPid);
			// fprintf(stdout, "childPid: %d\n", childPid);
			childPid = wait(&childStatus);
			kill(childPid, SIGTERM);
			// _to_stdin();
			/* false is 0 */
			// if(WIFEXITED(childStatus)){
      // 	printf("Child %d exited normally with status %d\n", childPid, WEXITSTATUS(childStatus));
    	// } else{
    	//   printf("Child %d exited abnormally due to signal %d\n", childPid, WTERMSIG(childStatus));
    	// }
			// printf("Parent's waiting is done as the child with pid %d exited\n", childPid);
			break;
	}
	// printf("This will be executed by both of us!\n");
	return WEXITSTATUS(childStatus);
}

/* USE THIS FOR CHANGING DIRECTORIES */
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

/* Returns true (1) if exit */
int handle_input(	struct cmd_line* line, 
									int* prev_stat, struct child_proc* head_childs)
{
	int status = -2; 
	char* tmp = NULL;
	if(is_comment(line) == true){
		/* This is a comment, do nothing */
	} else {
		/* Is not a comment */
		// if(strcmp(foo->args[0], "exit") == 0) ex = 1;
		if(strcmp(line->args[0], "exit") == 0){
			return true; /* return true or 1 to indicate we want to exit
											and call repsective exit functions */
		}
		else if(strcmp(line->args[0], "cd") == 0){
			// fprintf(stdout, "change dirs\n");
			status = change_dir(line);
			if(status == -1){
				fprintf(stdout, "-smallsh: cd: %s: No such file or directory\n",
								line->args[1]);
			}
			tmp = curr_dir();
			// fprintf(stdout, "curr dir: %s\n", tmp);

		}
		else if(strcmp(line->args[0], "status") == 0){
			if(*prev_stat){
      	printf("%d\n", *prev_stat);
    	} else{
    	  printf("%d\n", WTERMSIG(*prev_stat));
    	}
			// fprintf(stdout, "%d\n",prev_stat);
		}
		else{
			// fprintf(stdout, "not built in\n");
			status = fork_t(line, head_childs);
			*prev_stat = status; 
		}
		if(tmp!=NULL){ 
			free(tmp);
			tmp = NULL;
		}
	}
	return -1; 
}

void exit_ka(struct child_proc* head){
	/*Ignore the first because of the bug*/
	if(head->next == NULL){
		return;
	}else{
		for(struct child_proc* tmp = head->next;
				tmp!=NULL; tmp=tmp->next)
		{
			fprintf(stdout, "killing: %d\n", tmp->pid);
			kill(tmp->pid, SIGTERM);
		}
	}
	return;
}