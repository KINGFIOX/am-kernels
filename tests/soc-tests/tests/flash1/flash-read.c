#include "trap.h"

/* FLASH_BASE is defined via CFLAGS from NPC_HOME/.config */
#ifndef FLASH_BASE
#error "FLASH_BASE not defined. Please build with ARCH=riscv32-npc"
#endif

int main() {
  /* Point to flash memory */
  volatile char *flash = (volatile char *)FLASH_BASE;
  
  printf("=== Flash Read Test ===\n");
  printf("Reading from Flash at 0x%08x:\n\n", FLASH_BASE);
  
  /* Print the content from flash, character by character */
  /* Stop at null terminator or after 1024 chars to be safe */
  int i = 0;
  while (flash[i] != '\0' && i < 1024) {
    putch(flash[i]);
    i++;
  }
  
  printf("\n\n=== End of Flash Content ===\n");
  printf("Total %d characters read.\n", i);
  
  /* Test passed if we read at least some content */
  check(i > 0);
  
  return 0;
}
