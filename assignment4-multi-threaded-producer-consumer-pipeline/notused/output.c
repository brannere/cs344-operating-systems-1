/* NOT USED */

#include "./output.h"
#include "./input.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* really hacky solution for solving an extra newline in the output */
int called = false;

/* deletes history when printed */
void write_line(struct input* in){
	int i = 0;
	char* tmp = NULL;
	if(in->stop_reading == true){
		fprintf(stdout, "\n");
	}
	else{

		if(strlen(in->history) % OUTPUT_LEN == 0 && strlen(in->history) != 0){
			// fprintf(stdout, "printing multiple of %d\n", OUTPUT_LEN);
			/* Multiple of OUTPUT_LEN (80), write everything */
			// fprintf(stdout, "%s\n", in->history);
			for(i = 0; i < strlen(in->history); i++){
				if(in->start_flag == false){
					in->start_flag = true;
				}else{
					if(i % OUTPUT_LEN == 0) fprintf(stdout, "\n");
				}
				fprintf(stdout, "%c", in->history[i]);
			} 
			/* Clean history */
			memset(in->history, '\0', strlen(in->history));
		}
		else if(strlen(in->history) < OUTPUT_LEN){
			// fprintf(stdout, "less OUTPUT_LEN; do nothing\n");
		}
		else{
			// fprintf(stdout, "\nOUTPUT\n");
			for
			(
				i = 0;
				i < (strlen(in->history) - ((strlen(in->history))%OUTPUT_LEN));
				i++
			)
			{
				if(in->start_flag == false){
					in->start_flag = true;
				}else{
					if(i % OUTPUT_LEN == 0) fprintf(stdout, "\n");
				}
				fprintf(stdout, "%c", in->history[i]);
				// if(i % OUTPUT_LEN == 0) fprintf(stdout, "\n");
				// called = true; /* this is really hacky but it works for my purposes */
				// fprintf(stdout, "%c", in->history[i]);
			} 
			// fprintf(stdout, "\n");
			// fprintf(stdout, "i ended with: %d\n", i);
			// fprintf(stdout, "last char seen: %c\n", in->history[i]);

			tmp = calloc(strlen(&in->history[i]), sizeof(char));
			strcpy(tmp, &in->history[i]);
			// fprintf(stdout, "remaining string: %s\n", tmp);
			memset(in->history, '\0', strlen(in->history));
			strcpy(in->history, tmp);
			free(tmp);
		}
	}

	return; 
}
