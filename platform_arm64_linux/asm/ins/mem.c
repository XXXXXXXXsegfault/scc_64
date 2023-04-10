void ins_init_mem(void)
{
	ins_add("ldr X1,[X2]","1 1 1 1 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("str X1,[X2]","1 1 1 1 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldr W1,[X2]","1 0 1 1 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("str W1,[X2]","1 0 1 1 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldrsw X1,[X2]","1 0 1 1 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldrh W1,[X2]","0 1 1 1 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("strh W1,[X2]","0 1 1 1 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldrsh X1,[X2]","0 1 1 1 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldrb W1,[X2]","0 0 1 1 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("strb W1,[X2]","0 0 1 1 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);
	ins_add("ldrsb X1,[X2]","0 0 1 1 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 RS2 R1",0,0);

	ins_add("ldr X1,[X2,X3]","1 1 1 1 1 0 0 0 0 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("str X1,[X2,X3]","1 1 1 1 1 0 0 0 0 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("ldr W1,[X2,X3]","1 0 1 1 1 0 0 0 0 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("str W1,[X2,X3]","1 0 1 1 1 0 0 0 0 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("ldrsw X1,[X2,X3]","1 0 1 1 1 0 0 0 1 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("ldrh W1,[X2,X3]","0 1 1 1 1 0 0 0 0 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("strh W1,[X2,X3]","0 1 1 1 1 0 0 0 0 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("ldrsh X1,[X2,X3]","0 1 1 1 1 0 0 0 1 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("ldrb W1,[X2,X3]","0 0 1 1 1 0 0 0 0 1 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("strb W1,[X2,X3]","0 0 1 1 1 0 0 0 0 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);
	ins_add("ldrsb X1,[X2,X3]","0 0 1 1 1 0 0 0 1 0 1 R3 0 1 1 0 1 0 RS2 R1",0,0);

	ins_add("ldr X1,[X2,#I]","1 1 1 1 1 0 0 0 0 1 0 Is9 0 0 RS2 R1",0,0);
	ins_add("str X1,[X2,#I]","1 1 1 1 1 0 0 0 0 0 0 Is9 0 0 RS2 R1",0,0);
	ins_add("ldr W1,[X2,#I]","1 0 1 1 1 0 0 0 0 1 0 Is9 0 0 RS2 R1",0,0);
	ins_add("str W1,[X2,#I]","1 0 1 1 1 0 0 0 0 0 0 Is9 0 0 RS2 R1",0,0);
	ins_add("ldrsw X1,[X2,#I]","1 0 1 1 1 0 0 0 1 0 0 Is9 0 0 RS2 R1",0,0);
	ins_add("ldrh W1,[X2,#I]","0 1 1 1 1 0 0 0 0 1 0 Is9 0 0 RS2 R1",0,0);
	ins_add("strh W1,[X2,#I]","0 1 1 1 1 0 0 0 0 0 0 Is9 0 0 RS2 R1",0,0);
	ins_add("ldrsh X1,[X2,#I]","0 1 1 1 1 0 0 0 1 0 0 Is9 0 0 RS2 R1",0,0);
	ins_add("ldrb W1,[X2,#I]","0 0 1 1 1 0 0 0 0 1 0 Is9 0 0 RS2 R1",0,0);
	ins_add("strb W1,[X2,#I]","0 0 1 1 1 0 0 0 0 0 0 Is9 0 0 RS2 R1",0,0);
	ins_add("ldrsb X1,[X2,#I]","0 0 1 1 1 0 0 0 1 0 0 Is9 0 0 RS2 R1",0,0);

	ins_add("ldr X1,[X2,#I]!","1 1 1 1 1 0 0 0 0 1 0 Is9 1 1 RS2 R1",0,0);
	ins_add("str X1,[X2,#I]!","1 1 1 1 1 0 0 0 0 0 0 Is9 1 1 RS2 R1",0,0);
	ins_add("ldr W1,[X2,#I]!","1 0 1 1 1 0 0 0 0 1 0 Is9 1 1 RS2 R1",0,0);
	ins_add("str W1,[X2,#I]!","1 0 1 1 1 0 0 0 0 0 0 Is9 1 1 RS2 R1",0,0);
	ins_add("ldrsw X1,[X2,#I]!","1 0 1 1 1 0 0 0 1 0 0 Is9 1 1 RS2 R1",0,0);
	ins_add("ldrh W1,[X2,#I]!","0 1 1 1 1 0 0 0 0 1 0 Is9 1 1 RS2 R1",0,0);
	ins_add("strh W1,[X2,#I]!","0 1 1 1 1 0 0 0 0 0 0 Is9 1 1 RS2 R1",0,0);
	ins_add("ldrsh X1,[X2,#I]!","0 1 1 1 1 0 0 0 1 0 0 Is9 1 1 RS2 R1",0,0);
	ins_add("ldrb W1,[X2,#I]!","0 0 1 1 1 0 0 0 0 1 0 Is9 1 1 RS2 R1",0,0);
	ins_add("strb W1,[X2,#I]!","0 0 1 1 1 0 0 0 0 0 0 Is9 1 1 RS2 R1",0,0);
	ins_add("ldrsb X1,[X2,#I]!","0 0 1 1 1 0 0 0 1 0 0 Is9 1 1 RS2 R1",0,0);

	ins_add("ldr X1,[X2],#I","1 1 1 1 1 0 0 0 0 1 0 Is9 0 1 RS2 R1",0,0);
	ins_add("str X1,[X2],#I","1 1 1 1 1 0 0 0 0 0 0 Is9 0 1 RS2 R1",0,0);
	ins_add("ldr W1,[X2],#I","1 0 1 1 1 0 0 0 0 1 0 Is9 0 1 RS2 R1",0,0);
	ins_add("str W1,[X2],#I","1 0 1 1 1 0 0 0 0 0 0 Is9 0 1 RS2 R1",0,0);
	ins_add("ldrsw X1,[X2],#I","1 0 1 1 1 0 0 0 1 0 0 Is9 0 1 RS2 R1",0,0);
	ins_add("ldrh W1,[X2],#I","0 1 1 1 1 0 0 0 0 1 0 Is9 0 1 RS2 R1",0,0);
	ins_add("strh W1,[X2],#I","0 1 1 1 1 0 0 0 0 0 0 Is9 0 1 RS2 R1",0,0);
	ins_add("ldrsh X1,[X2],#I","0 1 1 1 1 0 0 0 1 0 0 Is9 0 1 RS2 R1",0,0);
	ins_add("ldrb W1,[X2],#I","0 0 1 1 1 0 0 0 0 1 0 Is9 0 1 RS2 R1",0,0);
	ins_add("strb W1,[X2],#I","0 0 1 1 1 0 0 0 0 0 0 Is9 0 1 RS2 R1",0,0);
	ins_add("ldrsb X1,[X2],#I","0 0 1 1 1 0 0 0 1 0 0 Is9 0 1 RS2 R1",0,0);

	ins_add("ldp X1,X2,[X3]","1 0 1 0 1 0 0 1 0 1 0 0 0 0 0 0 0 R2 RS3 R1",0,0);
	ins_add("stp X1,X2,[X3]","1 0 1 0 1 0 0 1 0 0 0 0 0 0 0 0 0 R2 RS3 R1",0,0);

	ins_add("ldp X1,X2,[X3,#I]","1 0 1 0 1 0 0 1 0 1 Is7m8 R2 RS3 R1",0,0);
	ins_add("stp X1,X2,[X3,#I]","1 0 1 0 1 0 0 1 0 0 Is7m8 R2 RS3 R1",0,0);

	ins_add("ldp X1,X2,[X3,#I]!","1 0 1 0 1 0 0 1 1 1 Is7m8 R2 RS3 R1",0,0);
	ins_add("stp X1,X2,[X3,#I]!","1 0 1 0 1 0 0 1 1 0 Is7m8 R2 RS3 R1",0,0);

	ins_add("ldp X1,X2,[X3],#I","1 0 1 0 1 0 0 0 1 1 Is7m8 R2 RS3 R1",0,0);
	ins_add("stp X1,X2,[X3],#I","1 0 1 0 1 0 0 0 1 0 Is7m8 R2 RS3 R1",0,0);

	ins_add("ldxr W1,[X2]","1 0 0 0 1 0 0 0 0 1 0 1 1 1 1 1 0 1 1 1 1 1 RS2 R1",0,0);
	ins_add("stxr W1,W2,[X3]","1 0 0 0 1 0 0 0 0 0 0 R1 0 1 1 1 1 1 RS3 R2",0,0);
}
