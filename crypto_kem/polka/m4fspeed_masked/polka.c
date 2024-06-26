/**
 * POLKA scheme implementation
 * Written by Thibaud Schoenauen, 2024
 * 
*/

#include "polka.h"
#include "msk_poly.h"
#include <stdlib.h>
#include <stdio.h>
#include "bench.h"

int polka_dec_1(plk_cipher* cipher, plk_sk* secret_key, poly rp, poly e1p, poly e2p, poly c1b, poly c2b){
    poly_random(rp,random_binomial);
    poly_random(e1p,random_binomial);
    poly_random(e2p,random_binomial);



    poly c1p;
    poly_ring_mul(secret_key->pk->a,rp,c1p);
    poly_ring_add(c1p,e1p,c1p);

    poly c2p;
    poly_ring_mul(secret_key->pk->b,rp,c2p);
    poly_ring_add(c2p,e2p,c2p);

    poly_ring_add(cipher->c1,c1p,c1b);

    poly_ring_add(cipher->c2,c2p,c2b);

    return 0;
}

int polka_dec_2(plk_sk* secret_key, poly t, poly c1b){
    msk_poly msk_s;
    poly tmp;

    poly_ring_scal(P,c1b,tmp);

    poly_ring_cpy(secret_key->s,msk_s[0]); // To stay complient with pqm4 API. TODO : For release, we should use masked key.
    for(int i = 1; i < NSHARES; i ++) poly_ring_init(msk_s[i]);
    msk_poly_ring_mul(tmp,msk_s,t);
    
    return 0;
}

int polka_dec_3(plk_sk* secret_key, poly c2b, poly t, poly e2b, poly rb, poly c1b, poly e1b, int* flag){
    	
    poly mb;
    poly_ring_sub(c2b,t,mb);


    poly_ring_red(mb,P,e2b);

    if(poly_ring_norm(e2b) > 2*B ) *flag = 1;

    poly_ring_sub(c2b,e2b,rb);
    poly_ring_mul(rb,secret_key->pk->b_inv,rb);


    if(poly_ring_norm(rb) > 2*B ) *flag = 2;

    poly_ring_mul(secret_key->pk->a,rb,e1b);
    poly_ring_sub(c1b,e1b,e1b);

    if(poly_ring_norm(e1b) > 2*B ) *flag = 3;

    return 0;
}

int polka_dec_4(poly r, poly rb, poly rp, poly e1, poly e1b, poly e1p, poly e2, poly e2b, poly e2p, int* flag){
    poly_ring_sub(rb,rp,r);

    if(poly_ring_norm(r) > B) *flag =  4;

    poly_ring_sub(e1b,e1p,e1);


    if(poly_ring_norm(e1) > B) *flag = 5;

    poly_ring_sub(e2b,e2p,e2);

    if(poly_ring_norm(e2) > B) *flag =  6;
    return 0;
}

int polka_dec_5(plk_cipher* cipher, poly r, poly e1, poly e2, unsigned char* message, unsigned long long* message_length, unsigned char* npub, int flag,
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
        const unsigned char*)){
            unsigned char key[32];
		
	    poly rs,e1s,e2s; //Generating random polynomials in case of decrpytion error.
	    poly_random(rs ,random_bounded_uniform);
	    poly_random(e1s,random_bounded_uniform);
            poly_random(e2s,random_bounded_uniform);

	    if(flag == 0) key_build(r,e1,e2,key);
	    else key_build(rs,e1s,e2s,key);
	    return dem_D(message,message_length, NULL, cipher->c0, cipher->c0_l, NULL, 0, npub, key);

        }



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
    ){
    poly r;
    poly e1;
    poly e2;

    poly_random(r,random_binomial);
    poly_random(e1,random_binomial);
    poly_random(e2,random_binomial);


    poly_ring_mul(r,public_key->a,cipher->c1);
    poly_ring_add(cipher->c1,e1,cipher->c1);

    poly_ring_mul(r,public_key->b,cipher->c2);
    poly_ring_add(cipher->c2,e2,cipher->c2);

    
    unsigned char key[32];
    key_build(r,e1,e2,key);
    
    dem_E(cipher->c0,&cipher->c0_l,message,message_length,NULL,0,NULL,npub,key);
    
    return 0;
}


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
        const unsigned char*)){

    
    int flag = 0;
	
    start_bench(plk_dec_1);
    poly r_prime;
    poly e1_prime;
    poly e2_prime;
    poly c1_bar;
    poly c2_bar;
    polka_dec_1(cipher,secret_key,r_prime,e1_prime,e2_prime,c1_bar,c2_bar);
    stop_bench(plk_dec_1);

    start_bench(plk_dec_2);
    poly temp;
    polka_dec_2(secret_key,temp,c1_bar);
    stop_bench(plk_dec_2);

    start_bench(plk_dec_3);
    poly e2_bar;
    poly e1_bar;
    poly r_bar;
    polka_dec_3(secret_key,c2_bar,temp,e2_bar, r_bar,c1_bar,e1_bar,&flag);
    stop_bench(plk_dec_3);

    start_bench(plk_dec_4);
    poly r;
    poly e1;
    poly e2;
    polka_dec_4(r,r_bar,r_prime,e1,e1_bar,e1_prime,e2,e2_bar,e2_prime,&flag);
    stop_bench(plk_dec_4);

    start_bench(plk_dec_5);
    polka_dec_5(cipher,r,e1,e2,message,message_length,npub,flag,key_build,dem_D);
    stop_bench(plk_dec_5);

    return 0;
}
