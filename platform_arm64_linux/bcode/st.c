void gen_st(struct ins *ins,int c)
{
	struct operand op1,op2;
	int class1,class2;
	int op2_pos;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	class1=0;
	class2=0;
	op2_pos=1;
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
		op2_pos=0;
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
	if(class2==1)
	{
		outs("mov x1,");
		out_reg64(op2.tab->reg+4);
		outs("\n");
	}
	else if(class2==2)
	{
		outs("mov64 x1,");
		op_out_const(c,&op2);
		outs("\n");
	}
	else if(class2==0)
	{
		op_mem_ldst("ldr",&op2,1);
	}
	else
	{
		op_calculate_addr(&op2,1);
	}
	if(class1==1)
	{
		op_reg_st(op1.tab->reg+4,1,c);
	}
	else 
	{
		if(class1==0)
		{
			op_mem_ldst("ldr",&op1,0);
		}
		else if(class1==2)
		{
			outs("mov64 x0,");
			op_out_const(c,&op1);
			outs("\n");
		}
		else if(class1==3)
		{
			op_calculate_addr(&op1,0);
		}
		op_reg_st(0,1,c);
	}
	last_store_valid=0;
}
