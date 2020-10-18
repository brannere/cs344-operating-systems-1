/**
 * Prgram Filename: movie.c
 * Author: Erick Branner
 * Date: 12 October 2020
 * Description:	Source file for functions that act on
 * a movie struct
 * Input:
 * Output:
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./movie.h"

/**
 * The movies struct contains information 
 * related to a movie provided froma csv file. 
 * Language variables appear twice -- one is 
 * the full list directly from the file, the 
 * other is a representation of the languages 
 * without delimiters in a 2d char array. 
*/
// struct movie{
//     char* title;
//     int year;
//     char* langs;
//     double rating;
//     struct movie* next;
//     char lang_arr[5][20];
//     int num_langs; 
// };

/* Utilities */
/* 	
	These are helper functions and data strucutres 
	that assist with movie functions 
*/


/**
 * the _year_list structure is a linked list of integers
 * to be created alongside an exisitng list of movies; 
 * this strucutre assits in finding the max rating for
 * each year.
*/
struct _year_list{
    int val;
    struct _year_list* next; 
};


/**
 * Function: _member()
 * Description: Helper function that determines 
 * if n exists in the integer list
 * Parameters: a year list struct, number to find
 * Pre-Conditions: The list exists
 * Post-Conditions: Returns 1 if n exists, otherwise 
 * returns 0
 */

/* 1 = yes, 0 = no*/
int _member(struct _year_list* list, int n){
    struct _year_list* tmp = list; 
    while(tmp != NULL){
        if(tmp->val == n) return 1; 
        tmp = tmp->next;
    }
    return 0;
}

/**
 * Function: _count_langs()
 * Description: Counts the number of languages in the 
 * formatted string from the csv file
 * Parameters: The language string
 * Pre-Conditions: The language string exists and is 
 * in format [Lang1;Lang2;Lang3]
 * Post-Conditions: None
 */

int _count_langs(char* langs){
		/* There number of languages is the delimiter plus one */
    int semi = 0; 
    for(int i = 0; i < strlen(langs); i++){
        if(langs[i] == 59) semi++;
    }
    return semi+1; 
}


/**
 * Function: _create_year_set()
 * Description: Creates a set of all years from a movie list 
 * Parameters: A movie list
 * Pre-Conditions: The movie list exists 
 * Post-Conditions: Pointer returned to memory allocated from
 * list/set creation
 */

struct _year_list* _create_year_set(struct movie* movies){
    struct movie* tmp = movies;
    struct _year_list* head = NULL; 
    struct _year_list* tail = NULL; 
    /* Make a list (set) of all years */
    while(tmp != NULL){
        if(_member(head, tmp->year) == 0){
            struct _year_list* new_node = malloc(sizeof(struct _year_list));  
            new_node->val = tmp->year;
            new_node->next = NULL; // be careful...
            if(head == NULL){
                head = new_node;
                tail = new_node;
            }
            else{
                tail->next = new_node; 
                tail = new_node;
            }
        }
        tmp = tmp->next;
    }
    return head;
}

/**
 * Function: _free_year_list()
 * Description: Frees memory of a struct year list 
 * Parameters: year list struct
 * Pre-Conditions: The list exists
 * Post-Conditions: Memory that list used is freed
 */

void _free_year_list(struct _year_list* list){
    struct _year_list* tmp = NULL;
    for(tmp = list; tmp != NULL; tmp=tmp->next){
        if(tmp != NULL) free(tmp);
    }
    if(tmp!=NULL) free(tmp);
}

/* Main functionality*/

/**
 * Function: movie_create()
 * Description: Allocates a movie srtruct from a csv file line
 * Parameters: Line of a csv file
 * Pre-Conditions: String passed is in format --> 
 * Title,Year,[language1;language2],Rating Value
 * Post-Conditions: Pointer returned memory 
 * allocated for a movie
 */

struct movie* movie_create(char* curr_line){
    struct movie* curr_movie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char* saveptr;
    char* tmp_saveptr;
    char* year;
    char* rating;

    // the first token is the title
    char* token = strtok_r(curr_line, ",", &saveptr);
    curr_movie->title = calloc(strlen(token)+1, sizeof(char));
    strcpy(curr_movie->title, token);

    // the next token is the year 
    token = strtok_r(NULL, ",", &saveptr);
    year = calloc(strlen(token)+1,sizeof(char));
    strcpy(year, token);
    //curr_movie->year = malloc(sizeof(int));
    curr_movie->year = atoi(token);

    // the next token are the languages
    token = strtok_r(NULL, ",", &saveptr);
    curr_movie->langs = calloc(strlen(token)+1,sizeof(char));
    strcpy(curr_movie->langs, token);

    // the last toke is the rating
    token = strtok_r(NULL, ",", &saveptr);
    rating = calloc(strlen(token)+1,sizeof(char));
    strcpy(rating, token);
    //curr_movie->rating = malloc(sizeof(double));
    curr_movie->rating = atof(token);
    curr_movie->next = NULL;

		/* Process languages into 2d char array interface */
    curr_movie->num_langs = _count_langs(curr_movie->langs);
    char* tmp_tk = strtok_r(curr_movie->langs, "][;",&tmp_saveptr);
    strcpy(curr_movie->lang_arr[0], tmp_tk);
    for(int i = 1; i < curr_movie->num_langs; i++){
       tmp_tk = strtok_r(NULL, "][;", &tmp_saveptr);
       strcpy(curr_movie->lang_arr[i], tmp_tk);
    }

    free(rating);
    free(year);
    return curr_movie;
}

