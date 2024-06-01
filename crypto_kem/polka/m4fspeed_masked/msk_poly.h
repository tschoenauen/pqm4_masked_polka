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
 * Computes ring multiplication between polynomial a and masked polynomial b.
 * The result in left unmasked
*/
void msk_poly_ring_mul(poly a, msk_poly b, poly prod);
