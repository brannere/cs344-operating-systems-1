CC = gcc -pthread -g -Wall --std=gnu99
exe_file = line_processor

$(exe_file): line_sep.o plus_sign_thread.o main.o
	$(CC) line_sep.o plus_sign_thread.o main.o -o $(exe_file)
line_sep.o: line_sep.c
	$(CC) -c line_sep.c	
plus_sign_thread.o: plus_sign_thread.c
	$(CC) -c plus_sign_thread.c	
main.o: main.c
	$(CC) -c main.c
clean:
	rm -f *.o $(exe_file)