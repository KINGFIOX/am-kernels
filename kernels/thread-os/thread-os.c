#include <am.h>
#include <klib.h>
#include <klib-macros.h>

typedef union task {
  struct {
    const char *name;
    union task *next;
    void      (*entry)(void *);
    Context    *context;
  };
  uint8_t stack[4096 * 3];
} Task;

// user-defined tasks

void func(void *arg) {
  while (1) {
    printf("%s", (char *)arg);
    yield();
  }
}

Task tasks[] = {
  { .name = "A", .entry = func },
  { .name = "B", .entry = func },
  { .name = "C", .entry = func },
  { .name = "D", .entry = func },
};

// ------------------

Context *schedular(Event ev, Context *ctx) {
  static int i = -1;
  if (i >= 0) tasks[i].context = ctx; // first come in, skip saving context
  i = (i + 1) % 4;
  return tasks[i].context;
}

int main() {
  cte_init(schedular);

  for (int i = 0; i < LENGTH(tasks); i++) {
    Task *task    = &tasks[i];
    Area stack    = (Area) { &task->context + 1, task + 1 };
    task->context = kcontext(stack, task->entry, (void *)task->name);
    task->next    = &tasks[(i + 1) % LENGTH(tasks)];
  }
  yield();
}
