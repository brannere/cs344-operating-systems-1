#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
struct movie{
    char *name;
    int year;
    char *langs;
    double rating;      
};

struct movie* create_movie(char* curr_line){

    return NULL;
}

struct list* process_file(char* file_path){
    FILE* movie_file = fopen(file_path, "r");
    char* curr_line = NULL;
    size_t len = 0;
    ssize_t nread; 
    char* token;
    struct movie* new_node = NULL;

    struct list* result = list_create();
    // void list_insert(the list, void* val)
    
    while((nread = getline(&curr_line, &len, movie_file)) != -1){
        new_node = create_movie(curr_line);
        list_insert(result, new_node);
        //insert into linked list
    }
    free(curr_line);
    fclose(movie_file);
    return result;
}

int main(int argc, char *argv[]){
        if (argc < 2){
            printf("You must provide the name of the file to process\n");
            printf("Example usage: ./students student_info1.txt\n");
            return EXIT_FAILURE;                    
        }
        struct movie *list = process_file(argv[1]);
        //printStudentList(list);
        return EXIT_SUCCESS;                   
}
