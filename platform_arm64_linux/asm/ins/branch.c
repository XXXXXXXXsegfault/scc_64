int ins_write_branch(struct ins_args *args,long priv)
{
	long addr_rel;
	unsigned int ins,op;
	addr_rel=args->imm-pc;
	if(addr_rel&3)
	{
		return 1;
	}
	if(addr_rel>0x7fffffc&&addr_rel<0xfffffffff8000000)
	{
		if(stage)
		{
			return 1;
		}
		ins=0xffffffff;
		swrite(&ins,4);
		return 0;
	}
	if(priv==0)
	{
		op=0x14000000;
	}
	else if(priv==1)
	{
		op=0x94000000;
	}
	ins=(addr_rel&0xfffffff)>>2|op;
	swrite(&ins,4);
	return 0;
}
int ins_write_branch_cond(struct ins_args *args,long priv)
{
	long addr_rel;
	unsigned int ins;
	addr_rel=args->imm-pc;
	if(addr_rel&3)
	{
		return 1;
	}
	if(addr_rel>0xffffc&&addr_rel<0xfffffffffff00000)
	{
		if(stage)
		{
			return 1;
		}
		ins=0xffffffff;
		swrite(&ins,4);
		return 0;
	}
	ins=(addr_rel&0x1fffff)<<3|0x54000000|priv;
	swrite(&ins,4);
	return 0;
}
void ins_init_branch(void)
{
	ins_add("b I",0,ins_write_branch,0);
	ins_add("beq I",0,ins_write_branch_cond,0);
	ins_add("bne I",0,ins_write_branch_cond,1);
	ins_add("bcs I",0,ins_write_branch_cond,2);
	ins_add("bcc I",0,ins_write_branch_cond,3);
	ins_add("bmi I",0,ins_write_branch_cond,4);
	ins_add("bpl I",0,ins_write_branch_cond,5);
	ins_add("bvs I",0,ins_write_branch_cond,6);
	ins_add("bvc I",0,ins_write_branch_cond,7);
	ins_add("bhi I",0,ins_write_branch_cond,8);
	ins_add("bls I",0,ins_write_branch_cond,9);
	ins_add("bge I",0,ins_write_branch_cond,10);
	ins_add("blt I",0,ins_write_branch_cond,11);
	ins_add("bgt I",0,ins_write_branch_cond,12);
	ins_add("ble I",0,ins_write_branch_cond,13);
	ins_add("bl I",0,ins_write_branch,1);
	ins_add("br X1","1 1 0 1 0 1 1 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 R1 0 0 0 0 0",0,0);
	ins_add("blr X1","1 1 0 1 0 1 1 0 0 0 1 1 1 1 1 1 0 0 0 0 0 0 R1 0 0 0 0 0",0,0);
	ins_add("csel X1,X2,X3,eq","1 0 0 1 1 0 1 0 1 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,ne","1 0 0 1 1 0 1 0 1 0 0 R3 0 0 0 1 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,cs","1 0 0 1 1 0 1 0 1 0 0 R3 0 0 1 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,cc","1 0 0 1 1 0 1 0 1 0 0 R3 0 0 1 1 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,mi","1 0 0 1 1 0 1 0 1 0 0 R3 0 1 0 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,pl","1 0 0 1 1 0 1 0 1 0 0 R3 0 1 0 1 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,vs","1 0 0 1 1 0 1 0 1 0 0 R3 0 1 1 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,vc","1 0 0 1 1 0 1 0 1 0 0 R3 0 1 1 1 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,hi","1 0 0 1 1 0 1 0 1 0 0 R3 1 0 0 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,ls","1 0 0 1 1 0 1 0 1 0 0 R3 1 0 0 1 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,ge","1 0 0 1 1 0 1 0 1 0 0 R3 1 0 1 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,lt","1 0 0 1 1 0 1 0 1 0 0 R3 1 0 1 1 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,gt","1 0 0 1 1 0 1 0 1 0 0 R3 1 1 0 0 0 0 R2 R1",0,0);
	ins_add("csel X1,X2,X3,le","1 0 0 1 1 0 1 0 1 0 0 R3 1 1 0 1 0 0 R2 R1",0,0);
	ins_add("ret","1 1 0 1 0 1 1 0 0 1 0 1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0",0,0);
}
