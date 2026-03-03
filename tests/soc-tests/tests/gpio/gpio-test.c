#include "trap.h"

void led_test(void * arg) {
  int i = 0;
  while(1) {
    volatile uint16_t * led_gpio = (uint16_t *)GPIO_LED;
    led_gpio[0] = (1 << i);
    i = (i + 1) % 16;
    yield();
  }
}

void switch_test(void * arg) {
  while(1) {
    volatile uint16_t * switch_gpio = (uint16_t *)GPIO_SWITCH;
    uint16_t switch_value = *switch_gpio;
    printf("Switch value: %04x\n", switch_value);
    yield();
  }
}

typedef union task {
  struct {
    const char *name;
    void      (*entry)(void *);
    Context    *context;
  };
  uint8_t stack[4096 * 3];
} Task;

Task tasks[] = {
  { .name = "A", .entry = led_test },
  { .name = "B", .entry = switch_test },
};

// ------------------

Context *schedular(Event ev, Context *ctx) {
  static int i = -1;
  if (i >= 0) tasks[i].context = ctx;

  i = (i + 1) % 2;
  return tasks[i].context;
}

int main() {
  cte_init(schedular);

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

  for (int i = 0; i < LENGTH(tasks); i++) {
    Task *task    = &tasks[i];
    Area stack    = (Area) { &task->context + 1, task + 1 };
    task->context = kcontext(stack, task->entry, (void *)task->name);
  }
  yield();
}