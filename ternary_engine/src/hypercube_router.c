#include "../include/hypercube_router.h"
#include "../include/ternary_math.h"
#include <stdlib.h>

void route_expert(
    const activation_t* x,
    const ternary_word_t* w_route,
    int k_trits,
    int8_t* target_coord_out
) {
    for (int i = 0; i < k_trits; i++) {
        int32_t s = ternary_dot_product(x, w_route + i * ((243 + 63) / 64), 243);
        target_coord_out[i] = sign3(s, 27);
    }
}

int hamming_distance(const int8_t* c1, const int8_t* c2, int k_trits) {
    int dist = 0;
    for (int i = 0; i < k_trits; i++) {
        if (c1[i] != c2[i]) dist++;
    }
    return dist;
}

uint32_t find_expert_index(const int8_t* coord, int k_trits) {
    uint32_t idx = 0;
    uint32_t multiplier = 1;
    for (int i = 0; i < k_trits; i++) {
        // Map {-1, 0, 1} to {0, 1, 2}
        int mapped = coord[i] + 1;
        idx += mapped * multiplier;
        multiplier *= 3;
    }
    return idx;
}
