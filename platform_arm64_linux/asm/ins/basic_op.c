int ins_write_shift(struct ins_args *args,int priv)
{
	unsigned int ins;
	if(args->reg1==63||args->reg2==63||args->imm>63)
	{
		return 1;
	}
	ins=(unsigned int)args->reg1|(unsigned int)args->reg2<<5;
	if(priv==0)
	{
		ins|=0xd3400000;
		ins|=(~args->imm&0x3f)<<10;
		ins|=(~args->imm+1&0x3f)<<16;
	}
	else if(priv==1)
	{
		ins|=0xd3400000;
		ins|=63<<10;
		ins|=args->imm<<16;
	}
	else if(priv==2)
	{
		ins|=0x93400000;
		ins|=63<<10;
		ins|=args->imm<<16;
	}
	swrite(&ins,4);
	return 0;
}
void ins_init_basic_op(void)
{
	ins_add("add X1,X2,X3","1 0 0 0 1 0 1 1 0 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("add X1,X2,X3","1 0 0 0 1 0 1 1 0 0 1 R3 0 1 1 0 0 0 RS2 RS1",0,0);
	ins_add("sub X1,X2,X3","1 1 0 0 1 0 1 1 0 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("sub X1,X2,X3","1 1 0 0 1 0 1 1 0 0 1 R3 0 1 1 0 0 0 RS2 RS1",0,0);
	ins_add("subs X1,X2,X3","1 1 1 0 1 0 1 1 0 0 0 R3 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("and X1,X2,X3","1 0 0 0 1 0 1 0 0 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("ands X1,X2,X3","1 1 1 0 1 0 1 0 0 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("orr X1,X2,X3","1 0 1 0 1 0 1 0 0 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("eor X1,X2,X3","1 1 0 0 1 0 1 0 0 0 0 R3 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("lsl X1,X2,X3","1 0 0 1 1 0 1 0 1 1 0 R3 0 0 1 0 0 0 R2 R1",0,0);
	ins_add("lsr X1,X2,X3","1 0 0 1 1 0 1 0 1 1 0 R3 0 0 1 0 0 1 R2 R1",0,0);
	ins_add("asr X1,X2,X3","1 0 0 1 1 0 1 0 1 1 0 R3 0 0 1 0 1 0 R2 R1",0,0);
	ins_add("mul X1,X2,X3","1 0 0 1 1 0 1 1 0 0 0 R3 0 1 1 1 1 1 R2 R1",0,0);
	ins_add("udiv X1,X2,X3","1 0 0 1 1 0 1 0 1 1 0 R3 0 0 0 0 1 0 R2 R1",0,0);
	ins_add("sdiv X1,X2,X3","1 0 0 1 1 0 1 0 1 1 0 R3 0 0 0 0 1 1 R2 R1",0,0);
	ins_add("lsl X1,X2,#I",0,ins_write_shift,0);
	ins_add("lsr X1,X2,#I",0,ins_write_shift,1);
	ins_add("asr X1,X2,#I",0,ins_write_shift,2);

	ins_add("add X1,X2,#I","1 0 0 1 0 0 0 1 0 0 I12 RS2 RS1",0,0);
	ins_add("sub X1,X2,#I","1 1 0 1 0 0 0 1 0 0 I12 RS2 RS1",0,0);
	ins_add("adds X1,X2,#I","1 0 1 1 0 0 0 1 0 0 I12 RS2 R1",0,0);
	ins_add("subs X1,X2,#I","1 1 1 1 0 0 0 1 0 0 I12 RS2 R1",0,0);

	ins_add("subs W1,W2,W3","0 1 1 0 1 0 1 1 0 0 0 R3 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("adds W1,W2,#I","0 0 1 1 0 0 0 1 0 0 I12 RS2 R1",0,0);
	ins_add("subs W1,W2,#I","0 1 1 1 0 0 0 1 0 0 I12 RS2 R1",0,0);
}
