void ins_init_float(void)
{
	ins_add("fmov F1,X2","1 0 0 1 1 1 1 0 0 1 1 0 0 1 1 1 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("fmov X1,F2","1 0 0 1 1 1 1 0 0 1 1 0 0 1 1 0 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("fmov H1,W2","0 0 0 1 1 1 1 0 0 0 1 0 0 1 1 1 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("fmov W1,H2","0 0 0 1 1 1 1 0 0 0 1 0 0 1 1 0 0 0 0 0 0 0 R2 R1",0,0);

	ins_add("fadd F1,F2,F3","0 0 0 1 1 1 1 0 0 1 1 R3 0 0 1 0 1 0 R2 R1",0,0);
	ins_add("fsub F1,F2,F3","0 0 0 1 1 1 1 0 0 1 1 R3 0 0 1 1 1 0 R2 R1",0,0);
	ins_add("fmul F1,F2,F3","0 0 0 1 1 1 1 0 0 1 1 R3 0 0 0 0 1 0 R2 R1",0,0);
	ins_add("fdiv F1,F2,F3","0 0 0 1 1 1 1 0 0 1 1 R3 0 0 0 1 1 0 R2 R1",0,0);
	ins_add("fneg F1,F2","0 0 0 1 1 1 1 0 0 1 1 0 0 0 0 1 0 1 0 0 0 0 R2 R1",0,0);

	ins_add("fadd H1,H2,H3","0 0 0 1 1 1 1 0 0 0 1 R3 0 0 1 0 1 0 R2 R1",0,0);
	ins_add("fsub H1,H2,H3","0 0 0 1 1 1 1 0 0 0 1 R3 0 0 1 1 1 0 R2 R1",0,0);
	ins_add("fmul H1,H2,H3","0 0 0 1 1 1 1 0 0 0 1 R3 0 0 0 0 1 0 R2 R1",0,0);
	ins_add("fdiv H1,H2,H3","0 0 0 1 1 1 1 0 0 0 1 R3 0 0 0 1 1 0 R2 R1",0,0);
	ins_add("fneg H1,H2","0 0 0 1 1 1 1 0 0 0 1 0 0 0 0 1 0 1 0 0 0 0 R2 R1",0,0);

	ins_add("scvtf F1,X2","1 0 0 1 1 1 1 0 0 1 1 0 0 0 1 0 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("fcvtns X1,F2","1 0 0 1 1 1 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 R2 R1",0,0);

	ins_add("scvtf H1,X2","1 0 0 1 1 1 1 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 R2 R1",0,0);
	ins_add("fcvtns X1,H2","1 0 0 1 1 1 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 R2 R1",0,0);

	ins_add("fcmp F1,F2","0 0 0 1 1 1 1 0 0 1 1 R2 0 0 1 0 0 0 R1 0 0 0 0 0",0,0);
	ins_add("fcmp H1,H2","0 0 0 1 1 1 1 0 0 0 1 R2 0 0 1 0 0 0 R1 0 0 0 0 0",0,0);

	ins_add("fcvt F1,H2","0 0 0 1 1 1 1 0 0 0 1 0 0 0 1 0 1 1 0 0 0 0 R2 R1",0,0);
	ins_add("fcvt H1,F2","0 0 0 1 1 1 1 0 0 1 1 0 0 0 1 0 0 1 0 0 0 0 R2 R1",0,0);

	ins_add("ldr Q1,[X2]","0 0 1 1 1 1 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("str Q1,[X2]","0 0 1 1 1 1 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldr Q1,[X2],#I","0 0 1 1 1 1 0 0 1 1 0 #Is9 0 1 RS2 R1",0,0);
	ins_add("str Q1,[X2],#I","0 0 1 1 1 1 0 0 1 0 0 #Is9 0 1 RS2 R1",0,0);
	ins_add("ldr Q1,[X2,#I]","0 0 1 1 1 1 0 0 1 1 0 #Is9 0 0 RS2 R1",0,0);
	ins_add("str Q1,[X2,#I]","0 0 1 1 1 1 0 0 1 0 0 #Is9 0 0 RS2 R1",0,0);
	ins_add("ldr Q1,[X2,#I]!","0 0 1 1 1 1 0 0 1 1 0 #Is9 1 1 RS2 R1",0,0);
	ins_add("str Q1,[X2,#I]!","0 0 1 1 1 1 0 0 1 0 0 #Is9 1 1 RS2 R1",0,0);
	ins_add("ldr Q1,[X2,X3]","0 0 1 1 1 1 0 0 1 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("str Q1,[X2,X3]","0 0 1 1 1 1 0 0 1 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);

	ins_add("ldr F1,[X2]","1 1 1 1 1 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("str F1,[X2]","1 1 1 1 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldr F1,[X2],#I","1 1 1 1 1 1 0 0 0 1 0 #Is9 0 1 RS2 R1",0,0);
	ins_add("str F1,[X2],#I","1 1 1 1 1 1 0 0 0 0 0 #Is9 0 1 RS2 R1",0,0);
	ins_add("ldr F1,[X2,#I]","1 1 1 1 1 1 0 0 0 1 0 #Is9 0 0 RS2 R1",0,0);
	ins_add("str F1,[X2,#I]","1 1 1 1 1 1 0 0 0 0 0 #Is9 0 0 RS2 R1",0,0);
	ins_add("ldr F1,[X2,#I]!","1 1 1 1 1 1 0 0 0 1 0 #Is9 1 1 RS2 R1",0,0);
	ins_add("str F1,[X2,#I]!","1 1 1 1 1 1 0 0 0 0 0 #Is9 1 1 RS2 R1",0,0);
	ins_add("ldr F1,[X2,X3]","1 1 1 1 1 1 0 0 0 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("str F1,[X2,X3]","1 1 1 1 1 1 0 0 0 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);

	ins_add("ldr H1,[X2]","1 0 1 1 1 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("str H1,[X2]","1 0 1 1 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldr H1,[X2],#I","1 0 1 1 1 1 0 0 0 1 0 #Is9 0 1 RS2 R1",0,0);
	ins_add("str H1,[X2],#I","1 0 1 1 1 1 0 0 0 0 0 #Is9 0 1 RS2 R1",0,0);
	ins_add("ldr H1,[X2,#I]","1 0 1 1 1 1 0 0 0 1 0 #Is9 0 0 RS2 R1",0,0);
	ins_add("str H1,[X2,#I]","1 0 1 1 1 1 0 0 0 0 0 #Is9 0 0 RS2 R1",0,0);
	ins_add("ldr H1,[X2,#I]!","1 0 1 1 1 1 0 0 0 1 0 #Is9 1 1 RS2 R1",0,0);
	ins_add("str H1,[X2,#I]!","1 0 1 1 1 1 0 0 0 0 0 #Is9 1 1 RS2 R1",0,0);
	ins_add("ldr H1,[X2,X3]","1 0 1 1 1 1 0 0 0 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("str H1,[X2,X3]","1 0 1 1 1 1 0 0 0 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);

	ins_add("ldp Q1,Q2,[X3]","1 0 1 0 1 1 0 1 0 1 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("stp Q1,Q2,[X3]","1 0 1 0 1 1 0 1 0 0 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("ldp Q1,Q2,[X3],#I","1 0 1 0 1 1 0 0 1 1 Is7m16 R2 RS3 R1",0,0);
	ins_add("stp Q1,Q2,[X3],#I","1 0 1 0 1 1 0 0 1 0 Is7m16 R2 RS3 R1",0,0);
	ins_add("ldp Q1,Q2,[X3,#I]","1 0 1 0 1 1 0 1 0 1 Is7m16 R2 RS3 R1",0,0);
	ins_add("stp Q1,Q2,[X3,#I]","1 0 1 0 1 1 0 1 0 0 Is7m16 R2 RS3 R1",0,0);
	ins_add("ldp Q1,Q2,[X3,#I]!","1 0 1 0 1 1 0 1 1 1 Is7m16 R2 RS3 R1",0,0);
	ins_add("stp Q1,Q2,[X3,#I]!","1 0 1 0 1 1 0 1 1 0 Is7m16 R2 RS3 R1",0,0);

	ins_add("ldp F1,F2,[X3]","0 1 1 0 1 1 0 1 0 1 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("stp F1,F2,[X3]","0 1 1 0 1 1 0 1 0 0 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("ldp F1,F2,[X3],#I","0 1 1 0 1 1 0 0 1 1 Is7m8 R2 RS3 R1",0,0);
	ins_add("stp F1,F2,[X3],#I","0 1 1 0 1 1 0 0 1 0 Is7m8 R2 RS3 R1",0,0);
	ins_add("ldp F1,F2,[X3,#I]","0 1 1 0 1 1 0 1 0 1 Is7m8 R2 RS3 R1",0,0);
	ins_add("stp F1,F2,[X3,#I]","0 1 1 0 1 1 0 1 0 0 Is7m8 R2 RS3 R1",0,0);
	ins_add("ldp F1,F2,[X3,#I]!","0 1 1 0 1 1 0 1 1 1 Is7m8 R2 RS3 R1",0,0);
	ins_add("stp F1,F2,[X3,#I]!","0 1 1 0 1 1 0 1 1 0 Is7m8 R2 RS3 R1",0,0);

	ins_add("ldp H1,H2,[X3]","0 0 1 0 1 1 0 1 0 1 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("stp H1,H2,[X3]","0 0 1 0 1 1 0 1 0 0 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("ldp H1,H2,[X3],#I","0 0 1 0 1 1 0 0 1 1 Is7m4 R2 RS3 R1",0,0);
	ins_add("stp H1,H2,[X3],#I","0 0 1 0 1 1 0 0 1 0 Is7m4 R2 RS3 R1",0,0);
	ins_add("ldp H1,H2,[X3,#I]","0 0 1 0 1 1 0 1 0 1 Is7m4 R2 RS3 R1",0,0);
	ins_add("stp H1,H2,[X3,#I]","0 0 1 0 1 1 0 1 0 0 Is7m4 R2 RS3 R1",0,0);
	ins_add("ldp H1,H2,[X3,#I]!","0 0 1 0 1 1 0 1 1 1 Is7m4 R2 RS3 R1",0,0);
	ins_add("stp H1,H2,[X3,#I]!","0 0 1 0 1 1 0 1 1 0 Is7m4 R2 RS3 R1",0,0);
}
