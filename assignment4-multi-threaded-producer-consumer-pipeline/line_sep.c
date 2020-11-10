
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./line_sep.h"

void char_replace(char* source, const int c, const int t){
	for(int i = 0; i < strlen(source); i++){
		if(source[i] == c){
			fprintf(stdout, "hit\n");
			source[i] = t;
		}
	}
	return;
}