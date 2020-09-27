CC = gcc -g --std=gnu99 
exe_file = movies

$(exe_file): dynarray.o movie.o prog.o main.o
	$(CC) dynarray.o movie.o prog.o main.o -o $(exe_file)
dynarray.o: dynarray.c
	$(CC) -c dynarray.c
movie.o: movie.c
	$(CC) -c movie.c
prog.o: prog.c
	$(CC) -c prog.c	
main.o: main.c
	$(CC) -c main.c
clean:
	rm -f *.out *.o $(exe_file)
