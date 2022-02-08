#ifndef PARAMS_H
#define PARAMS_H

#define KYBER_K 3

/* Don't change parameters below this line */

#define KYBER_N 256
#define KYBER_Q 3329

#define KYBER_ETA 2

#define KYBER_SYMBYTES 32 /* size in bytes of hashes, and seeds */
#define KYBER_SSBYTES 32  /* size in bytes of shared key */
#define KYBER_DU 10
#define KYBER_DV 4

#define KYBER_POLYBYTES 384
#define KYBER_POLYVECBYTES (KYBER_K * KYBER_POLYBYTES)

#define KYBER_POLYCOMPRESSEDBYTES 128
#define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 320)

#define KYBER_INDCPA_MSGBYTES KYBER_SYMBYTES
#define KYBER_INDCPA_PUBLICKEYBYTES (KYBER_POLYVECBYTES + KYBER_SYMBYTES)
#define KYBER_INDCPA_SECRETKEYBYTES (KYBER_POLYVECBYTES)
#define KYBER_INDCPA_BYTES                                                     \
  (KYBER_POLYVECCOMPRESSEDBYTES + KYBER_POLYCOMPRESSEDBYTES)

#define KYBER_PUBLICKEYBYTES (KYBER_INDCPA_PUBLICKEYBYTES)
#define KYBER_SECRETKEYBYTES                                                   \
  (KYBER_INDCPA_SECRETKEYBYTES + KYBER_INDCPA_PUBLICKEYBYTES +                 \
   2 * KYBER_SYMBYTES) /* 32 bytes of additional space to save H(pk) */
#define KYBER_CIPHERTEXTBYTES KYBER_INDCPA_BYTES

#endif
