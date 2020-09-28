/**
 * Prgram Filename: prog.c
 * Author: Erick Branner
 * Date: 12 October 2020
 * Description: Source file for prog.h
 * Input:
 * Output:
 * 
*/

#include "./prog.h"
#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * Function: is_int()
 * Description: Determines if string is an integer
 * Parameters: String
 * Pre-Conditions: String is non-empty
 * Post-Conditions: Returns 1 if true, 0 if false
 */

// this assumes the string is not empty
// returns 1 if true, 0 if false
unsigned int is_int(char* str){
    for(unsigned int i = 0; str[i] != '\0'; i++){
        if(!(str[i] >= 48 && str[i] <=57)){
            if(str[0] != 45){ //ignore negative numbers
                printf("You entered a non-number. Try again.\n");
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Function: get_int()
 * Description: Gets an integer from user input 
 * Parameters: Prompt to be printed
 * Pre-Conditions: None
 * Post-Conditions: Returns integer from input
 */
/*
// Used for reference on reading a string with spaces:
// Also used for clearing the input buffer
// S1: https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx
 * Used this for reference on the string approach but it didn't end up working
 * the way I wanted it to (negative numbers not working) -- didn't know why
 * atoi wasn't working on negative numbers
 * S2: https://stackoverflow.com/questions/31560778/why-doesnt-my-atoi-implementation-work-with-negative-numbers
 * */
int get_int(char* prompt){
    int i = -1; 
    printf("%s", prompt);
    scanf("%d", &i);
    return i;
    /*char input[32]; // statically allocated for now
    char tmp; //for clearing the input buffer
    int sign = 1;
    //do{
        do{
            printf("%s", prompt);
            scanf("%[^\n]", &input); // S1
            scanf("%c",&tmp); // S1
        }while(is_int(input)==0);
        //if(!(atoi(input) >= hi && atoi(input) <= low)){
        //    printf("You entered an incorrect choice. Try again.\n");
        //}
    //}while(!(atoi(input) >= hi && atoi(input) <= low));
    if(input[0] == 45) sign = -1; //S2; number is negative
    return atoi(input)*sign;*/ 
}

/**
 * Function: get_int_b()
 * Description: Gets an integer from user input 
 * Parameters: Prompt to be printed, upper and lower bound
 * Pre-Conditions: None
 * Post-Conditions: Returns integer from input
 */
// Used for reference on reading a string with spaces:
// Also used for clearing the input buffer
// S1: https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx

/*
 * Used this for reference on the string approach but it didn't end up working
 * the way I wanted it to (negative numbers not working) -- didn't know why
 * atoi wasn't working on negative numbers
 * S2: https://stackoverflow.com/questions/31560778/why-doesnt-my-atoi-implementation-work-with-negative-numbers
 * */
int get_int_b(char* prompt, int hi, int low){
    
    int i = -1; 
    do{
        printf("%s", prompt);
        scanf("%d", &i);
        if(!(i >= hi && i <= low)){
            printf("You entered an incorrect choice. Try again.\n");
        }
    }while(!(i>= hi && i <= low));
    return i;
    /*char input[32]; // statically allocated for now
    char tmp; //for clearing the input buffer
    int sign = 1;
    do{
        do{
            printf("%s", prompt);
            scanf("%[^\n]", &input); // S1
            scanf("%c",&tmp); // S1
        }while(is_int(input)==0);
        if(input[0] == 45){ // number is negative
            sign=-1; //S2
        }
        else sign = 1;
        if(!(atoi(input)*sign >= hi && atoi(input)*sign <= low)){
            printf("You entered an incorrect choice. Try again.\n");
        }
    }while(!(atoi(input)*sign >= hi && atoi(input)*sign <= low));
    return (atoi(input)*sign);*/ 
}

/**
 * Function: show_options()
 * Description: Prints user options to screen
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: options printed to screen
 */

void show_options(){
    printf("\n1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n\n");
    return;
}

/**
 * Function: choose_from_year()
 * Description: Containing function for showing movies by year
 * Parameters: Movies struct list
 * Pre-Conditions: None
 * Post-Conditions: movies printed to screen
 */

void choose_from_year(struct movie* movies){ 
    int year = get_int("Enter the year for which you want to see movies: ");
    movie_show_from_year(movies, year); 
}

/**
 * Function: show_highest_rate()
 * Description: containig function for showing highest rate
 * Parameters: Movies struct list
 * Pre-Conditions: None
 * Post-Conditions: movies printed to screen
 */

void show_highest_rate(struct movie* movies){
    movie_show_highest_rate(movies);
    return;
}

/**
 * Function: show_specif_lang()
 * Description: Containing function for showing movies 
 * in specific language 
 * Parameters: Movies struct list
 * Pre-Conditions: None
 * Post-Conditions: Movies printed to screen
 */

void show_specif_lang(struct movie* movies){
    char lang[32];
    char input[32]; // statically allocated for now
    printf("Enter the language for which you want to see movies: ");
    scanf("%s", lang);
    scanf("%[^\n]", &input); // S1
    movie_show_specif_lang(movies, lang);
    return;
}

/**
 * Function: main_loop()
 * Description: Containing function for all 
 * program functionality
 * Parameters: Movies struct list
 * Pre-Conditions: None
 * Post-Conditions: None
 */

void main_loop(struct movie* movies){
    int choice = -1; 
    do{
        show_options();
        choice = get_int_b("Enter a choice from 1 to 4: ",1,4);
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
