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


int poly_load(poly a, c_int* src){
    for(int i = 0; i < N; i++){
        a[i] = src[i];
    }
    return 0;
}

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

int poly_ring_deg(poly a){
    for(int i = N-1 ; i > 0; i--) if (a[i] != 0) return i;
    return 0;
}

int integer_ring_inv(int a){
    int t = 0;
    int new_t = 1;
    int r = Q;
    int new_r = a;

    while(new_r != 0){
        int quotient = r / new_r;
        int buf_t = new_t;
        new_t = t - quotient*new_t;
        t = buf_t;
        int buf_r = new_r;
        new_r = r - quotient*new_r;
        r = buf_r;
    }

    if(r > 1) return -1;
    if(t < 0) t += Q;
    return t;
}

int poly_ring_eq(poly a,poly b){
    for(int i = 0; i < N; i ++) if ((((a[i]%Q)+Q)%Q) != (((b[i]%Q)+Q)%Q)) return false;
    return true;
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
    int64_t result[N];
    for(int i = 0; i < N; i ++){
        result[i] = a[i] + b[i]; //TODO : Correct bug where negative values makes bad things.
    }
    for(int i = 0; i < N; i ++){ // Placing back the coefficient in the ring
        result[i] = ((result[i] % Q) + Q) % Q;
    }
    for(int i = 0; i < N; i++) sum[i] = (c_int) result[i];
    stop_bench(plk_poly_add);
    return 1;
}

int poly_ring_sub(poly a, poly b, poly diff){
    start_bench(plk_poly_sub);
    int64_t result[N];
    for(int i = 0; i < N; i ++){
        result[i] = Q + a[i] - b[i]; //TODO : Correct bug where negative values makes bad things.
    }
    for(int i = 0; i < N; i ++){ // Placing back the coefficient in the ring
        result[i] = ((result[i] % Q) + Q) % Q;
    }
    for(int i = 0; i < N; i++) diff[i] = (c_int) result[i];
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

int poly_ring_scal(int a, poly b, poly prod){
    start_bench(plk_poly_scal);
    int64_t result[N];
    for(int i = 0; i < N; i ++){
        result[i] = a * b[i];
    }
    for(int i = 0; i < N; i ++){
        result[i] = ((result[i] % Q) + Q) % Q;
    }
    for(int i = 0; i < N; i ++){
        prod[i] = (c_int) result[i];
    }
    stop_bench(plk_poly_scal);
    return 0;
}

int poly_ring_norm(poly p){
    start_bench(plk_poly_norm);
    int norm = p[0];
    for(int i = 0; i < N; i++){
        int coeff = 0;
        if(p[i] >= Q/2) coeff = abs(p[i] - Q);
        else coeff = p[i];
        if (norm < coeff) norm = coeff;
    }
    stop_bench(plk_poly_norm);
    return norm;
}

int poly_ring_div(poly a, poly b, poly quotient){
    poly a_cpy;
    poly_ring_cpy(a,a_cpy);
    int d_a = poly_ring_deg(a_cpy);
    int d_b = poly_ring_deg(b);
    poly temp_q;
    poly_ring_init(temp_q);
    while(d_a >= d_b && poly_ring_norm(a) != 0){ // As long as our polynomial is not null and b can be used to reduce it
        int d_q = d_a - d_b;
        quotient[d_q] = (((a[d_a] * integer_ring_inv(b[d_b])) % Q) +Q) %Q;
        temp_q[d_q] = quotient[d_q];
        poly substractor;
        poly_ring_mul(temp_q,b,substractor);
        poly_ring_sub(a,substractor,a);
        d_a = poly_ring_deg(a);
        temp_q[d_q] = 0;
    }
    return 0;
}

int poly_ring_inv(poly a, poly b){
    // Initialization.
    poly t;
    poly_ring_init(t);

    poly new_t;
    poly_ring_init(new_t);
    new_t[0] = 1;

    poly r;
    poly_ring_init(r);
    r[0] = 1; r[N-1] = 1;

    poly new_r;
    poly_ring_cpy(a,new_r);


    while(poly_ring_norm(new_r) != 0){
        poly quotient;
        poly_ring_div(r, new_r, quotient);

        poly buf;
        poly temp;

        // (t, new_t) = (new_t, t - quotient * new_t)
        poly_ring_cpy(new_t, buf);
        poly_ring_mul(quotient, new_t, temp);
        poly_ring_sub(t, temp, new_t);
        poly_ring_cpy(buf, t);

        // (r, new_r) = (new_r , r - quotient * new_r)
        poly_ring_cpy(new_r, buf);
        poly_ring_mul(quotient, new_r, temp);
        poly_ring_sub(r, temp, new_r);
        poly_ring_cpy(buf, r);
    }

    if(poly_ring_deg(r) > 0) return -1;

    // b = 1/r * t. r is only scalar now.
    poly_ring_init(new_r);
    new_r[0] = integer_ring_inv(r[0]);
    poly_ring_mul(new_r,t,b);

    return 0;
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