/**
 * Function: process_file()
 * Description: Processes file one line at a time
 * to store in a movie struct
 * Parameters: Path to a csv file
 * Pre-Conditions: First line of csv file need not be stored 
 * File exists and is in format -->
 * Title,Year,[language1;language2]
 * Post-Conditions: Returns pointer to head of movie list
 * memory allocated
 */

struct movie* process_file(char* file_path){
    FILE* movie_file = fopen(file_path, "r");
    char* curr_line = NULL;
    size_t len = 0;
    ssize_t nread; 
    char* token;
    int line1_flag = 0;
    unsigned int counter = 0;

    // head of linked list
    struct movie* head = NULL;
    // tail of linked list
    struct movie* tail = NULL;
    // void list_insert(the list, void* val)
    
		/* For each line, make a movie */
    while((nread = getline(&curr_line, &len, movie_file)) != -1){
        if(line1_flag != 0){ /* Skips the first line */
            struct movie* new_node = movie_create(curr_line);
            if(head == NULL){
                head = new_node;
                tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = new_node; 
            }
            counter++;
        }else line1_flag = 1;
    }
    free(curr_line);
    fclose(movie_file);
    printf("Processed file %s and parsed data for %d movies\n", file_path, counter);
    return head;
}

/**
 * Function: movie_free_all()
 * Description: Frees all movies in a list
 * Parameters: Head to a movie list
 * Pre-Conditions: List exists and tail points to null
 * Post-Conditions: Movie list freed
 */

void movie_free_all(struct movie* head){
    struct movie* tmp = head;
    struct movie* rmv = NULL;

    while(tmp != NULL){
        rmv = tmp;
        if(rmv->langs != NULL) free(rmv->langs);
        if(rmv->title != NULL) free(rmv->title);
        free(rmv);
        tmp = tmp->next;
    }
    return;
}

/**
 * Function: movie_print()
 * Description: Prints one movie 
 * Parameters: A movie to be printed, flag for rating
 * do be displayed or not to be displayed; if rating is 1, 
 * print the rating, otherwise don't print the rating 
 * Pre-Conditions: Movie exists
 * Post-Conditions: Movie printed to screen
 */

// rating 1, yes; otherwise no
void movie_print(struct movie* head, int rating){

    printf("%d ", head->year);
    if(rating==1)printf("%.1f ", head->rating);
    printf("%s\n", head->title);
    return;
}

/**
 * Function: movie_print_all()
 * Description: Prints all movies in a list
 * Parameters: Head of a movie list, rating flag 
 * Pre-Conditions: Movie exists 
 * Post-Conditions: Movies printed to screen
 */

void movie_print_all(struct movie* head, int rating){
    struct movie* tmp = head;
    while(tmp != NULL){
        movie_print(tmp, rating);
        tmp = tmp->next;
    }
    return;
}

/**
 * Function: movie_show_from_year()
 * Description: Shows movies from a specific year
 * Parameters: Head of a movie list, requested year
 * Pre-Conditions: Movies exists in memory
 * Post-Conditions: Prints movies, or none, to the screen
 */

void movie_show_from_year(struct movie* head, int year){
    struct movie* tmp = head; 
    int p_flag = 0;
    while(tmp != NULL){
        if(tmp->year == year){
            movie_print(tmp, 0);
            p_flag = 1;
        }
        tmp = tmp->next;
    }
    if(p_flag == 0) printf("No data about movies released in the year %d\n", year);
    return;
}


/**
 * Function: movie_show_highest_rate()
 * Description: Shows highest rated movie from each year
 * Parameters: Movies list
 * Pre-Conditions: Movies exist in memory
 * Post-Conditions: Prints movies to the screen
 */

void movie_show_highest_rate(struct movie* movies){
		/* Make a set/list of all years */
    struct _year_list* year_set = _create_year_set(movies);  
    struct _year_list* y_tmp = NULL; 
    struct movie* m_tmp = NULL;
    struct movie* curr_max_m = NULL; 
    double max = 0;
    /* For each year, look over all movies, see if the year 
     * matches and find the max */
    for(y_tmp = year_set; y_tmp != NULL; y_tmp=y_tmp->next){
        for(m_tmp = movies; m_tmp != NULL; m_tmp = m_tmp->next){
            /* If it's the year we're looking for */
						if(m_tmp->year == y_tmp->val){
								/* compute max */
                if(m_tmp->rating > max){
                    max = m_tmp->rating; 
                    curr_max_m = m_tmp; 
                } 
            } 
        }
        movie_print(curr_max_m ,1);
        max = 0;
        curr_max_m = NULL;
    }
    _free_year_list(year_set);   
    return;
}

/**
 * Function: movie_show_specif_lang()
 * Description: Shows movies available in a specific language
 * Parameters: Movies list, requested language 
 * Pre-Conditions: Movies struct exists
 * Post-Conditions: Movies from that language, or none, are 
 * printed to the screen
 */

void movie_show_specif_lang(struct movie* movies, char* lang){
    struct movie* tmp = movies;
    int p_flag = 0;
    while(tmp != NULL){
        for(int i = 0; i < tmp->num_langs; i++){
            if(strcmp(tmp->lang_arr[i], lang) == 0){
                movie_print(tmp, 0);
                p_flag = 1;
            }
        }
        tmp = tmp->next; 
    } 
    if(p_flag == 0) printf("No data about movies released in %s\n", lang);
    return; 
}

/*int main(int argc, char *argv[]){
        if (argc < 2){
            printf("You must provide the name of the file to process\n");
            printf("Example usage: ./movies file.csv\n");
            return EXIT_FAILURE;                    
        }
        struct movie* movies = process_file(argv[1]);
        movie_free_all(movies);
        //printStudentList(list);
        //list_free_internal(movies, &movie_free);
        //list_free(movies);
        //free(movies);
        return EXIT_SUCCESS;                   
}*/
