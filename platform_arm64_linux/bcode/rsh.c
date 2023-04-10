void gen_rsh(struct ins *ins)
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
	if(sign)
	{
		gen_basic_op(ins,"asr");
	}
	else
	{
		gen_basic_op(ins,"lsr");
	}
}
