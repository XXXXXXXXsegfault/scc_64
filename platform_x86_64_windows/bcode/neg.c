
void gen_neg(struct ins *ins)
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
	if((class1==0||class1==1)&&op1.tab->class==9)
	{	
		if(class2==3)
		{
			outs("lea ");
			op_out_mem(&op2);
			outs(",%ecx\n");
		}
		else if(class2==0)
		{
			outs("mov ");
			op_out_mem(&op2);
			outs(",");
			out_rcx(op2.tab->class);
			outs("\n");
			acd_extend(1,op1.tab->class,op2.tab->class);
		}
		else if(class2==1)
		{
			outs("mov ");
			op_out_reg(8,&op2);
			outs(",%rcx\n");
			acd_extend(1,op1.tab->class,op2.tab->class);
		}
		else
		{
			outs("mov ");
			op_out_const(9,&op2);
			outs(",%ecx\n");
		}
		outs("btc $31,%ecx\n");
		outs("mov %ecx,");
		if(class1==0)
		{
			op_out_mem(&op1);
		}
		else
		{
			op_out_reg(6,&op1);
		}
		outs("\n");
		return;
	}
	else if((class1==0||class1==1)&&op1.tab->class==10)
	{	
		if(class2==3)
		{
			outs("lea ");
			op_out_mem(&op2);
			outs(",%rcx\n");
		}
		else if(class2==0)
		{
			outs("mov ");
			op_out_mem(&op2);
			outs(",");
			out_rcx(op2.tab->class);
			outs("\n");
			acd_extend(1,op1.tab->class,op2.tab->class);
		}
		else if(class2==1)
		{
			outs("mov ");
			op_out_reg(8,&op2);
			outs(",%rcx\n");
			acd_extend(1,op1.tab->class,op2.tab->class);
		}
		else
		{
			outs("mov ");
			op_out_const(10,&op2);
			outs(",%rcx\n");
		}
		outs("btc $63,%rcx\n");
		outs("mov %rcx,");
		if(class1==0)
		{
			op_out_mem(&op1);
		}
		else
		{
			op_out_reg(8,&op1);
		}
		outs("\n");
		return;
	}
	if(class1==1)
	{
		if(class2==0)
		{
			outs("mov ");
			op_out_mem(&op2);
			outs(",");
			op_out_reg(op1.tab->class,&op1);
			outs("\n");
			outs("neg ");
			op_out_reg(op1.tab->class,&op1);
			outs("\n");
		}
		else if(class2==1)
		{
			outs("mov ");
			op_out_reg(op2.tab->class,&op2);
			outs(",");
			op_out_reg(op2.tab->class,&op1);
			outs("\n");
			reg_extend(op1.tab->class,op2.tab->class,&op1);
			outs("neg ");
			op_out_reg(op1.tab->class,&op1);
			outs("\n");
		}
		else if(class2==2)
		{
			outs("mov $");
			op_out_const(op1.tab->class,&op2);
			outs(",");
			op_out_reg(op1.tab->class,&op1);
			outs("\n");
			outs("neg ");
			op_out_reg(op1.tab->class,&op1);
			outs("\n");
		}
		else
		{
			outs("lea ");
			op_out_mem(&op2);
			outs(",");
			op_out_reg(8,&op1);
			outs("\n");
			outs("neg ");
			op_out_reg(8,&op1);
			outs("\n");
		}
	}
	else if(class1==0)
	{
		if(class2==0)
		{
			outs("mov ");
			op_out_mem(&op2);
			outs(",");
			out_rax(op2.tab->class);
			outs("\n");
			acd_extend(0,op1.tab->class,op2.tab->class);
			outs("neg ");
			out_rax(op1.tab->class);
			outs("\n");
			outs("mov ");
			out_rax(op1.tab->class);
			outs(",");
			op_out_mem(&op1);
			outs("\n");
		}
		else if(class2==1)
		{
			reg_extend(op1.tab->class,op2.tab->class,&op2);
			outs("mov ");
			op_out_reg(op2.tab->class,&op2);
			outs(",");
			out_rax(op2.tab->class);
			outs("\n");
			acd_extend(0,op1.tab->class,op2.tab->class);
			outs("neg ");
			out_rax(op1.tab->class);
			outs("\n");
			outs("mov ");
			out_rax(op1.tab->class);
			outs(",");
			op_out_mem(&op1);
			outs("\n");
		}
		else if(class2==2)
		{
			outs("mov $");
			op_out_const(op1.tab->class,&op2);
			outs(",");
			out_rax(op1.tab->class);
			outs("\n");
			outs("neg ");
			out_rax(op1.tab->class);
			outs("\n");
			outs("mov ");
			out_rax(op1.tab->class);
			outs(",");
			op_out_mem(&op1);
			outs("\n");
		}
		else
		{
			outs("lea ");
			op_out_mem(&op2);
			outs(",");
			out_rax(8);
			outs("\n");
			outs("neg ");
			out_rax(8);
			outs("\n");
			outs("mov ");
			out_rax(op1.tab->class);
			outs(",");
			op_out_mem(&op1);
			outs("\n");
		}
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
