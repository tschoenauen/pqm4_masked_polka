#include "poly.h"
#include "masked_poly.h"
#include "masked.h"

#include "cbd.h"
#include "ntt.h"
#include "params.h"
#include "symmetric.h"

#include <stdint.h>

/*************************************************
* Name:        masked_poly_ntt
*
* Description: Computes negacyclic number-theoretic transform (NTT) of
*              a polynomial in place;
*              inputs assumed to be in normal order, output in bitreversed order
*
* Arguments:   - uint16_t *r: pointer to in/output polynomial
**************************************************/
void masked_poly_ntt(StrAPoly r) {
    for(int d=0;d<NSHARES;d++){
        ntt(r[d]);
    }
}

/*************************************************
* Name:        masked_poly_invntt
*
* Description: Computes inverse of negacyclic number-theoretic transform (NTT) of
*              a polynomial in place;
*              inputs assumed to be in bitreversed order, output in normal order
*
* Arguments:   - uint16_t *a: pointer to in/output polynomial
**************************************************/
void masked_poly_invntt(StrAPoly r) {
    for(int d=0; d<NSHARES;d++){
        invntt(r[d]);
    }
}
