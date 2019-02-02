#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Function to encrypt the data block with key data by xor */
void xor_encrypt(unsigned char *key, unsigned char *data, int *datalen, int keylen, int shift);

/* Function to get bitmask based on shift value passed */
int get_ls_mask(int shift);

/* Function to rotate the key block  by shift value */ 
void rotate_left(unsigned char* key, int key_len, int shift);
