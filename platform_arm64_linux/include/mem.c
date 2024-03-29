void *memcpy(void *dst,void *src,unsigned long int size);
asm "@memcpy"
asm "stp x4,x5,[sp,#-16]!"
asm "stp x6,x7,[sp,#-16]!"
asm "stp x8,x9,[sp,#-16]!"
asm "stp x10,x11,[sp,#-16]!"
asm "str x12,[sp,#-16]!"
asm "ldr x1,[sp,#96]"
asm "ldr x2,[sp,#80]"
asm "ldr x3,[sp,#112]"
asm "mov x0,x2"
asm "mov x12,#64"
asm "@memcpy_loop_start"
asm "subs x3,x3,x12"
asm "bcc @memcpy_loop_end"
asm "ldp q0,q1,[x1],#32"
asm "ldp q2,q3,[x1],#32"
asm "stp q0,q1,[x2],#32"
asm "stp q2,q3,[x2],#32"
asm "b @memcpy_loop_start"
asm "@memcpy_loop_end"
asm "mov x12,#32"
asm "ands xzr,x3,x12"
asm "beq @memcpy_X1"
asm "ldp x4,x5,[x1],#16"
asm "ldp x6,x7,[x1],#16"
asm "stp x4,x5,[x2],#16"
asm "stp x6,x7,[x2],#16"
asm "@memcpy_X1"
asm "mov x12,#16"
asm "ands xzr,x3,x12"
asm "beq @memcpy_X2"
asm "ldp x4,x5,[x1],#16"
asm "stp x4,x5,[x2],#16"
asm "@memcpy_X2"
asm "mov x12,#8"
asm "ands xzr,x3,x12"
asm "beq @memcpy_X3"
asm "ldr x4,[x1],#8"
asm "str x4,[x2],#8"
asm "@memcpy_X3"
asm "mov x12,#4"
asm "ands xzr,x3,x12"
asm "beq @memcpy_X4"
asm "ldr w4,[x1],#4"
asm "str w4,[x2],#4"
asm "@memcpy_X4"
asm "mov x12,#2"
asm "ands xzr,x3,x12"
asm "beq @memcpy_X5"
asm "ldrh w4,[x1],#2"
asm "strh w4,[x2],#2"
asm "@memcpy_X5"
asm "mov x12,#1"
asm "ands xzr,x3,x12"
asm "beq @memcpy_X6"
asm "ldrb w4,[x1],#1"
asm "strb w4,[x2],#1"
asm "@memcpy_X6"

asm "ldr x12,[sp],#16"
asm "ldp x10,x11,[sp],#16"
asm "ldp x8,x9,[sp],#16"
asm "ldp x6,x7,[sp],#16"
asm "ldp x4,x5,[sp],#16"
asm "ret"
void *memset(void *mem,int val,unsigned long int size);
asm "@memset"
asm "stp x4,x5,[sp,#-16]!"
asm "stp x6,x7,[sp,#-16]!"
asm "stp x8,x9,[sp,#-16]!"
asm "stp x10,x11,[sp,#-16]!"
asm "str x12,[sp,#-16]!"
asm "ldr x1,[sp,#80]"
asm "ldrb w2,[sp,#96]"
asm "ldr x3,[sp,#112]"
asm "mov x0,x1"
asm "mov x12,#8"
asm "lsl x4,x2,x12"
asm "lsl x5,x4,x12"
asm "lsl x6,x5,x12"
asm "lsl x7,x6,x12"
asm "lsl x8,x7,x12"
asm "lsl x9,x8,x12"
asm "lsl x10,x9,x12"
asm "orr x2,x2,x4"
asm "orr x2,x2,x5"
asm "orr x2,x2,x6"
asm "orr x2,x2,x7"
asm "orr x2,x2,x8"
asm "orr x2,x2,x9"
asm "orr x2,x2,x10"
asm "mov x4,x2"
asm "mov x12,#64"
asm "@memset_loop_start"
asm "subs x3,x3,x12"
asm "bcc @memset_loop_end"
asm "stp x2,x4,[x1],#16"
asm "stp x2,x4,[x1],#16"
asm "stp x2,x4,[x1],#16"
asm "stp x2,x4,[x1],#16"
asm "b @memset_loop_start"
asm "@memset_loop_end"
asm "mov x12,#32"
asm "ands xzr,x3,x12"
asm "beq @memset_X1"
asm "stp x2,x4,[x1],#16"
asm "stp x2,x4,[x1],#16"
asm "@memset_X1"
asm "mov x12,#16"
asm "ands xzr,x3,x12"
asm "beq @memset_X2"
asm "stp x2,x4,[x1],#16"
asm "@memset_X2"
asm "mov x12,#8"
asm "ands xzr,x3,x12"
asm "beq @memset_X3"
asm "str x2,[x1],#8"
asm "@memset_X3"
asm "mov x12,#4"
asm "ands xzr,x3,x12"
asm "beq @memset_X4"
asm "str w2,[x1],#4"
asm "@memset_X4"
asm "mov x12,#2"
asm "ands xzr,x3,x12"
asm "beq @memset_X5"
asm "strh w2,[x1],#2"
asm "@memset_X5"
asm "mov x12,#1"
asm "ands xzr,x3,x12"
asm "beq @memset_X6"
asm "strb w2,[x1],#1"
asm "@memset_X6"

asm "ldr x12,[sp],#16"
asm "ldp x10,x11,[sp],#16"
asm "ldp x8,x9,[sp],#16"
asm "ldp x6,x7,[sp],#16"
asm "ldp x4,x5,[sp],#16"
asm "ret"
int memcmp(void *mem1,void *mem2,unsigned long int size)
{
	unsigned long val;
	while(size>=8)
	{
		if(val=*(unsigned long *)mem1-*(unsigned long *)mem2)
		{
			while(!(char)val)
			{
				val>>=8;
			}
			return (char)val;
		}
		mem1=(char *)mem1+8;
		mem2=(char *)mem2+8;
		size-=8;
	}
	while(size)
	{
		if(val=*(char *)mem1-*(char *)mem2)
		{
			return val;
		}
		mem1=(char *)mem1+1;
		mem2=(char *)mem2+1;
		--size;
	}
	return 0;
}
unsigned long int strlen(char *str)
{
	unsigned long n;
	n=0;
	while(*str)
	{
		++n;
		++str;
	}
	return n;
}
unsigned long int strnlen(char *str,unsigned long int max)
{
	unsigned long int l;
	if(max==0)
	{
		return 0;
	}
	--max;
	l=0;
	while(*str&&l<max)
	{
		++l;
		++str;
	}
	return l;
}
int strcmp(char *str1,char *str2)
{
	unsigned long int l1,l2;
	l1=strlen(str1);
	l2=strlen(str2);
	if(l1>l2)
	{
		l1=l2;
	}
	return memcmp(str1,str2,l1+1);
}
int strncmp(char *str1,char *str2,unsigned long int max)
{
	unsigned long int l1,l2;
	l1=strnlen(str1,max);
	l2=strnlen(str2,max);
	if(l1>l2)
	{
		l1=l2;
	}
	return memcmp(str1,str2,l1+1);
}
char *strcpy(char *str1,char *str2)
{
	unsigned long int l;
	l=strlen(str2);
	return memcpy(str1,str2,l+1);
}
