#include "trap.h"

static char lut[256] = {
    [AM_KEY_1] = '1', [AM_KEY_2] = '2', [AM_KEY_3] = '3', [AM_KEY_4] = '4',
    [AM_KEY_5] = '5', [AM_KEY_6] = '6', [AM_KEY_7] = '7', [AM_KEY_8] = '8',
    [AM_KEY_9] = '9', [AM_KEY_0] = '0', [AM_KEY_MINUS] = '-', [AM_KEY_EQUALS] = '=',
    [AM_KEY_A] = 'A', [AM_KEY_B] = 'B', [AM_KEY_C] = 'C', [AM_KEY_D] = 'D',
    [AM_KEY_E] = 'E', [AM_KEY_F] = 'F', [AM_KEY_G] = 'G', [AM_KEY_H] = 'H',
    [AM_KEY_I] = 'I', [AM_KEY_J] = 'J', [AM_KEY_K] = 'K', [AM_KEY_L] = 'L',
    [AM_KEY_M] = 'M', [AM_KEY_N] = 'N', [AM_KEY_O] = 'O', [AM_KEY_P] = 'P',
    [AM_KEY_Q] = 'Q', [AM_KEY_R] = 'R', [AM_KEY_S] = 'S', [AM_KEY_T] = 'T',
    [AM_KEY_U] = 'U', [AM_KEY_V] = 'V', [AM_KEY_W] = 'W', [AM_KEY_X] = 'X',
    [AM_KEY_Y] = 'Y', [AM_KEY_Z] = 'Z',
};

int main() {

  ioe_init();
  panic_on(!io_read(AM_INPUT_CONFIG).present, "requires keyboard");

  printf("=== KBD Test ===\n");

  while (1) {
    AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
    if (ev.keycode == AM_KEY_ESCAPE) { break; }
    if (lut[ev.keycode]) { 
      if (ev.keydown) {
        printf("press Keycode: [%02x], key: %c\n", ev.keycode, lut[ev.keycode]);
      } else {
        printf("release Keycode: [%02x], key: %c\n", ev.keycode, lut[ev.keycode]);
      }
    } else if (ev.keycode != AM_KEY_NONE) {
      printf("unknown Keycode: [%02x]\n", ev.keycode);
    }
  }

  printf("=== KBD Test Passed ===\n");
}