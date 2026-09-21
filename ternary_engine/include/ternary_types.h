#ifndef TERNARY_TYPES_H
#define TERNARY_TYPES_H

#include <stdint.h>

// Base-3 types
// Dual-bitplane representation of ternary values {-1, 0, +1}
typedef struct {
    uint64_t pos; // Bit i = 1 if Trit == +1
    uint64_t neg; // Bit i = 1 if Trit == -1
                  // Both 0 means Trit == 0. Both 1 is invalid.
} ternary_word_t;

// Compact 5-trits-per-byte format used for disk serialization
// 3^5 = 243 <= 256. Value = t0 + t1*3 + t2*9 + t3*27 + t4*81
// where t_i is in {0, 1, 2} corresponding to {-1, 0, 1} mapped via x+1
typedef uint8_t packed_trit_block_t;

// Standard activation type (int8 signed integer [-128, +127])
typedef int8_t activation_t;

// Retention state type (int16 signed integer)
typedef int16_t retention_state_t;

// Intermediate accumulator type (int32 signed integer)
typedef int32_t accumulator_t;

#endif // TERNARY_TYPES_H
