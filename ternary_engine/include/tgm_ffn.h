#ifndef TGM_FFN_H
#define TGM_FFN_H

#include <stdint.h>
#include "ternary_types.h"

// Ternary Gated Multiplexer (TGM)
// Applies +Up, 0, -Up switch based on W_gate * x
void apply_tgm_ffn(
    const activation_t* x,          // 243 dim
    const ternary_word_t* w_gate,   // 729 x 243
    const ternary_word_t* w_up,     // 729 x 243
    const ternary_word_t* w_down,   // 243 x 729
    accumulator_t* out_vec          // 243 dim
);

#endif // TGM_FFN_H
