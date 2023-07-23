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
		reg_extend(c,op2.tab->class,&op2);
	}
	else if(class2==2)
	{
		if(class1==1&&op2.type==2&&(c<7||op2.value<=0x7fffffff||op2.value>=0xffffffff80000000))
		{
			outs("mov");
			outs(get_len(c));
			outs(" $");
			op_out_const(c,&op2);
			outs(",(");
			op_out_reg(8,&op1);
			outs(")\n");
			last_store_valid=0;
			return;
		}
		outs("mov $");
		op_out_const(c,&op2);
		outs(",");
		out_rax(c);
		outs("\n");
	}
	else if(class2==0)
	{
		outs("mov ");
		op_out_mem(&op2);
		outs(",");
		out_rax(op2.tab->class);
		outs("\n");
		acd_extend(0,c,op2.tab->class);
	}
	else
	{
		outs("lea ");
		op_out_mem(&op2);
		outs(",");
		out_rax(8);
		outs("\n");
	}
	if(class1==1)
	{
		reg_extend(8,op1.tab->class,&op1);
		outs("mov ");
		if(op2_pos)
		{
			out_rax(c);
		}
		else
		{
			op_out_reg(c,&op2);
		}
		outs(",(");
		op_out_reg(8,&op1);
		outs(")\n");
	}
	else if(class1==3)
	{
		outs("mov ");
		if(op2_pos)
		{
			out_rax(c);
		}
		else
		{
			op_out_reg(c,&op2);
		}
		outs(",");
		op_out_mem(&op1);
		outs("\n");
	}
	else 
	{
		if(class1==0)
		{
			outs("mov ");
			op_out_mem(&op1);
			outs(",");
			out_rcx(op1.tab->class);
			outs("\n");
			acd_extend(1,8,op1.tab->class);
		}
		else if(class1==2)
		{
			outs("mov $");
			op_out_const(8,&op1);
			outs(",");
			out_rcx(8);
			outs("\n");
		}
		outs("mov ");
		if(op2_pos)
		{
			out_rax(c);
		}
		else
		{
			op_out_reg(c,&op2);
		}
		outs(",(%rcx)\n");
	}
	last_store_valid=0;
}
void gen_sto(struct ins *ins,int c)
{
	struct operand op1,op2,op3;
	int class1,class2;
	int op2_pos;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	get_operand(ins,3,&op3);
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
	if(op3.type!=2)
	{
		error(ins->line,"invalid op.");
	}
	if(class2==1)
	{
		reg_extend(c,op2.tab->class,&op2);
	}
	else if(class2==2)
	{
		if(class1==1&&op2.type==2&&(c<7||op2.value<=0x7fffffff||op2.value>=0xffffffff80000000))
		{
			outs("mov");
			outs(get_len(c));
			outs(" $");
			op_out_const(c,&op2);
			outs(",");
			op_out_const(8,&op3);
			outs("(");
			op_out_reg(8,&op1);
			outs(")\n");
			last_store_valid=0;
			return;
		}
		outs("mov $");
		op_out_const(c,&op2);
		outs(",");
		out_rax(c);
		outs("\n");
	}
	else if(class2==0)
	{
		outs("mov ");
		op_out_mem(&op2);
		outs(",");
		out_rax(op2.tab->class);
		outs("\n");
		acd_extend(0,c,op2.tab->class);
	}
	else
	{
		outs("lea ");
		op_out_mem(&op2);
		outs(",");
		out_rax(8);
		outs("\n");
	}
	if(class1==1)
	{
		reg_extend(8,op1.tab->class,&op1);
		outs("mov ");
		if(op2_pos)
		{
			out_rax(c);
		}
		else
		{
			op_out_reg(c,&op2);
		}
		outs(",");
		op_out_const(8,&op3);
		outs("(");
		op_out_reg(8,&op1);
		outs(")\n");
	}
	else if(class1==3)
	{
		outs("mov ");
		if(op2_pos)
		{
			out_rax(c);
		}
		else
		{
			op_out_reg(c,&op2);
		}
		outs(",");
		op_out_mem_off(&op1,&op3);
		outs("\n");
	}
	else 
	{
		if(class1==0)
		{
			outs("mov ");
			op_out_mem(&op1);
			outs(",");
			out_rcx(op1.tab->class);
			outs("\n");
			acd_extend(1,8,op1.tab->class);
		}
		else if(class1==2)
		{
			outs("mov $");
			op_out_const(8,&op1);
			outs(",");
			out_rcx(8);
			outs("\n");
		}
		outs("mov ");
		if(op2_pos)
		{
			out_rax(c);
		}
		else
		{
			op_out_reg(c,&op2);
		}
		outs(",");
		op_out_const(8,&op3);
		outs("(%rcx)\n");
	}
	last_store_valid=0;
}
