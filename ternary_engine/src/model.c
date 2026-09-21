#include "../include/model.h"
#include <stdlib.h>
#include <string.h>

ternary_model_t* model_load(const char* filepath) {
    // Stub for testing
    ternary_model_t* model = (ternary_model_t*)calloc(1, sizeof(ternary_model_t));
    if (!model) return NULL;

    // Set minimal valid header
    model->header.magic = TERNARY_MAGIC;
    model->header.format_version = TERNARY_FORMAT_VERSION;
    model->header.num_layers = 27;
    model->header.dim_model = 243;
    model->header.dim_ffn = 729;
    model->header.num_heads_q = 9;
    model->header.num_heads_kv = 3;
    model->header.dim_head = 27;
    model->header.expert_stride_bytes = 106368;

    return model;
}

void model_free(ternary_model_t* model) {
    if (!model) return;
    free(model->kv_state);
    free(model);
}

void model_forward(
    ternary_model_t* model,
    const activation_t* input_x,
    activation_t* output_x,
    int pos
) {
    // Minimal stub mapping input to output directly
    memcpy(output_x, input_x, 243 * sizeof(activation_t));
}
