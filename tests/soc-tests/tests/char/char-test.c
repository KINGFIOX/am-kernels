/*
 * UART Character Test
 *
 * This test initializes UART 16550 and sends characters to verify UART output.
 * Based on npc/resource/char-test
 */

#include "trap.h"

/* UART base address - should match NPC SoC config */
#ifndef UART_BASE
#define UART_BASE 0x10000000
#endif

/* UART 16550 register definitions */
#define UART_THR (UART_BASE + 0) /* Transmit Holding Register (DLAB=0) */
#define UART_RBR (UART_BASE + 0) /* Receiver Buffer Register (DLAB=0) */
#define UART_DLL (UART_BASE + 0) /* Divisor Latch Low (DLAB=1) */
#define UART_DLM (UART_BASE + 1) /* Divisor Latch High (DLAB=1) */
#define UART_IER (UART_BASE + 1) /* Interrupt Enable Register (DLAB=0) */
#define UART_FCR (UART_BASE + 2) /* FIFO Control Register (write) */
#define UART_LCR (UART_BASE + 3) /* Line Control Register */
#define UART_LSR (UART_BASE + 5) /* Line Status Register */

/* LCR bit definitions */
#define LCR_DLAB 0x83u /* Divisor Latch Access Bit */
#define LCR_8N1  0x03u /* 8 data bits, no parity, 1 stop bit */

/* FCR bit definitions */
#define FCR_FIFO_ENABLE 0x01u /* FIFO Enable */
#define FCR_RX_RESET    0x02u /* Receiver FIFO Reset */
#define FCR_TX_RESET    0x04u /* Transmitter FIFO Reset */

/* LSR bit definitions */
#define LSR_DR   0x01u /* Data Ready */
#define LSR_THRE 0x20u /* Transmitter Holding Register Empty */
#define LSR_TEMT 0x40u /* Transmitter Empty */

static void uart_init(void) {
  volatile char *lcr = (volatile char *)UART_LCR;
  volatile char *dll = (volatile char *)UART_DLL;
  volatile char *dlm = (volatile char *)UART_DLM;
  volatile char *fcr = (volatile char *)UART_FCR;
  volatile char *ier = (volatile char *)UART_IER;

  /* 1. Disable all interrupts */
  *ier = 0x00; // 1

  /* 2. Enable DLAB to set baud rate */
  *lcr = LCR_DLAB; // 3
  *dll = 0x01; /* Divisor Latch Low */ // 0
  *dlm = 0x00; /* Divisor Latch High */ // 1

  /* 3. Disable DLAB, set data format: 8N1 */
  *lcr = LCR_8N1; // 3

  /* 4. Enable and reset FIFO */
  *fcr = FCR_FIFO_ENABLE | FCR_RX_RESET | FCR_TX_RESET; // 2
}

static void uart_putchar_direct(char c) {
  volatile char *thr = (volatile char *)UART_THR;

  volatile char *lsr = (volatile char *)UART_LSR;
  /* Wait for transmit FIFO to have space (THRE=1 means ready to write) */
  while ((*lsr & LSR_THRE) == 0)
    ;

  *thr = c;
}

static void uart_puts(const char *s) {
  while (*s) {
    uart_putchar_direct(*s++);
  }
}

int main() {
  /* Initialize UART */
  uart_init();

  /* Send test string directly via UART registers */
  uart_puts("Hello from UART 16550!\r\n");

  /* Send alphabet */
  uart_puts("Alphabet: ");
  for (char c = 'A'; c <= 'Z'; c++) {
    uart_putchar_direct(c);
  }
  uart_puts("\r\n");

  /* Send numbers */
  uart_puts("Numbers: ");
  for (char c = '0'; c <= '9'; c++) {
    uart_putchar_direct(c);
  }
  uart_puts("\r\n");

  uart_puts("UART test completed!\r\n");

  return 0;
}
