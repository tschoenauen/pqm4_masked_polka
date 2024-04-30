
#include "poly.h"

typedef struct polka_public_key_t{
    poly a;
    poly b;
    poly b_inv;
} plk_pk;

typedef struct polka_secret_key_t{
    poly s;
    plk_pk* pk;
} plk_sk;


/*
* Generates keys.
*/
int keygen(plk_sk* sk, plk_pk* pk);