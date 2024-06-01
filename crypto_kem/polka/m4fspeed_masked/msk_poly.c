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

void msk_poly_ring_add(msk_poly a, msk_poly b, msk_poly sum){
    for(int i = 0; i < NSHARES; i ++) poly_ring_add(a[i],b[i],sum[i]);
}

void msk_poly_ring_sub(msk_poly a, msk_poly b, msk_poly diff){
    for(int i = 0; i < NSHARES; i ++) poly_ring_sub(a[i],b[i],diff[i]);
}

void msk_poly_ring_mul(poly a, msk_poly b, poly prod){
    poly_ring_init(prod);
    for(int i = 0; i < NSHARES; i ++) poly_ring_mul_acc(a,b[i],prod);
}

void msk_poly_ring_scal(int a, msk_poly b, msk_poly prod){ //a n'est pas masqué car c'est P dans le schéma, une valeur publique.
    for(int i = 0; i < NSHARES; i ++) poly_ring_scal(a,b[i],prod[i]);
}

void msk_poly_ring_red(msk_poly a, int n, msk_poly b){
    for(int i = 0; i < NSHARES; i ++) poly_ring_red(a[i],n,b[i]);
}
