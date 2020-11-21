#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
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
 * Function: _rand()
 * Description: Generates a random number in 
 * range [lo, hi]
 * Parameters: a floor, lo, and a ceiling, hi 
 * Pre-Conditions: should seed with time and srand before calling
 * Post-Conditions: returns random number in range [lo, hi]
 */

int _rand(int lo, int hi){
	int output = -1;
	output = rand()% (hi - lo + 1) +lo;
	return output;
}



char* gen_key(const int len){
	int n = 0;
	char* k = calloc(len, sizeof(char) +1);
	for(int i = 0; i < len; i++){
		n = _rand(65,91); /* A-[, using 91 as space */
		if(n == 91){ // if it's a '[', just make it a space
			k[i] = 32; 
		}else{
			k[i] = n;
		}
	}
	return k;
}
/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */
int main(int argc, char* argv[]){

	time_t t;
	srand((unsigned) time(&t));

	int len = 0;
	char* key = NULL;
	/* Are there enough arguments */
	if(argc <= 1){
		fprintf(stdout, "keygen: not enough arguments\n");
		exit(1);
	}

	/* Ther's at least two arguments; is the second argument an integer? */
	if(is_int(argv[1]) == false){
		fprintf(stdout, "keygen: argument is not an integer\n");
	}
	else if(is_int(argv[1]) == true){
		// fprintf(stdout, "int\n");
		len = atoi(argv[1]);
		key = gen_key(len);
		fprintf(stdout, "%s\n", key);
	}
	else{
		fprintf(stderr,"keygen: is_int() did not return correctly\n");
		exit(-1);
	}
	
	if(key != NULL) free(key);

	return EXIT_SUCCESS;                   
}