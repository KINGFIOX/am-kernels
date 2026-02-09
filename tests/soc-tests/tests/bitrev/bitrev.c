#include "trap.h"
#include "spi.h"

uint8_t bitrev8(uint8_t x) {
  uint8_t result = 0;
  for (int i = 0; i < 8; i++) {
    result |= ((x >> i) & 1) << (7 - i);
  }
  return result;
}

uint8_t bitrev_test(uint8_t tx_data) {
  REG32(SPI_SS) = BITREV_SS;
  REG32(SPI_TX0) = (uint32_t)tx_data << 8;
  REG32(SPI_CTRL) = SPI_CTRL_CHAR_LEN(16) | SPI_CTRL_ASS | SPI_CTRL_GO;
  spi_wait_done();
  return (uint8_t)(REG32(SPI_RX0) & 0xFF);
}

int main(void) {
  spi_init();

  int pass = 0;
  int fail = 0;

  // 测试用例
  uint8_t test_cases[] = {
      0x00, // 0000_0000 -> 0000_0000
      0xFF, // 1111_1111 -> 1111_1111
      0x01, // 0000_0001 -> 1000_0000 (0x80)
      0x80, // 1000_0000 -> 0000_0001 (0x01)
      0x0F, // 0000_1111 -> 1111_0000 (0xF0)
      0xF0, // 1111_0000 -> 0000_1111 (0x0F)
      0xAA, // 1010_1010 -> 0101_0101 (0x55)
      0x55, // 0101_0101 -> 1010_1010 (0xAA)
      0x12, // 0001_0010 -> 0100_1000 (0x48)
      0xE7, // 1110_0111 -> 1110_0111 (0xE7, 回文)
  };

  int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

  for (int i = 0; i < num_tests; i++) {
    uint8_t tx = test_cases[i];
    uint8_t expected = bitrev8(tx);
    uint8_t rx = bitrev_test(tx);

    if (rx == expected) {
      pass++;
      printf("PASS: TX=%x\n", tx);
      printf("      RX=%x\n", rx);
    } else {
      fail++;
      printf("FAIL: TX=%x\n", tx);
      printf("  Expected=%x\n", expected);
      printf("  Got=%x\n", rx);
    }
  }

  if (fail == 0) {
    printf("All tests passed!\n");
    return 0;
  } else {
    printf("Some tests failed!\n");
    return 1;
  }
}
