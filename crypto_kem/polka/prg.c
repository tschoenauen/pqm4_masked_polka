/**
 * Pseudorandom generator based on cc65 LCG.
 * 
*/

#include "prg.h"
#include <stdio.h>
#include <time.h>

int i = 0;
uint32_t state = 0;
uint32_t a = 0x01010101;
uint32_t c = 0xb3b3b3b3;


void setup_seed(uint32_t seed){
    state = seed;
    i = 0;
}

c_int random_uniform(){
    // Update function
    state = (a*state) + c;

    //Return
    uint16_t low15 = (uint16_t) state & 0x7fff;
    uint16_t high16 = (uint16_t) (state >> 16);
    
    return low15 ^ high16; //As the modulo is a power of 2, I can simply dismiss exceeding bit.
}

int bit_count = -1; //TODO : Refaire le générateur binomial, là c'est immonde.

void reset_bit_count(){
    bit_count = -1;
}

c_int random_binomial(){
    // ATTENTION : Cette fonction ne sert qu'à générer un coefficient contrairement à __sample_binomial(self) qui génère un polynôme entier.

    //Assert on K;
    if((16 % (2 * K)) != 0) printf("ASSERTION ERROR");

    if(bit_count == -1) bit_count = 0; //Resetting bit count if required.
    c_int r;
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