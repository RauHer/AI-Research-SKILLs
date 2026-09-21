#include "../include/gateway.h"
#include <stdio.h>

bool gateway_init(const char* host, int port) {
    // Stub
    return true;
}

void gateway_close(void) {
    // Stub
}

bool gateway_query(const char* prompt, int8_t* target_coords_out, int k_trits) {
    // Stub
    for (int i = 0; i < k_trits; i++) {
        target_coords_out[i] = 0;
    }
    return true;
}
