CC = gcc -pthread -g -Wall --std=gnu99
exe_file = line_processor

$(exe_file): line.o input.o line_sep.o plus_sign_thread.o prog.o main.o
	$(CC) line.o input.o line_sep.o plus_sign_thread.o  prog.o main.o -o $(exe_file)
line.o: line.c
	$(CC) -c line.c	
input.o: input.c
	$(CC) -c input.c	
line_sep.o: line_sep.c
	$(CC) -c line_sep.c	
plus_sign_thread.o: plus_sign_thread.c
	$(CC) -c plus_sign_thread.c	
# output.o: output.c
# 	$(CC) -c output.c	
prog.o: prog.c
	$(CC) -c prog.c	
main.o: main.c
	$(CC) -c main.c
clean:
	rm -f *.o $(exe_file)