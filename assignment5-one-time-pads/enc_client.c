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
    char* curr_line = NULL;
    size_t len = 0;
    ssize_t nread; 
    char* token;
    unsigned int counter = 0;
    
		/* For each line, make a movie */
    while((nread = getline(&curr_line, &len, f)) != -1){
			fprintf(stdout, "curr line: %s\n", curr_line);
			counter++;
		}
    free(curr_line);
    fclose(f);
    // printf("Processed file %s and parsed data for %d movies\n", f, counter);
    return NULL;
}

void verify_args(const char* ad, const char* allowed){
	//argv[1] plaintext
	//argv[2] key
	
	return;
}

void enough_args(const int argc, const char* argv[], char* allowed){
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

  char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	enough_args(argc, argv, valid_chars);
	read_file(argv[1]);

  int socketFD, portNumber, charsWritten, charsRead;
  struct sockaddr_in serverAddress;
  char buffer[256];
  // Check usage & args
	// verify the key and plaintext has good chars

  // Create a socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketFD < 0){
    error("CLIENT: ERROR opening socket");
  }

   // Set up the server address struct
  setupAddressStruct(&serverAddress, atoi(argv[2]), argv[1]);

  // Connect to server
  if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    error("CLIENT: ERROR connecting");
  }
  
	

	// Get input message from user
  printf("CLIENT: Enter text to send to the server, and then hit enter: ");
  // Clear out the buffer array
  memset(buffer, '\0', sizeof(buffer));
  // Get input from the user, trunc to buffer - 1 chars, leaving \0
  fgets(buffer, sizeof(buffer) - 1, stdin);
  // Remove the trailing \n that fgets adds
  buffer[strcspn(buffer, "\n")] = '\0'; 


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