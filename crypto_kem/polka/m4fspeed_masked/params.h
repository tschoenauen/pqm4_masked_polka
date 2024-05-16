
#include <stdint.h>
#pragma once

#define POLKA_SECRETKEYBYTES 16384 // Size of the secret key.
#define POLKA_PUBLICKEYBYTES 12288 // Size of the public key.
#define POLKA_CIPHERTEXTBYTES 16   // Size of the message/
#define POLKA_SSBYTES 8248         // Size of the ciphertext.

#define N 1024      // Polynomial degree. Standard key element
#define Q 59393     // Value used as a modulo. Standard key element.
#define K 2         // Noise parameter for binomial distribution. Standard key element.
#define B 3801152   // norm Bound. Equal to K*Q*sqrt(N). Standard key element.
#define P 5         // Polka standard key element.

#ifndef NSHARES
#define NSHARES 2    // Shares used for masking
#endif
typedef uint32_t c_int; //In case it needs to be changed later. If changed, change hash_feed definition in polka.c
