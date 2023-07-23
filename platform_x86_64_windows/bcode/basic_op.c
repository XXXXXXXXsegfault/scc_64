void gen_hfloat_basic_op(int class1,int class2,int class3,struct operand *op1,struct operand *op2,struct operand *op3,char *ins)
{
	if(class2==1&&class3==1)
	{
		if(op2->tab->class==9&&op3->tab->class==9)
		{
			outs("movd ");
			op_out_reg(6,op2);
			outs(",%xmm0\nmovd ");
			op_out_reg(6,op3);
			outs(",%xmm1\n");
			outs(ins);
			outs("%xmm1,%xmm0\n");
			if(class1==0)
			{
				outs("movss %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movd %xmm0,");
				op_out_reg(6,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==0&&class3==1)
	{
		if(op2->tab->class==9&&op3->tab->class==9)
		{
			outs("movss ");
			op_out_mem(op2);
			outs(",%xmm0\nmovd ");
			op_out_reg(6,op3);
			outs(",%xmm1\n");
			outs(ins);
			outs("%xmm1,%xmm0\n");
			if(class1==0)
			{
				outs("movss %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movd %xmm0,");
				op_out_reg(6,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==1&&class3==0)
	{
		if(op2->tab->class==9&&op3->tab->class==9)
		{
			outs("movd ");
			op_out_reg(6,op2);
			outs(",%xmm0\n");
			outs(ins);
			op_out_mem(op3);
			outs(",%xmm0\n");
			if(class1==0)
			{
				outs("movss %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movd %xmm0,");
				op_out_reg(6,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==0&&class3==0)
	{
		if(op2->tab->class==9&&op3->tab->class==9)
		{
			outs("movss ");
			op_out_mem(op2);
			outs(",%xmm0\n");
			outs(ins);
			op_out_mem(op3);
			outs(",%xmm0\n");
			if(class1==0)
			{
				outs("movss %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movd %xmm0,");
				op_out_reg(6,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==3)
	{
		outs("lea ");
		op_out_mem(op2);
		outs(",%rax\n");
	}
	else if(class2==0)
	{
		outs("mov ");
		op_out_mem(op2);
		outs(",");
		out_rax(op2->tab->class);
		outs("\n");
		acd_extend(0,op1->tab->class,op2->tab->class);
	}
	else if(class2==1)
	{
		outs("mov ");
		op_out_reg(8,op2);
		outs(",%rax\n");
		acd_extend(0,op1->tab->class,op2->tab->class);
	}
	else
	{
		outs("mov ");
		op_out_const(9,op2);
		outs(",%eax\n");
	}
	if(class3==3)
	{
		outs("lea ");
		op_out_mem(op3);
		outs(",%rcx\n");
	}
	else if(class3==0)
	{
		outs("mov ");
		op_out_mem(op3);
		outs(",");
		out_rcx(op3->tab->class);
		outs("\n");
		acd_extend(1,op1->tab->class,op3->tab->class);
	}
	else if(class3==1)
	{
		outs("mov ");
		op_out_reg(8,op3);
		outs(",%rcx\n");
		acd_extend(1,op1->tab->class,op3->tab->class);
	}
	else
	{
		outs("mov $");
		op_out_const(9,op3);
		outs(",%eax\n");
	}
	outs("movd %eax,%xmm0\n");
	outs("movd %ecx,%xmm1\n");
	outs(ins);
	outs("%xmm1,%xmm0\n");
	if(class1==0)
	{
		outs("movss %xmm0,");
		op_out_mem(op1);
	}
	else
	{
		outs("movd %xmm0,");
		op_out_reg(6,op1);
	}
	outs("\n");
}
void gen_float_basic_op(int class1,int class2,int class3,struct operand *op1,struct operand *op2,struct operand *op3,char *ins)
{
	if(class2==1&&class3==1)
	{
		if(op2->tab->class==10&&op3->tab->class==10)
		{
			outs("movq ");
			op_out_reg(8,op2);
			outs(",%xmm0\nmovq ");
			op_out_reg(8,op3);
			outs(",%xmm1\n");
			outs(ins);
			outs("%xmm1,%xmm0\n");
			if(class1==0)
			{
				outs("movsd %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movq %xmm0,");
				op_out_reg(8,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==0&&class3==1)
	{
		if(op2->tab->class==10&&op3->tab->class==10)
		{
			outs("movsd ");
			op_out_mem(op2);
			outs(",%xmm0\nmovq ");
			op_out_reg(8,op3);
			outs(",%xmm1\n");
			outs(ins);
			outs("%xmm1,%xmm0\n");
			if(class1==0)
			{
				outs("movsd %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movq %xmm0,");
				op_out_reg(8,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==1&&class3==0)
	{
		if(op2->tab->class==10&&op3->tab->class==10)
		{
			outs("movq ");
			op_out_reg(8,op2);
			outs(",%xmm0\n");
			outs(ins);
			op_out_mem(op3);
			outs(",%xmm0\n");
			if(class1==0)
			{
				outs("movsd %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movq %xmm0,");
				op_out_reg(8,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==0&&class3==0)
	{
		if(op2->tab->class==10&&op3->tab->class==10)
		{
			outs("movsd ");
			op_out_mem(op2);
			outs(",%xmm0\n");
			outs(ins);
			op_out_mem(op3);
			outs(",%xmm0\n");
			if(class1==0)
			{
				outs("movsd %xmm0,");
				op_out_mem(op1);
			}
			else
			{
				outs("movq %xmm0,");
				op_out_reg(8,op1);
			}
			outs("\n");
			return;
		}
	}
	if(class2==3)
	{
		outs("lea ");
		op_out_mem(op2);
		outs(",%rax\n");
	}
	else if(class2==0)
	{
		outs("mov ");
		op_out_mem(op2);
		outs(",");
		out_rax(op2->tab->class);
		outs("\n");
		acd_extend(0,op1->tab->class,op2->tab->class);
	}
	else if(class2==1)
	{
		outs("mov ");
		op_out_reg(8,op2);
		outs(",%rax\n");
		acd_extend(0,op1->tab->class,op2->tab->class);
	}
	else
	{
		outs("mov ");
		op_out_const(10,op2);
		outs(",%rax\n");
	}
	if(class3==3)
	{
		outs("lea ");
		op_out_mem(op3);
		outs(",%rcx\n");
	}
	else if(class3==0)
	{
		outs("mov ");
		op_out_mem(op3);
		outs(",");
		out_rcx(op3->tab->class);
		outs("\n");
		acd_extend(1,op1->tab->class,op3->tab->class);
	}
	else if(class3==1)
	{
		outs("mov ");
		op_out_reg(8,op3);
		outs(",%rcx\n");
		acd_extend(1,op1->tab->class,op3->tab->class);
	}
	else
	{
		outs("mov $");
		op_out_const(10,op3);
		outs(",%rax\n");
	}
	outs("movq %rax,%xmm0\n");
	outs("movq %rcx,%xmm1\n");
	outs(ins);
	outs("%xmm1,%xmm0\n");
	if(class1==0)
	{
		outs("movsd %xmm0,");
		op_out_mem(op1);
	}
	else
	{
		outs("movq %xmm0,");
		op_out_reg(8,op1);
	}
	outs("\n");
}
void gen_basic_op(struct ins *ins,char *op)
{
	struct operand op1,op2,op3;
	int class1,class2,class3;
	get_operand(ins,1,&op1);
	get_operand(ins,2,&op2);
	get_operand(ins,3,&op3);
	class1=0;
	class2=0;
	class3=0;
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
	if(op1.tab->class==10&&(!strcmp(op,"add")||!strcmp(op,"sub")))
	{
		if(!strcmp(op,"add"))
		{
			gen_float_basic_op(class1,class2,class3,&op1,&op2,&op3,"addsd ");
		}
		else
		{
			gen_float_basic_op(class1,class2,class3,&op1,&op2,&op3,"subsd ");
		}
		return;
	}
	if(op1.tab->class==9&&(!strcmp(op,"add")||!strcmp(op,"sub")))
	{
		if(!strcmp(op,"add"))
		{
			gen_hfloat_basic_op(class1,class2,class3,&op1,&op2,&op3,"addss ");
		}
		else
		{
			gen_hfloat_basic_op(class1,class2,class3,&op1,&op2,&op3,"subss ");
		}
		return;
	}
	if(class1==0)
	{
		if(!opcmp(&op1,&op2))
		{
			if(class3==1)
			{
				out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
				return;
			}
			if(class3==2&&op3.type==2&&(op1.tab->class<7||op3.value<0x7fffffff||op3.value>0xffffffff80000000))
			{
				if(op3.value==0&&strcmp(op,"and"))
				{
					return;
				}
				else
				{
					out_ins(op,get_len(op1.tab->class),0,&op3,&op1,0,op1.tab->class);
					return;
				}
			}
		}
		else if(class2==0)
		{
			if(class3==1)
			{
				out_ins_acd1("mov",0,0,&op2,0,op1.tab->class);
				out_ins_acd1(op,0,0,&op3,0,op1.tab->class);
				out_ins_acd2("mov",0,0,0,&op1,op1.tab->class);
				return;
			}
			else if(class3==2&&op3.type==2&&(op1.tab->class<7||op3.value<0x7fffffff||op3.value>0xffffffff80000000))
			{
				out_ins_acd1("mov",0,0,&op2,0,op1.tab->class);
				out_ins_acd1(op,0,0,&op3,0,op1.tab->class);
				out_ins_acd2("mov",0,0,0,&op1,op1.tab->class);
				return;
			}
		}
		else if(class2==1)
		{
			if(class3==1)
			{
				out_ins_acd1("mov",0,0,&op2,0,op1.tab->class);
				out_ins_acd1(op,0,0,&op3,0,op1.tab->class);
				out_ins_acd2("mov",0,0,0,&op1,op1.tab->class);
				return;
			}
			else if(class3==2&&op3.type==2&&(op1.tab->class<7||op3.value<0x7fffffff||op3.value>0xffffffff80000000))
			{
				out_ins_acd1("mov",0,0,&op2,0,op1.tab->class);
				out_ins_acd1(op,0,0,&op3,0,op1.tab->class);
				out_ins_acd2("mov",0,0,0,&op1,op1.tab->class);
				return;
			}
		}
	}
	if(class1==1)
	{
		if(class2==1)
		{
			if(class3==1)
			{
				if(!opcmp(&op1,&op2))
				{
					out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
					return;
				}
				else if(!opcmp(&op1,&op3))
				{
					out_ins_acd1("mov",0,0,&op2,0,op1.tab->class);
					out_ins_acd1(op,0,0,&op3,0,op1.tab->class);
					out_ins_acd2("mov",0,0,0,&op1,op1.tab->class);
					return;
				}
				else
				{
					if(!strcmp(op,"add"))
					{
						reg_extend(5,op2.tab->class,&op2);
						reg_extend(5,op3.tab->class,&op3);
						outs("lea (");
						op_out_reg(8,&op2);
						outs(",");
						op_out_reg(8,&op3);
						outs("),");
						if(op1.tab->class<5)
						{
							op_out_reg(5,&op1);
							outs("\n");
						}
						else
						{
							op_out_reg(op1.tab->class,&op1);
							outs("\n");
						}
						return;
					}
					out_ins("mov",0,0,&op2,&op1,0,op1.tab->class);
					out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
					return;
				}
			}
			else if(class3==2&&op3.type==2)
			{
				if(op1.tab->class<7||op3.value<0x7fffffff||op3.value>0xffffffff80000000)
				{
					if(op3.value==0&&strcmp(op,"and"))
					{
						if(opcmp(&op1,&op2))
						{
							out_ins("mov",0,0,&op2,&op1,0,op1.tab->class);
						}
						return;
					}
					else if(!opcmp(&op1,&op2))
					{
						out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
						return;
					}
					else
					{
						out_ins("mov",0,0,&op2,&op1,0,op1.tab->class);
						out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
						return;
					}
				}
			}
		}
		else if(class2==3)
		{
			if(class3==2&&op3.type==2)
			{
				if(op3.value<0x7fffffff||op3.value>0xffffffff80000000)
				{
					out_ins("lea",0,0,&op2,&op1,0,8);
					out_ins(op,0,0,&op3,&op1,0,8);
					return;
				}
			}
			else if(class3==1)
			{
				if(opcmp(&op1,&op3))
				{
					out_ins("lea",0,0,&op2,&op1,0,8);
					out_ins(op,0,0,&op3,&op1,0,8);
					return;
				}
			}
		}
		else if(class2==0&&!needs_convert(&op2,&op1))
		{
			if(class3==2&&op3.type==2)
			{
				if(op3.value<0x7fffffff||op3.value>0xffffffff80000000)
				{
					out_ins("mov",0,0,&op2,&op1,0,op1.tab->class);
					out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
					return;
				}
			}
			else if(class3==1&&opcmp(&op1,&op3))
			{
				out_ins("mov",0,0,&op2,&op1,0,op1.tab->class);
				out_ins(op,0,0,&op3,&op1,0,op1.tab->class);
				return;
			}
		}
	}
	if(class2==3)
	{
		out_ins_acd1("lea",0,0,&op2,0,8);
	}
	else
	{
		out_ins_acd1("mov",0,0,&op2,0,op1.tab->class);
	}
	if(class3==3)
	{
		out_ins_acd1("lea",0,0,&op3,1,8);
	}
	else
	{
		out_ins_acd1("mov",0,0,&op3,1,op1.tab->class);
	}
	out_ins_acd3(op,0,0,1,0,op1.tab->class);
	out_ins_acd2("mov",0,0,0,&op1,op1.tab->class);
}
