#include "arcfour.h"

// Number of initial key stream bytes to discard (security measure)
#define RC4_DISCARD 256

// ----------------------------
// RC4 Key Scheduling Algorithm (KSA)
// Initializes permutation array S based on the key
// ----------------------------
Arcfour *rc4init(int8 *key, int16 size) {
    Arcfour *p = malloc(sizeof(Arcfour));
    if (!p) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // Initialize S with values 0..255
    for(int16 i = 0; i < 256; i++)
        p->s[i] = i;

    p->i = 0;
    p->j = 0;

    // Key mixing
    int8 j = 0;
    for(int16 i = 0; i < 256; i++) {
        j = (j + p->s[i] + key[i % size]) & 0xFF;
        int8 tmp = p->s[i];
        p->s[i] = p->s[j];
        p->s[j] = tmp;
    }

    // Reset indices for PRGA
    p->i = 0;
    p->j = 0;

    // Discard first RC4_DISCARD bytes for security
    for(int k = 0; k < RC4_DISCARD; k++)
        rc4byte(p);

    return p;
}

// ----------------------------
// RC4 Pseudo-Random Generation Algorithm (PRGA)
// Generates one byte from the key stream
// ----------------------------
int8 rc4byte(Arcfour *p) {
    p->i = (p->i + 1) & 0xFF;
    p->j = (p->j + p->s[p->i]) & 0xFF;

    // Swap S[i] and S[j]
    int8 tmp = p->s[p->i];
    p->s[p->i] = p->s[p->j];
    p->s[p->j] = tmp;

    // Output key stream byte
    return p->s[(p->s[p->i] + p->s[p->j]) & 0xFF];
}

// ----------------------------
// RC4 Encrypt/Decrypt Function
// XORs input data with key stream bytes
// ----------------------------
int8 *rc4encrypt(Arcfour *p, int8 *data, int16 size) {
    int8 *out = malloc(size);
    if (!out) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for(int16 i = 0; i < size; i++)
        out[i] = data[i] ^ rc4byte(p);

    return out;
}
