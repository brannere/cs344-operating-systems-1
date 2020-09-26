#ifndef MOVIE_H
#define MOVIE_H

struct movie;

// functions that act on movie
struct movie* movie_create(char* curr_line);
void movie_free(struct movie* remove);
#endif
