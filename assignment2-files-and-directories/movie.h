/**
 * Prgram Filename: movie.h
 * Author: Erick Branenr
 * Date: 12 October 2020
 * Description: Header file for movie.c and movie data type
 * Input:
 * Output:
 * 
*/

#ifndef MOVIE_H
#define MOVIE_H

/**
 * The movies struct contains information 
 * related to a movie provided froma csv file. 
 * Language variables appear twice -- one is 
 * the full list directly from the file, the 
 * other is a representation of the languages 
 * without delimiters in a 2d char array. 
*/
struct movie{
    char* title;
    int year;
    char* langs;
    double rating;
    struct movie* next;
    char lang_arr[5][20];
    int num_langs; 
};


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