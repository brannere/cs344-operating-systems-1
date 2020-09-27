/*********************************************************************
* ** Program Filename: asn1.c
* ** Author: Erick Branner
* ** Date: 24 September 2020
* ** Description: Contains main function for assignment
* ** Input: CSV Files
* ** Output: Strings of text
* *********************************************************************/
/*********************************************************************
* ** Function:
* ** Description:
* ** Parameters:
* ** Pre-Conditions:
* ** Post-Conditions:
* *********************************************************************/
#include "./prog.h"
#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    struct movie* movies = NULL;     
    if (argc < 2){    
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies file.csv\n");
        return EXIT_FAILURE;                    
    }
    movies = process_file(argv[1]);    
    movies_print(movies, 1);
    main_loop();
        
    movie_free_all(movies);
    return EXIT_SUCCESS;                   
}
