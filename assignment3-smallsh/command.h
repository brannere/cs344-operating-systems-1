/**
 * Prgram Filename: command.h
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: interface file for command.c
 * Input:
 * Output:
 *
*/

#ifndef COMMAND_H
#define COMMAND_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./cmd_line.h"
#include "./child_proc.h"


// int fork_t();
int is_comment(struct cmd_line* l);
int handle_input(	struct cmd_line* line, int* prev_stat, 
									struct child_proc* head_childs,
									struct sigaction* ignore, struct sigaction* sigtstp,
									struct sigaction* sigint);
void clear_procs(struct child_proc* head);
void exit_ka(struct child_proc* head);

#endif