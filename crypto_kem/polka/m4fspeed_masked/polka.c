/**
 * POLKA scheme implementation
 * Written by Thibaud Schoenauen, 2024
 * 
*/

#include "polka.h"
#include "msk_poly.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef DEBUG
#define DEBUG_PRINT(poly,name) print_poly(poly) ; printf("(%s)\n",name); getchar()
#else
#define DEBUG_PRINT(poly,name) ;
#endif

void print_cipher(plk_cipher* cipher){
    printf("CIPHER ======================================\nLength = %lld\n",cipher->c0_l);
    for(unsigned int i = 0; i < cipher->c0_l; i++) printf("%c",cipher->c0[i]);
    printf("\nc1 = ");
    print_poly(cipher->c1);
    printf("\nc2 = ");
    print_poly(cipher->c2);
    printf("\n===============================================\n");
}

int polka_dec_1(plk_cipher* cipher, plk_sk* secret_key, poly rp, poly e1p, poly e2p, poly c1b, poly c2b){
    poly_random(rp,random_binomial);
    poly_random(e1p,random_binomial);
    poly_random(e2p,random_binomial);

    DEBUG_PRINT(rp,"rp");
    DEBUG_PRINT(e1p,"e1p");
    DEBUG_PRINT(e2p,"e2p");


    poly c1p;
    poly_ring_mul(secret_key->pk->a,rp,c1p);
    poly_ring_add(c1p,e1p,c1p);
    DEBUG_PRINT(c1p,"c1p");

    poly c2p;
    poly_ring_mul(secret_key->pk->b,rp,c2p);
    poly_ring_add(c2p,e2p,c2p);
    DEBUG_PRINT(c2p,"c2p");

    poly_ring_add(cipher->c1,c1p,c1b);
    DEBUG_PRINT(c1b,"c1b");

    poly_ring_add(cipher->c2,c2p,c2b);
    DEBUG_PRINT(c2b,"c2b");

    return 0;
}

int polka_dec_2(plk_sk* secret_key, poly t, poly c1b){
    msk_poly msk_s;
    msk_poly msk_t;

    poly_ring_scal(P,c1b,t);

    poly_ring_cpy(secret_key->s,msk_s[0]); // To stay complient with pqm4 API. TODO : For release, we should use masked key.
    for(int i = 1; i < NSHARES; i ++) poly_ring_init(msk_s[i]);
    msk_poly_ring_mul(t,msk_s,msk_t);

    poly_ring_mul(t,secret_key->s,t);

    unmask_poly(msk_t,t);

    DEBUG_PRINT(t,"t");
    return 0;
}

int polka_dec_3(plk_sk* secret_key, poly c2b, poly t, poly e2b, poly rb, poly c1b, poly e1b){
    poly mb;
    poly_ring_sub(c2b,t,mb);
    DEBUG_PRINT(mb,"mb");


    poly_ring_red(mb,P,e2b);
    DEBUG_PRINT(e2b,"e2b");

    if(poly_ring_norm(e2b) > 2*B ) return 1;

    poly_ring_sub(c2b,e2b,rb);
    poly_ring_mul(rb,secret_key->pk->b_inv,rb);
    DEBUG_PRINT(rb,"rb");


    if(poly_ring_norm(rb) > 2*B ) return 2;

    poly_ring_mul(secret_key->pk->a,rb,e1b);
    poly_ring_sub(c1b,e1b,e1b);
    DEBUG_PRINT(e1b,"e1b");

    if(poly_ring_norm(e1b) > 2*B ) return 3;

    return 0;
}

int polka_dec_4(poly r, poly rb, poly rp, poly e1, poly e1b, poly e1p, poly e2, poly e2b, poly e2p){
    poly_ring_sub(rb,rp,r);
    DEBUG_PRINT(r,"r");

    if(poly_ring_norm(r) > B) return 4;

    poly_ring_sub(e1b,e1p,e1);
    DEBUG_PRINT(e1,"e1");


    if(poly_ring_norm(e1) > B) return 5;

    poly_ring_sub(e2b,e2p,e2);
    DEBUG_PRINT(e2,"e2");

    if(poly_ring_norm(e2) > B) return 6;
    return 0;
}

int polka_dec_5(plk_cipher* cipher, poly r, poly e1, poly e2, unsigned char* message, unsigned long long* message_length, unsigned char* npub,
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
            key_build(r,e1,e2,key);

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

    printf("polynomials randomized\n");

    poly_ring_mul(r,public_key->a,cipher->c1);
    poly_ring_add(cipher->c1,e1,cipher->c1);

    printf("First cipher part created\n");

    poly_ring_mul(r,public_key->b,cipher->c2);
    poly_ring_add(cipher->c2,e2,cipher->c2);

    printf("Second cipher part created\n");
    
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

    
    int res = 0;

    poly r_prime;
    poly e1_prime;
    poly e2_prime;
    poly c1_bar;
    poly c2_bar;
    res = polka_dec_1(cipher,secret_key,r_prime,e1_prime,e2_prime,c1_bar,c2_bar);
    if(res != 0) return res;

    poly temp;
    res = polka_dec_2(secret_key,temp,c1_bar);
    if(res != 0) return res;

    poly e2_bar;
    poly e1_bar;
    poly r_bar;
    res = polka_dec_3(secret_key,c2_bar,temp,e2_bar, r_bar,c1_bar,e1_bar);
    if(res != 0) return res;

    poly r;
    poly e1;
    poly e2;
    res = polka_dec_4(r,r_bar,r_prime,e1,e1_bar,e1_prime,e2,e2_bar,e2_prime);
    if(res != 0) return res;

    res = polka_dec_5(cipher,r,e1,e2,message,message_length,npub,key_build,dem_D);

    return 0;
}
