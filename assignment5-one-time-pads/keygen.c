#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define true 1
#define false 0





/**
 * Function: is_int()
 * Description: Determines if string is an integer
 * Parameters: String
 * Pre-Conditions: String is non-empty
 * Post-Conditions: Returns 1 if true, 0 if false
 */

// this assumes the string is not empty
// returns 1 if true, 0 if false
int is_int(char* str){
    for(unsigned int i = 0; str[i] != '\0'; i++){
        if(!(str[i] >= 48 && str[i] <=57)){
            if(str[0] != 45){ //ignore negative numbers
                // printf("You entered a non-number. Try again.\n");
                return false;
            }
        }
    }
    return true;
}


/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */
int main(int argc, char* argv[]){

	int len = 0;
	
	/* Are there enough arguments */
	if(argc <= 1){
		fprintf(stdout, "keygen: not enough arguments\n");
		exit(1);
	}

	/* Ther's at least two arguments; is the second argument an integer? */
	if(is_int(argv[1]) == false){
		fprintf(stdout, "not int\n");
	}
	else if(is_int(argv[1]) == true){
		fprintf(stdout, "int\n");
	}
	else{
		fprintf(stderr,"keygen: is_int() did not return correctly\n");
	}

	return EXIT_SUCCESS;                   
}