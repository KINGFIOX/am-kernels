#ifndef __SPI_H__
#define __SPI_H__

#include <am.h>

#define SPI_BASE 0x10001000

#define SPI_RX0 (SPI_BASE + 0x00)
#define SPI_RX1 (SPI_BASE + 0x04)
#define SPI_TX0 (SPI_BASE + 0x00)
#define SPI_TX1 (SPI_BASE + 0x04)
#define SPI_CTRL (SPI_BASE + 0x10)
#define SPI_DIVIDER (SPI_BASE + 0x14)
#define SPI_SS (SPI_BASE + 0x18)

#define SPI_CTRL_CHAR_LEN(n) ((n)&0x7F)
#define SPI_CTRL_GO (1 << 8)
#define SPI_CTRL_ASS (1 << 13)

#define REG32(addr) (*(volatile uint32_t *)(addr))

static inline void spi_init(void) {
  REG32(SPI_DIVIDER) = 4;
  REG32(SPI_SS) = 0;
}

static inline void spi_wait_done(void) {
  while (REG32(SPI_CTRL) & SPI_CTRL_GO)
    ;
}

#endif
