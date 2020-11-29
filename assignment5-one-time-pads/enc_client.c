#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>  // ssize_t
#include <sys/socket.h> // send(),recv()
#include <netdb.h>      // gethostbyname()
#include "./globals.h"
#define BUFF_SIZE 80000




void char_replace(char* source, const int c, const int t){
	/* 	If the current index is the char to change, 
			change its value */
	for(int i = 0; i < strlen(source); i++){
		if(source[i] == c){
			source[i] = t;
		}
	}
	return;
}

// MUST BE A UNIQUE SET OF CHARS
// finds idx of c in str
// returns -1 if not found or len is 0
int char_idx(const char* str, const char c){
    if(strlen(str) <= 0) return -1;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == c){
            return i;
        }
    }
    return -1;
}

//returns pointer to file contents in char array
char* read_file(const char* file){

	  FILE* f = fopen(file, "r");
		if(f == NULL){
			fprintf(stderr, "enc_client: error opening file\n");
			exit(1);
		}
    char* curr_line = NULL;
    char* ret = NULL;
    size_t len = 0;
    ssize_t nread; 
    
		/* For each line, make a movie */
    nread = getline(&curr_line, &len, f);
		if(nread == -1) curr_line = NULL;
    fclose(f);
    ret = calloc(strlen(curr_line)+1, sizeof(char));
    strcpy(ret, curr_line);
		return ret; 
    // printf("Processed file %s and parsed data for %d movies\n", f, counter);
    // return NULL;
}

void verify_args(char* file_conts, char* key_conts, const char* allowed){
	//argv[1] plaintext
	//argv[2] key
	// file_conts = read_file(argv[1]);
  // key_conts = read_file(argv[2]);
	// printf("file conts: %s\n", file_conts);
	// key > message?
  char_replace(file_conts, '\n', '\0');
  char_replace(key_conts, '\n', '\0');
	if(strlen(key_conts) < strlen(file_conts)){
		fprintf(stderr, "enc_cleint: message is shorter than key\n");
		exit(1);
	}
	for(int i = 0; i < strlen(file_conts); i++){
		if(char_idx(allowed, file_conts[i]) == -1){
			fprintf(stderr, "enc_client: invalid char in file contents\n");
			exit(1);
		}
	}
	for(int i = 0; i < strlen(key_conts); i++){
		if(char_idx(allowed, key_conts[i]) == -1){
			fprintf(stderr, "enc_client: invalid char in key\n");
			exit(1);
		}
	}

	return;
}

void enough_args(const int argc, char** argv, char* allowed){
	if(argc < 4){
    fprintf(stderr,"USAGE: %s plaintext key port\n", argv[0]);
		exit(0);
	}
	// there's enough args.. 
	return;
}


/**
* Client code
* 1. Create a socket and connect to the server specified in the command arugments.
* 2. Prompt the user for input and send that input as a message to the server.
* 3. Print the message received from the server and exit the program.
*/

// Error function used for reporting issues
void error(const char *msg) { 
  perror(msg); 
  exit(0); 
} 

// Set up the address struct
void setupAddressStruct(struct sockaddr_in* address, 
                        int portNumber, 
                        char* hostname){
 
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);

  // Get the DNS entry for this host name
  struct hostent* hostInfo = gethostbyname(hostname); 
  if (hostInfo == NULL) { 
    fprintf(stderr, "CLIENT: ERROR, no such host\n"); 
    exit(0); 
  }
  // Copy the first IP address from the DNS entry to sin_addr.s_addr
  memcpy((char*) &address->sin_addr.s_addr, 
        hostInfo->h_addr_list[0],
        hostInfo->h_length);
}



int main(int argc, char *argv[]) {

  char valid_chars[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	enough_args(argc, argv, valid_chars);
  
	char* m_conts = read_file(argv[1]);
  char* key_conts = read_file(argv[2]);
  
  if(m_conts == NULL || key_conts == NULL){
    fprintf(stderr, "enc_client: file contents or key contents are null\n");
  }
  verify_args(m_conts, key_conts, valid_chars);

  int socketFD, portNumber, charsWritten, charsRead;
  struct sockaddr_in serverAddress;
  char buffer[BUFF_SIZE];
  // Check usage & args
	// verify the key and plaintext has good chars

  // Create a socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketFD < 0){
    error("CLIENT: ERROR opening socket");
  }

   // Set up the server address struct
  setupAddressStruct(&serverAddress, atoi(argv[3]), "localhost");

  // Connect to server
  if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    error("CLIENT: ERROR connecting");
  }
  
	

	// Get input message from user
  // printf("CLIENT: Enter text to send to the server, and then hit enter: ");
  // Clear out the buffer array
  memset(buffer, '\0', sizeof(buffer));
  // Get input from the user, trunc to buffer - 1 chars, leaving \0
  // fgets(buffer, sizeof(buffer) - 1, stdin);
  // strcpy(buffer, file_conts);
  // buffer[strcspn(buffer, "\n")] = '\0'; 
  // strcat(buffer, key_conts);
  // Remove the trailing \n that fgets adds
  // buffer[strcspn(buffer, "\n")] = '\0'; 
  
  /*  Put the plaintext in the buffer
      and place end of pt sequence */
  strcpy(buffer, m_conts);
  strcat(buffer, END_OF_PT);

  /*  Put the key in the buffer
      and place end of key sequnce*/
  strcat(buffer, key_conts);
  strcat(buffer, END_OF_K);

  /* Put end of message sequence*/
  strcat(buffer, END_OF_M);


  /* SEND TO SERVER */

  // Send message to server
  // Write to the server
  charsWritten = send(socketFD, buffer, strlen(buffer), 0); 
  if (charsWritten < 0){
    error("CLIENT: ERROR writing to socket");
  }
  if (charsWritten < strlen(buffer)){
    printf("CLIENT: WARNING: Not all data written to socket!\n");
  }

  // Get return message from server
  // Clear out the buffer again for reuse
  memset(buffer, '\0', sizeof(buffer));
  // Read data from the socket, leaving \0 at end
  charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); 
  if (charsRead < 0){
    error("CLIENT: ERROR reading from socket");
  }
  printf("CLIENT: I received this from the server: \"%s\"\n", buffer);

  // Close the socket
  close(socketFD); 
  return 0;
}