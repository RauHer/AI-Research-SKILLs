#include "../include/tgm_ffn.h"
#include "../include/ternary_math.h"

void apply_tgm_ffn(
    const activation_t* x,
    const ternary_word_t* w_gate,
    const ternary_word_t* w_up,
    const ternary_word_t* w_down,
    accumulator_t* out_vec
) {
    activation_t hidden[729] = {0};

    // Evaluate gate and up simultaneously
    for (int i = 0; i < 729; i++) {
        int32_t gate_val = ternary_dot_product(x, w_gate + i * ((243 + 63) / 64), 243);
        int8_t gate = sign3(gate_val, 27);

        if (gate != 0) {
            int32_t up_val = ternary_dot_product(x, w_up + i * ((243 + 63) / 64), 243);
            hidden[i] = (gate == 1) ? up_val : -up_val;

            // Apply MAD-Norm scaling internally to fit back into activation_t bounds
            hidden[i] = (activation_t)(mad_norm_scale(hidden[i] < 0 ? -hidden[i] : hidden[i]) * (hidden[i] < 0 ? -1 : 1));
        }
    }

    // Project back down
    for (int i = 0; i < 243; i++) {
        out_vec[i] = ternary_dot_product(hidden, w_down + i * ((729 + 63) / 64), 729);
    }
}
