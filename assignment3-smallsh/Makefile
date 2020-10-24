CC = gcc -g -Wall --std=gnu99
exe_file = smallsh

$(exe_file): cmd_line.o command.o prog.o main.o
	$(CC)  cmd_line.c command.o prog.o main.o -o $(exe_file)
command.o: command.c
	$(CC) -c command.c	
cmd_line.o: cmd_line.c
	$(CC) -c cmd_line.c	
prog.o: prog.c
	$(CC) -c prog.c	
main.o: main.c
	$(CC) -c main.c
clean:
	rm -f *.out *.o $(exe_file)