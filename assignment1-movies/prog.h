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
#include "./movie.h"

unsigned int is_int(char* str);
int get_int(char* prompt, int hi, int low);
void show_options();
void choose_from_year(struct movie* movies);
void show_highest_rate(struct movie* movies);
void show_specif_lang(struct movie* movies);
void main_loop(struct movie* movies);
//error handling prompt
//need a string input function
#endif
