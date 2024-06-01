/**
 * Module for ring computations for POLKA scheme.
 * Written by Thibaud Schoenauen, november 2023.
 * Only works with values between 0 and q-1.
*/

#include "params.h"
#include <stdint.h>
#pragma once

typedef c_int poly[N];

// Tools ======================================================================


/*
 * Performs the addition of a and b, two polynomials in the ring R_qn
 * The result is stored in sum.
*/
int poly_ring_add(poly a, poly b, poly sum);

/*
 * Performs the substraction of a by b, two polynomials in the ring R_qn
 * The result is stored in diff.
*/
int poly_ring_sub(poly a, poly b, poly diff);

/*
 * Performs the multiplication of a by b, two polynomials in the ring R_qn
 * The result is stored in prod.
*/
int poly_ring_mul(poly a, poly b, poly prod);

/*
 * Performs the multiplication of a by b, two polynomials in the ring R_qn
 * The result is added to prod. Considered as a multiplication for benchmarks.
*/
int poly_ring_mul_acc(poly a, poly b, poly prod);

/**
 * Performs a scalar multiplication between integer a and polynomial b.
 * The result is stored in prod.
*/
int poly_ring_scal(int a, poly b, poly prod);


/**
 * Computes the inf-norm (aka the highest coefficient) of p.
*/
int poly_ring_norm(poly p);

/**
 * Sets all the coefficient of a to 0.
*/
int poly_ring_init(poly a);

/**
 * Copies the coefficient of src in target.
 * Coefficient are sanitized.
*/
int poly_ring_cpy(poly src, poly target);


/**
 * Reduces the coefficients in a using (mod n).
*/
int poly_ring_red(poly a, int n, poly b);

/**
 * Produces a random polynomial using the given distribution.
*/
int poly_random(poly rcv,c_int (*distr)());

