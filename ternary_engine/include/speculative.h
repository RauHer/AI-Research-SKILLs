#ifndef SPECULATIVE_H
#define SPECULATIVE_H

#include <stdint.h>
#include "model.h"

// Speculative drafting engine
// Tier 3 model drafts tokens, Tier 1 verifies
int draft_tokens(
    ternary_model_t* tier3_model,
    const int32_t* prompt_tokens,
    int prompt_len,
    int32_t* drafted_tokens,
    int max_drafts
);

int verify_tokens(
    ternary_model_t* tier1_model,
    const int32_t* prompt_tokens,
    int prompt_len,
    const int32_t* drafted_tokens,
    int num_drafts,
    int32_t* verified_tokens
);

#endif // SPECULATIVE_H
