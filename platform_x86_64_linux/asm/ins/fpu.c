void ins_init_fpu(void)
{
	ins_add("fldl ADDR",0,"\xdd",1,0,0,I_MEM,0);
	ins_add("fstpl ADDR",0,"\xdd",1,0,0x18,I_MEM,0);
	ins_add("flds ADDR",0,"\xd9",1,0,0,I_MEM,0);
	ins_add("fstps ADDR",0,"\xd9",1,0,0x18,I_MEM,0);
	ins_add("fildq ADDR",0,"\xdf",1,0,0x28,I_MEM,0);
	ins_add("fistpq ADDR",0,"\xdf",1,0,0x38,I_MEM,0);
	ins_add("faddp",0,"\xde\xc1",2,0,0,0,0);
	ins_add("fsubp",0,"\xde\xe1",2,0,0,0,0);
	ins_add("fsubrp",0,"\xde\xe9",2,0,0,0,0);
	ins_add("fmulp",0,"\xde\xc9",2,0,0,0,0);
	ins_add("fdivp",0,"\xde\xf1",2,0,0,0,0);
	ins_add("fdivrp",0,"\xde\xf9",2,0,0,0,0);
	ins_add("fcomip",0,"\xdf\xf1",2,0,0,0,0);
	ins_add("fchs",0,"\xd9\xe0",2,0,0,0,0);
}
