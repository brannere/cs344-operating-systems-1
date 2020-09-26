#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./list.h"
#include "./movie.h"
/*struct movie{
    char* name;
    int year;
    char* langs;
    double rating;      
};*/

/*struct movie* create_movie(char* curr_line){
    struct movie* curr_movie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char* saveptr;
    char* year;
    char* rating;

    // the first token is the title
    char* token = strtok_r(curr_line, ",", &saveptr);
    curr_movie->name = calloc(strlen(token)+1, sizeof(char));
    strcpy(curr_movie->name, token);

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
    
    printf( "%s\t%d\t%s\t%f\n", curr_movie->name, curr_movie->year, 
            curr_movie->langs, curr_movie->rating);
    return curr_movie;
}*/

struct list* process_file(char* file_path){
    FILE* movie_file = fopen(file_path, "r");
    char* curr_line = NULL;
    size_t len = 0;
    ssize_t nread; 
    char* token;
    struct movie* new_node = NULL;
    int line1_flag = 0;

    struct list* result = list_create();
    // void list_insert(the list, void* val)
    
    while((nread = getline(&curr_line, &len, movie_file)) != -1){
        if(line1_flag != 0){
            new_node = movie_create(curr_line);
            list_insert(result, new_node);
            //insert into linked list
        }else line1_flag = 1;
    }
    free(curr_line);
    fclose(movie_file);
    return result;
}

int main(int argc, char *argv[]){
        if (argc < 2){
            printf("You must provide the name of the file to process\n");
            printf("Example usage: ./movies file.csv\n");
            return EXIT_FAILURE;                    
        }
        struct list* movies = process_file(argv[1]);
        //printStudentList(list);
        list_free(movies);
        return EXIT_SUCCESS;                   
}
