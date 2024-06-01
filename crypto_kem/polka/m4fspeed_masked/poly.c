/**
 * Module for ring computations for POLKA scheme.
 * Written by Thibaud Schoenauen, november 2023.
 * Only works with values between 0 and q-1.
 * 
 * Quick notes : 
 * Results do not depends on previous value of receiver.
 * Operands are NOT modified.
 * Operators are in-place.
*/

#include "poly.h"
#include "prg.h"
#include <stdlib.h>
#include <stdbool.h>
#include "bench.h"

// Tools ======================================================================


int poly_ring_init(poly a){
    for(int i = 0; i < N; i++){
        a[i] = 0;
    }
    return 0;
}

int poly_ring_cpy(poly src, poly target){
    for(int i = 0; i < N; i++){
        target[i] = ((src[i] % Q) + Q) % Q;
    }
    return 0;
}


int poly_random(poly rcv,c_int (*distr)()){
    start_bench(plk_poly_random);
    reset_bit_count();
    for(int i = 0; i < N; i++){
        rcv[i] = distr();
    }
    stop_bench(plk_poly_random);
    return 0;
}


// Operators ==================================================================

int poly_ring_add(poly a, poly b, poly sum){
    start_bench(plk_poly_add);
    for(int i = 0; i < N; i ++) sum[i] = (c_int) ((((uint32_t) a[i]) + ((uint32_t) b[i])) % Q);
    stop_bench(plk_poly_add);
    return 1;
}

int poly_ring_sub(poly a, poly b, poly diff){
    start_bench(plk_poly_sub);
    for(int i = 0; i < N; i ++) diff[i] = (c_int) (( Q + ((uint32_t) a[i]) + ((uint32_t) b[i])) % Q);
    stop_bench(plk_poly_sub);
    return 1;
}
int poly_ring_mul(poly a, poly b, poly prod){
    start_bench(plk_poly_mul);
    int64_t result[N];
    for(int i = 0; i < N; i ++){
        result[i] = 0;
        for(int j = 0; j <= i; j++){
            result[i] += a[j]*b[i-j];
        }
        for(int j = i+1; j < N; j++){
            result[i] -= a[j]*b[i+N-j];
        }
    }

    for(int i = 0; i < N; i ++){ // Placing back the coefficient in the ring
        result[i] = ((result[i] % Q) + Q) % Q;
    }
    for(int i = 0; i < N; i++) prod[i] = (c_int) result[i];
    stop_bench(plk_poly_mul);
    return 1;
}

int poly_ring_mul_acc(poly a, poly b, poly prod){
    start_bench(plk_poly_mul);
    int64_t result[N];
    for(int i = 0; i < N; i ++){
        result[i] = 0;
        for(int j = 0; j <= i; j++){
            result[i] += a[j]*b[i-j];
        }
        for(int j = i+1; j < N; j++){
            result[i] -= a[j]*b[i+N-j];
        }
    }

    for(int i = 0; i < N; i ++){ // Placing back the coefficient in the ring
        result[i] = ((result[i] % Q) + Q) % Q;
    }
    for(int i = 0; i < N; i++) prod[i] += (c_int) result[i];
    stop_bench(plk_poly_mul);
    return 1;
}

int poly_ring_scal(int a, poly b, poly prod){
    start_bench(plk_poly_scal);
    for(int i = 0; i < N; i ++) prod[i] = (c_int) ((a * ((uint32_t) b[i])) % Q);
    stop_bench(plk_poly_scal);
    return 0;
}

int poly_ring_norm(poly p){
    start_bench(plk_poly_norm);
    int norm = p[0];
    for(int i = 1; i < N; i++){
        int coeff = (p[i] >= Q/2) ? p[i] : Q-p[i];
        if (norm < coeff) norm = coeff;
    }
    stop_bench(plk_poly_norm);
    return norm;
}

int poly_ring_red(poly a, int n, poly b){
    int64_t result[N];
    
    for(int i = 0; i < N; i ++) result[i] = a[i];

    for(int i = 0; i < N; i ++){
        if(result[i] > ((Q-1)/2)) result[i] = result[i] - Q;
    }

    for(int i = 0; i < N; i ++) result[i] = ((result[i] % n) + n) % n;

    for(int i = 0; i < N; i ++){
        if(result[i] > ((n-1)/2)) result[i] = result[i] - n;
    }

    for(int i = 0; i < N; i ++){
        result[i] = ((result[i] % Q) + Q) % Q;
    }
    for(int i = 0; i < N; i ++){
        b[i] = (c_int) result[i];
    }
    return 0;
}
