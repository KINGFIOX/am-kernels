#include "trap.h"

int main() {
    printf("=== CSR Test ===\n");
    printf("mvendorid: %c%c%c%c\n", MVENDORID >> 24, MVENDORID >> 16, MVENDORID >> 8, MVENDORID);
    printf("marchid: %d\n", MARCHID);
    printf("=== End of CSR Test ===\n");
    return 0;
}
