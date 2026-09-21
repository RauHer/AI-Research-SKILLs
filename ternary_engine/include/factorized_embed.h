#ifndef FACTORIZED_EMBED_H
#define FACTORIZED_EMBED_H

#include <stdint.h>
#include "ternary_types.h"

// Initialize the universal 11 orthogonal basis vectors
void init_universal_basis(void);

// Get the basis matrix (11x243)
const int8_t* get_universal_basis(void);

// Unembed hidden state to 11 demodulation scores
void coordinate_demodulate(const activation_t* hidden_state, int32_t* scores_out, int k);

// Embed 11-trit coordinate to hidden state
void coordinate_embed(const int8_t* coords, activation_t* hidden_state_out, int k);

#endif // FACTORIZED_EMBED_H
