int parse_num(char **str,unsigned long int *result)
{
	char *old_str,*word;
	int s;
	struct label *label;
	old_str=*str;
	*str=skip_spaces(*str);
	s=0;
	if(**str=='-')
	{
		++*str;
		s=1;
	}
	if(**str=='@')
	{
		//label
		++*str;
		word=read_word(str);
		if(!strcmp(word,"_$DATA"))
		{
			free(word);
			if(s)
			{
				*result=-data_addr;
			}
			else
			{
				*result=data_addr;
			}
			l->needs_recompile=1;
			return 0;
		}
		else
		{
			label=label_tab_find(word);
			if(stage)
			{
				if(label)
				{
					free(word);
					*result=label->value;
					if(s)
					{
						*result=-*result;
					}
					return 0;
				}
				error(l->line,"label undefined.");
			}
			else
			{
				l->needs_recompile=1;
			}
		}
		free(word);
		return -2;
	}
	else if(**str>='0'&&**str<='9'||**str=='\'')
	{
		*result=const_to_num(*str);
		word=read_word(str);
		free(word);
	}
	else
	{
		*str=old_str;
		return -1;
	}
	if(s)
	{
		*result=-*result;
	}
	return 0;
}
int parse_const(char **str,unsigned long int *result)
{
	unsigned long int num;
	int ret,s,s1;
	char *old_str;
	old_str=*str;
	s=0;
	s1=0;
	*result=0;
	while(1)
	{
		ret=parse_num(str,&num);
		if(ret==-1)
		{
			*str=old_str;
			return -1;
		}
		if(ret==-2)
		{
			s=1;
		}
		if(s1)
		{
			*result-=num;
		}
		else
		{
			*result+=num;
		}
		*str=skip_spaces(*str);
		if(**str=='+')
		{
			s1=0;
			++*str;
		}
		else if(**str=='-')
		{
			s1=1;
			++*str;
		}
		else
		{
			break;
		}
	}
	if(s)
	{
		*result=0;
	}
	return 0;
}
int str_match(char **pstr,char *str)
{
	int l;
	char *old_str;
	old_str=*pstr;
	l=strlen(str);
	*pstr=skip_spaces(*pstr);
	if(strncmp(*pstr,str,l))
	{
		*pstr=old_str;
		return 0;
	}
	*pstr+=l;
	return 1;
}
int str_match2(char **pstr,char *str,int l)
{
	char *old_str;
	old_str=*pstr;
	*pstr=skip_spaces(*pstr);
	if(strncmp(*pstr,str,l))
	{
		*pstr=old_str;
		return 0;
	}
	*pstr+=l;
	return 1;
}
int parse_reg32(char **str)
{
	if(str_match2(str,"eax",3))
	{
		return 0;
	}
	if(str_match2(str,"ecx",3))
	{
		return 1;
	}
	if(str_match2(str,"edx",3))
	{
		return 2;
	}
	if(str_match2(str,"ebx",3))
	{
		return 3;
	}
	if(str_match2(str,"esp",3))
	{
		return 4;
	}
	if(str_match2(str,"ebp",3))
	{
		return 5;
	}
	if(str_match2(str,"esi",3))
	{
		return 6;
	}
	if(str_match2(str,"edi",3))
	{
		return 7;
	}
	if(str_match2(str,"r8d",3))
	{
		return 8;
	}
	if(str_match2(str,"r9d",3))
	{
		return 9;
	}
	if(str_match2(str,"r10d",4))
	{
		return 10;
	}
	if(str_match2(str,"r11d",4))
	{
		return 11;
	}
	if(str_match2(str,"r12d",4))
	{
		return 12;
	}
	if(str_match2(str,"r13d",4))
	{
		return 13;
	}
	if(str_match2(str,"r14d",4))
	{
		return 14;
	}
	if(str_match2(str,"r15d",4))
	{
		return 15;
	}
	if(str_match2(str,"eiz",3))
	{
		return -2;
	}
	return -1;
}
int parse_reg16(char **str)
{
	if(str_match2(str,"ax",2))
	{
		return 0;
	}
	if(str_match2(str,"cx",2))
	{
		return 1;
	}
	if(str_match2(str,"dx",2))
	{
		return 2;
	}
	if(str_match2(str,"bx",2))
	{
		return 3;
	}
	if(str_match2(str,"sp",2))
	{
		return 4;
	}
	if(str_match2(str,"bp",2))
	{
		return 5;
	}
	if(str_match2(str,"si",2))
	{
		return 6;
	}
	if(str_match2(str,"di",2))
	{
		return 7;
	}
	if(str_match2(str,"r8w",3))
	{
		return 8;
	}
	if(str_match2(str,"r9w",3))
	{
		return 9;
	}
	if(str_match2(str,"r10w",4))
	{
		return 10;
	}
	if(str_match2(str,"r11w",4))
	{
		return 11;
	}
	if(str_match2(str,"r12w",4))
	{
		return 12;
	}
	if(str_match2(str,"r13w",4))
	{
		return 13;
	}
	if(str_match2(str,"r14w",4))
	{
		return 14;
	}
	if(str_match2(str,"r15w",4))
	{
		return 15;
	}
	return -1;
}
int parse_reg8(char **str)
{
	if(str_match2(str,"al",2))
	{
		return 0;
	}
	if(str_match2(str,"cl",2))
	{
		return 1;
	}
	if(str_match2(str,"dl",2))
	{
		return 2;
	}
	if(str_match2(str,"bl",2))
	{
		return 3;
	}
	if(str_match2(str,"r8b",3))
	{
		return 8;
	}
	if(str_match2(str,"r9b",3))
	{
		return 9;
	}
	if(str_match2(str,"r10b",4))
	{
		return 10;
	}
	if(str_match2(str,"r11b",4))
	{
		return 11;
	}
	if(str_match2(str,"r12b",4))
	{
		return 12;
	}
	if(str_match2(str,"r13b",4))
	{
		return 13;
	}
	if(str_match2(str,"r14b",4))
	{
		return 14;
	}
	if(str_match2(str,"r15b",4))
	{
		return 15;
	}
	if(str_match2(str,"spl",3))
	{
		return 20;
	}
	if(str_match2(str,"bpl",3))
	{
		return 21;
	}
	if(str_match2(str,"sil",3))
	{
		return 22;
	}
	if(str_match2(str,"dil",3))
	{
		return 23;
	}
	if(str_match2(str,"ah",2))
	{
		return 28;
	}
	if(str_match2(str,"ch",2))
	{
		return 29;
	}
	if(str_match2(str,"dh",2))
	{
		return 30;
	}
	if(str_match2(str,"bh",2))
	{
		return 31;
	}
	return -1;
}
int parse_reg64(char **str)
{
	if(str_match2(str,"rax",3))
	{
		return 0;
	}
	if(str_match2(str,"rcx",3))
	{
		return 1;
	}
	if(str_match2(str,"rdx",3))
	{
		return 2;
	}
	if(str_match2(str,"rbx",3))
	{
		return 3;
	}
	if(str_match2(str,"rsp",3))
	{
		return 4;
	}
	if(str_match2(str,"rbp",3))
	{
		return 5;
	}
	if(str_match2(str,"rsi",3))
	{
		return 6;
	}
	if(str_match2(str,"rdi",3))
	{
		return 7;
	}
	if(str_match2(str,"r8",2))
	{
		return 8;
	}
	if(str_match2(str,"r9",2))
	{
		return 9;
	}
	if(str_match2(str,"r10",3))
	{
		return 10;
	}
	if(str_match2(str,"r11",3))
	{
		return 11;
	}
	if(str_match2(str,"r12",3))
	{
		return 12;
	}
	if(str_match2(str,"r13",3))
	{
		return 13;
	}
	if(str_match2(str,"r14",3))
	{
		return 14;
	}
	if(str_match2(str,"r15",3))
	{
		return 15;
	}
	if(str_match2(str,"riz",3))
	{
		return -2;
	}
	return -1;
}
int parse_creg(char **str)
{
	if(str_match2(str,"cr0",3))
	{
		return 0;
	}
	if(str_match2(str,"cr2",3))
	{
		return 2;
	}
	if(str_match2(str,"cr3",3))
	{
		return 3;
	}
	if(str_match2(str,"cr4",3))
	{
		return 4;
	}
	if(str_match2(str,"cr8",3))
	{
		return 8;
	}
	return -1;
}
int parse_xreg(char **str)
{
	if(str_match2(str,"xmm0",4))
	{
		return 0;
	}
	if(str_match2(str,"xmm10",5))
	{
		return 10;
	}
	if(str_match2(str,"xmm11",5))
	{
		return 11;
	}
	if(str_match2(str,"xmm12",5))
	{
		return 12;
	}
	if(str_match2(str,"xmm13",5))
	{
		return 13;
	}
	if(str_match2(str,"xmm14",5))
	{
		return 14;
	}
	if(str_match2(str,"xmm15",5))
	{
		return 15;
	}
	if(str_match2(str,"xmm1",4))
	{
		return 1;
	}
	if(str_match2(str,"xmm2",4))
	{
		return 2;
	}
	if(str_match2(str,"xmm3",4))
	{
		return 3;
	}
	if(str_match2(str,"xmm4",4))
	{
		return 4;
	}
	if(str_match2(str,"xmm5",4))
	{
		return 5;
	}
	if(str_match2(str,"xmm6",4))
	{
		return 6;
	}
	if(str_match2(str,"xmm7",4))
	{
		return 7;
	}
	if(str_match2(str,"xmm8",4))
	{
		return 8;
	}
	if(str_match2(str,"xmm9",4))
	{
		return 9;
	}
	return -1;
}
int parse_yreg(char **str)
{
	if(str_match2(str,"ymm0",4))
	{
		return 0;
	}
	if(str_match2(str,"ymm10",5))
	{
		return 10;
	}
	if(str_match2(str,"ymm11",5))
	{
		return 11;
	}
	if(str_match2(str,"ymm12",5))
	{
		return 12;
	}
	if(str_match2(str,"ymm13",5))
	{
		return 13;
	}
	if(str_match2(str,"ymm14",5))
	{
		return 14;
	}
	if(str_match2(str,"ymm15",5))
	{
		return 15;
	}
	if(str_match2(str,"ymm1",4))
	{
		return 1;
	}
	if(str_match2(str,"ymm2",4))
	{
		return 2;
	}
	if(str_match2(str,"ymm3",4))
	{
		return 3;
	}
	if(str_match2(str,"ymm4",4))
	{
		return 4;
	}
	if(str_match2(str,"ymm5",4))
	{
		return 5;
	}
	if(str_match2(str,"ymm6",4))
	{
		return 6;
	}
	if(str_match2(str,"ymm7",4))
	{
		return 7;
	}
	if(str_match2(str,"ymm8",4))
	{
		return 8;
	}
	if(str_match2(str,"ymm9",4))
	{
		return 9;
	}
	return -1;
}
struct addr
{
	char bit32;
	char reg1;
	char reg2;
	char scale;
	unsigned int offset;
};
int parse_addr(char **str,struct addr *addr)
{
	char *old_str;
	unsigned long int off;
	old_str=*str;
	addr->offset=0;
	if(!str_match(str,"("))
	{
		if(parse_const(str,&off)==-1)
		{
			return -1;
		}
		if(off>0x7fffffff&&off<0xffffffff80000000)
		{
			error(l->line,"address out of range.");
		}
		addr->offset=off;
		if(!str_match(str,"("))
		{
			addr->bit32=0;
			addr->reg1=-1;
			addr->reg2=-1;
			addr->scale=0;
			return 0;
		}
	}
	if(!str_match(str,"%"))
	{
		error(l->line,"register required.");
	}
	if((addr->reg1=parse_reg64(str))!=-1)
	{
		addr->bit32=0;
		if(str_match(str,")"))
		{
			addr->reg2=-1;
			addr->scale=0;
			return 0;
		}
		else if(!str_match(str,","))
		{
			error(l->line,"expected \')\' or \',\' after register.");
		}
		if(!str_match(str,"%"))
		{
			error(l->line,"register required.");
		}
		if((addr->reg2=parse_reg64(str))==-1)
		{
			error(l->line,"invalid index register.");
		}
		if(addr->reg2==4)
		{
			error(l->line,"invalid index register.");
		}
		if(str_match(str,")"))
		{
			addr->scale=0;
			return 0;
		}
		else if(!str_match(str,","))
		{
			error(l->line,"expected \')\' or \',\' after register.");
		}
		if(str_match(str,"1"))
		{
			addr->scale=0;
		}
		else if(str_match(str,"2"))
		{
			addr->scale=0x40;
		}
		else if(str_match(str,"4"))
		{
			addr->scale=0x80;
		}
		else if(str_match(str,"8"))
		{
			addr->scale=0xc0;
		}
		else
		{
			error(l->line,"invalid scaler.");
		}
		if(!str_match(str,")"))
		{
			error(l->line,"expected \')\' after scaler.");
		}
		return 0;
	}
	else if((addr->reg1=parse_reg32(str))!=-1)
	{
		addr->bit32=1;
		if(str_match(str,")"))
		{
			addr->reg2=-1;
			addr->scale=0;
			return 0;
		}
		else if(!str_match(str,","))
		{
			error(l->line,"expected \')\' or \',\' after register.");
		}
		if(!str_match(str,"%"))
		{
			error(l->line,"register required.");
		}
		if((addr->reg2=parse_reg32(str))==-1)
		{
			error(l->line,"invalid index register.");
		}
		if(addr->reg2==4)
		{
			error(l->line,"invalid index register.");
		}
		if(str_match(str,")"))
		{
			addr->scale=0;
			return 0;
		}
		else if(!str_match(str,","))
		{
			error(l->line,"expected \')\' or \',\' after register.");
		}
		if(str_match(str,"1"))
		{
			addr->scale=0;
		}
		else if(str_match(str,"2"))
		{
			addr->scale=0x40;
		}
		else if(str_match(str,"4"))
		{
			addr->scale=0x80;
		}
		else if(str_match(str,"8"))
		{
			addr->scale=0xc0;
		}
		else
		{
			error(l->line,"invalid scaler.");
		}
		if(!str_match(str,")"))
		{
			error(l->line,"expected \')\' after scaler.");
		}
		return 0;
	}
	else if(str_match(str,"rip"))
	{
		if(!str_match(str,")"))
		{
			error(l->line,"expected \')\' after %rip.");
		}
		addr->bit32=0;
		addr->reg1=16;
		addr->reg2=-1;
		addr->scale=0;
		return 0;
	}
	else
	{
		error(l->line,"invalid address.");
	}
}
struct ins_args
{
	struct addr addr;
	char reg1;
	char reg2;
	char pad[6];
	unsigned long int imm;
};
int get_ins_args(char *input,char *format,struct ins_args *args)
{
	char *word;
	while(word=read_word(&format))
	{
		if(!strcmp(word,"ADDR"))
		{
			if(parse_addr(&input,&args->addr))
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"B1"))
		{
			if((args->reg1=parse_reg8(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"B2"))
		{
			if((args->reg2=parse_reg8(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"W1"))
		{
			if((args->reg1=parse_reg16(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"W2"))
		{
			if((args->reg2=parse_reg16(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"L1"))
		{
			if((args->reg1=parse_reg32(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"L2"))
		{
			if((args->reg2=parse_reg32(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Q1"))
		{
			if((args->reg1=parse_reg64(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Q2"))
		{
			if((args->reg2=parse_reg64(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"C1"))
		{
			if((args->reg1=parse_creg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"C2"))
		{
			if((args->reg2=parse_creg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"X1"))
		{
			if((args->reg1=parse_xreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"X2"))
		{
			if((args->reg2=parse_xreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Y1"))
		{
			if((args->reg1=parse_yreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Y2"))
		{
			if((args->reg2=parse_yreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"I"))
		{
			if((parse_const(&input,&args->imm))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!str_match(&input,word))
		{
			free(word);
			return -1;
		}
		free(word);
	}
	input=skip_spaces(input);
	if(*input!=0)
	{
		return -1;
	}
	return 0;
}
