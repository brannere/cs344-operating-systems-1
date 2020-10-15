/**
 * Prgram Filename: main.c
 * Author: Erick Branner
 * Date: 12 October 2020
 * Description: Contains main function/process for assginment
 * Input: CSV Files
 * Output: Strings of text
 * 
*/

#include "./prog.h"
#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */

int main(int argc, char *argv[]){
    struct movie* movies = NULL;     
    if (argc < 2){    
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies file.csv\n");
        return EXIT_FAILURE;                    
    }
    movies = process_file(argv[1]);    
    main_loop(movies);
        
    movie_free_all(movies);
    return EXIT_SUCCESS;                   
}