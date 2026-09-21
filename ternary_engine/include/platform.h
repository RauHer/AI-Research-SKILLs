#ifndef PLATFORM_H
#define PLATFORM_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef _GNU_SOURCE
#include <sys/mman.h>
#endif

// Define alignment macros
#define TERNARY_ALIGN_64 __attribute__((aligned(64)))

// Fallback for madvise if not available
#ifndef MADV_HUGEPAGE
#define MADV_HUGEPAGE 14
#endif
#ifndef MADV_WILLNEED
#define MADV_WILLNEED 3
#endif

// Helper function to allocate 64-byte aligned memory
static inline void* ternary_alloc_aligned(size_t size) {
    void* ptr = NULL;
    if (posix_memalign(&ptr, 64, size) != 0) {
        return NULL;
    }
    return ptr;
}

static inline void ternary_free_aligned(void* ptr) {
    free(ptr);
}

#endif // PLATFORM_H
