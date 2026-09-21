#ifndef RETENTION_H
#define RETENTION_H

#include <stdint.h>
#include "ternary_types.h"

// Base-3 Linear Retention Recurrent Update
// S_t = S_(t-1) - (S_(t-1) >>_3 e_h) + (K_t >>_3 1)^T (V_t >>_3 1)
void update_retention_state(
    retention_state_t* state, // 27x27 matrix per head
    const activation_t* k_vec, // 27 dim
    const activation_t* v_vec, // 27 dim
    int head_idx
);

// Apply retention to query
void apply_retention(
    const retention_state_t* state, // 27x27 matrix
    const activation_t* q_vec,      // 27 dim
    accumulator_t* out_vec          // 27 dim
);

// Discrete Galois Base-3 RoPE
void apply_galois_rope(activation_t* vec, int pos);

#endif // RETENTION_H
