#include "trap.h"

#define VGA_BASE (0x21000000)

static void fill_test_pattern() {
  static const uint32_t colors[8] = {
      0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00,
      0x00FFFF, 0xFF00FF, 0xFFFFFF, 0x808080,
  };

  const int W = 640;
  const int H = 480;
  const int bar_w = W / 8;

  printf("Filling framebuffer (%d x %d)\n", W, H);

  for (int x = 0; x < W; x++) {
    uint64_t color = colors[x / bar_w];
    for (int y = 0; y < H; y++) {
      uint64_t addr = (((uint64_t)x << 10) | (uint64_t)y) + VGA_BASE;
      volatile uint64_t * vga = (volatile uint64_t *)addr;
      vga[0] = color;
    }
    if (x % 64 == 0) {
      printf("  column %d / %d\n", x, W);
    }
  }

  printf("Framebuffer fill complete.\n");
}

int main() {

  // init segments
  printf("=== Segment Test ===\n");
  volatile uint8_t * seg_gpio = (uint8_t *)GPIO_SEGS;
  seg_gpio[0] = SEG_THREE;
  seg_gpio[1] = SEG_ZERO;
  seg_gpio[2] = SEG_ZERO;
  seg_gpio[3] = SEG_ZERO;
  seg_gpio[4] = SEG_ONE;
  seg_gpio[5] = SEG_ZERO;
  seg_gpio[6] = SEG_SIX;
  seg_gpio[7] = SEG_TWO;
  printf("=== Segment Test Passed ===\n");

  fill_test_pattern();

  while(1);
}