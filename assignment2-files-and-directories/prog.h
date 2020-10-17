/**
 * Prgram Filename: prog.h
 * Author: Erick Branner
 * Date: 12 October 2020
 * Description: Header file for prog.c 
 * Input:
 * Output:
 * 
*/

#ifndef PROG_H
#define PROG_H

unsigned int is_int(char* str);
int get_int(char* prompt);
int get_int_b(char* prompt, int hi, int low);
void show_options_main();
void main_loop();
void select_from_file(); 
char* curr_dir_largest();
char* curr_dir_smallest();
int create_file(char* filename);
char* generate_dir_name();
char* create_dir(char* name);
void process_movies(char* filename);

//error handling prompt
//need a string input function
#endif
