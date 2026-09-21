#ifndef DEMOD_HEAD_H
#define DEMOD_HEAD_H

#include <stdint.h>
#include "ternary_types.h"

// Direct Coordinate Demodulation LM Head
// Samples next token based on 11 demodulation scores
int32_t sample_next_token(
    const int32_t* scores,  // 11 dim
    int k_trits,            // 9, 10, or 11
    int32_t theta,          // dynamic threshold
    float temperature       // 0.0 for greedy argmax
);

#endif // DEMOD_HEAD_H
