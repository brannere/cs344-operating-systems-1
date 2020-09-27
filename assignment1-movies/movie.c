#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./movie.h"
#include "./dynarray.h"
struct movie{
    char* title;
    int year;
    char* langs;
    double rating;
    struct movie* next;
};

struct movie* movie_create(char* curr_line){
    struct movie* curr_movie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char* saveptr;
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
    /*printf( "%s\t%d\t%s\t%f\n", curr_movie->title, curr_movie->year, 
            curr_movie->langs, curr_movie->rating);*/
    free(rating);
    free(year);
    return curr_movie;
}

// assumes that elements of the list are movies
/*void free_all_movies(struct list* list){

    struct link* tmp = list->head;
    
    while(tmp != NULL){
        movie_free(tmp->val);
        tmp = tmp->next;
    }
    return;
}*/

struct movie* process_file(char* file_path){
    FILE* movie_file = fopen(file_path, "r");
    char* curr_line = NULL;
    size_t len = 0;
    ssize_t nread; 
    char* token;
    //struct movie* new_node = NULL;
    int line1_flag = 0;
    unsigned int counter = 0;

    //struct list* result = list_create();
    // head of linked list
    struct movie* head = NULL;
    // tail of linked list
    struct movie* tail = NULL;
    // void list_insert(the list, void* val)
    
    while((nread = getline(&curr_line, &len, movie_file)) != -1){
        if(line1_flag != 0){
            struct movie* new_node = movie_create(curr_line);
            if(head == NULL){
                head = new_node;
                tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = new_node; 
            }
            //list_insert(result, new_node);
            //insert into linked list
            counter++;
        }else line1_flag = 1;
    }
    free(curr_line);
    fclose(movie_file);
    printf("Processed file %s and parsed data for %d movies\n", file_path, counter);
    return head;
}

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
// rating 1, yes; otherwise no

void movie_print(struct movie* head, int rating){

    printf("%d ", head->year);
    if(rating==1)printf("%.1f ", head->rating);
    printf("%s\n", head->title);
    return;
}

void movie_print_all(struct movie* head, int rating){
    struct movie* tmp = head;
    while(tmp != NULL){
        movie_print(tmp, rating);
        tmp = tmp->next;
    }
    return;
}

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

void movie_show_highest_rate(struct movie* movies){
    struct movie* tmp = movies;
    int len = 0;
    int found = 0;
    // This is a slow approach but the only way 
    // I could easily write this without making a hash table from scratch
    while(tmp != NULL){
        len++;
        tmp = tmp->next; 
    }
    // make an array with more than enough elements
    int* year_history = malloc(sizeof(int)*len);
    for(int i = 0; i < len; i++){
        year_history[i] = -1; // set everything to -1
    }
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
