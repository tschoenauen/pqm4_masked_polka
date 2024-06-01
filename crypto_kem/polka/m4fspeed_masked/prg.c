/**
 * Pseudorandom generator based on cc65 LCG.
 * 
*/

#include "prg.h"
#include <stdio.h>
#include <time.h>

uint32_t lcg_state = 0;
uint32_t lcg_multiplier = 0x01010101;
uint32_t lcg_increment = 0xb3b3b3b3;


void setup_seed(unsigned int seed){
    lcg_state = seed;
}

c_int random_uniform(){
    // Update function
    lcg_state = (lcg_multiplier*lcg_state) + lcg_increment;

    //Return
    uint16_t low15 = (uint16_t) lcg_state & 0x7fff;
    uint16_t high16 = (uint16_t) (lcg_state >> 16);
    
    return low15 ^ high16; //As the modulo is a power of 2, I can simply dismiss exceeding bit.
}

int bit_count = -1;

void reset_bit_count(){
    bit_count = -1;
}

c_int random_binomial(){
    // ATTENTION : This function only generates a coefficient. __sample_binomial(self) from SageMath generates an entire poly.

    //Assert on K;
    if((16 % (2 * K)) != 0) printf("ASSERTION ERROR");

    if(bit_count == -1) bit_count = 0; //Resetting bit count if required.
    c_int r = 0;
    if((bit_count % 16) == 0){ // bitcount check
        bit_count = 0;
        r = random_uniform();
    }
    // For each coeff
    c_int a[K];
    c_int b[K];
    for(int i = 0; i < K; i ++) a[i] = (r >> (bit_count + i)) & 0x1;
    for(int i = 0; i < K; i ++) b[i] = (r >> (bit_count + K + i)) & 0x1;

    bit_count += 2*K;
    int8_t acc = 0;
    for(int j = 0; j < K; j ++) acc += a[j] - b[j];
    acc = ((acc % 3) + 3) % 3;


    if(acc <= (3-1)/2) acc=acc;
    else acc=acc-3;

    c_int to_ret = (((acc) % Q) + Q) % Q;

    return to_ret;


}

c_int random_bounded_uniform(){
    c_int r = random_uniform();
    while(r >= Q) r = random_uniform(); 
    //Optimization for Q<<MAX: instead of tossing all incorrect value, we keep multiple instances as long as all values are equiprobable.
    return r;
}
