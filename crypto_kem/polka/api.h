#ifndef API_H
#define API_H

#include "params.h"

#define CRYPTO_SECRETKEYBYTES POLKA_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES POLKA_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES POLKA_CIPHERTEXTBYTES
#define CRYPTO_BYTES POLKA_SSBYTES

#define CRYPTO_ALGNAME "POLKA"

int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int crypto_kem_enc(unsigned char *ct, unsigned char *ss,
                   const unsigned char *pk);

int crypto_kem_dec(unsigned char *ss, const unsigned char *ct,
                   const unsigned char *sk);

#endif
