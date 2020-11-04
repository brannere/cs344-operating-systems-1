/**
 * Prgram Filename: cmd_line.h
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: Interface file for cmd_line.c
 * Input:
 * Output:
 *
*/

#ifndef CMD_LINE_H
#define CMD_LINE_H
// #define MAX_ARGS 513 /* +1 from max to add null*/
#include "./globals.h"

/* 
	A struct that represents all components of a command comand entered 
	into the shell
*/
struct cmd_line{
	char* args[MAX_ARGS]; // number of arguments
	int len; // length of inner char* arr
	int status; // last status 
	char* out; // outputfile
	char* in; // input file 
	int bg; // bg process (used with predfeined true and false)
};

struct cmd_line* cmd_line_process(char* line, int* fg);
void cmd_line_free(struct cmd_line* c);
struct cmd_line* cmd_line_expand(struct cmd_line* l);
void cmd_line_strip(struct cmd_line* l, char* word);
void cmd_line_proc_from_file(struct cmd_line* l);

// char* _str_repalce(char* dest, char* word);

#endif