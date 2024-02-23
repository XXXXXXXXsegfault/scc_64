#include "format.c"
struct ins
{
	char *name;
	char *format;
	char *encoding;
	int (*special_handler)(struct ins_args *,long);
	long priv;
	struct ins *next;
} *ins_list[1021];
void ins_add(char *format,char *encoding,int (*special_handler)(struct ins_args *,long),long priv)
{
	struct ins *ins;
	int hash;
	hash=0;
	ins=xmalloc(sizeof(*ins));
	ins->name=read_word(&format);
	ins->format=format;
	ins->encoding=encoding;
	ins->priv=priv;
	ins->special_handler=special_handler;
	hash+=name_hash(ins->name);
	hash=hash%1021;
	ins->next=ins_list[hash];
	ins_list[hash]=ins;
}
int write_default_ins(char *encoding,struct ins_args *args)
{
	char *word;
	unsigned int ins;
	ins=0;
	while(word=read_word(&encoding))
	{
		if(!strcmp(word,"0"))
		{
			ins=ins<<1;
		}
		else if(!strcmp(word,"1"))
		{
			ins=ins<<1|1;
		}
		else if(!strcmp(word,"R1"))
		{
			if(args->reg1==63)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg1;
		}
		else if(!strcmp(word,"R2"))
		{
			if(args->reg2==63)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg2;
		}
		else if(!strcmp(word,"R3"))
		{
			if(args->reg3==63)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg3;
		}
		else if(!strcmp(word,"R4"))
		{
			if(args->reg4==63)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg4;
		}
		else if(!strcmp(word,"RS1"))
		{
			if(args->reg1==31)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg1&31;
		}
		else if(!strcmp(word,"RS2"))
		{
			if(args->reg2==31)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg2&31;
		}
		else if(!strcmp(word,"RS3"))
		{
			if(args->reg3==31)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg3&31;
		}
		else if(!strcmp(word,"RS4"))
		{
			if(args->reg4==31)
			{
				free(word);
				return 1;
			}
			ins=ins<<5|args->reg4&31;
		}
		else if(!strcmp(word,"I16"))
		{
			if(args->imm>0xffff)
			{
				free(word);
				return 1;
			}
			ins=ins<<16|args->imm;
		}
		else if(!strcmp(word,"I12"))
		{
			if(args->imm>0xfff)
			{
				free(word);
				return 1;
			}
			ins=ins<<12|args->imm;
		}
		else if(!strcmp(word,"Is9"))
		{
			if(args->imm<0xffffffffffffff00&&args->imm>0xff)
			{
				free(word);
				return 1;
			}
			ins=ins<<9|args->imm&0x1ff;
		}
		else if(!strcmp(word,"Is7m8"))
		{
			if(args->imm&7||args->imm<0xfffffffffffffe00&&args->imm>0x1ff)
			{
				free(word);
				return 1;
			}
			ins=ins<<7|args->imm>>3&0x7f;
		}
		else if(!strcmp(word,"Is7m16"))
		{
			if(args->imm&15||args->imm<0xfffffffffffffc00&&args->imm>0x3ff)
			{
				free(word);
				return 1;
			}
			ins=ins<<7|args->imm>>4&0x7f;
		}
		free(word);
	}
	swrite(&ins,4);
	return 0;
}
void ins_write(char *input)
{
	struct ins *ins;
	struct ins_args args;
	char *p,*word;
	int hash;
	hash=0;
	word=read_word(&input);
	hash+=name_hash(word);
	hash=hash%1021;
	ins=ins_list[hash];
	while(ins)
	{
		if(!strcmp(ins->name,word))
		{
			if(!get_ins_args(input,ins->format,&args))
			{
				if(ins->special_handler)
				{
					if(!ins->special_handler(&args,ins->priv))
					{
						free(word);
						return;
					}
				}
				else
				{
					if(!write_default_ins(ins->encoding,&args))
					{
						free(word);
						return;
					}
				}
			}
		}
		ins=ins->next;
	}
	error(l->line,"unknown instruction.");
}
#include "branch.c"
#include "basic_op.c"
#include "mem.c"
#include "float.c"
int ins_write_mov64(struct ins_args *args,long priv)
{
	unsigned int ins;
	unsigned long n,c;
	if(args->reg1==63)
	{
		return 1;
	}
	if(args->imm<=0xffff)
	{
		ins=0xd2800000|args->imm<<5|args->reg1;
		swrite(&ins,4);
		return 0;
	}
	if(args->imm>=0xffffffffffff0000)
	{
		ins=0xd2800000|~args->imm<<5|args->reg1;
		swrite(&ins,4);
		ins=0xaa2003e0|args->reg1|(unsigned int)args->reg1<<16;
		swrite(&ins,4);
		return 0;
	}
	n=args->imm;
	c=n&0xffff;
	ins=0xd2800000|c<<5|args->reg1;
	swrite(&ins,4);
	n>>=16;
	if(n)
	{
		c=n&0xffff;
		ins=0xf2a00000|c<<5|args->reg1;
		swrite(&ins,4);
	}
	n>>=16;
	if(n)
	{
		c=n&0xffff;
		ins=0xf2c00000|c<<5|args->reg1;
		swrite(&ins,4);
	}
	n>>=16;
	if(n)
	{
		c=n&0xffff;
		ins=0xf2e00000|c<<5|args->reg1;
		swrite(&ins,4);
	}
	return 0;
}
void ins_init(void)
{
	ins_add("mov X1,#I","1 1 0 1 0 0 1 0 1 0 0 I16 R1",0,0);
	ins_add("mov X1,X2","1 0 1 0 1 0 1 0 0 0 0 R2 0 0 0 0 0 0 1 1 1 1 1 R1",0,0);
	ins_add("mov sp,X1","1 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS1 1 1 1 1 1",0,0);
	ins_add("mov X1,sp","1 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 RS1",0,0);
	ins_add("mov W1,W2","0 0 1 0 1 0 1 0 0 0 0 R2 0 0 0 0 0 0 1 1 1 1 1 R1",0,0);
	ins_add("sxtb X1,W2","1 0 0 1 0 0 1 1 0 1 0 0 0 0 0 0 0 0 0 1 1 1 R2 R1",0,0);
	ins_add("uxtb X1,W2","0 1 0 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 1 1 1 R2 R1",0,0);
	ins_add("sxth X1,W2","1 0 0 1 0 0 1 1 0 1 0 0 0 0 0 0 0 0 1 1 1 1 R2 R1",0,0);
	ins_add("uxth X1,W2","0 1 0 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 1 1 1 1 R2 R1",0,0);
	ins_add("sxtw X1,W2","1 0 0 1 0 0 1 1 0 1 0 0 0 0 0 0 0 1 1 1 1 1 R2 R1",0,0);
	ins_add("mvn X1,X2","1 0 1 0 1 0 1 0 0 0 1 R2 0 0 0 0 0 0 1 1 1 1 1 R1",0,0);
	ins_add("mov64 X1,I",0,ins_write_mov64,0);
	ins_init_branch();
	ins_init_basic_op();
	ins_init_mem();
	ins_init_float();
	ins_add("svc #I","1 1 0 1 0 1 0 0 0 0 0 I16 0 0 0 0 1",0,0);
}
