#include "am.h"
#include "trap.h"

volatile unsigned x = 0xffffffff;
volatile unsigned char buf[16];

static Context * handler(Event ev, Context * c) {
    return c;
}

int main() {
    cte_init(handler);
	for(int i = 0; i < 4; i++) {
		*((volatile unsigned*)(buf + 3)) = 0xaabbccdd;

		x = *((volatile unsigned*)(buf + 3));
		check(x == 0xaabbccdd);

		buf[0] = buf[1] = 0;
	}

	return 0;
}
