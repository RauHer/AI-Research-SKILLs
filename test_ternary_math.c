#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

// Multiplication-free dot product for ternary weights
int32_t ternary_dot(const int8_t* w, const int8_t* x, size_t len) {
    int32_t sum = 0;
    for (size_t i = 0; i < len; i++) {
        if (w[i] == 1) {
            sum += x[i];
        } else if (w[i] == -1) {
            sum -= x[i];
        }
        // If w[i] == 0, skip (no addition or subtraction)
    }
    return sum;
}

int main(void) {
    // Test vector of length 9
    const size_t len = 9;

    // Weights: strictly -1, 0, 1
    int8_t w[9] = {1, 0, -1, 1, 1, 0, -1, 0, 1};

    // Activations: int8 values
    int8_t x[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    // Expected mathematical result:
    // (1 * 10) + (0 * 20) + (-1 * 30) + (1 * 40) + (1 * 50) +
    // (0 * 60) + (-1 * 70) + (0 * 80) + (1 * 90)
    // = 10 + 0 - 30 + 40 + 50 + 0 - 70 + 0 + 90
    // = 90
    int32_t expected = 90;

    int32_t result = ternary_dot(w, x, len);

    // Assert the calculated sum matches expected
    assert(result == expected);

    printf("[PASS] Ternary multiplication-free math verified successfully.\n");

    return 0;
}
