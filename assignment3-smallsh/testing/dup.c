#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){

  if (argc == 1){
      printf("Usage: ./main <filename to redirect stdout to>\n");
      exit(1);
  }

  int targetFD = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0640);
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
    exit(2); 
  }
  // Now whatever we write to standard out will be written to targetFD
  fprintf(stdout,"All of this is being written to the file using printf\n"); 
  return(0);
}