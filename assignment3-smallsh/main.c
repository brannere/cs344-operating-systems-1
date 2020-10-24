/**
 * Prgram Filename: main.c
 * Author: Erick Branner
 * Date: 20 October 2020
 * Description: Contains main function/process for assginment
 * Input: Strings of text relating to file names
 * Output: Files, directoires
 * 
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./prog.h"

/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */

int main(int argc, char *argv[]){
	main_proc();
	return EXIT_SUCCESS;                   
}
