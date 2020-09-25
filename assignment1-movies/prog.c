#include "./prog.h"


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

int get_int(char* prompt, int hi, int low){

    printf("%s",prompt);
    do{
        printf("loop");
    }while(is_int(prompt)==0);
    return -1; 
}

void show_options(){
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n");
    return;
}

void main_loop(){
    show_options();
    get_int("Prompt:",1,4);
    return;
}
