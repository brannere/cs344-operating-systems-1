#ifndef CHILD_PROC_H
#define CHILD_PROC_H

struct child_proc{
  pid_t pid;
	int status;
	struct child_proc* next;
};

struct child_proc* child_proc_create();
// struct child_proc* child_proc_add(pid_t pid);
struct child_proc* child_proc_insert(struct child_proc* head, pid_t pid);
void child_proc_print_all(struct child_proc* head);
void child_proc_free_all(struct child_proc* head);
#endif