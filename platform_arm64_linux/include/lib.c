asm ".align 3"
asm ".entry"
asm "add x1,sp,#8"
asm "ldr x0,[sp]"
asm "str x1,[sp,#-16]!"
asm "str x0,[sp,#-16]!"
asm "bl @main"
asm "mov x8,#94"
asm "svc #0"

#define ARCH_BAD_INST asm ".long 0xffffffff"
#include "syscall.c"
#include "mem.c"
#include "malloc.c"
#include "xmalloc.c"
#include "string.c"
