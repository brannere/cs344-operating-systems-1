#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct movie{
    char* title;
    int year; 
    char* language;
    double rating; 
};


// functions that act on movies
