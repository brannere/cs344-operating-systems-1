#include <string.h>
#include <stdio.h>
#define MODULO 27 // for encipher



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


// no lowercase ??
// enciphers message m from key k; returns cipher text; null if key is too short
char* encipher(const char* m, const char* k, const char* allowed){
    
    int tmpk = -1;
    int tmpm = -1;

    if(strlen(m) < strlen(k)){
        fprintf(stdout, "Key is shorter than message; returning\n");
        return NULL;
    }
    // scrap the extra chars
    for(int i = 0; i < strlen(m); i++){
        tmpk = char_idx(allowed, k[i]);
        printf("tmpk: %d\n", tmpk);
    }
    return NULL;
}

int main(){
    const char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
    printf("%d\n", strlen(valid_chars));
    fprintf(stdout, "ciphertext: %s\n",
            encipher("HELLO", "ABCDE", valid_chars));


    return 0;
}
