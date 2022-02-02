#ifndef MASKED_H
#define MASKED_H
#include <stdint.h>
#include "params.h"

#define NSHARES 3
#define COEF_NBITS 12

#define BSSIZE 32

typedef uint32_t BsBBit[NSHARES]; // dense
typedef BsBBit BsBCoef[COEF_NBITS]; // dense
typedef int16_t Coef;
typedef Coef ACoef[NSHARES]; // dense
typedef ACoef APoly[KYBER_N]; // dense
typedef APoly APolyVec[KYBER_K]; // dense
typedef Coef StrAPoly[NSHARES][KYBER_N]; // strided
typedef StrAPoly StrAPolyVec[KYBER_K]; // strided

#endif