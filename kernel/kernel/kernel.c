#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>

#include <kernel/interrupts.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>

extern void enable_A20();
static inline void outb(uint16_t port, uint8_t val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
  /* There's an outb %al, $imm8  encoding, for compile-time constant port
   * numbers that fit in 8b.  (N constraint). Wider immediate constants would be
   * truncated at assemble-time (e.g. "i" constraint). The  outb  %al, %dx
   * encoding is the only option for all other cases.
   * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we
   * had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

static inline bool are_interrupts_enabled() {
  unsigned long flags;
  asm volatile("pushf\n\t"
               "pop %0"
               : "=g"(flags));
  return flags & (1 << 9);
}

static inline void disable_interrupts() { asm volatile("cli"); }

int check_a20() { return 0; }

void NMI_enable() { outb(0x70, inb(0x70) & 0x7F); }

void NMI_disable() { outb(0x70, inb(0x70) | 0x80); }

void kernel_main(void) {
  terminal_initialize();
  printf("Hello, World!\n");
  printf("OS Starting!\n");
  idt_init();
  printf("Checking for the A20 line\n");
  if (!check_a20()) {
    printf("Setting A20 line\n");
    enable_A20();
  } else {
    printf("A20 line already set\n");
  }
  NMI_disable();
  disable_interrupts();
  if (are_interrupts_enabled()) {
    printf("Interrupts are enabled\n");
  } else {
    printf("Interrupts are disabled\n");
  }
  printf("OS Started!\n");
  while (1) {
  }
}
