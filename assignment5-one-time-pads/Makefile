CC = gcc -g -Wall --std=gnu99

all: enc_server enc_client dec_server dec_client keygen

enc_server: enc_server.o otp.o
	$(CC) otp.o enc_server.o -o enc_server
enc_client: enc_client.o
	$(CC) enc_client.o -o enc_client
dec_server: dec_server.o
	$(CC) dec_server.o -o dec_server
dec_client: dec_client.o
	$(CC) dec_client.o -o dec_client
keygen: keygen.o
	$(CC) keygen.o -o keygen


otp.o: otp.c otp.h
	$(CC) -c otp.c
enc_server.o: otp.h enc_server.c
	$(CC) -c enc_server.c
enc_client.o: enc_client.c
	$(CC) -c enc_client.c
dec_server.o: dec_server.c
	$(CC) -c dec_server.c
dec_client.o: dec_client.c
	$(CC) -c dec_client.c
keygen.o: keygen.c
	$(CC) -c keygen.c

clean:
	rm -f *.o enc_server enc_client dec_server dec_client keygen
