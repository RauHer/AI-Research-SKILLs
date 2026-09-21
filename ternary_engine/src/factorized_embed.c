#include "../include/factorized_embed.h"
#include <string.h>

static int8_t universal_basis[11][243];

void init_universal_basis(void) {
    memset(universal_basis, 0, sizeof(universal_basis));

    // Basis vector b_i has non-zero entries exclusively on disjoint coordinate slice [22*i .. 22*i + 21]
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 22; j++) {
            if (i * 22 + j < 243) {
                // Alternating signs (+1, -1, +1...)
                universal_basis[i][i * 22 + j] = (j % 2 == 0) ? 1 : -1;
            }
        }
    }
}

const int8_t* get_universal_basis(void) {
    return &universal_basis[0][0];
}

void coordinate_demodulate(const activation_t* hidden_state, int32_t* scores_out, int k) {
    for (int i = 0; i < k; i++) {
        int32_t score = 0;
        for (int j = 0; j < 243; j++) {
            score += hidden_state[j] * universal_basis[i][j];
        }
        scores_out[i] = score;
    }
}

void coordinate_embed(const int8_t* coords, activation_t* hidden_state_out, int k) {
    memset(hidden_state_out, 0, 243 * sizeof(activation_t));
    for (int i = 0; i < k; i++) {
        if (coords[i] == 0) continue;
        for (int j = 0; j < 243; j++) {
            hidden_state_out[j] += coords[i] * universal_basis[i][j];
        }
    }
}
