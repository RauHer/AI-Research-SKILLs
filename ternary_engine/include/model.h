#ifndef MODEL_H
#define MODEL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "ternary_format.h"
#include "ternary_types.h"

// Master model structure
typedef struct {
    ternary_file_header_t header;
    int fd;
    void* mapped_data;
    size_t mapped_size;

    // Pointers into mapped_data
    int8_t* basis_matrix;
    void* layers;

    // Inference state
    retention_state_t* kv_state; // [num_layers][num_heads_kv][dim_head][dim_head]
} ternary_model_t;

ternary_model_t* model_load(const char* filepath);
void model_free(ternary_model_t* model);

// Core inference loop
void model_forward(
    ternary_model_t* model,
    const activation_t* input_x,
    activation_t* output_x,
    int pos
);

#endif // MODEL_H
