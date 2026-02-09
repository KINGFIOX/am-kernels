#include "spi.h"
#include "trap.h"

#define FLASH_SS (1 << 0)

#define FLASH_CMD_READ 0x03

static inline void flash_select(void) { REG32(SPI_SS) = FLASH_SS; }
static inline void flash_deselect(void) { REG32(SPI_SS) = 0; }
// [ 0, cmd, addr, data ]
// high                low
// Tx3                 Tx0
// Rxx 与 Txx 其实是同一个寄存器
//
static inline uint32_t flash_read_word(uint32_t addr) {
  flash_select();
  REG32(SPI_TX1) = (FLASH_CMD_READ << 24) | (addr & 0x00FFFFFF);
  REG32(SPI_TX0) = 0;
  REG32(SPI_CTRL) = SPI_CTRL_CHAR_LEN(64) | SPI_CTRL_ASS | SPI_CTRL_GO;
  spi_wait_done();
  uint32_t data = REG32(SPI_RX0);
  flash_deselect();
  return data;
}

int main() {
  printf("=== SPI Flash Article Reader ===\n\n");

  spi_init();

  /* 读取并打印文章 (约 16KB 应该足够) */
  uint32_t addr = 0;
  int done = 0;
  while (!done && addr < 16 * 1024) {
    uint32_t word = flash_read_word(addr);
    for (int i = 3; i >= 0; i--) {
      char c = (word >> (i * 8)) & 0xFF;
      if (c == '\0') {
        done = 1;
        break;
      }
      putch(c);
    }
    addr += 4;
  }

  printf("\n\n=== Article Complete ===\n");
  check(1);

  return 0;
}
