#include "trap.h"

const static char lut[256] = {
    [AM_KEY_1]     = '1', [AM_KEY_2]         = '2', [AM_KEY_3]          = '3', [AM_KEY_4]            = '4',
    [AM_KEY_5]     = '5', [AM_KEY_6]         = '6', [AM_KEY_7]          = '7', [AM_KEY_8]            = '8',
    [AM_KEY_9]     = '9', [AM_KEY_0]         = '0', [AM_KEY_MINUS]      = '-', [AM_KEY_EQUALS]       = '=',
    [AM_KEY_A]     = 'a', [AM_KEY_B]         = 'b', [AM_KEY_C]          = 'c', [AM_KEY_D]            = 'd',
    [AM_KEY_E]     = 'e', [AM_KEY_F]         = 'f', [AM_KEY_G]          = 'g', [AM_KEY_H]            = 'h',
    [AM_KEY_I]     = 'i', [AM_KEY_J]         = 'j', [AM_KEY_K]          = 'k', [AM_KEY_L]            = 'l',
    [AM_KEY_M]     = 'm', [AM_KEY_N]         = 'n', [AM_KEY_O]          = 'o', [AM_KEY_P]            = 'p',
    [AM_KEY_Q]     = 'q', [AM_KEY_R]         = 'r', [AM_KEY_S]          = 's', [AM_KEY_T]            = 't',
    [AM_KEY_U]     = 'u', [AM_KEY_V]         = 'v', [AM_KEY_W]          = 'w', [AM_KEY_X]            = 'x',
    [AM_KEY_Y]     = 'y', [AM_KEY_Z]         = 'z', [AM_KEY_COMMA]      = ',', [AM_KEY_PERIOD]       = '.',
    [AM_KEY_SLASH] = '/', [AM_KEY_SEMICOLON] = ';', [AM_KEY_APOSTROPHE] = '\'', [AM_KEY_LEFTBRACKET] = '[',
    [AM_KEY_RIGHTBRACKET] = ']', [AM_KEY_BACKSLASH] = '\\', [AM_KEY_BACKSPACE] = '\b', [AM_KEY_TAB] = '\t',
    [AM_KEY_RETURN] = '\n',
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