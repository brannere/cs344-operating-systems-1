/**
 * Prgram Filename: main.c
 * Author: Erick Branner
 * Date: 16 November 2020
 * Description: Contains main function/process for assginment
 * Input:
 * Output: 
 * 
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "./globals.h"
#include "./line_sep.h"
#include "./plus_sign_thread.h"




/* The following variables and buffers are from the example program
linked on the assignment documentation  */



/* Buffer 1 */
char buffer_1[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
// char* buffer_1[MAX_IPT_LINE_NUM];
// Number of items in the buffer
int count_1 = 0;
// Index where the square-root thread will put the next item
int prod_idx_1 = 0;
// Index where the output thread will pick up the next item
int con_idx_1 = 0;
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;

/* Buffer 2 */
char buffer_2[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
// char* buffer_2[MAX_IPT_LINE_NUM];
int count_2 = 0;
int prod_idx_2 = 0;
int con_idx_2 = 0;
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;

/* Buffer 2 */
char buffer_3[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
// char* buffer_3[MAX_IPT_LINE_NUM];

int count_3 = 0;
int prod_idx_3 = 0;
int con_idx_3 = 0;
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;


/* End of threading useage code */


/* Functions */

/**
 * Function: write_line()
 * Description: Writes a line of exactly OUTPUT_LEN (80) chars 
 * from an input string
 * Parameters: C string of source string to be printed
 * Pre-Conditions:
 * Post-Conditions: writes to stdout
 */
void write_line(char* history){
	int i = 0;
	char* tmp = NULL;
		/* Less than output length, do nothing*/
	if(strlen(history) < OUTPUT_LEN){
		/* Do nothing */
	}
	else{
		/* Print each char in history */
		for
		(
			i = 0;
			i < (strlen(history) - ((strlen(history))%OUTPUT_LEN));
			i++
		)
		{
			/* Print a new line on the OUTPUT_LENth char written */
			if(i != 0 && i % OUTPUT_LEN == 0) fprintf(stdout, "\n");
			fprintf(stdout, "%c", history[i]);
			fflush(stdout);
		} 
		/* Copy the remaning string */
		tmp = calloc(strlen(&history[i]), sizeof(char));
		strcpy(tmp, &history[i]);
		/* Clear history and add remaining string to new start of history */
		memset(history, '\0', strlen(history));
		strcpy(history, tmp);
		// free(tmp);
	/* Print a new line after printing multiple of OUTPUT_LEN */
	fprintf(stdout, "\n");
	fflush(stdout);
	}
	return; 
}


/*
 Put an item in buff_1
*/
void put_buff_1(char* item){
  // Lock the mutex before putting the item in the buffer
  pthread_mutex_lock(&mutex_1);
  // Put the item in the buffer
  // buffer_1[prod_idx_1] = item;
	strcpy(buffer_1[prod_idx_1], item);
  // Increment the index where the next item will be put.
  prod_idx_1 = prod_idx_1 + 1;
  count_1++;
  // Signal to the consumer that the buffer is no longer empty
  pthread_cond_signal(&full_1);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_1);
}

/* 
	Put an item in buff_2
*/
void put_buff_2(char* item){
	pthread_mutex_lock(&mutex_2);
  // Put the item in the buffer
  // buffer_2[prod_idx_2] = item;
	strcpy(buffer_2[prod_idx_2], item);
  // Increment the index where the next item will be put.
  prod_idx_2 = prod_idx_2 + 1;
  count_2++;
  // Signal to the consumer that the buffer is no longer empty
  pthread_cond_signal(&full_2);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_2);
}

/* 
	Put an item in buff_3
*/
void put_buff_3(char* item){
	pthread_mutex_lock(&mutex_3);
  // Put the item in the buffer
  // buffer_3[prod_idx_3] = item;
	strcpy(buffer_3[prod_idx_3], item);
  // Increment the index where the next item will be put.
  prod_idx_3 = prod_idx_3 + 1;
  count_3++;
  // Signal to the consumer that the buffer is no longer empty
  pthread_cond_signal(&full_3);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_3);
}


/* 
	get contents of buff_1
*/
char* get_buff_1(){

	pthread_mutex_lock(&mutex_1);
	while(count_1 == 0){
		// Buffer is empty. Wait for the producer to signal that the buffer has data
  	pthread_cond_wait(&full_1, &mutex_1);
	}
  	char* item = buffer_1[con_idx_1];
  	// Increment the index from which the item will be picked up
  	con_idx_1 = con_idx_1 + 1;
  	count_1--;
  	// Unlock the mutex
  	pthread_mutex_unlock(&mutex_1);
  	// Return the item
  	return item;
}


