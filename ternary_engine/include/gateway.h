#ifndef GATEWAY_H
#define GATEWAY_H

#include <stdint.h>
#include <stdbool.h>

// Initialize raw POSIX stream socket bridge to Ollama
bool gateway_init(const char* host, int port);
void gateway_close(void);

// Query external model and fetch coordinate targets
bool gateway_query(const char* prompt, int8_t* target_coords_out, int k_trits);

#endif // GATEWAY_H
