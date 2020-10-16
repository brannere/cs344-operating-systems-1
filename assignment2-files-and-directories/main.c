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
	create_file("a-test-file.txt");
		main_loop();
    return EXIT_SUCCESS;                   
}
