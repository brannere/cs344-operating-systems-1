#include "./prog.h"
#include "./list.h"
#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// this assumes the string is not empty
// returns 1 if true, 0 if false
unsigned int is_int(char* str){
    for(unsigned int i = 0; str[i] != '\0'; i++){
        if(!(str[i] >= 48 && str[i] <=57)){
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
    }while(!(atoi(input) >= hi && atoi(input) <= low));
    return atoi(input); 
}

void show_options(){
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n");
    return;
}

void main_loop(){
    int choice = -1; 
    do{
        show_options();
        choice = get_int("Enter a choice from 1 to 4: ",1,4);
        switch(choice){
            case 1:
                printf("case1\n");
                break;
            case 2:
                printf("case2\n");
                break;
            case 3:
                printf("case3\n");
                break; 
            case 4:
                printf("case4\n");
                break;
            default:
                printf("Something went wrong");
        }
    }while(choice != 4);
    return;
}
