


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./prog.h"

void main_proc(){
	char PS1[] = ": ";
	char* buff = malloc(sizeof(char)*255);
	size_t buffsize = 255;
	int ex = 0;
	
	while(ex != 1){
		fprintf(stdout, PS1);
		getline(&buff, &buffsize, stdin);

	}
	



	return;
}
