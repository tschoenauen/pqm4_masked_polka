#ifndef MASKED_POLY_H
#define MASKED_POLY_H

#include "SABER_params.h"
#include <stdint.h>

uint32_t masked_MatrixVectorMulEncNTT(uint8_t ct0[SABER_POLYVECCOMPRESSEDBYTES], uint8_t ct1[SABER_SCALEBYTES_KEM], const uint8_t seed_s[SABER_NOISE_SEEDBYTES], const uint8_t seed_A[SABER_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], const uint8_t m[SABER_KEYBYTES], int compare);
void masked_InnerProdDecNTT(uint8_t m[SABER_KEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES]);
void masked_poly_cmp(size_t b_start, size_t b_end, size_t coeffs_size, uint32_t *rc, const uint16_t *mp,
                     int16_t *ref);
void finalize_cmp(uint32_t *bits);
#endif
