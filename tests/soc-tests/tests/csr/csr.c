#include "trap.h"

#define MVENDORID ({ \
    uintptr_t mvendorid; \
    asm volatile ("csrr %0, mvendorid\n" : "=r" (mvendorid)); \
    (mvendorid); \
})

#define MARCHID ({ \
    uintptr_t marchid; \
    asm volatile ("csrr %0, marchid\n" : "=r" (marchid)); \
    (marchid); \
})

int main() {
    printf("=== CSR Test ===\n");
    printf("mvendorid: %c%c%c%c\n", MVENDORID >> 24, MVENDORID >> 16, MVENDORID >> 8, MVENDORID);
    printf("marchid: %d\n", MARCHID);
    printf("=== End of CSR Test ===\n");
    return 0;
}
