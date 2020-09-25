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
// Used for reference on reading a string with spaces:
// Also used for clearing the input buffer
// https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx
int get_int(char* prompt, int hi, int low){
    char input[32]; // statically allocated for now
    char tmp; //for clearing the input buffer
    do{
        printf("%s", prompt);
        scanf("%[^\n]", &input);
        scanf("%c",&tmp);
    }while(is_int(input)==0);
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
    int foo = 0;
    show_options();
    foo = get_int("Prompt:",1,4);
    printf("Foo: %d\n", foo);
    return;
}
