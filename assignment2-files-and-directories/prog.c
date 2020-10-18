/**
 * Prgram Filename: prog.c
 * Author: Erick Branner
 * Date: 12 October 2020
 * Description: Source file for prog.h
 * Input:
 * Output:
 * 
 */

#include "./prog.h"
#include "./movie.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>


#define PREFIX "movies_"
#define FILE_MODE 0640
#define DIR_PERMISSION 0750
#define MAX_FILE_LEN 21 /* brannere.movies.nnnnn */
#define GEN_FILE_PRFX "brannere.movies."
/**
 * Function: is_int()
 * Description: Determines if string is an integer
 * Parameters: String
 * Pre-Conditions: String is non-empty
 * Post-Conditions: Returns 1 if true, 0 if false
 */

// this assumes the string is not empty
// returns 1 if true, 0 if false
unsigned int is_int(char* str){
    for(unsigned int i = 0; str[i] != '\0'; i++){
        if(!(str[i] >= 48 && str[i] <=57)){
            if(str[0] != 45){ //ignore negative numbers
                printf("You entered a non-number. Try again.\n");
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Function: get_int()
 * Description: Gets an integer from user input 
 * Parameters: Prompt to be printed
 * Pre-Conditions: None
 * Post-Conditions: Returns integer from input
 */
/*
// Used for reference on reading a string with spaces:
// Also used for clearing the input buffer
// S1: https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx
 * Used this for reference on the string approach but it didn't end up working
 * the way I wanted it to (negative numbers not working) -- didn't know why
 * atoi wasn't working on negative numbers
 * S2: https://stackoverflow.com/questions/31560778/why-doesnt-my-atoi-implementation-work-with-negative-numbers
 * */
int get_int(char* prompt){
    int i = -1; 
    printf("%s", prompt);
    scanf("%d", &i);
    return i;
    /*char input[32]; // statically allocated for now
      char tmp; //for clearing the input buffer
      int sign = 1;
    //do{
    do{
    printf("%s", prompt);
    scanf("%[^\n]", &input); // S1
    scanf("%c",&tmp); // S1
    }while(is_int(input)==0);
    //if(!(atoi(input) >= hi && atoi(input) <= low)){
    //    printf("You entered an incorrect choice. Try again.\n");
    //}
    //}while(!(atoi(input) >= hi && atoi(input) <= low));
    if(input[0] == 45) sign = -1; //S2; number is negative
    return atoi(input)*sign;*/ 
}

/**
 * Function: get_int_b()
 * Description: Gets an integer from user input 
 * Parameters: Prompt to be printed, upper and lower bound
 * Pre-Conditions: None
 * Post-Conditions: Returns integer from input
 */
// Used for reference on reading a string with spaces:
// Also used for clearing the input buffer
// S1: https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx

/*
 * Used this for reference on the string approach but it didn't end up working
 * the way I wanted it to (negative numbers not working) -- didn't know why
 * atoi wasn't working on negative numbers
 * S2: https://stackoverflow.com/questions/31560778/why-doesnt-my-atoi-implementation-work-with-negative-numbers
 * */
int get_int_b(char* prompt, int hi, int low){

    int i = -1; 
    do{
        printf("%s", prompt);
        scanf("%d", &i);
        if(!(i >= hi && i <= low)){
            printf("You entered an incorrect choice. Try again.\n");
        }
    }while(!(i>= hi && i <= low));
    return i;
    /*char input[32]; // statically allocated for now
      char tmp; //for clearing the input buffer
      int sign = 1;
      do{
      do{
      printf("%s", prompt);
      scanf("%[^\n]", &input); // S1
      scanf("%c",&tmp); // S1
      }while(is_int(input)==0);
      if(input[0] == 45){ // number is negative
      sign=-1; //S2
      }
      else sign = 1;
      if(!(atoi(input)*sign >= hi && atoi(input)*sign <= low)){
      printf("You entered an incorrect choice. Try again.\n");
      }
      }while(!(atoi(input)*sign >= hi && atoi(input)*sign <= low));
      return (atoi(input)*sign);*/ 
}

/**
 * Function: show_options()
 * Description: Prints user options to screen
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: options printed to screen
 */

int _rand(int lo, int hi){
	time_t t;
	srand((unsigned) time(&t));
	int output = -1;
	output = random()% (hi - lo + 1) +lo;
	return output;
}

char* generate_dir_name(){
	char* output = NULL;
	char extn[MAX_FILE_LEN - strlen(GEN_FILE_PRFX)];
	output = malloc(sizeof(char)*MAX_FILE_LEN);
	sprintf(extn, "%d", _rand(0,99999));
	memset(output, '\0', sizeof(char)*MAX_FILE_LEN);
	strcpy(output, GEN_FILE_PRFX);
	strcat(output, extn);
	return output;
}

char* create_dir(char* name){
	mkdir(name, DIR_PERMISSION);
	fprintf(stdout, "Created directory with name %s\n", name);
	return name;
}

int create_file(char* filename){
	int fd;
	// FILE* output;
	
	// output = fopen(filename, "w+");
	// chmod(filename, FILE_MODE);
	// fprintf(output, "hello world\n");
	// fputs("fputs\n", output);
	// fclose(output);
	/* file name can be a path*/
	fd = open(	filename, O_RDWR | O_CREAT | O_APPEND, 
													S_IRUSR | S_IWUSR | S_IRGRP);
	if (fd == -1){
		printf("open() failed on \"%s\"\n", filename);
		perror("Error");
		exit(1);
	}
	// char message[] = "hello!\n";
	// int howMany = write(fd, message, strlen(message));
  // printf("wrote %d bytes to the file\n", howMany);	

	return fd; 
}

void show_options_main(){
    fprintf(stdout, "\n1. Select file to process\n");
    fprintf(stdout, "2. Exit the program\n\n");
    return;
}

void show_options_file(){
    fprintf(stdout, "Which file you want to process? \n");
    fprintf(stdout, "Enter 1 to pick the largest file\n");
    fprintf(stdout, "Enter 2 to pick the smallest file\n");
    fprintf(stdout, "Enter 3 to specify the name of a file\n\n");
    return;
}

int _is_csv(char* file){
    int len = 0;
    len = strlen(file);
    char exten[5];
    exten[0] = file[len-4];
    exten[1] = file[len-3];
    exten[2] = file[len-2];
    exten[3] = file[len-1];
    exten[4] = '\0';
    if(strcmp(exten, ".csv") ==0){
        //fprintf(stdout, "is csv\n");
        return 1;
    }
    else{
        //fprintf(stdout, "is not csv\n");
        return 0;
    }
    return -1;
}

char* curr_dir_smallest(){
    // Open the current directory
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    off_t file_size = 0;
    struct stat dirStat;
    int len = 0;
    int i = 0;
    char entryName[256];

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){
        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
            if(_is_csv(aDir->d_name) == 1){
                if(i==0){
                    file_size = dirStat.st_size;
                    memset(entryName, '\0', sizeof(entryName));
                    strcpy(entryName, aDir->d_name);
                    i = 1; 
                }
                // Get meta-data for the current entry
                stat(aDir->d_name, &dirStat);  

                /* Use the difftime function to get the time difference 
                   between the current value of lastModifTime and the st_mtime 
                   value of the directory entry*/

               // if(i == 0 || difftime(dirStat.st_mtime, lastModifTime) > 0){
                if(dirStat.st_size < file_size){
                    // lastModifTime = dirStat.st_mtime;
                    file_size = dirStat.st_size;
                    memset(entryName, '\0', sizeof(entryName));
                    strcpy(entryName, aDir->d_name);
                }
            } 
            }
        }
        // Close the directory
        closedir(currDir);
				// fprintf(stdout,"length is: %d\n", strlen(entryName));
				char* output = malloc(sizeof(char)*strlen(entryName)); // plus 1 for \0
				strcpy(output, entryName);
				// fprintf(stdout, "output: %s\n", output);
				// printf("The last file/directory starting with the prefix \"%s\" modified in the current directory is %s\n", PREFIX, entryName);
        // printf("The smallest file/directory starting with the prefix \"%s\" in the current directory is %s\n", PREFIX, entryName);
				return output;
}

char* curr_dir_largest(){
  // Open the current directory
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  time_t lastModifTime;
  off_t file_size = 0;
  struct stat dirStat;
  int len = 0;
  // int i = 0;
  char entryName[256];
  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){
  	if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
  		if(_is_csv(aDir->d_name) == 1){
  			// Get meta-data for the current entry
  			stat(aDir->d_name, &dirStat);  
  			/* Use the difftime function to get the time difference 
  			   between the current value of lastModifTime and the st_mtime 
  			   value of the directory entry*/
  			// if(i == 0 || difftime(dirStat.st_mtime, lastModifTime) > 0){
  			if(dirStat.st_size > file_size){
  				// lastModifTime = dirStat.st_mtime;
  				file_size = dirStat.st_size;
  				memset(entryName, '\0', sizeof(entryName));
  				strcpy(entryName, aDir->d_name);
  			}
			} 
  	}
	}
  // Close the directory
  closedir(currDir);
  // printf("The last file/directory starting with the prefix \"%s\" modified in the current directory is %s\n", PREFIX, entryName);
	// fprintf(stdout,"length is: %d\n", strlen(entryName));
	char* output = malloc(sizeof(char)*strlen(entryName)+1); // plus 1 for \0
	strcpy(output, entryName);
	// fprintf(stdout, "output: %s\n", output);

  // printf("The largest file/directory starting with the prefix \"%s\" in the current directory is %s\n", PREFIX, entryName);
  return output;
}

