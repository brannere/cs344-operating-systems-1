#include "./prog.h"
#include "./movie.h"
#include "./dynarray.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// this assumes the string is not empty
// returns 1 if true, 0 if false
unsigned int is_int(char* str){
    for(unsigned int i = 0; str[i] != '\0'; i++){
        if(!(str[i] >= 48 && str[i] <=57)){
            printf("You entered a non-number. Try again.\n");
            return 0;
        }
    }
    return 1;
}
// Used for reference on reading a string with spaces:
// Also used for clearing the input buffer
// S1: https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx
int get_int(char* prompt, int hi, int low){
    char input[32]; // statically allocated for now
    char tmp; //for clearing the input buffer
    do{
        do{
            printf("%s", prompt);
            scanf("%[^\n]", &input); // S1
            scanf("%c",&tmp); // S1
        }while(is_int(input)==0);
        if(!(atoi(input) >= hi && atoi(input) <= low)){
            printf("You entered an incorrect choice. Try again.\n");
        }
    }while(!(atoi(input) >= hi && atoi(input) <= low));
    return atoi(input); 
}

void show_options(){
    printf("\n1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n\n");
    return;
}

void choose_from_year(struct movie* movies){ // MAKE VERSION WITH NO BOUNDS
    int year = get_int("Enter the year for which you want to see movies: ",0, 9999);
    movie_show_from_year(movies, year); 
}

void show_highest_rate(struct movie* movies){
    movie_show_highest_rate(movies);
    return;
}

void show_specif_lang(struct movie* movies){
    char lang[32];
    char input[32]; // statically allocated for now
    printf("Enter the language for which you want to see movies: ");
    scanf("%s", lang);
    scanf("%[^\n]", &input); // S1
    movie_show_specif_lang(movies, lang);
    return;
}

void main_loop(struct movie* movies){
    int choice = -1; 
    do{
        show_options();
        choice = get_int("Enter a choice from 1 to 4: ",1,4);
        printf("\n");
        switch(choice){
            case 1:
                choose_from_year(movies);
                break;
            case 2:
                show_highest_rate(movies);
                break;
            case 3:
                show_specif_lang(movies); 
                break; 
            case 4:
                printf("Goodbye.\n");
                break;
            default:
                printf("Something went wrong");
                exit(0);
            printf("\n\n");
        }
    }while(choice != 4);
    return;
}
