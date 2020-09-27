#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./movie.h"
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
void movie_print_all(struct movie* head, int rating){
    struct movie* tmp = head;
    while(tmp != NULL){
        printf("%d ", tmp->year);
        if(rating==1)printf("%.1f ", tmp->rating);
        printf("%s\n", tmp->title);
        tmp = tmp->next;
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
