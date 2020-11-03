/**
 * Prgram Filename: child_proc.c
 * Author: Erick Branner
 * Date: 3 November 2020
 * Description: implementation for child process linked list
 * Input:
 * Output:
 *
*/


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./child_proc.h"


/**
 * Function: child_proc_create()
 * Description: Creates and returns a head of a child_proc
 * Parameters:
 * Pre-Conditions:
 * Post-Conditions: Returns pointer to allocated memory
 */


struct child_proc* child_proc_create(){
	struct child_proc* output = malloc(sizeof(struct child_proc));
	output->next = NULL;
	output->pid = 0; 
	output->status = 0;
	return output;  
}



/**
 * Function: child_proc_insert()
 * Description: Inserts a new child process into the linked list
 * Parameters: a head of a child process list, pid 
 * Pre-Conditions: 
 * Post-Conditions: returns a new head, memory allocated
 */

/* returns a new head */
struct child_proc* child_proc_insert(struct child_proc* head, pid_t pid){
	/* Head of list */
	struct child_proc* add = NULL;
	struct child_proc* tmp = NULL;
	if(head == NULL){
		head = child_proc_create();
		head->pid = pid;  
		return head;
	}
	else{ //if(tmp->next != NULL){
		for(tmp = head; tmp->next != NULL; tmp=tmp->next){
			// fprintf(stdout, "children[%p]->pid: %d\n", tmp, tmp->pid);
		}
	}
	add = child_proc_create();
	add->pid = pid;
	tmp->next = add;

	// struct child_proc* new_h = NULL;
	return head; /* Shouldn't get here ever */
}


/**
 * Function: child_proc_print_all
 * Description: Prints all child processes, used for debugging
 * Parameters: head of child process list
 * Pre-Conditions: 
 * Post-Conditions:
 */

void child_proc_print_all(struct child_proc* head){
	for(struct child_proc* tmp = head; tmp != NULL; tmp=tmp->next){
		fprintf(stdout, "children[%p]->pid: %d\n", tmp, tmp->pid);
	}
	return;
}


/**
 * Function: child_proc_free_all()
 * Description: Frees all child processes in list
 * Parameters: Head to child process list
 * Pre-Conditions:
 * Post-Conditions:
 */

/* Free all nodes */
void child_proc_free_all(struct child_proc* head){
	struct child_proc* tmp = NULL;
	struct child_proc* f = NULL;
	while(tmp!=NULL){
		f = tmp;
		tmp = tmp->next;
		free(f);
	}
	return; 
}
