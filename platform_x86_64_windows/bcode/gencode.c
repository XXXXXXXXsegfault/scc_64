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
	if(op->tab->reg>=0&&op->tab->reg<11)
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
void op_out_const(int class,struct operand *op)
{
	unsigned long val;
	double fval;
	float hval;
	if(op->type==2)
	{
		if(class==9||class==10)
		{
			if(op->is_float)
			{
				if(class==10)
				{
					out_num(class,op->fvalue);
				}
				else
				{
					memcpy(&fval,&op->fvalue,8);
					hval=fval;
					val=0;
					memcpy(&val,&hval,4);
					out_num(class,val);
				}
			}
			else
			{
				if(class==10)
				{
					fval=(double)op->value;
					memcpy(&val,&fval,8);
					out_num(class,val);
				}
				else
				{
					hval=(float)op->value;
					val=0;
					memcpy(&val,&hval,4);
					out_num(class,val);
				}
			}
		}
		else
		{
			if(op->is_float)
			{
				val=(long)op->fvalue;
				out_num(class,val);
			}
			else
			{
				out_num(class,op->value);
			}
		}
	}
	else if(op->type==3)
	{
		outs("@");
		outs(op->str);
	}
}
void op_out_reg(int class,struct operand *op)
{
	out_reg(class,op->tab->reg+1);
}
void op_out_mem(struct operand *op)
{
	long int x;
	if(op->tab->storage==0)
	{
		if(op->tab->reg>=11)
		{
			x=op->tab->reg-11;
			out_num(7,x*8+fun_stack_size);
		}
		else
		{
			out_num(7,op->tab->off);
		}
		outs("(%rbp)");
	}
	else if(op->tab->storage==2)
	{
		outs("@_$DATA+");
		out_num(7,op->tab->off);
	}
	else if(op->tab->storage==1)
	{
		out_num(7,op->tab->off*8+16);
		outs("(%rbp)");
	}
}
void op_out_mem_off(struct operand *op,struct operand *off)
{
	long int x;
	if(op->tab->storage==0)
	{
		if(op->tab->reg>=11)
		{
			x=op->tab->reg-11;
			out_num(7,x*8+fun_stack_size+off->value);
		}
		else
		{
			out_num(7,op->tab->off+off->value);
		}
		outs("(%rbp)");
	}
	else if(op->tab->storage==2)
	{
		outs("@_$DATA+");
		out_num(7,op->tab->off+off->value);
	}
	else if(op->tab->storage==1)
	{
		out_num(7,op->tab->off*8+16+off->value);
		outs("(%rbp)");
	}
}
int if_class_signed(int class)
{
	if(class==9||class==10)
	{
		return 0;
	}
	if(class&1)
	{
		return 1;
	}
	return 0;
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
void reg_extend(int class,int old_class,struct operand *op)
{
	int size1,size2;
	if(class==9||class==10)
	{
		if(old_class!=9&&old_class!=10)
		{
			if(old_class<7)
			{
				reg_extend(7,old_class,op);
				old_class=7;
			}
			if(class==10)
			{
				outs("cvtsi2sd ");
			}
			else
			{
				outs("cvtsi2ss ");
			}
			op_out_reg(old_class,op);
			outs(",%xmm0\n");
			if(class==10)
			{
				outs("movq %xmm0,");
			}
			else
			{
				outs("movd %xmm0,");
			}
			op_out_reg(class,op);
			outs("\n");
		}
		else if(class==9&&old_class==10)
		{
			outs("movq ");
			op_out_reg(10,op);
			outs(",%xmm0\ncvtsd2ss %xmm0,%xmm0\nmovd %xmm0,");
			op_out_reg(9,op);
			outs("\n");
		}
		else if(class==10&&old_class==9)
		{
			outs("movd ");
			op_out_reg(9,op);
			outs(",%xmm0\ncvtss2sd %xmm0,%xmm0\nmovq %xmm0,");
			op_out_reg(10,op);
			outs("\n");
		}
		return;
	}	
	else if(old_class==9)
	{
		outs("movd ");
		op_out_reg(9,op);
		outs(",%xmm0\ncvtss2si %xmm0,");
		op_out_reg(8,op);
		outs("\n");
		return;
	}
	else if(old_class==10)
	{
		outs("movq ");
		op_out_reg(10,op);
		outs(",%xmm0\ncvtsd2si %xmm0,");
		op_out_reg(8,op);
		outs("\n");
		return;
	}
	size1=class-1>>1;
	size2=old_class-1>>1;
	if(size1<=size2)
	{
		return;
	}
	outs("mov");
	if(size1==3&&size2==2&&!(old_class&1))
	{
		outs(" ");
		op_out_reg(5,op);
		outs(",");
		op_out_reg(5,op);
		outs("\n");
		return;
	}
	if(old_class&1)
	{
		outs("s");
	}
	else
	{
		outs("z");
	}
	if(size2==0)
	{
		outs("b");
	}
	else if(size2==1)
	{
		outs("w");
	}
	else if(size2==2)
	{
		outs("l");
	}
	else if(size2==3)
	{
		outs("q");
	}
	if(size1==0)
	{
		outs("b ");
	}
	else if(size1==1)
	{
		outs("w ");
	}
	else if(size1==2)
	{
		outs("l ");
	}
	else if(size1==3)
	{
		outs("q ");
	}
	op_out_reg(old_class,op);
	outs(",");
	op_out_reg(class,op);
	outs("\n");
}
void out_ins_acd1(char *ins1,char *ins2,char *ins3,struct operand *op1,int reg,int class)
{
	outs(ins1);
	if(ins2)
	{
		outs(ins2);
	}
	if(ins3)
	{
		outs(ins3);
	}
	outs(" ");
	if(op1)
	{
		if(op_is_reg(op1))
		{
			op_out_reg(op1->tab->class,op1);
			outs(",");
			out_acd(op1->tab->class,reg);
		}
		else if(op_is_const(op1))
		{
			outs("$");
			op_out_const(class,op1);
			outs(",");
			out_acd(class,reg);
		}
		else
		{
			op_out_mem(op1);
			outs(",");
			if(op_is_addr(op1))
			{
				out_acd(8,reg);
			}
			else
			{
				out_acd(class,reg);
			}
		}
	}
	outs("\n");
	if(op_is_addr(op1))
	{
		acd_extend(reg,class,8);
	}
	else if(!op_is_const(op1))
	{
		acd_extend(reg,class,op1->tab->class);
	}
}
void out_ins_acd2(char *ins1,char *ins2,char *ins3,int reg,struct operand *op1,int class)
{
	outs(ins1);
	if(ins2)
	{
		outs(ins2);
	}
	if(ins3)
	{
		outs(ins3);
	}
	outs(" ");
	out_acd(class,reg);
	if(op1)
	{
		outs(",");
		if(op_is_reg(op1))
		{
			op_out_reg(class,op1);
		}
		else if(op_is_const(op1))
		{
			outs("$");
			op_out_const(class,op1);
		}
		else
		{
			op_out_mem(op1);
		}
	}
	outs("\n");
}
void out_ins_acd3(char *ins1,char *ins2,char *ins3,int reg1,int reg2,int class)
{
	outs(ins1);
	if(ins2)
	{
		outs(ins2);
	}
	if(ins3)
	{
		outs(ins3);
	}
	outs(" ");
	out_acd(class,reg1);
	outs(",");
	out_acd(class,reg2);
	outs("\n");
}
void out_ins(char *ins1,char *ins2,char *ins3,struct operand *op1,struct operand *op2,char *ins4,int class)
{
	if(class==0)
	{
		if(op2)
		{
			class=op2->tab->class;
		}
		else
		{
			class=op1->tab->class;
		}
	}
	if(op_is_reg(op1)&&op1->tab->class!=9&&op2->tab->class!=9)
	{
		reg_extend(class,op1->tab->class,op1);
	}
	outs(ins1);
	if(ins2)
	{
		outs(ins2);
	}
	if(ins3)
	{
		outs(ins3);
	}
	outs(" ");
	if(op_is_reg(op1))
	{
		op_out_reg(class,op1);
	}
	else if(op_is_const(op1))
	{
		outs("$");
		op_out_const(class,op1);
	}
	else
	{
		op_out_mem(op1);
	}
	if(op2)
	{
		outs(",");
		if(op_is_reg(op2))
		{
			op_out_reg(class,op2);
		}
		else if(op_is_const(op2))
		{
			outs("$");
			op_out_const(class,op2);
		}
		else
		{
			op_out_mem(op2);
		}
	}
	if(ins4)
	{
		outs(ins4);
	}
	outs("\n");
	if(op2)
	{
		if(op_is_reg(op2))
		{
			reg_extend(class,op2->tab->class,op2);
		}
	}
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
#include "mul.c"
#include "div.c"
#include "mod.c"
#include "lsh.c"
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
	int x;
	int in_asm;
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
			gen_basic_op(ins,"or");
		}
		else if(!strcmp(ins->args[0],"eor"))
		{
			gen_basic_op(ins,"xor");
		}
		else if(!strcmp(ins->args[0],"mul"))
		{
			gen_mul(ins);
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
			gen_lsh(ins);
		}
		else if(!strcmp(ins->args[0],"rsh"))
		{
			gen_rsh(ins);
		}
		else if(!strcmp(ins->args[0],"ble"))
		{
			gen_branch(ins,"jle","jbe","jg","ja");
		}
		else if(!strcmp(ins->args[0],"bge"))
		{
			gen_branch(ins,"jge","jae","jl","jb");
		}
		else if(!strcmp(ins->args[0],"blt"))
		{
			gen_branch(ins,"jl","jb","jge","jae");
		}
		else if(!strcmp(ins->args[0],"bgt"))
		{
			gen_branch(ins,"jg","ja","jle","jbe");
		}
		else if(!strcmp(ins->args[0],"beq"))
		{
			gen_branch(ins,"je","je","jne","jne");
		}
		else if(!strcmp(ins->args[0],"bne"))
		{
			gen_branch(ins,"jne","jne","je","je");
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
			gen_ld(ins,10);
		}
		else if(!strcmp(ins->args[0],"ldh"))
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
			gen_st(ins,10);
		}
		else if(!strcmp(ins->args[0],"sth"))
		{
			gen_st(ins,9);
		}
		else if(!strcmp(ins->args[0],"ldob"))
		{
			gen_ldo(ins,1);
		}
		else if(!strcmp(ins->args[0],"ldow"))
		{
			gen_ldo(ins,3);
		}
		else if(!strcmp(ins->args[0],"ldol"))
		{
			gen_ldo(ins,5);
		}
		else if(!strcmp(ins->args[0],"ldoq"))
		{
			gen_ldo(ins,7);
		}
		else if(!strcmp(ins->args[0],"ldof"))
		{
			gen_ldo(ins,10);
		}
		else if(!strcmp(ins->args[0],"ldoh"))
		{
			gen_ldo(ins,9);
		}
		else if(!strcmp(ins->args[0],"stob"))
		{
			gen_sto(ins,1);
		}
		else if(!strcmp(ins->args[0],"stow"))
		{
			gen_sto(ins,3);
		}
		else if(!strcmp(ins->args[0],"stol"))
		{
			gen_sto(ins,5);
		}
		else if(!strcmp(ins->args[0],"stoq"))
		{
			gen_sto(ins,7);
		}
		else if(!strcmp(ins->args[0],"stof"))
		{
			gen_sto(ins,10);
		}
		else if(!strcmp(ins->args[0],"stoh"))
		{
			gen_sto(ins,9);
		}
		else if(!strcmp(ins->args[0],"push"))
		{
			gen_push(ins,7);
		}
		else if(!strcmp(ins->args[0],"pushh"))
		{
			gen_push(ins,9);
		}
		else if(!strcmp(ins->args[0],"pushf"))
		{
			gen_push(ins,10);
		}
		else if(!strcmp(ins->args[0],"call"))
		{
			gen_call(ins,0);
		}
		else if(!strcmp(ins->args[0],"hcall"))
		{
			gen_call(ins,1);
		}
		else if(!strcmp(ins->args[0],"fcall"))
		{
			gen_call(ins,2);
		}
		else if(!strcmp(ins->args[0],"retval"))
		{
			gen_retval(ins,7);
		}
		else if(!strcmp(ins->args[0],"retvalh"))
		{
			gen_retval(ins,9);
		}
		else if(!strcmp(ins->args[0],"retvalf"))
		{
			gen_retval(ins,10);
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
		else if(!strcmp(ins->args[0],"adro"))
		{
			gen_adro(ins);
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
				outs("add $");
				out_num64(size*8);
				outs(",%rsp\n");
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
			outs("push %rbp\n");
			outs("mov %rsp,%rbp\n");
			if(ins->stack_size)
			{
				outs("sub $");
				out_num64(-ins->stack_size);
				outs(",%rsp\n");
			}
			x=0;
			while(x<11)
			{
				if(ins->used_regs&1<<x)
				{
					outs("push ");
					out_reg64(x+1);
					outs("\n");
					if(ins->arg_map[x]!=-1)
					{
						outs("mov ");
						out_num(7,ins->arg_map[x]*8+16);
						outs("(%rbp),");
						out_reg64(x+1);
						outs("\n");
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
				x=11;
				while(x)
				{
					--x;
					if(fstart->used_regs&1<<x)
					{
						outs("pop ");
						out_reg64(x+1);
						outs("\n");
					}
				}
				outs("mov %rbp,%rsp\npop %rbp\nret\n");
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
					outs("jmp ");
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
			outs("jmp @_$LB");
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
