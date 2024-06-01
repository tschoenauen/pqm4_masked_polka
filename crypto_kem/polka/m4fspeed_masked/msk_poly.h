/**
 * Module for masked computations over polynomial.
 * Written by Thibaud Schoenauen, february 2023.
 * Only works with values between 0 and q-1.
*/

#include "poly.h"

typedef poly msk_poly[NSHARES];

/**
 * Mask the source polynomial and store the masked version in a receiver.
*/
void mask_poly(poly src, msk_poly rcv);

/**
 * Unmask the source polynomial and store the result in a receiver.
*/
void unmask_poly(msk_poly src, poly rcv);


/**
 * Performs addition over masked polynomials. 
*/
void msk_poly_ring_add(msk_poly a, msk_poly b, msk_poly sum);

/**
 * Performs substraction over masked polynomials. 
*/
void msk_poly_ring_sub(msk_poly a, msk_poly b, msk_poly diff);

/**
 * Performs a modulo reduction on masked polynomial a and stores the result in b.
*/
void msk_poly_ring_red(msk_poly a, int n, msk_poly b);

/**
 * Performs a scalar product on masked polynomial b and stores the result in prod.
*/
void msk_poly_ring_scal(int a, msk_poly b, msk_poly prod);

/**
 * Computes ring multiplication between polynomial a and masked polynomial b.
 * The result in left unmasked
*/
void msk_poly_ring_mul(poly a, msk_poly b, poly prod);
