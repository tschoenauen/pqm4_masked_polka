/* Copyright 2022 UCLouvain, Belgium and PQM4 contributors
 *
 * This file is part of pqm4_masked.
 *
 * pqm4_masked is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, version 3.
 *
 * pqm4_masked is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * pqm4_masked. If not, see <https://www.gnu.org/licenses/>.
 */
#include "api.h"
#include "fips202.h"
#include "params.h"
#include "polka.h"
#include "saturnin.h"
#include "randombytes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debug_dev.h"

int sha256_build_key(poly r, poly e1, poly e2, unsigned char* key){
    uint8_t hash_feed[3*N*4]; // Contains coefficients of 3 polynomials containing N coeffs each four times bigger than uint8.
    size_t hf_l = 3*N*4;

    memcpy(&hash_feed[0*(N*4)],r, N*4); //Copying first poly;
    memcpy(&hash_feed[1*(N*4)],e1,N*4);
    memcpy(&hash_feed[2*(N*4)],e2,N*4);

    shake256(key,32,hash_feed,hf_l);
    return 0;
}

int convert_pk_vec2str(const unsigned char* src, plk_pk* rcv){
  memcpy(rcv->a    ,&src[0*(N*4)], sizeof(poly));
  memcpy(rcv->b    ,&src[1*(N*4)], sizeof(poly));
  memcpy(rcv->b_inv,&src[2*(N*4)], sizeof(poly));
  return 0;
}

int convert_pk_str2vec(const plk_pk* src, unsigned char* rcv){
  memcpy(&rcv[0*(N*4)], src->a    , sizeof(poly));
  memcpy(&rcv[1*(N*4)], src->b    , sizeof(poly));
  memcpy(&rcv[2*(N*4)], src->b_inv, sizeof(poly));
  return 0;
}

int convert_sk_vec2str(const unsigned char* src, plk_sk* rcv){
  memcpy(rcv->s,src,sizeof(poly));
  convert_pk_vec2str(&src[N*4],rcv->pk);
  return 0;
}

int convert_sk_str2vec(const plk_sk* src, unsigned char* rcv){
  memcpy(rcv,src->s,sizeof(poly));
  convert_pk_str2vec(src->pk,&rcv[N*4]);
  return 0;
}

int convert_ct_vec2str(const unsigned char* src, plk_cipher* rcv){
  memcpy(rcv->c1,   &src[N*0], sizeof(poly));
  memcpy(rcv->c2,   &src[N*1], sizeof(poly));
  memcpy(&rcv->c0_l, &src[N*2], sizeof(unsigned long long));
  memcpy(rcv->c0, &src[N*2+8], sizeof(char)*rcv->c0_l);
  return 0;
}

int convert_ct_str2vec(const plk_cipher* src, unsigned char* rcv){
  memcpy(&rcv[N*0], src->c1  , sizeof(poly));
  memcpy(&rcv[N*1], src->c2  , sizeof(poly));
  memcpy(&rcv[N*2], &src->c0_l, sizeof(unsigned long long));
  memcpy(&rcv[N*2+8], src->c0, sizeof(poly));
	
  return 0;
}


/*************************************************
 * Name:        crypto_kem_keypair
 *
 * Description: Generates public and private key
 *              for CCA-secure Kyber key encapsulation mechanism
 *
 * Arguments:   - unsigned char *pk: pointer to output public key (an already
 *allocated array of CRYPTO_PUBLICKEYBYTES bytes)
 *              - unsigned char *sk: pointer to output private key (an already
 *allocated array of CRYPTO_SECRETKEYBYTES bytes)
 *
 * Returns 0 (success)
 **************************************************/
int crypto_kem_keypair(unsigned char *pk, unsigned char *sk) {
  DEBUG_PRINT("Generating keys...");
  plk_pk public_key;
  plk_sk secret_key;
  keygen(&secret_key,&public_key);
  convert_pk_str2vec(&public_key,pk);
  convert_sk_str2vec(&secret_key,sk);
  DEBUG_PRINT("SUCCESS\n");
  return 0;
}

/*************************************************
 * Name:        crypto_kem_enc
 *
 * Description: Generates cipher text and shared
 *              secret for given public key
 *
 * Arguments:   - unsigned char *ct:       pointer to output cipher text (an
 *already allocated array of CRYPTO_CIPHERTEXTBYTES bytes)
 *              - unsigned char *ss:       pointer to output shared secret (an
 *already allocated array of CRYPTO_BYTES bytes)
 *              - const unsigned char *pk: pointer to input public key (an
 *already allocated array of CRYPTO_PUBLICKEYBYTES bytes)
 *
 * Returns 0 (success)
 **************************************************/
int crypto_kem_enc(unsigned char *ct, unsigned char *ss,
                   const unsigned char *pk) {
  DEBUG_PRINT("Encrypting...");
  unsigned char npub[16] = "000000000000000"; //Does not impact performances so it is a fix value for performances benchmarks.
  plk_pk public_key;
  convert_pk_vec2str(pk,&public_key);
  plk_cipher cipher_text;	
  polka_encrypt(ss,CRYPTO_BYTES,&public_key, &cipher_text, npub, sha256_build_key, saturnin_aead_encrypt);
  convert_ct_str2vec(&cipher_text,ct);
  DEBUG_PRINT("SUCCESS\n");
  return 0;
}

/*************************************************
 * Name:        crypto_kem_dec
 *
 * Description: Generates shared secret for given
 *              cipher text and private key
 *
 * Arguments:   - unsigned char *ss:       pointer to output shared secret (an
 *already allocated array of CRYPTO_BYTES bytes)
 *              - const unsigned char *ct: pointer to input cipher text (an
 *already allocated array of CRYPTO_CIPHERTEXTBYTES bytes)
 *              - const unsigned char *sk: pointer to input private key (an
 *already allocated array of CRYPTO_SECRETKEYBYTES bytes)
 *
 * Returns 0.
 *
 * On failure, ss will contain a pseudo-random value.
 **************************************************/
int crypto_kem_dec(unsigned char *ss, const unsigned char *ct,
                   const unsigned char *sk) {
  DEBUG_PRINT("Decrypting...");
  unsigned char npub[16] = "000000000000000"; //Does not impact performances so it is a fix value for performances benchmarks.
  plk_sk secret_key;
  convert_sk_vec2str(sk,&secret_key);
  plk_cipher cipher_text;
  convert_ct_vec2str(ct,&cipher_text);
  unsigned long long ss_l;
  polka_decrypt(&cipher_text, &secret_key, ss, &ss_l, npub, sha256_build_key, saturnin_aead_decrypt);
  
  DEBUG_PRINT("SUCCESS\n");
  return 0;
}
