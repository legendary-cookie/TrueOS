jmp load_gdt
 
;global descriptor table
gdt:
 
gdt_null:
  dq 0
 
gdt_code:
  dw 0xFFFF
  dw 0
 
  db 0
  db 10011010b
  db 11001111b
  db 0
 
gdt_data:
  dw 0xFFFF
  dw 0
 
  db 0
  db 10010010b
  db 11001111b
  db 0
 
gdt_end:
 
gdt_desc:
 
gdt_size:
  dw gdt_end - gdt - 1
  dq gdt_null
  codeseg equ gdt_code - gdt_null
  dataseg equ gdt_data - gdt_null
global load_gdt:function
load_gdt:
  cli
  lgdt [gdt_desc]
  jmp codeseg:reload_cs
reload_cs:
  mov ax, dataseg
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  sti
  ret