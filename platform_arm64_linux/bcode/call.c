void gen_push(struct ins *ins,int c)
{
	struct operand op1;
	int class1;
	get_operand(ins,1,&op1);
	class1=0;
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
	if(class1==1)
	{
		if(c<=8&&op1.tab->class<=8||op1.tab->class==c)
		{
			reg_ext(op1.tab->reg+4,op1.tab->class,c);
			outs("str ");
			out_reg64(op1.tab->reg+4);
			outs(",[sp,#-16]!\n");
			return;
		}
		else
		{
			outs("mov x0,");
			out_reg64(op1.tab->reg+4);
			outs("\n");
		}
	}
	else if(class1==0)
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
	if(class1!=2&&class1!=3)
	{
		reg_ext(0,op1.tab->class,c);
	}
	outs("str x0,[sp,#-16]!\n");
}
void gen_call(struct ins *ins,int if_float)
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
	if(class1==2||class1==3)
	{
		error(ins->line,"invalid op.");
	}
	if(class2==2)
	{
		outs("bl ");
		op_out_const(8,&op2);
		outs("\n");
	}
	else if(class2==1)
	{
		outs("blr ");
		out_reg64(op2.tab->reg+4);
		outs("\n");
	}
	else
	{
		if(class2==0)
		{
			op_mem_ldst("ldr",&op2,0);
		}
		else
		{
			op_calculate_addr(&op2,0);
		}
		outs("blr x0\n");
	}
	last_store_valid=0;
	if(op1.tab->unused)
	{
		return;
	}
	if(if_float==1)
	{
		reg_ext(0,9,op1.tab->class);
	}
	else if(if_float==2)
	{
		reg_ext(0,10,op1.tab->class);
	}
	else
	{
		reg_ext(0,8,op1.tab->class);
	}
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
void gen_retval(struct ins *ins,int c)
{
	struct operand op1;
	int class1;
	struct ins *p;
	get_operand(ins,1,&op1);
	class1=0;
	if(fun_name==0)
	{
		error(ins->line,"ret outside of function.");
	}
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
	if(class1==1)
	{
		outs("mov x0,");
		out_reg64(op1.tab->reg+4);
		outs("\n");
	}
	else if(class1==0)
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
	if(class1!=2&&class1!=3)
	{
		reg_ext(0,op1.tab->class,c);
	}
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
}
