/**
 * Prgram Filename: line_sep.c
 * Author: Erick Branner
 * Date: 16 November 2020
 * Description: Implementation of code used by line sepration thread
 * Input:
 * Output:
 *
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./line_sep.h"

void char_replace(char* source, const int c, const int t){
	/* 	If the current index is the char to change, 
			change its value */
	for(int i = 0; i < strlen(source); i++){
		if(source[i] == c){
			source[i] = t;
		}
	}
	return;
}