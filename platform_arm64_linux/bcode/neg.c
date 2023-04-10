
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
	if(class1!=2&&class1!=3&&(op1.tab->class==9||class2!=2&&class2!=3&&op2.tab->class==9))
	{
		if(class2==1)
		{
			outs("mov ");
			out_reg64(0);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs("\n");
		}
		else if(class2==0)
		{
			op_mem_ldst("ldr",&op2,0);
		}
		else if(class2==2)
		{
			outs("mov64 ");
			out_reg64(0);
			outs(",");
			op_out_const(op1.tab->class,&op2);
			outs("\n");
		}
		else if(class2==3)
		{
			op_calculate_addr(&op2,0);
		}
		if(class2==2||class2==3||op2.tab->class!=9)
		{
			outs("scvtf d0,x0\n");
		}
		else
		{
			outs("fmov d0,x0\n");
		}
		outs("fneg d0,d0\n");
		if(op1.tab->class!=9)
		{
			outs("fcvtns x0,d0\n");
		}
		else
		{
			outs("fmov x0,d0\n");
		}
		if(class1==1)
		{
			outs("mov ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs("\n");
		}
		else
		{
			op_mem_ldst("str",&op1,0);
		}
		return;
	}
	if(class1==1)
	{
		if(class2==1)
		{
			outs("mvn ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs("\n");
			outs("add ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",#1\n");

		}
		else
		{	
			if(class2==0)
			{
				op_mem_ldst("ldr",&op2,0);
			}
			else if(class2==2)
			{
				outs("mov64 ");
				out_reg64(0);
				outs(",");
				op_out_const(op1.tab->class,&op2);
				outs("\n");
			}
			else if(class2==3)
			{
				op_calculate_addr(&op2,0);
			}
			outs("mvn ");
			out_reg64(op1.tab->reg+4);
			outs(",x0\n");
			outs("add ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",#1\n");
		}
	}
	else if(class1==0)
	{
		if(class2==1)
		{
			outs("mvn ");
			out_reg64(0);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs("\n");
			outs("add x0,x0,#1");
			op_mem_ldst("str",&op1,0);
		}
		else
		{
			if(class2==0)
			{
				op_mem_ldst("ldr",&op2,1);
			}
			else if(class2==2)
			{
				outs("mov64 ");
				out_reg64(1);
				outs(",");
				op_out_const(op1.tab->class,&op2);
				outs("\n");
			}
			else if(class2==3)
			{
				op_calculate_addr(&op2,1);
			}
			outs("mvn x1,x1\n");
			outs("add x1,x1,#1");
			op_mem_ldst("str",&op1,1);
		}
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
