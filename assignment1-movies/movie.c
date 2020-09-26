#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct movie{
    char* title;
    int year; 
    char* langs;
    double rating; 
};

// functions that act on movies

// assumes the movie to remove exists and is not null
void movie_free(struct movie* remove){
    if(remove->title != NULL){
        free(remove->title);
    }
    if(remove->langs != NULL){
        free(remove->langs);
    }
    return;
}
