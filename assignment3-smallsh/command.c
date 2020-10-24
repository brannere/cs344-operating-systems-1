#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./cmd_line.h"
#include "./globals.h"
#include "./command.h"



int is_comment(struct cmd_line* l){
	// fprintf(stdout, "args[0][0]: %s\n",l->args[0] );
	if(l->args[0][0] == 35){
		return true; 
	} else return false;

}

int handle_input(struct cmd_line* line){

	if(is_comment(line) == true){
		fprintf(stdout, "is comment\n");
	} else fprintf(stdout, "is not comment\n");

	return -1; 
}

// int fork_t(){
// 	pid_t spawnpid = -5;
// 	int intVal = 10;
//   // If fork is successful, the value of spawnpid will be 0 in the child, the child's pid in the parent
// 	spawnpid = fork();
// 	switch (spawnpid){
// 		case -1:
//       // Code in this branch will be exected by the parent when fork() fails and the creation of child process fails as well
// 			perror("fork() failed!");
// 			exit(1);
// 			break;
// 		case 0:
//       // spawnpid is 0. This means the child will execute the code in this branch
// 			intVal = intVal + 1;
// 			fprintf(stdout, "I am the child! intVal = %d\n", intVal);
// 			break;
// 		default:
//       // spawnpid is the pid of the child. This means the parent will execute the code in this branch
// 			intVal = intVal - 1;
// 			fprintf(stdout, "I am the parent! ten = %d\n", intVal);
// 			break;
// 	}
// 	printf("This will be executed by both of us!\n");
// }