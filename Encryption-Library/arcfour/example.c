#include <stdio.h>
#include <arcfour.h>

int main() {
    char *key = "mykey";
    char *data = "Hello from arcfour library!";
    int16 key_len = strlen(key);
    int16 data_len = strlen(data);

    // Initialize arcfour
    Arcfour *cipher = rc4init((int8*)key, key_len);

    // Encrypt
    int8 *enc = rc4encrypt(cipher, (int8*)data, data_len);

    printf("Encrypted: ");
    for(int i=0; i<data_len; i++)
        printf("%.02x ", enc[i]);
    printf("\n");

    // Decrypt
    Arcfour *dec_cipher = rc4init((int8*)key, key_len);
    int8 *dec = rc4encrypt(dec_cipher, enc, data_len);
    printf("Decrypted: %s\n", dec);

    free(cipher);
    free(dec_cipher);
    free(enc);
    free(dec);

    return 0;
}
