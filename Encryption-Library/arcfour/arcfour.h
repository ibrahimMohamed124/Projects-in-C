#ifndef ARCFOUR_H
#define ARCFOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Type definitions
typedef unsigned char int8;       // 8-bit byte
typedef unsigned short int int16;  // 16-bit unsigned integer

// Structure representing RC4 state
struct s_arcfour {
    int16 i, j;        // indices for PRGA
    int8 s[256];       // permutation array
};

typedef struct s_arcfour Arcfour;

// Function prototypes

// Initialize RC4 state with the given key
// Discards first RC4_DISCARD bytes for security
Arcfour *rc4init(int8* key, int16 size);

// Generate one byte from the key stream
int8 rc4byte(Arcfour *p);

// Encrypt or decrypt data (XOR with key stream)
int8 *rc4encrypt(Arcfour *p, int8 *data, int16 size);

#endif
