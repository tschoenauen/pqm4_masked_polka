#include "keygen.h"
#include <stdlib.h>
#include <stdio.h>


int keygen(plk_sk* sk, plk_pk* pk){
    /*FILE* key_file = fopen("key_0","r");
    if(key_file == NULL){
        printf("ERROR : Unable to open ressource file");
        return 1;   
    }*/

    //The key file stores data on 16bits, the buffers reads them as such and then we cast the values on c_int.
    //uint32_t buf[N];
    //fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->a[i] = default_polka_key_a[i];

    //fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->b[i] = default_polka_key_b[i];

    //fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->b_inv[i] = default_polka_key_b_inv[i];

    //fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) sk->s[i] = default_polka_key_s[i];

    sk->pk = pk;
    //fclose(key_file);


    return 0;
}
