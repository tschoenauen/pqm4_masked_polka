#include "msk_poly.h"
#include <stdlib.h>
#include "prg.h"
#include <stdio.h>

void mask_poly(poly src, msk_poly rcv){
    poly_ring_cpy(src,rcv[0]);
    for(int i = 1; i < NSHARES; i++){
        poly_random(rcv[i],random_bounded_uniform);
        poly_ring_sub(rcv[0],rcv[i],rcv[0]);
    }
}

void unmask_poly(msk_poly src, poly rcv){
    poly_ring_init(rcv);
    for(int i = 0; i < NSHARES; i++) poly_ring_add(rcv,src[i],rcv);
}

void msk_poly_ring_mul(poly a, msk_poly b, poly prod){
    poly_ring_init(prod);
    for(int i = 0; i < NSHARES; i ++) poly_ring_mul_acc(a,b[i],prod);
}

