CC = gcc -g -Wall --std=gnu99

all: enc_server enc_client dec_server dec_client keygen

# enc_server: enc_server.c enc_server.o
# 	$(CC) enc_server.c -o enc_server
# enc_client: enc_client.c enc_client.o
# 	$(CC) enc_client.c -o enc_client
# dec_server: dec_server.c dec_server.o
# 	$(CC) dec_server.c -o dec_server
# dec_client: dec_client.c dec_client.o
# 	$(CC) dec_client.c -o dec_client
# keygen: keygen.c keygen.o
# 	$(CC) keygen.c -o keygen

enc_server.o: enc_server.c
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