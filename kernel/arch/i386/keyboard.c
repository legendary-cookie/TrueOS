#include <kernel/keyboard_map.h>
#include <stdint.h>
#include <stdio.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e

/* video memory begins at address 0xb8000 */
char *vidptr = (char *)0xb8000;
/* current cursor location */
unsigned int current_loc = 0;
/* Get the keyboard layout map */
extern unsigned char keyboard_map[128];

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

void kb_init(void) {
  /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
  outb(0x21, 0xFD);
}