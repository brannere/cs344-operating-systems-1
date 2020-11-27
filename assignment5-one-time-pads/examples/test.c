#include <string.h>
#include <stdio.h>
#define MODULO 27 // for encipher

// no lowercase ??
// enciphers message m from key k; returns cipher text; null if key is too short
char* encipher(const char* m, const char* k){

    if(strlen(m) < strlen(k)){
        fprintf(stdout, "Key is shorter than message; returning\n");
        return NULL;
    }
    // scrap the extra chars
    for(int i = 0; i < strlen(m); i++){

    }
    return NULL;
}



int main(){
    const char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
    printf("%d\n", strlen(valid_chars));
    fprintf(stdout, "ciphertext: %s\n",
            encipher("HELLO", "ABCDE"));


    return 0;
}
