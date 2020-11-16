/**
 * Prgram Filename: prog.c
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: Main functionality of smallsh
 * Input:
 * Output:
 *
*/

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <pthread.h>
// #include "./prog.h"
// #include "./input.h"
// #include "./line_sep.h"
// #include "./plus_sign_thread.h"
// #include "./output.h"

// // ??????
// // char* buff = NULL;
// // size_t buffsize = MAX_IPT_LINE_LEN;
// // struct input* ipt_ctx = NULL;
// // ipt_ctx = input_init();



// // /* Same code from assignment documentation */
// // char buffer_1[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
// // // Number of items in the buffer
// // int count_1 = 0;
// // // Index where the square-root thread will put the next item
// // int prod_idx_1 = 0;
// // // Index where the output thread will pick up the next item
// // int con_idx_1 = 0;
// // // Initialize the mutex for buffer 1
// // pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
// // // Initialize the condition variable for buffer 1
// // pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;


// // char buffer_2[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
// // int count_2 = 0;
// // int prod_idx_2 = 0;
// // int con_idx_2 = 0;
// // // Initialize the mutex for buffer 1
// // pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
// // // Initialize the condition variable for buffer 1
// // pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;


// // char buffer_3[MAX_IPT_LINE_NUM][MAX_IPT_LINE_LEN];
// // int count_3 = 0;
// // int prod_idx_3 = 0;
// // int con_idx_3 = 0;
// // // Initialize the mutex for buffer 1
// // pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
// // // Initialize the condition variable for buffer 1
// // pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;


// // /* functions */

// // /*
// //  Put an item in buff_1
// // */
// // void put_buff_1(char* item){
// //   // Lock the mutex before putting the item in the buffer
// //   pthread_mutex_lock(&mutex_1);
// //   // Put the item in the buffer
// //   // buffer_1[prod_idx_1] = item;
// // 	strcpy(buffer_1[prod_idx_1], item);
// //   // Increment the index where the next item will be put.
// //   prod_idx_1 = prod_idx_1 + 1;
// //   count_1++;
// //   // Signal to the consumer that the buffer is no longer empty
// //   pthread_cond_signal(&full_1);
// //   // Unlock the mutex
// //   pthread_mutex_unlock(&mutex_1);
// // }


// // /*
// //  Function that the input thread will run.
// //  Get input from the user.
// //  Put the item in the buffer shared with the square_root thread.
// // */
// // void *get_input(void *args)
// // {
// // 		struct input* ipt_ctx = NULL;
// // 		ipt_ctx = input_init();

// // 		char* buff = NULL;
// // 		size_t buffsize = MAX_IPT_LINE_LEN;
// //     // for (int i = 0; i < NUM_ITEMS; i++)
// //     for (;;)
// //     {
// //       // Get the user input
// //       // int item = get_user_input();
// //       // put_buff_1(item);
// // 			getline(&buff, &buffsize, stdin);
// // 			input_store_line(ipt_ctx, buff);
// // 			if(ipt_ctx->stop_reading == true) break;
// // 			put_buff_1(buff);
// // 			free(buff);

// //     }
// //     return NULL;
// // }



// // void threading_prog(){

// 	// char* buff = NULL;
// 	// size_t buffsize = MAX_IPT_LINE_LEN;
// 	// struct input* ipt_ctx = NULL;
// 	// ipt_ctx = input_init();


	
// 	// while(ipt_ctx->stop_reading == false){

// 	// 	/* run thread 1 */
// 	// 	// getline(&buff, &buffsize, stdin); 
// 	// 	// input_store_line(ipt_ctx, buff);
		
// 	// 	/* processing */
// 	// 	// char_replace(ipt_ctx->line, LINE_SEP, ' ');
// 	// 	// ipt_ctx->processed = _str_replace(ipt_ctx->line, "^");
// 	// 	// // fprintf(stdout, "line: %s\n", ipt_ctx->processed);
// 	// 	// input_append_history(ipt_ctx);
// 	// 	// /* output */
// 	// 	// write_line(ipt_ctx);

// 	// }	
// // 	return; 
// // }