void process_movies(char* filename){
	int fd = -1; 
	int year = 0;
	char full[50];
	char nametxt[10];
	char path[MAX_FILE_LEN+1]; /* +1, space for '/' */
	// memset(path, '\0', strlen);
	char* dir_name = NULL;
	dir_name = create_dir(generate_dir_name());
	struct movie* movies = process_file(filename);
	struct movie* tmp = NULL;
	strcpy(path, dir_name);
	strcat(path, "/");
	for(tmp = movies; tmp != NULL; tmp = tmp->next){
		
		/* Filepath creation */
		sprintf(nametxt, "%d", tmp->year); /* int to ascii */
		strcpy(full, path);
		strcat(full, nametxt);
		strcat(full, ".txt");
		
		/* Write to file */
		fd = create_file(full);
 		char outf[255];
		memset(outf, '\0', 255); 
		strcpy(outf, tmp->title);
		int size_outf = write(fd, outf, strlen(outf));
		write(fd, "\n", 1);

		/* Setting strings to null terminator to prevent c string issues */
		memset(outf, '\0', 255);
		memset(full, '\0', 50);
	}	
	return;
}

void select_from_file(){
  show_options_file();
	char* file = NULL;
	char input[255];
	int choice = -1;
	int fd = 0;
	do{
		choice = get_int("Enter a choice from 1 to 3: ");
		  printf("\n");
      switch(choice){
        case 1:
					file = curr_dir_largest();
					fprintf(stdout, "Now processing the chosen file named %s\n", file);
					process_movies(file);
					free(file);
					break; 
        case 2:
					file = curr_dir_smallest();
					fprintf(stdout, "Now processing the chosen file named %s\n", file);
					process_movies(file);
					free(file);
          break;
        case 3:
					fprintf(stdout, "Enter the complete file name: ");
					scanf("%s", input);
					if(open(input, O_RDONLY) == -1){
						choice = -1; 
						fprintf(stdout, "The file %s was not found. Try again\n", input);
					}else{
						fprintf(stdout, "Now processing the chosen file named %s\n", input);
						process_movies(input);
					}

					break;
				default:
          fprintf(stdout, "You entered an incorect choice. Try again.\n");
          break;
      }
          // printf("\n\n");
    }while(choice > 3 || choice < 1);
  return;
}
/**
 * Function: main_loop()
 * Description: Containing function for all 
 * program functionality
 * Parameters: Movies struct list
 * Pre-Conditions: None
 * Post-Conditions: None
 */
void main_loop(){
    int choice = -1; 
    do{
      show_options_main();
      //choice = get_int_b("Enter a choice from 1 to 4: ",1,4);
      choice = get_int("Enter a choice 1 to 2: ");
      printf("\n");
      switch(choice){
        case 1:
            select_from_file();
						break; 
        case 2:
            printf("Goodbye.\n");
            break;
        default:
            printf("You entered an incorect choice. Try again.\n");
            break;
            printf("\n\n");
      }
    }while(choice != 2);
    return;
}