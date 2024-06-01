#include "poly.h"
#include "prg.h"
#include "keygen.h"
#pragma once

typedef struct polka_cipher_t{
    unsigned char* c0;
    unsigned long long c0_l;
    poly c1;
    poly c2;
} plk_cipher;

void print_cipher(plk_cipher* cipher);

/**
 * Encrypt the message using the public key and store the result in cipher. dem is the symetric part.
 * dem_E is complient with NIST API for CAESAR competition. Parameters are : 32bits message, 32bits key, 32bits cipher.
 * cipher, cipher length, message, message length, (unused) AD, (unused) AD length, (unused) nsec, public nonce and 32 bitkey.
 * As it should not impact the efficiency of the target algorithm, it only considers fixed size messages for now.
*/
int polka_encrypt(unsigned char* message, unsigned long long message_length, plk_pk* public_key, plk_cipher* cipher, unsigned char* npub,
    int (*key_build)(
        poly r, poly e1, poly e2,
        unsigned char* key
    ),
    int (*dem_E)(
        unsigned char*,       unsigned long long*,
        const unsigned char*, unsigned long long,
        const unsigned char*, unsigned long long,
        const unsigned char*, const unsigned char*,
        const unsigned char*)
    );


/**
 * Decrypt the cipher using the private key and store the result in message. dem is the symetric part.
 * dem_D parameters are : cipher, 32bit key, message, message_length
*/
int polka_decrypt(plk_cipher* cipher, plk_sk* secret_key, unsigned char* message, unsigned long long* message_length, unsigned char* npub,
    int (*key_build)(
        poly r, poly e1, poly e2,
        unsigned char* key
    ),
    int (*dem_D)(
        unsigned char*, unsigned long long*,
        unsigned char*,
        const unsigned char*, unsigned long long,
        const unsigned char*, unsigned long long,
        const unsigned char*,
        const unsigned char*));
