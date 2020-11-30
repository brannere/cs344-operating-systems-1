/**
 * Prgram Filename: otp.h
 * Author: Erick Branner
 * Date: 30 November 2020
 * Description:
 * Input:
 * Output:
 *
*/

#ifndef OTP_H
#define OTP_H

char* encipher(const char* m, const char* k, const char* allowed);
char* decipher(const char* ct, const char* k, const char* allowed);

#endif
