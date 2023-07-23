void gen_movc(struct ins *ins)
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
	if(class1==1)
	{
		if(class2==1)
		{
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			outs(ins->cond);
			outs("\n");
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(op1.tab->reg+4,op2.tab->class,op1.tab->class);
			}
		}
		else if(class2==0)
		{
			op_mem_ldst("ldr",&op2,0);
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(0,op2.tab->class,op1.tab->class);
			}
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			outs(ins->cond);
			outs("\n");
		}
		else if(class2==2)
		{
			outs("mov64 ");
			out_reg64(0);
			outs(",");
			op_out_const(op1.tab->class,&op2);
			outs("\n");
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			outs(ins->cond);
			outs("\n");
		}
		else if(class2==3)
		{
			op_calculate_addr(&op2,0);
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			outs(ins->cond);
			outs("\n");
		}
	}
	else if(class1==0)
	{
		if(class2==1)
		{
			op_mem_ldst("ldr",&op1,1);
			outs("csel x1,");
			out_reg64(op2.tab->reg+4);
			outs(",x1,");
			outs(ins->cond);
			outs("\n");
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(1,op2.tab->class,op1.tab->class);
			}
			op_mem_ldst("str",&op1,1);
		}
		else
		{
			op_mem_ldst("ldr",&op1,0);
			if(class2==0)
			{
				op_mem_ldst("ldr",&op2,1);
				if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
				{
					reg_ext(1,op2.tab->class,op1.tab->class);
				}
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
			outs("csel x0,");
			out_reg64(1);
			outs(",x0,");
			outs(ins->cond);
			outs("\n");
			op_mem_ldst("str",&op1,0);
		}
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
void gen_movnc(struct ins *ins)
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
	if(class1==1)
	{
		if(class2==1)
		{
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs(",");
			outs(ins->cond);
			outs("\n");
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(op1.tab->reg+4,op2.tab->class,op1.tab->class);
			}
		}
		else if(class2==0)
		{
			op_mem_ldst("ldr",&op2,0);
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(0,op2.tab->class,op1.tab->class);
			}
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs(",");
			outs(ins->cond);
			outs("\n");
		}
		else if(class2==2)
		{
			outs("mov64 ");
			out_reg64(0);
			outs(",");
			op_out_const(op1.tab->class,&op2);
			outs("\n");
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs(",");
			outs(ins->cond);
			outs("\n");
		}
		else if(class2==3)
		{
			op_calculate_addr(&op2,0);
			outs("csel ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(0);
			outs(",");
			outs(ins->cond);
			outs("\n");
		}
	}
	else if(class1==0)
	{
		if(class2==1)
		{
			op_mem_ldst("ldr",&op1,1);
			outs("csel x1,x1,");
			out_reg64(op2.tab->reg+4);
			outs(",");
			outs(ins->cond);
			outs("\n");
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(1,op2.tab->class,op1.tab->class);
			}
			op_mem_ldst("str",&op1,1);
		}
		else
		{
			op_mem_ldst("ldr",&op1,0);
			if(class2==0)
			{
				op_mem_ldst("ldr",&op2,1);
				if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
				{
					reg_ext(1,op2.tab->class,op1.tab->class);
				}
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
			outs("csel x0,x0,");
			out_reg64(1);
			outs(",");
			outs(ins->cond);
			outs("\n");
			op_mem_ldst("str",&op1,0);
		}
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
void gen_mov(struct ins *ins)
{
	struct operand op1,op2;
	int class1,class2;
	if(ins->bo==1)
	{
		gen_movnc(ins);
		return;
	}
	if(ins->bo==2)
	{
		gen_movc(ins);
		return;
	}
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
	if(!opcmp(&op1,&op2))
	{
		return;
	}
	if(class1==1)
	{
		if(class2==1)
		{
			outs("mov ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			out_reg64(op2.tab->reg+4);
			outs("\n");
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(op1.tab->reg+4,op2.tab->class,op1.tab->class);
			}
		}
		else if(class2==0)
		{
			op_mem_ldst("ldr",&op2,op1.tab->reg+4);
			if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
			{
				reg_ext(op1.tab->reg+4,op2.tab->class,op1.tab->class);
			}
		}
		else if(class2==2)
		{
			outs("mov64 ");
			out_reg64(op1.tab->reg+4);
			outs(",");
			op_out_const(op1.tab->class,&op2);
			outs("\n");
		}
		else if(class2==3)
		{
			op_calculate_addr(&op2,op1.tab->reg+4);
		}
	}
	else if(class1==0)
	{
		if(class2==1)
		{
			if(op2.tab->class==9&&op1.tab->class!=9)
			{
				outs("mov x1,");
				out_reg64(op2.tab->reg+4);
				outs("\n");
				if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
				{
					reg_ext(1,op2.tab->class,op1.tab->class);
				}
				op_mem_ldst("str",&op1,1);
				return;
			}
			if(op2.tab->class!=9&&op1.tab->class==9)
			{
				outs("mov x1,");
				out_reg64(op2.tab->reg+4);
				outs("\n");
				if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
				{
					reg_ext(1,op2.tab->class,op1.tab->class);
				}
				op_mem_ldst("str",&op1,1);
				return;
			}
			op_mem_ldst("str",&op1,op2.tab->reg+4);
		}
		else
		{
			if(class2==0)
			{
				op_mem_ldst("ldr",&op2,1);
				if((op1.tab->class==9||op2.tab->class==9||op1.tab->class==10||op2.tab->class==10)&&op1.tab->class!=op2.tab->class)
				{
					reg_ext(1,op2.tab->class,op1.tab->class);
				}
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
			op_mem_ldst("str",&op1,1);
		}
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
