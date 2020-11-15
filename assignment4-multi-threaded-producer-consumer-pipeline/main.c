/**
 * Prgram Filename: main.c
 * Author: Erick Branner
 * Date: 16 November 2020
 * Description: Contains main function/process for assginment
 * Input: Strings of text relating to file names
 * Output: Files, directoires
 * 
*/

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <string.h>
// #include <sys/types.h>
// #include "./prog.h"

// #include "./globals.h"

/**
 * Function: main()
 * Description: main process for program
 * Parameters: argument count and argument number
 * Pre-Conditions: csv file passed from command line exists
 * Post-Conditions: None
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "./prog.h"
#include "./input.h"
#include "./line_sep.h"
#include "./plus_sign_thread.h"
#include "./output.h"






/* Same code from assignment documentation */
char buffer_1[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
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


char buffer_2[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
int count_2 = 0;
int prod_idx_2 = 0;
int con_idx_2 = 0;
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;


char buffer_3[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
int count_3 = 0;
int prod_idx_3 = 0;
int con_idx_3 = 0;
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;


/* functions */

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

char* get_buff_1(){

	pthread_mutex_lock(&mutex_1);
	while(count_1 == 0){
		// Buffer is empty. Wait for the producer to signal that the buffer has data
  	pthread_cond_wait(&full_1, &mutex_1);
  	char* item = buffer_1[con_idx_1];
  	// Increment the index from which the item will be picked up
  	con_idx_1 = con_idx_1 + 1;
  	count_1--;
  	// Unlock the mutex
  	pthread_mutex_unlock(&mutex_1);
  	// Return the item
  	return item;
	}
	return NULL;
}

/*
 Function that the input thread will run.
 Get input from the user.
 Put the item in the buffer shared with the square_root thread.
*/
void *get_input(void *args)
{
		fprintf(stdout, "get_input thread!\n");
		fflush(stdout);
		struct input* ipt_ctx = NULL;
		ipt_ctx = input_init();

		char* buff = NULL;
		size_t buffsize = MAX_IPT_LINE_LEN;
    // for (int i = 0; i < NUM_ITEMS; i++)
    for (;;)
    {
      // Get the user input
      // int item = get_user_input();
      // put_buff_1(item);
			getline(&buff, &buffsize, stdin);
			input_store_line(ipt_ctx, buff);
			if(ipt_ctx->stop_reading == true) break;
			put_buff_1(buff);
			// free(buff);

    }
    return NULL;
}


void* line_sep(void* args){
	fprintf(stdout, "line_sep thread\n");
	fflush(stdout);

	char* tmp = get_buff_1();
	fprintf(stdout, "got: %s\n", tmp);
	fflush(stdout);
	if(tmp != NULL){
		char_replace(tmp, LINE_SEP, ' ');
		tmp  = _str_replace(tmp, "^");
		fprintf(stdout, "changed to: %s\n", tmp);
		fflush(stdout);
	}

	return NULL;
}

int main(){

	// threading_prog();	
	pthread_t input_t, line_sep_t;
	pthread_create(&input_t, NULL, get_input, NULL);
	pthread_create(&line_sep_t, NULL, line_sep, NULL);
	// pthread_create(&plus_sign_t, NULL, plus_sign, NULL);
	// pthread_create(&output_t, NULL, write_output, NULL);
	// Wait for the threads to terminate
	pthread_join(input_t, NULL);
	pthread_join(line_sep_t, NULL);
	// pthread_join(plus_sign_t, NULL);
	// pthread_join(output_t, NULL);	
	return EXIT_SUCCESS;                   
}