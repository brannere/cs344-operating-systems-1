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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

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

void show_options_main(){
    printf("\n1. Select file to process");
    printf("2. Exit the program\n\n");
    return;
}
void show_options_file(){
    fprintf(stdout, "Which file you want to process? \n");
    fprintf(stdout, "Enter 1 to pick the largest file\n");
    fprintf(stdout, "Enter 2 to pick the smallest file\n");
    fprintf(stdout, "Enter 3 to specify the name of a file\n\n");
    return;
}

void testing(){
    DIR* currDir = opendir(".");
    struct dirent *aDir;

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){
        printf("%s  %lu\n", aDir->d_name, aDir->d_ino);    
    }
    //Close the directory
    closedir(currDir);
    return;
}

void select_from_file(){
    fprintf(stdout, "select from file\n");
    show_options_file();
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

void main_loop(){
    int choice = -1; 
    do{
        show_options_main();
        //choice = get_int_b("Enter a choice from 1 to 4: ",1,4);
        choice = get_int("Enter a choice 1 to 2: ");
        printf("\n");
        switch(choice){
            case 1:
                fprintf(stdout, "select file to process\n");
                break; 
            case 2:
                printf("Goodbye.\n");
                break;
            default:
                printf("You entered an incorect choice. Try again.\n");
                break;
                printf("\n\n");
        }
    }while(choice != 2);
    return;
}
