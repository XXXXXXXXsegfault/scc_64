void gen_float_basic_op(int class1,int class2,int class3,struct operand *op1,struct operand *op2,struct operand *op3,char *ins)
{
	char *fins;
	int reg1,reg2;
	reg1=1;
	reg2=2;
	if(!strcmp(ins,"add"))
	{
		fins="fadd";
	}
	else if(!strcmp(ins,"sub"))
	{
		fins="fsub";
	}
	else if(!strcmp(ins,"mul"))
	{
		fins="fmul";
	}
	else if(!strcmp(ins,"udiv"))
	{
		fins="fdiv";
	}
	else
	{
		fins=ins;
	}
	if(class2==0&&op2->tab->class==10)
	{
		op_mem_ldst_float("ldr ",op2,1,10);
	}
	else if(class2==0&&op2->tab->class==9)
	{
		op_mem_ldst_float("ldr ",op2,1,9);
		outs("fcvt d1,s1\n");
	}
	else
	{
		if(class2==1)
		{
			reg1=op2->tab->reg+4;
		}
		else if(class2==0)
		{
			op_mem_ldst("ldr",op2,1);
		}
		else if(class2==2)
		{
			outs("mov64 x1,");
			op_out_const(10,op2);
			outs("\n");
		}
		else if(class2==3)
		{
			op_calculate_addr(op2,1);
		}
		if(class2==2||class2==3||op2->tab->class==10)
		{
			outs("fmov d1,");
			out_reg64(reg1);
			outs("\n");
		}
		else if(op2->tab->class==9)
		{
			outs("fmov s1,");
			out_reg32(reg1);
			outs("\n");
			outs("fcvt d1,s1\n");
		}
		else
		{
			outs("scvtf d1,");
			out_reg64(reg1);
			outs("\n");
		}
	}
	if(class3==0&&op3->tab->class==10)
	{
		op_mem_ldst_float("ldr ",op3,2,10);
	}
	else if(class3==0&&op3->tab->class==9)
	{
		op_mem_ldst_float("ldr ",op3,2,9);
		outs("fcvt d2,s2\n");
	}
	else
	{
		if(class3==1)
		{
			reg2=op3->tab->reg+4;
		}
		else if(class3==0)
		{
			op_mem_ldst("ldr",op3,2);
		}
		else if(class3==2)
		{
			outs("mov64 x2,");
			op_out_const(10,op3);
			outs("\n");
		}
		else if(class3==3)
		{
			op_calculate_addr(op3,2);
		}
		if(class3==2||class3==3||op3->tab->class==10)
		{
			outs("fmov d2,");
			out_reg64(reg2);
			outs("\n");
		}
		else if(op3->tab->class==9)
		{
			outs("fmov s2,");
			out_reg32(reg2);
			outs("\n");
			outs("fcvt d2,s2\n");
		}
		else
		{
			outs("scvtf d2,");
			out_reg64(reg2);
			outs("\n");
		}
	}
	outs(fins);
	outs(" d0,d1,d2\n");
	if(class1==1)
	{
		outs("fmov ");
		out_reg64(op1->tab->reg+4);
		outs(",d0\n");
	}
	else
	{
		op_mem_ldst_float("str ",op1,0,10);
	}
}
void gen_hfloat_basic_op(int class1,int class2,int class3,struct operand *op1,struct operand *op2,struct operand *op3,char *ins)
{
	char *fins;
	int reg1,reg2;
	reg1=1;
	reg2=2;
	if(!strcmp(ins,"add"))
	{
		fins="fadd";
	}
	else if(!strcmp(ins,"sub"))
	{
		fins="fsub";
	}
	else if(!strcmp(ins,"mul"))
	{
		fins="fmul";
	}
	else if(!strcmp(ins,"udiv"))
	{
		fins="fdiv";
	}
	else
	{
		fins=ins;
	}
	if(class2==0&&op2->tab->class==9)
	{
		op_mem_ldst_float("ldr ",op2,1,9);
	}
	else if(class2==0&&op2->tab->class==10)
	{
		op_mem_ldst_float("ldr ",op2,1,10);
		outs("fcvt s1,d1\n");
	}
	else
	{
		if(class2==1)
		{
			reg1=op2->tab->reg+4;
		}
		else if(class2==0)
		{
			op_mem_ldst("ldr",op2,1);
		}
		else if(class2==2)
		{
			outs("mov64 x1,");
			op_out_const(9,op2);
			outs("\n");
		}
		else if(class2==3)
		{
			op_calculate_addr(op2,1);
		}
		if(class2==2||class2==3||op2->tab->class==9)
		{
			outs("fmov s1,");
			out_reg32(reg1);
			outs("\n");
		}
		else if(op2->tab->class==10)
		{
			outs("fmov d1,");
			out_reg64(reg1);
			outs("\n");
			outs("fcvt s1,d1\n");
		}
		else
		{
			outs("scvtf s1,");
			out_reg64(reg1);
			outs("\n");
		}
	}
	if(class3==0&&op3->tab->class==9)
	{
		op_mem_ldst_float("ldr ",op3,2,9);
	}
	else if(class3==0&&op3->tab->class==10)
	{
		op_mem_ldst_float("ldr ",op3,2,10);
		outs("fcvt s2,d2\n");
	}
	else
	{
		if(class3==1)
		{
			reg2=op3->tab->reg+4;
		}
		else if(class3==0)
		{
			op_mem_ldst("ldr",op3,2);
		}
		else if(class3==2)
		{
			outs("mov64 x2,");
			op_out_const(9,op3);
			outs("\n");
		}
		else if(class3==3)
		{
			op_calculate_addr(op3,2);
		}
		if(class3==2||class3==3||op3->tab->class==9)
		{
			outs("fmov s2,");
			out_reg32(reg2);
			outs("\n");
		}
		else if(op3->tab->class==10)
		{
			outs("fmov d2,");
			out_reg64(reg2);
			outs("\n");
			outs("fcvt s2,d2\n");
		}
		else
		{
			outs("scvtf s2,");
			out_reg64(reg2);
			outs("\n");
		}
	}
	outs(fins);
	outs(" s0,s1,s2\n");
	if(class1==1)
	{
		outs("fmov ");
		out_reg32(op1->tab->reg+4);
		outs(",s0\n");
	}
	else
	{
		op_mem_ldst_float("str ",op1,0,9);
	}
}
void gen_basic_op(struct ins *ins,char *op)
{
	struct operand op1,op2,op3;
	int class1,class2,class3;
	int c;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	get_operand(ins,3,&op3);
	class1=0;
	class2=0;
	class3=0;
	if(op_is_reg(&op1))
	{
		class1=1;
	}
	else if(op_is_const(&op1))
	{
		class1=2;
	}
	else if(op_is_addr(&op1))
	{
		class1=3;
	}
	if(op_is_reg(&op2))
	{
		class2=1;
	}
	else if(op_is_const(&op2))
	{
		class2=2;
	}
	else if(op_is_addr(&op2))
	{
		class2=3;
	}
	if(op_is_reg(&op3))
	{
		class3=1;
	}
	else if(op_is_const(&op3))
	{
		class3=2;
	}
	else if(op_is_addr(&op3))
	{
		class3=3;
	}
	if(class1==2||class1==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op1.tab->class==9)
	{
		gen_hfloat_basic_op(class1,class2,class3,&op1,&op2,&op3,op);
		return;
	}
	if(op1.tab->class==10)
	{
		gen_float_basic_op(class1,class2,class3,&op1,&op2,&op3,op);
		return;
	}
	if(!strcmp(op,"sdiv")||!strcmp(op,"udiv")||!strcmp(op,"asr")||!strcmp(op,"lsr"))
	{
		if(class2==1)
		{
			reg_ext(op2.tab->reg+4,op2.tab->class,8);
		}
		if(class3==1)
		{
			reg_ext(op3.tab->reg+4,op3.tab->class,8);
		}
	}
	else
	{
		c=-1;
		if(class2==1||class2==0)
		{
			if(op2.tab->class>c)
			{
				c=op2.tab->class;
			}
		}
		if(class3==1||class3==0)
		{
			if(op3.tab->class>c)
			{
				c=op3.tab->class;
			}
		}
		if(op1.tab->class>c)
		{
			c=op1.tab->class;
		}
		if(c>8)
		{
			c=8;
		}
		if(class2==1)
		{
			reg_ext(op2.tab->reg+4,op2.tab->class,c);
		}
		if(class3==1)
		{
			reg_ext(op3.tab->reg+4,op3.tab->class,c);
		}
	}
	if(class1==1)
	{
		if(class2==1&&class3==1)
		{
			outs(op);
			outs(" ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",");
			out_reg64(op3.tab->reg+4);
			outs("\n");
			return;
		}
		if(class2==1&&class3==2)
		{
			if(!strcmp(op,"add")||!strcmp(op,"sub"))
			{
				if(op3.type==2&&op3.value<4096)
				{
					outs(op);
					outs(" ");
					out_reg64(op1.tab->reg+4);
					outs(",");
					out_reg64(op2.tab->reg+4);
					outs(",#");
					op_out_const(7,&op3);
					outs("\n");
					return;
				}
			}
			if(!strcmp(op,"lsl")||!strcmp(op,"lsr")||!strcmp(op,"asr"))
			{
				if(op3.type==2&&op3.value<64)
				{
					outs(op);
					outs(" ");
					out_reg64(op1.tab->reg+4);
					outs(",");
					out_reg64(op2.tab->reg+4);
					outs(",#");
					op_out_const(7,&op3);
					outs("\n");
					return;
				}
			}
			outs("mov64 x1,");
			op_out_const(7,&op3);
			outs("\n");
			outs(op);
			outs(" ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",x1\n");
			return;
		}
		if(class2==1&&class3==0)
		{
			op_mem_ldst("ldr",&op3,1);
			outs(op);
			outs(" ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",x1\n");
			return;
		}
		if(class2==2&&class3==1)
		{
			outs("mov64 x1,");
			op_out_const(7,&op2);
			outs("\n");
			outs(op);
			outs(" ");
			out_reg64(op1.tab->reg+4);
			outs(",x1,");
			out_reg64(op3.tab->reg+4);
			outs("\n");
			return;
		}
		if(class2==0&&class3==1)
		{
			op_mem_ldst("ldr",&op2,1);
			outs(op);
			outs(" ");
			out_reg64(op1.tab->reg+4);
			outs(",x1,");
			out_reg64(op3.tab->reg+4);
			outs("\n");
			return;
		}
	}
	else
	{
		if(class2==1&&class3==1)
		{
			outs(op);
			outs(" ");
			out_reg64(2);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",");
			out_reg64(op3.tab->reg+4);
			outs("\n");
			op_mem_ldst("str",&op1,2);
			return;
		}
		else if(class2==1&&class3==2)
		{
			if(!strcmp(op,"add")||!strcmp(op,"sub"))
			{
				if(op3.type==2&&op3.value<4096)
				{
					outs(op);
					outs(" ");
					out_reg64(2);
					outs(",");
					out_reg64(op2.tab->reg+4);
					outs(",#");
					op_out_const(7,&op3);
					outs("\n");
					op_mem_ldst("str",&op1,2);
					return;
				}
			}
			outs("mov64 x1,");
			op_out_const(7,&op3);
			outs("\n");
			outs(op);
			outs(" ");
			out_reg64(2);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",x1\n");
			op_mem_ldst("str",&op1,2);
			return;
		}
		else if(class2==1&&class3==0)
		{
			op_mem_ldst("ldr",&op3,1);
			outs(op);
			outs(" ");
			out_reg64(2);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",x1\n");
			op_mem_ldst("str",&op1,2);
			return;
		}
		else if(class2==2&&class3==1)
		{
			outs("mov64 x1,");
			op_out_const(7,&op2);
			outs("\n");
			outs(op);
			outs(" ");
			out_reg64(2);
			outs(",x1,");
			out_reg64(op3.tab->reg+4);
			outs("\n");
			op_mem_ldst("str",&op1,2);
			return;
		}
		else if(class2==0&&class3==1)
		{
			op_mem_ldst("ldr",&op2,1);
			outs(op);
			outs(" ");
			out_reg64(2);
			outs(",x1,");
			out_reg64(op3.tab->reg+4);
			outs("\n");
			op_mem_ldst("str",&op1,2);
			return;
		}
	}
	if(class2==1)
	{
		outs("mov x1,");
		out_reg64(op2.tab->reg+4);
		outs("\n");
	}
	else if(class2==0)
	{
		op_mem_ldst("ldr",&op2,1);
	}
	else if(class2==2)
	{
		outs("mov64 x1,");
		op_out_const(op1.tab->class,&op2);
		outs("\n");
	}
	else if(class2==3)
	{
		op_calculate_addr(&op2,1);
	}
	if(class3==1)
	{
		outs("mov x2,");
		out_reg64(op3.tab->reg+4);
		outs("\n");
	}
	else if(class3==0)
	{
		op_mem_ldst("ldr",&op3,2);
	}
	else if(class3==2)
	{
		outs("mov64 x2,");
		op_out_const(op1.tab->class,&op3);
		outs("\n");
	}
	else if(class3==3)
	{
		op_calculate_addr(&op3,2);
	}
	outs(op);
	outs(" x0,x1,x2\n");
	if(class1==1)
	{
		outs("mov ");
		out_reg64(op1.tab->reg+4);
		outs(",x0\n");
	}
	else
	{
		op_mem_ldst("str",&op1,0);
	}
}