/* 
	get contents of buff_2
*/
char* get_buff_2(){

	pthread_mutex_lock(&mutex_2);
	while(count_2 == 0){
		// Buffer is empty. Wait for the producer to signal that the buffer has data
  	pthread_cond_wait(&full_2, &mutex_2);
	}
  	char* item = buffer_2[con_idx_2];
  	// Increment the index from which the item will be picked up
  	con_idx_2 = con_idx_2 + 1;
  	count_2--;
  	// Unlock the mutex
  	pthread_mutex_unlock(&mutex_2);
  	// Return the item
  	return item;
}

/* 
	get contents of buff_3
*/
char* get_buff_3(){

	pthread_mutex_lock(&mutex_3);
	while(count_3 == 0){
		// Buffer is empty. Wait for the producer to signal that the buffer has data
  	pthread_cond_wait(&full_3, &mutex_3);
	}
  	char* item = buffer_3[con_idx_3];
  	// Increment the index from which the item will be picked up
  	con_idx_3 = con_idx_3 + 1;
  	count_3--;
  	// Unlock the mutex
  	pthread_mutex_unlock(&mutex_3);
  	// Return the item
  	return item;
}

/**
 * Function: get_input
 * Description: ran by input thread; gets input from stdin; 
 * expects to be termineted by `\n`
 * Parameters: arguments
 * Pre-Conditions: 
 * Post-Conditions: writes intput read from stdin to buff 1
 */
void *get_input(void *args){	
		char* buff = calloc(MAX_IPT_LINE_NUM+1, sizeof(char));
		size_t buffsize = MAX_IPT_LINE_LEN;
    for (;;){
      // Get the user input
			getline(&buff, &buffsize, stdin);
			put_buff_1(buff);
			if(strcmp(buff, STOP_SEQ) == 0){
				break;
			}
    }
    return NULL;
}

/**
 * Function: line_sep
 * Description: ran by line separator thread; replaces occurences
 * of LINE_SEP (\n) with a space (ASCII 32)
 * Parameters: arguments
 * Pre-Conditions: 
 * Post-Conditions: writes changed string to buff 2
 */
void* line_sep(void* args){
	for(;;){
		char* tmp = get_buff_1();
			if(strcmp(STOP_SEQ, tmp) != 0){
				char_replace(tmp, LINE_SEP, ' ');
			}
			put_buff_2(tmp);
			if(strcmp(STOP_SEQ, tmp) == 0) break;
	}
	return NULL;
}

/**
 * Function: plus_sign()
 * Description: Ran by plus sign thread; replaces occurences 
 * of "++" with "^" 
 * Parameters: arguments
 * Pre-Conditions:
 * Post-Conditions: Writes changed string to buff 3 
 */
void* plus_sign(void* args){
	for(;;){
		char* tmp = get_buff_2();
		tmp  = _str_replace(tmp, "^");
		put_buff_3(tmp);
		if(strcmp(STOP_SEQ, tmp) == 0) break;
	}
	return NULL;
}

/**
 * Function: output()
 * Description: ran by output thread; handles program output 
 * writes chars to stdout in lines of 80
 * Parameters: arguemnts
 * Pre-Conditions:
 * Post-Conditions: writes to stdout
 */
void* output(void* args){
	char history[MAX_IPT_LINE_LEN*MAX_IPT_LINE_NUM];
	char* tmp_b;
	for(;;){
		tmp_b = get_buff_3();
		if(strcmp(STOP_SEQ, tmp_b) == 0) break;
		strcat(history,tmp_b);
		write_line(history);
	}
	return NULL;
}

/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */
int main(){

	// threading_prog();	
	/* create the threads */
	pthread_t input_t, line_sep_t, plus_sign_t, output_t;
	pthread_create(&input_t, NULL, get_input, NULL);
	pthread_create(&line_sep_t, NULL, line_sep, NULL);
	pthread_create(&plus_sign_t, NULL, plus_sign, NULL);
	pthread_create(&output_t, NULL, output, NULL);
	// Wait for the threads to terminate
	pthread_join(input_t, NULL);
	pthread_join(line_sep_t, NULL);
	pthread_join(plus_sign_t, NULL);
	pthread_join(output_t, NULL);	
	return EXIT_SUCCESS;                   
}