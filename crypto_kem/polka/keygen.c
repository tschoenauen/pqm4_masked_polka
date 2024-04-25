#include "keygen.h"
#include <stdlib.h>
#include <stdio.h>


int keygen(plk_sk* sk, plk_pk* pk){
    FILE* key_file = fopen("res/key_0","r");
    if(key_file == NULL){
        printf("ERROR : Unable to open ressource file");
        return 1;   
    }

    //The key file stores data on 16bits, the buffers reads them as such and then we cast the values on c_int.
    uint32_t buf[N];
    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->a[i] = (c_int) buf[i];

    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->b[i] = (c_int) buf[i];

    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->b_inv[i] = (c_int) buf[i];

    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) sk->s[i] = (c_int) buf[i];

    sk->pk = pk;
    fclose(key_file);

    return 0;
}