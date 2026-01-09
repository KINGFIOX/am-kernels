#include <amtest.h>

void csr_test() {
  printf("CSR test\n");

  uintptr_t mvendorid;
  asm volatile ("csrr %0, mvendorid\n" : "=r" (mvendorid));
  printf("mvendorid: %c%c%c%c\n", mvendorid >> 24, mvendorid >> 16, mvendorid >> 8, mvendorid);

  uintptr_t marchid;
  asm volatile ("csrr %0, marchid\n" : "=r" (marchid));
  printf("marchid: %d\n", marchid);

  while (1) {
    for (int i = 0; i < 100000; i++) ;
    uintptr_t mcycle;
    asm volatile ("csrr %0, mcycle\n" : "=r" (mcycle));
    printf("mcycle: %lx\n", mcycle);
  }
}