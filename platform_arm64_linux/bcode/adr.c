
void gen_adr(struct ins *ins)
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
	if(class2==1||class2==2)
	{
		error(ins->line,"invalid op.");
	}
	if(class1==1)
	{
		op_calculate_addr(&op2,op1.tab->reg+4);
	}
	else if(class1==0)
	{
		op_calculate_addr(&op2,0);
		op_mem_ldst("str",&op1,0);
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
void gen_adro(struct ins *ins)
{
	struct operand op1,op2,op3;
	int class1,class2;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	get_operand(ins,3,&op3);
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
	if(class2==1||class2==2||op3.type!=2)
	{
		error(ins->line,"invalid op.");
	}
	if(class1==1)
	{
		op_calculate_addr_off(&op2,op1.tab->reg+4,&op3);
	}
	else if(class1==0)
	{
		op_calculate_addr_off(&op2,0,&op3);
		op_mem_ldst("str",&op1,0);
	}
	else
	{
		error(ins->line,"invalid op.");
	}
}
