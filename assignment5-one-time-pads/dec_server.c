/**
 * Prgram Filename: dec_server.c
 * Author: Erick Branner
 * Date: 30 November 2020
 * Description:
 * Input:
 * Output:
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include "./otp.h"
#include "./globals.h"
// #define BUFF_SIZE 140000


// Error function used for reporting issues
void error(const char *msg) {
  perror(msg);
  exit(1);
} 
/*****/

// read data from socket until end of message sequence is seen
void
read_from_client(const int socket, char* buffer, const int buffersize, const int port,
                const char* end_seq){
  int chars_read;
  char acc[BUFF_SIZE]; 

  for(;;){
    chars_read = recv(socket, acc, buffersize, port);
    if(chars_read < 0){
      error("ERROR reading from socket");
    }
    strcat(buffer, acc);
    if(strstr(buffer, end_seq) != NULL) break;
  }
}

// send message to socket until the entire message is sent
void
send_to_client(const int socket, const char* msg, const int msg_len, const int port){
  int sent = 0;
  int chars_read = 0;
  for(;;){
    // chars_read = send(socket, msg, msg_len, port);
    chars_read = send(socket, msg+sent, msg_len-chars_read, port);

    if(chars_read < 0){
      error("ERROR writing to socket");
    }
    sent += chars_read;
    if(sent >= msg_len) break;
  }
  return;
}

/* Return false if indicating dec client sequence is not recieved */
int is_dec_client(const char* m){
  if(strstr(m, END_OF_CIPH) == NULL){
    return false; 
  }
  return true;
}

// get cipher text from message
char* get_ct(char* m){
  char* start = strstr(m, END_OF_CIPH);
	if(start == NULL){
		fprintf(stderr, "dec_server: could not find END_OF_CIPH\n");
		return NULL;
	}
  char* cat_str = calloc(1+1, sizeof(char)); // to concat 1 char in strcat
  // char* ret = NULL;//calloc(1+1, sizeof(char));
  char* ret = calloc(BUFF_SIZE, sizeof(char));//calloc(1+1, sizeof(char));
  /* The first end of pt message will start with a **/
  int i = 0;
	for(i = 0; m[i] != '*'; i++){
    cat_str[0] = m[i];
    // ret = realloc(ret,(i+1)*sizeof(char*));
    strcat(ret, cat_str);
  }
  free(cat_str);
  return ret;
}

// get key from message
char* get_k(const char* m){
  char* start = strstr(m, END_OF_CIPH);
  if(start == NULL){
    fprintf(stderr, "dec_server: could not find END_OF_CIPH\n");
    return NULL;
  }
  char* cat_str = calloc(1+1, sizeof(char)); // to concat 1 char in strcat
  // char* ret = NULL; //calloc(1+1, sizeof(char));
  char* ret = calloc(BUFF_SIZE, sizeof(char));//calloc(1+1, sizeof(char));

  /* The second end of end of key sequence will start with a **/
  int i = 0;
	for(i = 0; start[i+strlen(END_OF_CIPH)] != '*'; i++){
    cat_str[0] = start[i+strlen(END_OF_CIPH)];
    // ret = realloc(ret,(i+1)*sizeof(char*));
    strcat(ret, cat_str);
  }
  // if(i > strlen(m)){
  //   fprintf(stderr, "dec_server: could not find '*' in message");
  // 	free(cat_str);
	// 	return NULL;
  // }
  free(cat_str);
  return ret;
}

/* Network stuff */

// // Error function used for reporting issues
// void error(const char *msg) {
//   perror(msg);
//   exit(1);
// } 

// Set up the address struct for the server socket
void setupAddressStruct(struct sockaddr_in* address, 
                        int portNumber){
 
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);
  // Allow a client at any address to connect to this server
  address->sin_addr.s_addr = INADDR_ANY;
}

/*************/



