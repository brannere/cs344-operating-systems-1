CC = gcc --std=gnu99 
exe_file = movies

$(exe_file): list.o prog.o main.o
	$(CC) list.o prog.o main.o -o $(exe_file)
list.o: list.c
	$(CC) -c list.c
prog.o: prog.c
	$(CC) -c prog.c	
main.o: main.c
	$(CC) -c main.c
clean:
	rm -f *.out *.o $(exe_file)
