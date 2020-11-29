#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "./otp.h"
#include "./globals.h"


char* get_pt(char* m){
  char* cat_str = calloc(1+1, sizeof(char)); // to concat 1 char in strcat
  char* ret = NULL;//calloc(1+1, sizeof(char));
  /* The first end of pt message will start with a **/
  for(int i = 0; m[i] != '*'; i++){
    cat_str[0] = m[i];
    ret = realloc(ret,(i+1)*sizeof(char*));
    strcat(ret, cat_str);
  }
  return ret;
}

char* get_k(char* m){
  char* start = strstr(m, END_OF_PT);
  char* cat_str = calloc(1+1, sizeof(char)); // to concat 1 char in strcat
  char* ret = NULL; //calloc(1+1, sizeof(char));
  /* The second end of end of key sequence will start with a **/
  for(int i = 0; m[i+*start] != '*'; i++){
    cat_str[0] = m[i+*start];
    ret = realloc(ret,(i+1)*sizeof(char*));
    strcat(ret, cat_str);
  }
  return ret;
}

/* Network stuff */

// Error function used for reporting issues
void error(const char *msg) {
  perror(msg);
  exit(1);
} 

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




int main(int argc, char *argv[]){
    
  const char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
  int connectionSocket, charsRead;
  char buffer[256];
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

    printf("SERVER: Connected to client running at host %d port %d\n", 
                          ntohs(clientAddress.sin_addr.s_addr),
                          ntohs(clientAddress.sin_port));

    // Get the message from the client and display it
    memset(buffer, '\0', 256);
    // Read the client's message from the socket
    charsRead = recv(connectionSocket, buffer, 255, 0); 
    if (charsRead < 0){
      error("ERROR reading from socket");
    }
		/* HERE WE GET THE KEY AND PLAIN TEXT*/
    printf("SERVER: I received this from the client: \"%s\"\n", buffer);
    char* foo = get_pt(buffer);
    printf("foo: %s\n",foo);
    char* bar = get_k(buffer);
    printf("bar: %s\n",bar);
	 /* ENCIPHER WITH THE KEY AND PLAIN TEXT */
    // char* cipher_text = encipher("HELLO", "XMCKL", valid_chars); 
    /* SEND CIPHER TEXT BACK*/
		
    // Send a Success message back to the client
    charsRead = send(connectionSocket, 
                    "I am the server, and I got your message", 39, 0); 
    if (charsRead < 0){
      error("ERROR writing to socket");
    }
    // Close the connection socket for this client
    close(connectionSocket); 
  }
  // Close the listening socket
  close(listenSocket); 


  return 0;
}