// main thread
int main(int argc, char *argv[]){
    
  const char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
  int connectionSocket;
  char buffer[BUFF_SIZE];
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);

  // Check usage & args
  if (argc < 2) { 
    fprintf(stderr,"USAGE: %s port\n", argv[0]); 
    exit(1);
  } 
  
  // Create the socket that will listen for connections
  int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0) {
    error("ERROR opening socket");
  }

  // Set up the address struct for the server socket
  setupAddressStruct(&serverAddress, atoi(argv[1]));

  // Associate the socket to the port
  if (bind(listenSocket, 
          (struct sockaddr *)&serverAddress, 
          sizeof(serverAddress)) < 0){
    error("ERROR on binding");
  }

  // Start listening for connetions. Allow up to 5 connections to queue up
  listen(listenSocket, 5); 
  
  // Accept a connection, blocking if one is not available until one connects
  while(1){
    // Accept the connection request which creates a connection socket
    connectionSocket = accept(listenSocket, 
                (struct sockaddr *)&clientAddress, 
                &sizeOfClientInfo); 
    if (connectionSocket < 0){
      error("ERROR on accept");
    }

    // printf("SERVER: Connected to client running at host %d port %d\n", 
    //                       ntohs(clientAddress.sin_addr.s_addr),
    //                       ntohs(clientAddress.sin_port));

    /* So server can take multiple requests on the same port */

    pid_t spawnpid = -5;
    pid_t child_pid;
    int child_status;
    spawnpid = fork();
    switch(spawnpid){
      case -1:
        perror("fork() failed!");
        exit(1);
        break;     
      case 0:
        // Get the message from the client and display it
        memset(buffer, '\0', sizeof(buffer));
        // Read the client's message from the socket
        
        read_from_client(connectionSocket, buffer, sizeof(buffer), 0, END_OF_M);      
          // charsRead = recv(connectionSocket, buffer, BUFF_SIZE-1, 0);
        if(is_dec_client(buffer) == false){
          // fprintf(stdout,"buffer got: %s\n", buffer);
          send_to_client(connectionSocket, "bad*eom", 3, 0);
        }
        else{
		      /* HERE WE GET THE KEY AND PLAIN TEXT*/
          // printf("SERVER: I received this from the client: \"%s\"\n", buffer);
          char* cipher_t = get_ct(buffer);
          char* key = get_k(buffer);
	        /* ENCIPHER WITH THE KEY AND PLAIN TEXT */
          if(cipher_t == NULL || key == NULL){
            fprintf(stderr, "enc_server: plain text or key is null\n");
          }
          else{
            char* plain_text = decipher(cipher_t, key, valid_chars); 
            /* SEND CIPHER TEXT BACK*/
            if(plain_text == NULL){
		      		fprintf(stderr, "dec_server: error getting plain text\n");
		      	}else{
            	// Send a Success message back to the client
              strcat(plain_text, END_OF_M);
              send_to_client(connectionSocket, plain_text, strlen(plain_text), 0);
		      	}
          }
        }
        // Close the connection socket for this client
        close(connectionSocket); 
        break;

      default:
        child_pid = spawnpid;
        child_pid = waitpid(child_pid, &child_status, 0);
        break;  
    }
    // if(is_dec_client(buffer) == false){
    //   // fprintf(stdout,"buffer got: %s\n", buffer);
    //   send_to_client(connectionSocket, "bad", 3, 0);
    // }
    // else{
		//   /* HERE WE GET THE KEY AND PLAIN TEXT*/
    //   // printf("SERVER: I received this from the client: \"%s\"\n", buffer);
    //   char* cipher_t = get_ct(buffer);
    //   char* key = get_k(buffer);
	  //   /* ENCIPHER WITH THE KEY AND PLAIN TEXT */
    //   if(cipher_t == NULL || key == NULL){
    //     fprintf(stderr, "enc_server: plain text or key is null\n");
    //   }
    //   else{
    //     char* plain_text = decipher(cipher_t, key, valid_chars); 
    //     /* SEND CIPHER TEXT BACK*/
    //     if(plain_text == NULL){
		//   		fprintf(stderr, "dec_server: error getting plain text\n");
		//   	}else{
    //     	// Send a Success message back to the client
    //       send_to_client(connectionSocket, plain_text, strlen(plain_text), 0);
		//   	}
    //   }
    // }
    // // Close the connection socket for this client
    // close(connectionSocket); 
  }
  // Close the listening socket
  close(listenSocket); 


  return 0;
}
