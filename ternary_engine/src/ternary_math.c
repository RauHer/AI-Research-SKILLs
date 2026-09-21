#include "../include/ternary_math.h"
#include <immintrin.h>

// Fallback generic C implementation for ternary dot product
// Treats dual-bitplane weights as {-1, 0, +1}
int32_t ternary_dot_product(const activation_t* x, const ternary_word_t* w, int dim) {
    int32_t sum = 0;

    // Process in chunks of 64
    for (int i = 0; i < dim; i += 64) {
        uint64_t pos = w[i/64].pos;
        uint64_t neg = w[i/64].neg;

        for (int j = 0; j < 64 && (i + j) < dim; j++) {
            int bit_pos = (pos >> j) & 1;
            int bit_neg = (neg >> j) & 1;

            if (bit_pos) sum += x[i + j];
            if (bit_neg) sum -= x[i + j];
        }
    }

    return sum;
}
