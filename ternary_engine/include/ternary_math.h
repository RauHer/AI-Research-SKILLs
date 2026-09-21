#ifndef TERNARY_MATH_H
#define TERNARY_MATH_H

#include <stdint.h>
#include "ternary_types.h"

// Division-Free MAD-Norm
// mad = (sum(|x_i|) * 17261U) >> 22
static inline int32_t mad_norm_scale(int32_t sum_abs) {
    return (sum_abs * 17261U) >> 22;
}

// Compute dot product of int8 vector with ternary dual-bitplane weights
// Generic C implementation fallback
int32_t ternary_dot_product(const activation_t* x, const ternary_word_t* w, int dim);

// Sign3 function (returns +1 if x >= theta, -1 if x <= -theta, 0 otherwise)
static inline int8_t sign3(int32_t x, int32_t theta) {
    if (x >= theta) return 1;
    if (x <= -theta) return -1;
    return 0;
}

#endif // TERNARY_MATH_H
