CC = gcc -g --std=gnu99 
exe_file = movies_by_year

$(exe_file): prog.o main.o
	$(CC)  prog.o main.o -o $(exe_file)
prog.o: prog.c
	$(CC) -c prog.c	
main.o: main.c
	$(CC) -c main.c
clean:
	rm -f *.out *.o $(exe_file)
