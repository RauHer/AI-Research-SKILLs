#ifndef HYPERCUBE_ROUTER_H
#define HYPERCUBE_ROUTER_H

#include <stdint.h>
#include "ternary_types.h"

// 9-D Hypercube Coordinate Router
// W_route is 9x243 ternary matrix
void route_expert(
    const activation_t* x,          // 243 dim
    const ternary_word_t* w_route,  // 9 x 243 (packed)
    int k_trits,                    // 3, 6, 7, 8, or 9
    int8_t* target_coord_out        // k_trits dim output
);

// Compute Hamming distance between two coordinates
int hamming_distance(const int8_t* c1, const int8_t* c2, int k_trits);

// Spillover logic to find active expert index (0 to 3^k - 1)
uint32_t find_expert_index(const int8_t* coord, int k_trits);

#endif // HYPERCUBE_ROUTER_H
