#include <stdio.h>

#include <stdint.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, World!\nGoodbye, World!");
}
