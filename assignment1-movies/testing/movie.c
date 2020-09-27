#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct movie{
    char* title;
    int year; 
    char* langs;
    double rating;
    struct movie* next;
};

// functions that act on movies

/*struct movie* movie_create(char* curr_line){
    struct movie* curr_movie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char* saveptr;
    //char* year;
    //char* rating;

    // the first token is the title
    char* token = strtok_r(curr_line, ",", &saveptr);
    curr_movie->title = calloc(strlen(token)+1, sizeof(char));
    strcpy(curr_movie->title, token);

    // the next token is the year 
    token = strtok_r(NULL, ",", &saveptr);
    //year = calloc(strlen(token)+1,sizeof(char));
    //strcpy(year, token);
    //curr_movie->year = malloc(sizeof(int));
    curr_movie->year = atoi(token);

    // the next token are the languages
    token = strtok_r(NULL, ",", &saveptr);
    curr_movie->langs = calloc(strlen(token)+1,sizeof(char));
    strcpy(curr_movie->langs, token);

    // the last toke is the rating
    token = strtok_r(NULL, ",", &saveptr);
    //rating = calloc(strlen(token)+1,sizeof(char));
    //strcpy(rating, token);
    //curr_movie->rating = malloc(sizeof(double));
    curr_movie->rating = atof(token);
    curr_movie->next = NULL; 
    printf( "%s\t%d\t%s\t%f\n", curr_movie->title, curr_movie->year, 
            curr_movie->langs, curr_movie->rating);
    return curr_movie;
}*/

// assumes the movie to remove exists and is not null
void movie_free_all(struct movie* head){
    struct movie* tmp = head;
    struct movie* rmv = NULL;

    while(tmp != NULL){
        rmv = tmp;
        free(rmv->langs);
        free(rmv->title);
        free(rmv);
        tmp = tmp->next;
    }
    return;
}
