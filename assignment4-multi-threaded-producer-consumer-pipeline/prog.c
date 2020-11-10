/**
 * Prgram Filename: prog.c
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: Main functionality of smallsh
 * Input:
 * Output:
 *
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./prog.h"
#include "./input.h"
#include "./line_sep.h"

// char* get_input(){
// 	char* buff;
// 	size_t buffsize = MAX_IPT_LINE_LEN;
// 	getline(&buff, &buffsize, stdin); 
// 	return buff;
// }


void threading_prog(){

	char* buff = NULL;
	size_t buffsize = MAX_IPT_LINE_LEN;


	// char* curr_line = NULL;
	struct input* ipt_ctx = NULL;

	// curr_line = get_input();
	getline(&buff, &buffsize, stdin); 
	ipt_ctx = input_init();
	input_store_line(ipt_ctx, buff);
	char_replace(ipt_ctx->line, 'h', '@');
	fprintf(stdout, "line: %s\n", ipt_ctx->line);

	
	// free(buff);
	// input_read_line(ipt_ctx, curr_line);
	
	// fprintf(stdout, "got: %s\n", ipt_ctx->line);
	// fprintf(stdout, "len: %d\n", strlen(ipt_ctx->line));

	return; 
}