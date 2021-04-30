#include <stdio.h>

#include <stdint.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/io.h>

static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

void kernel_main(void) {
  terminal_initialize();
  printf("Hello, World!\n");
  if (are_interrupts_enabled()) {
	  printf("Interrupts are enabled\n");
  } else {
	  printf("Interrupts are disabled\n");
  }
}


