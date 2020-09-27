#ifndef MOVIE_H
#define MOVIE_H

struct movie;

// functions that act on movie
void movie_free(struct movie* remove);
struct movie* movie_create(char* curr_line);
struct movie* process_file(char* file_path);
void movie_free_all(struct movie* head);
void movie_print(struct movie* head, int rating);
void movie_print_all(struct movie* head, int rating);
void movie_show_from_year(struct movie* head, int year);
void movie_show_highest_rate(struct movie* movies);
void movie_show_specif_lang(struct movie* movies, char* lang);
#endif
