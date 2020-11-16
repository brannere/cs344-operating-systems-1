/**
 * Prgram Filename: plus_sign_thread.c
 * Author: Erick Branner
 * Date: 16 November 2020
 * Description: implementation of functions used by plus sign thread
 * Input:
 * Output:
 *
*/

#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "./plus_sign_thread.h"


/* Replace first occurace*/
/* Assumes both args are not null */
/* Returns the original string if not found */
/* This leaks an incredible amount of memory */
char* _str_replace(char* dest, char* word){

	int w_len = strlen(word);
	char* new_d = NULL;
	char* remainder = NULL;
	for(int i = 1; i < strlen(dest); i++){
		if(dest[i] == 43 && dest[i-1] == 43){ // plus sign
			// fprintf(stdout, "Found ++ pair\n");
			new_d = calloc((strlen(dest) + w_len)+1, sizeof(char));
			/* copy to idx(s) where ++ was found */
			for(int j = 0; j < i-1; j++){
				// fprintf(stdout,"jloop\n");
				new_d[j] = dest[j];
			}
			/* Now append the word */
			strcat(new_d, word);
			if(i == strlen(dest) -1){
				// fprintf(stdout, "is at end\n");
				// if(dest!=NULL) free(dest);
				return new_d;
			}else{
				/* The remainder of the string to add is just past (i+1) the $$ pair */
				remainder = &dest[i+1]; 
				strcat(new_d, remainder);
				// fprintf(stdout, "new_d: %s\n", new_d);
				// if(dest!=NULL) free(dest);
				return _str_replace(new_d, word);
			}
			return NULL;
		}
	}
	return dest;
}