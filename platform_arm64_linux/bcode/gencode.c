long int fun_stack_size;
struct operand
{
	long int type;
	struct id_tab *tab;
	unsigned long int value;
	long int fvalue;
	long int is_float;
	char *str;
};
void get_operand(struct ins *ins,int index,struct operand *ret)
{
	char *str;
	int s;
	memset(ret,0,sizeof(*ret));
	if(index>=ins->count_args)
	{
		error(ins->line,"too few arguments.");
	}
	str=ins->args[index];
	ret->str=str;
	if(ret->tab=id_find(str))
	{
		if(ret->tab->class==0)
		{
			ret->type=0;
		}
		else
		{
			ret->type=1;
		}
	}
	else if(str[0]>='0'&&str[0]<='9'||str[0]=='\'')
	{
		ret->type=2;
		ret->fvalue=fconst_to_num(str,&s);
		ret->is_float=s;
		ret->value=const_to_num(str);
	}
	else
	{
		ret->type=3;
	}
}
int op_is_reg(struct operand *op)
{
	if(!op->tab)
	{
		return 0;
	}
	if(op->tab->reg>=0&&op->tab->reg<REGS)
	{
		return 1;
	}
	return 0;
}
int op_is_const(struct operand *op)
{
	if(op->type==2||op->type==3)
	{
		return 1;
	}
	return 0;
}
int op_is_addr(struct operand *op)
{
	if(op->type==0)
	{
		return 1;
	}
	return 0;
}
int if_class_signed(int class)
{
	if(class==9)
	{
		return 0;
	}
	if(class&1)
	{
		return 1;
	}
	return 0;
}
void op_reg_st(int addr_reg,int reg,int class)
{
	if(class==1||class==2)
	{
		outs("strb ");
		out_reg32(reg);
	}
	else if(class==3||class==4)
	{
		outs("strh ");
		out_reg32(reg);
	}
	else if(class==5||class==6)
	{
		outs("str ");
		out_reg32(reg);
	}
	else
	{
		outs("str ");
		out_reg64(reg);
	}
	outs(",[");
	out_reg64(addr_reg);
	outs("]\n");
}	
void op_reg_ld(int addr_reg,int reg,int class)
{
	if(class==1||class==2)
	{
		if(class==1)
		{
			outs("ldrsb ");
			out_reg64(reg);
		}
		else
		{
			outs("ldrb ");
			out_reg32(reg);
		}
	}
	else if(class==3||class==4)
	{
		if(class==3)
		{
			outs("ldrsh ");
			out_reg64(reg);
		}
		else
		{
			outs("ldrh ");
			out_reg32(reg);
		}
	}
	else if(class==5||class==6)
	{
		if(class==5)
		{
			outs("ldrsw ");
			out_reg64(reg);
		}
		else
		{
			outs("ldr ");
			out_reg32(reg);
		}
	}
	else
	{
		outs("ldr ");
		out_reg64(reg);
	}
	outs(",[");
	out_reg64(addr_reg);
	outs("]\n");
}	
void op_mem_ldst(char *ld_st,struct operand *op,int reg)
{
	long int x;
	if(op->tab->storage==0)
	{
		if(op->tab->reg>=REGS)
		{
			x=op->tab->reg-REGS;
			x=x*16+fun_stack_size;
		}
		else
		{
			x=op->tab->off;
		}
		if(x<256&&x>-256)
		{
			outs(ld_st);
			out_reg_size(reg,op->tab->class);
			outs(",[x29,#");
			out_num64(x);
			outs("]\n");
		}
		else
		{
			outs("mov64 x3,");
			out_num64(x);
			outs("\n");
			outs(ld_st);
			out_reg_size(reg,op->tab->class);
			outs(",[x29,x3]\n");
		}
	}
	else if(op->tab->storage==2)
	{
		outs("mov64 x3,@_$DATA+");
		out_num64(op->tab->off);
		outs("\n");
		outs(ld_st);
		out_reg_size(reg,op->tab->class);
		outs(",[x3]\n");
	}
	else if(op->tab->storage==1)
	{
		outs("mov64 x3,");
		out_num64(op->tab->off*16+16);
		outs("\n");
		outs(ld_st);
		out_reg_size(reg,op->tab->class);
		outs(",[x29,x3]\n");
	}
	if(!strcmp(ld_st,"ldr"))
	{
		if(op->tab->class==1)
		{
			outs("sxtb ");
			out_reg64(reg);
			outs(",");
			out_reg32(reg);
			outs("\n");
		}
		else if(op->tab->class==3)
		{
			outs("sxth ");
			out_reg64(reg);
			outs(",");
			out_reg32(reg);
			outs("\n");
		}
		else if(op->tab->class==5)
		{
			outs("sxtw ");
			out_reg64(reg);
			outs(",");
			out_reg32(reg);
			outs("\n");
		}
	}
}
void op_calculate_addr(struct operand *op,int reg)
{
	long int x;
	if(op->tab->storage==0)
	{
		if(op->tab->reg>=REGS)
		{
			x=op->tab->reg-REGS;
			x=x*16+fun_stack_size;
		}
		else
		{
			x=op->tab->off;
		}
		if(x<256&&x>=0)
		{
			outs("add ");
			out_reg64(reg);
			outs(",x29,#");
			out_num64(x);
			outs("\n");
		}
		else if(x>-256&&x<0)
		{
			outs("sub ");
			out_reg64(reg);
			outs(",x29,#");
			out_num64(-x);
			outs("\n");
		}
		else
		{
			outs("mov64 x3,");
			out_num64(x);
			outs("\n");
			outs("add ");
			out_reg64(reg);
			outs(",x29,x3\n");
		}
	}
	else if(op->tab->storage==2)
	{
		outs("mov64 ");
		out_reg64(reg);
		outs(",@_$DATA+");
		out_num64(op->tab->off);
		outs("\n");
	}
	else if(op->tab->storage==1)
	{
		outs("mov64 x3,");
		out_num64(op->tab->off*16+16);
		outs("\n");
		outs("add ");
		out_reg64(reg);
		outs(",x29,x3\n");
	}
}
void reg_f2q(int reg)
{
	outs("fmov d0,");
	out_reg64(reg);
	outs("\nfcvtns ");
	out_reg64(reg);
	outs(",d0\n");
}
void reg_q2f(int reg)
{
	outs("scvtf d0,");
	out_reg64(reg);
	outs("\nfmov ");
	out_reg64(reg);
	outs(",d0\n");
}
void reg_ext(int reg,int class,int new_class)
{
	if(class==1)
	{
		outs("sxtb ");
		out_reg64(reg);
		outs(",");
		out_reg32(reg);
		outs("\n");
	}
	else if(class==2)
	{
		outs("uxtb ");
		out_reg64(reg);
		outs(",");
		out_reg32(reg);
		outs("\n");
	}
	else if(class==3)
	{
		outs("sxth ");
		out_reg64(reg);
		outs(",");
		out_reg32(reg);
		outs("\n");
	}
	else if(class==4)
	{
		outs("uxth ");
		out_reg64(reg);
		outs(",");
		out_reg32(reg);
		outs("\n");
	}
	else if(class==5)
	{
		outs("sxtw ");
		out_reg64(reg);
		outs(",");
		out_reg32(reg);
		outs("\n");
	}
	else if(class==6)
	{
		outs("mov ");
		out_reg32(reg);
		outs(",");
		out_reg32(reg);
		outs("\n");
	}
	if(class==9&&new_class!=9)
	{
		reg_f2q(reg);
	}
	if(class!=9&&new_class==9)
	{
		reg_q2f(reg);
	}
}
void op_out_const(int class,struct operand *op)
{
	unsigned long val;
	float fval;
	if(op->type==2)
	{
		if(class==9)
		{
			if(op->is_float)
			{
				out_num64(op->fvalue);
			}
			else
			{
				fval=(float)op->value;
				memcpy(&val,&fval,8);
				out_num64(val);
			}
		}
		else
		{
			if(op->is_float)
			{
				val=(long)op->fvalue;
				out_num64(val);
			}
			else
			{
				out_num64(op->value);
			}
		}
	}
	else if(op->type==3)
	{
		outs("@");
		outs(op->str);
	}
}
int opcmp(struct operand *op1,struct operand *op2)
{
	int class1,class2;
	class1=0;
	class2=0;
	if(op_is_reg(op1))
	{
		class1=1;
	}
	else if(op_is_const(op1))
	{
		class1=2;
	}
	else if(op_is_addr(op1))
	{
		class1=3;
	}
	if(op_is_reg(op2))
	{
		class2=1;
	}
	else if(op_is_const(op2))
	{
		class2=2;
	}
	else if(op_is_addr(op2))
	{
		class2=3;
	}
	if(class1!=class2)
	{
		return 1;
	}
	if(class1==0)
	{
		if(op1->tab->storage!=op2->tab->storage)
		{
			return 1;
		}
		if(op1->tab->reg!=op2->tab->reg)
		{
			return 1;
		}
		if(op1->tab->off==op2->tab->off)
		{
			return 0;
		}
	}
	else if(class1==1)
	{
		if(op1->tab->reg==op2->tab->reg)
		{
			return 0;
		}
	}
	return 1;
}
int needs_convert(struct operand *op,struct operand *op2)
{
	if(op2->tab->class-1>>1>op->tab->class-1>>1)
	{
		return 1;
	}
	return 0;
}
int last_store_valid;
struct operand last_store[2];
char *fun_name;
#include "mov.c"
#include "basic_op.c"
#include "div.c"
#include "mod.c"
#include "rsh.c"
#include "branch.c"
#include "ld.c"
#include "st.c"
#include "call.c"
#include "not.c"
#include "neg.c"
#include "adr.c"
void write_msg(void)
{
	struct ins *ins;
	int x;
	long int num;
	char *name;
	num=1;
	ins=ins_head;
	while(ins)
	{
		x=1;
		while(x<ins->count_args)
		{
			if(ins->args[x][0]=='\"'&&strcmp(ins->args[0],"asm"))
			{
				//TODO CHANGE
				name=xstrdup("_$MSG");
				name=str_i_app(name,num);
				outs("@");
				outs(name);
				outs("\n");
				outs(".string ");
				outs(ins->args[x]);
				outs("\n");
				free(ins->args[x]);
				ins->args[x]=name;
				++num;
			}
			++x;
		}
		ins=ins->next;
	}
}
void gen_code(struct ins *ins)
{
	unsigned long int size;
	int x,x2;
	int in_asm;
	unsigned long val;
	if(ins->count_args)
	{
		if(!strcmp(ins->args[0],"mov"))
		{
			gen_mov(ins);
		}
		else if(!strcmp(ins->args[0],"add"))
		{
			gen_basic_op(ins,"add");
		}
		else if(!strcmp(ins->args[0],"sub"))
		{
			gen_basic_op(ins,"sub");	
		}
		else if(!strcmp(ins->args[0],"and"))
		{
			gen_basic_op(ins,"and");
		}
		else if(!strcmp(ins->args[0],"orr"))
		{
			gen_basic_op(ins,"orr");
		}
		else if(!strcmp(ins->args[0],"eor"))
		{
			gen_basic_op(ins,"eor");
		}
		else if(!strcmp(ins->args[0],"mul"))
		{
			gen_basic_op(ins,"mul");
		}
		else if(!strcmp(ins->args[0],"div"))
		{
			gen_div(ins);
		}
		else if(!strcmp(ins->args[0],"mod"))
		{
			gen_mod(ins);
		}
		else if(!strcmp(ins->args[0],"lsh"))
		{
			gen_basic_op(ins,"lsl");
		}
		else if(!strcmp(ins->args[0],"rsh"))
		{
			gen_rsh(ins);
		}
		else if(!strcmp(ins->args[0],"ble"))
		{
			gen_branch(ins,"ble","bls");
		}
		else if(!strcmp(ins->args[0],"bge"))
		{
			gen_branch(ins,"bge","bcs");
		}
		else if(!strcmp(ins->args[0],"blt"))
		{
			gen_branch(ins,"blt","bcc");
		}
		else if(!strcmp(ins->args[0],"bgt"))
		{
			gen_branch(ins,"bgt","bhi");
		}
		else if(!strcmp(ins->args[0],"beq"))
		{
			gen_branch(ins,"beq","beq");
		}
		else if(!strcmp(ins->args[0],"bne"))
		{
			gen_branch(ins,"bne","bne");
		}
		else if(!strcmp(ins->args[0],"ldb"))
		{
			gen_ld(ins,1);
		}
		else if(!strcmp(ins->args[0],"ldw"))
		{
			gen_ld(ins,3);
		}
		else if(!strcmp(ins->args[0],"ldl"))
		{
			gen_ld(ins,5);
		}
		else if(!strcmp(ins->args[0],"ldq"))
		{
			gen_ld(ins,7);
		}
		else if(!strcmp(ins->args[0],"ldf"))
		{
			gen_ld(ins,9);
		}
		else if(!strcmp(ins->args[0],"stb"))
		{
			gen_st(ins,1);
		}
		else if(!strcmp(ins->args[0],"stw"))
		{
			gen_st(ins,3);
		}
		else if(!strcmp(ins->args[0],"stl"))
		{
			gen_st(ins,5);
		}
		else if(!strcmp(ins->args[0],"stq"))
		{
			gen_st(ins,7);
		}
		else if(!strcmp(ins->args[0],"stf"))
		{
			gen_st(ins,9);
		}
		else if(!strcmp(ins->args[0],"push"))
		{
			gen_push(ins);
		}
		else if(!strcmp(ins->args[0],"call"))
		{
			gen_call(ins,0);
		}
		else if(!strcmp(ins->args[0],"fcall"))
		{
			gen_call(ins,1);
		}
		else if(!strcmp(ins->args[0],"retval"))
		{
			gen_retval(ins);
		}
		else if(!strcmp(ins->args[0],"not"))
		{
			gen_not(ins);
		}
		else if(!strcmp(ins->args[0],"neg"))
		{
			gen_neg(ins);
		}
		else if(!strcmp(ins->args[0],"adr"))
		{
			gen_adr(ins);
		}
		else if(!strcmp(ins->args[0],"del"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			size=const_to_num(ins->args[1]);
			if(size)
			{
				if(size<256)
				{
					outs("add sp,sp,#");
					out_num64(size*16);
					outs("\n");
				}
				else
				{
					outs("mov64 x1,");
					out_num64(size*16);
					outs("\nadd sp,sp,x1\n");
				}
			}
		}
		else if(!strcmp(ins->args[0],"fun"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			fstart=ins;
			fun_name=ins->args[1];
			fun_stack_size=ins->stack_size;
			out_label(fun_name);
			outs("stp x29,x30,[sp,#-16]!\nmov x29,sp\n");
			if(ins->stack_size)
			{
				if(-ins->stack_size<2048)
				{
					outs("sub sp,sp,#");
					out_num64(-ins->stack_size);
					outs("\n");
				}
				else
				{
					outs("mov64 x1,");
					out_num64(-ins->stack_size);
					outs("\n");
					outs("sub sp,sp,x1\n");
				}
			}
			x=0;
			while(x<REGS)
			{
				if(ins->used_regs&1<<x)
				{
					outs("str ");
					out_reg64(x+4);
					outs(",[sp,#-16]!\n");
					if(ins->arg_map[x]!=-1)
					{
						val=ins->arg_map[x]*16+16;
						if(val<256)
						{
							outs("ldr ");
							out_reg64(x+4);
							outs(",[x29,#");
							out_num64(val);
							outs("]\n");
						}
						else
						{
							outs("mov64 x1,");
							out_num64(val);
							outs("\nldr ");
							out_reg64(x+4);
							outs(",[x29,x1]\n");
						}
					}
				}
				++x;
			}
			last_store_valid=0;
		}
		else if(!strcmp(ins->args[0],"endf"))
		{
			if(fun_name)
			{
				outs("@");
				out_label_name(fun_name);
				outs("$END\n");
				x=REGS;
				while(x)
				{
					--x;
					if(fstart->used_regs&1<<x)
					{
						outs("ldr ");
						out_reg64(x+4);
						outs(",[sp],#16\n");
					}
				}
				outs("mov sp,x29\nldp x29,x30,[sp],#16\nret\n");
				fstart=0;
			}
			else
			{
				error(ins->line,"endf without fun.");
			}
			fun_name=0;
			last_store_valid=0;
		}
		else if(!strcmp(ins->args[0],"ret"))
		{
			struct ins *p;
			p=ins->next;
			while(p)
			{
				if(p->op)
				{
					outs("b ");
					outs("@");
					outs(fun_name);
					outs("$END\n");
					break;
				}
				if(p->count_args&&!strcmp(p->args[0],"endf"))
				{
					break;
				}
				p=p->next;
			}
			last_store_valid=0;
		}
		else if(!strcmp(ins->args[0],"bal"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			outs("b @_$LB");
			outs(ins->args[1]);
			outs("\n");
			last_store_valid=0;
		}
		else if(!strcmp(ins->args[0],"label"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			outs("@_$LB");
			outs(ins->args[1]);
			outs("\n");
			last_store_valid=0;
		}
		else if(!strcmp(ins->args[0],"asm"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			out_str(ins->args[1]);
			outs("\n");
		}
	}
}
