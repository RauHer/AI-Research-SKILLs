#include "../include/dabt_tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

dabt_tokenizer_t* dabt_init(uint32_t vocab_size) {
    dabt_tokenizer_t* tokenizer = (dabt_tokenizer_t*)calloc(1, sizeof(dabt_tokenizer_t));
    if (!tokenizer) return NULL;

    tokenizer->vocab_size = vocab_size;
    // For a minimal working stub, we allocate basic arrays
    tokenizer->max_states = vocab_size * 2;
    tokenizer->base = (int32_t*)calloc(tokenizer->max_states, sizeof(int32_t));
    tokenizer->check = (int32_t*)calloc(tokenizer->max_states, sizeof(int32_t));

    tokenizer->string_offsets = (uint32_t*)calloc(vocab_size, sizeof(uint32_t));
    tokenizer->string_lengths = (uint16_t*)calloc(vocab_size, sizeof(uint16_t));

    // Allocate a dummy string arena for demonstration
    tokenizer->string_arena = (char*)calloc(vocab_size * 16, sizeof(char));

    return tokenizer;
}

void dabt_free(dabt_tokenizer_t* tokenizer) {
    if (!tokenizer) return;
    free(tokenizer->base);
    free(tokenizer->check);
    free(tokenizer->string_offsets);
    free(tokenizer->string_lengths);
    free(tokenizer->string_arena);
    free(tokenizer);
}

bool dabt_load(dabt_tokenizer_t* tokenizer, const char* filepath) {
    // Stub implementation
    (void)tokenizer;
    (void)filepath;
    return true;
}

int32_t dabt_encode(dabt_tokenizer_t* tokenizer, const char* text, int32_t* tokens_out, int max_tokens) {
    // Basic byte fallback mapping for testing
    int count = 0;
    while (*text && count < max_tokens) {
        tokens_out[count++] = (unsigned char)(*text) + 4; // Map byte to token 4..259
        text++;
    }
    return count;
}

const char* dabt_decode(dabt_tokenizer_t* tokenizer, int32_t token_id, uint16_t* length_out) {
    // Basic byte fallback mapping for testing
    static char buf[2];
    if (token_id >= 4 && token_id <= 259) {
        buf[0] = (char)(token_id - 4);
        buf[1] = '\0';
        *length_out = 1;
        return buf;
    }
    *length_out = 0;
    return "";
}
