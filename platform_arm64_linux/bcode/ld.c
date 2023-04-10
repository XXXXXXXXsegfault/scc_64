void gen_ld(struct ins *ins,int c)
{
	struct operand op1,op2;
	int class1,class2;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	class1=0;
	class2=0;
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
	if(class1==2||class1==3||class2==3)
	{
		error(ins->line,"invalid op.");
	}
	if(class1==1)
	{
		if(class2==1)
		{
			op_reg_ld(op2.tab->reg+4,op1.tab->reg+4,c);
		}
		else
		{
			if(class2==2)
			{
				outs("mov64 ");
				out_reg64(1);
				outs(",");
				op_out_const(7,&op2);
				outs("\n");
			}
			else if(class2==0)
			{
				op_mem_ldst("ldr",&op2,1);
			}
			op_reg_ld(1,op1.tab->reg+4,c);
		}
	}
	else if(class1==0)
	{
		if(class2==1)
		{
			op_reg_ld(op2.tab->reg+4,0,c);
		}
		else
		{
			if(class2==2)
			{
				outs("mov64 ");
				out_reg64(1);
				outs(",");
				op_out_const(7,&op2);
				outs("\n");
			}
			else if(class2==0)
			{
				op_mem_ldst("ldr",&op2,1);
			}
			op_reg_ld(1,0,c);
		}
		op_mem_ldst("str",&op1,0);
	}
}
