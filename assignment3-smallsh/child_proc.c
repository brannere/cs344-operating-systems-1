#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./child_proc.h"

struct child_proc* child_proc_create(){
	struct child_proc* output = malloc(sizeof(struct child_proc));
	output->next = NULL;
	output->pid = 0; 
	output->status = 0;
	return output;  
}

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

void child_proc_print_all(struct child_proc* head){
	for(struct child_proc* tmp = head; tmp != NULL; tmp=tmp->next){
		fprintf(stdout, "children[%p]->pid: %d\n", tmp, tmp->pid);
	}
	return;
}

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
