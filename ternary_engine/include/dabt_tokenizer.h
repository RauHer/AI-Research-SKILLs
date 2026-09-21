#ifndef DABT_TOKENIZER_H
#define DABT_TOKENIZER_H

#include <stdint.h>
#include <stdbool.h>

#define SPECIAL_TOKEN_PAD 0
#define SPECIAL_TOKEN_BOS 1
#define SPECIAL_TOKEN_EOS 2
#define SPECIAL_TOKEN_PONDER 3

typedef struct {
    int32_t* base;
    int32_t* check;
    uint32_t max_states;
    uint32_t vocab_size;

    // String arena
    char* string_arena;
    uint32_t* string_offsets;
    uint16_t* string_lengths;
} dabt_tokenizer_t;

dabt_tokenizer_t* dabt_init(uint32_t vocab_size);
void dabt_free(dabt_tokenizer_t* tokenizer);
bool dabt_load(dabt_tokenizer_t* tokenizer, const char* filepath);

// Tokenization functions
int32_t dabt_encode(dabt_tokenizer_t* tokenizer, const char* text, int32_t* tokens_out, int max_tokens);
const char* dabt_decode(dabt_tokenizer_t* tokenizer, int32_t token_id, uint16_t* length_out);

#endif // DABT_TOKENIZER_H
