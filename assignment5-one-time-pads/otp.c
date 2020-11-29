#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./otp.h"
//#define MODULO 27 // for encipher

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


// no lowercase ??
// enciphers message m from key k; returns cipher text; null if key is too short
// returns null on calling function errors (-1)
char* encipher(const char* m, const char* k, const char* allowed){
    
    int tmpk = -1;
    int tmpm = -1;
    int sum = 0;
    char* cat_str = calloc(1+1, sizeof(char)); // to concat 1 char in strcat
    char* ct = calloc(strlen(allowed)+1, sizeof(char));
     
    if(strlen(m) > strlen(k)){
        fprintf(stdout, "Key is shorter than message; returning\n");
        return NULL;
    }
    // scrap the extra chars
    for(int i = 0; i < strlen(m); i++){
        tmpk = char_idx(allowed, k[i]);
        tmpm = char_idx(allowed, m[i]);
        sum = tmpk + tmpm;
    
        //error check 
        if(tmpk == -1 || tmpm == -1) return NULL;
        if(sum > (strlen(allowed)-1)){
            sum -= strlen(allowed);
            //printf("sum > len\n");
        }
        cat_str[0] = allowed[sum];
        strcat(ct, cat_str);
    }
    free(cat_str);
    return ct;
}

// Assumes key is at least the same length of the ct and pt
char* decipher(const char* ct, const char* k, const char* allowed){ 
    int tmpk = -1;
    int tmpct = -1;
    int diff = 0;
    char* cat_str = calloc(1+1, sizeof(char)); // to concat 1 char in strcat
    char* pt = calloc(strlen(allowed)+1, sizeof(char));
     
    if(strlen(ct) < strlen(k)){
        fprintf(stdout, "Cipher text is shorter than message; returning\n");
        return NULL;
    }
    // scrap the extra chars
    for(int i = 0; i < strlen(ct); i++){
        tmpk = char_idx(allowed, k[i]);
        tmpct = char_idx(allowed, ct[i]);
        diff = tmpct - tmpk;
    
        //error check 
        if(tmpk == -1 || tmpct == -1) return NULL;
        if(diff < 0){
            diff += strlen(allowed);
            //printf("diff < 0\n");
        }
        cat_str[0] = allowed[diff];
        strcat(pt, cat_str);
    }
    free(cat_str);
    return pt;
}

/*int main(){
    const char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
    char* cipher = encipher("HELLO", "XMCKL", valid_chars);
    fprintf(stdout, "ciphertext: %s\n", cipher);
    
    char* plain = decipher(cipher, "XMCKL", valid_chars);
    fprintf(stdout, "de-cipherd ciphertext: %s\n", plain);
    
    free(plain);
    free(cipher);
        
    return 0;
}*/
