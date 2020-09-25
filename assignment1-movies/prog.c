#include "./prog.h"


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int get_int(char* prompt){

    printf("%s",prompt);

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
    get_int("Test test \t\t test test \n\n\n");
    return;
}
