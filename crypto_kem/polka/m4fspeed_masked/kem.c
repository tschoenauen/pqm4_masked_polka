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
#include <string.h>


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
}

int convert_pk_str2vec(const plk_pk* src, unsigned char* rcv){
  memcpy(&rcv[0*(N*4)], src->a    , sizeof(poly));
  memcpy(&rcv[1*(N*4)], src->b    , sizeof(poly));
  memcpy(&rcv[2*(N*4)], src->b_inv, sizeof(poly));
}

int convert_sk_vec2str(const unsigned char* src, plk_sk* rcv){
  memcpy(rcv->s,src,sizeof(poly));
  convert_pk_vec2str(rcv->pk,&src[N*4]);
  return 0;
}

int convert_sk_str2vec(const plk_sk* src, unsigned char* rcv){
  memcpy(rcv,src->s,sizeof(poly));
  convert_pk_str2vec(&src[N*4],rcv->pk);
  return 0;
}

int convert_ct_vec2str(plk_cipher* rcv, const unsigned char* src){
  return 0;
}

int convert_ct_str2vec(plk_cipher* rcv, const unsigned char* src){
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
  keygen((plk_pk*) pk, (plk_sk*) sk);
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
	unsigned char npub[16] = "000000000000000"; //Does not impact performances so it is a fix value for performances benchmarks.
	plk_pk pk;
	convert_pk_vec2str();
	polka_encrypt(ss,CRYPTO_BYTES,(plk_pk*) pk, (plk_cipher*) ct, npub, sha256_build_key, saturnin_aead_encrypt);
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
  unsigned char npub[16] = "000000000000000"; //Does not impact performances so it is a fix value for performances benchmarks.
  polka_decrypt((plk_cipher*) ct,(plk_sk*) sk, ss, CRYPTO_BYTES, npub, sha256_build_key, saturnin_aead_encrypt);
  return 0;
}
