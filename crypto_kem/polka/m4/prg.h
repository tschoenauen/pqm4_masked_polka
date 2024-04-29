/**
 * Module for pseudo-random number generation.
 * Written by Thibaud Schoenauen, november 2023.
*/

#include "params.h"
#include <stdint.h>
#pragma once

void setup_seed(unsigned int seed);

c_int random_uniform();

c_int random_binomial();

c_int random_bounded_uniform();

void reset_bit_count();