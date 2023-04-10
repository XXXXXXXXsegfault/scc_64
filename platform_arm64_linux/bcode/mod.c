void gen_mod(struct ins *ins)
{
	struct operand op1,op2,op3;
	int class1,class2,class3;
	int sign;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	get_operand(ins,3,&op3);
	class1=0;
	class2=0;
	class3=0;
	sign=1;
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
		if(!if_class_signed(op2.tab->class))
		{
			sign=0;
		}
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
	else if(!if_class_signed(op2.tab->class))
	{
		sign=0;
	}
	if(op_is_reg(&op3))
	{
		if(!if_class_signed(op3.tab->class))
		{
			sign=0;
		}
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
	else if(!if_class_signed(op2.tab->class))
	{
		sign=0;
	}
	if(class1==2||class1==3)
	{
		error(ins->line,"invalid op.");
	}
	if(class2==1)
	{
		reg_ext(op2.tab->reg+4,op2.tab->class,8);
	}
	if(class3==1)
	{
		reg_ext(op3.tab->reg+4,op3.tab->class,8);
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
		op_out_const(7,&op2);
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
		op_out_const(7,&op3);
		outs("\n");
	}
	else if(class3==3)
	{
		op_calculate_addr(&op3,2);
	}
	if(sign)
	{
		outs("sdiv x0,x1,x2\n");
	}
	else
	{
		outs("udiv x0,x1,x2\n");
	}
	outs("mul x0,x0,x2\nsub x0,x1,x0\n");
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
