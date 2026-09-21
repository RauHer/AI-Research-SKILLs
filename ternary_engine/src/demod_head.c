#include "../include/demod_head.h"
#include "../include/ternary_math.h"
#include <stdlib.h>

int32_t sample_next_token(
    const int32_t* scores,
    int k_trits,
    int32_t theta,
    float temperature
) {
    int32_t token_id = 0;
    int32_t multiplier = 1;

    // Greedy argmax mapping back to vocabulary ID
    for (int i = 0; i < k_trits; i++) {
        int8_t trit = sign3(scores[i], theta);
        // Map {-1, 0, 1} to {0, 1, 2}
        int mapped = trit + 1;
        token_id += mapped * multiplier;
        multiplier *= 3;
    }

    return token_id;
}
