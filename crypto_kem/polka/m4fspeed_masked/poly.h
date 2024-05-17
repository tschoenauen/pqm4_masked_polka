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

/**
 * Loads the polynomial to a from an array src.
*/
int poly_load(poly a, c_int* src);

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

/**
 * Performs a scalar multiplication between integer a and polynomial b.
 * The result is stored in prod.
*/
int poly_ring_scal(int a, poly b, poly prod);


/**
 * Computes the inf-norm (aka the highest coefficient) of p.
*/
int poly_ring_norm(poly p);

/*
 * Performs the division of a by b, two polynomials in the ring R_qn
 * The result is stored in quotient.
*/
int poly_ring_div(poly a, poly b, poly quotient);

/**
 * Computes the inverse of an integer a mod q
*/
int integer_ring_inv(int a);

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
 * Returns the degree (aka the index of the highest non null coefficient) of a.
*/
int poly_ring_deg(poly a);

/**
 * Computes the inverse of a polynom a mod q.
 * The resuilt is stored in b.
*/
int poly_ring_inv(poly a, poly b);

/**
 * Compare two polynomials and returns true if they are equal false otherwise.
*/
int poly_ring_eq(poly a, poly b);


/**
 * Reduces the coefficients in a using (mod n).
*/
int poly_ring_red(poly a, int n, poly b);

/**
 * Produces a random polynomial using the given distribution.
*/
int poly_random(poly rcv,c_int (*distr)());

