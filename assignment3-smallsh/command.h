#ifndef COMMAND_H
#define COMMAND_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./cmd_line.h"


// int fork_t();
int is_comment(struct cmd_line* l);
int handle_input(struct cmd_line* line);

#endif