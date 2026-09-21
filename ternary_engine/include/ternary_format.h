#ifndef TERNARY_FORMAT_H
#define TERNARY_FORMAT_H

#include <stdint.h>

#define TERNARY_MAGIC 0x33333333
#define VOCAB_MAGIC 0x3333564F // "33VO"
#define TERNARY_FORMAT_VERSION 0x00000001

#pragma pack(push, 1)
typedef struct {
    uint32_t magic;              /* 0x33333333 (Base-3 Magic Signature) */
    uint32_t format_version;     /* 0x00000001 (Release 25.0) */
    uint32_t tier_index;         /* 1, 2, 3, 4, or 5 */
    uint32_t num_layers;         /* Strictly 27 */
    uint32_t dim_model;          /* Strictly 243 */
    uint32_t dim_ffn;            /* Strictly 729 */
    uint32_t num_heads_q;        /* Strictly 9 */
    uint32_t num_heads_kv;       /* Strictly 3 */
    uint32_t dim_head;           /* Strictly 27 */
    uint32_t num_experts;        /* 27, 729, 2187, 6561, or 19683 */
    uint32_t vocab_size;         /* 19683, 59049, or 177147 */
    uint32_t context_training;   /* Strictly 2187 */
    uint64_t total_trits;        /* e.g., 282429536481 for Tier 1 */
    uint64_t expert_stride_bytes;/* Strictly 106368 bytes (35456B x 3) */
} ternary_file_header_t;
#pragma pack(pop)

// Static assertion to ensure exactly 64 bytes
_Static_assert(sizeof(ternary_file_header_t) == 64, "ternary_file_header_t must be exactly 64 bytes");

#endif // TERNARY_FORMAT_H
