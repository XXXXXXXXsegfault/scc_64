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
	if(str_match2(str,"w10",3))
	{
		return 10;
	}
	if(str_match2(str,"w11",3))
	{
		return 11;
	}
	if(str_match2(str,"w12",3))
	{
		return 12;
	}
	if(str_match2(str,"w13",3))
	{
		return 13;
	}
	if(str_match2(str,"w14",3))
	{
		return 14;
	}
	if(str_match2(str,"w15",3))
	{
		return 15;
	}
	if(str_match2(str,"w16",3))
	{
		return 16;
	}
	if(str_match2(str,"w17",3))
	{
		return 17;
	}
	if(str_match2(str,"w18",3))
	{
		return 18;
	}
	if(str_match2(str,"w19",3))
	{
		return 19;
	}
	if(str_match2(str,"w20",3))
	{
		return 20;
	}
	if(str_match2(str,"w21",3))
	{
		return 21;
	}
	if(str_match2(str,"w22",3))
	{
		return 22;
	}
	if(str_match2(str,"w23",3))
	{
		return 23;
	}
	if(str_match2(str,"w24",3))
	{
		return 24;
	}
	if(str_match2(str,"w25",3))
	{
		return 25;
	}
	if(str_match2(str,"w26",3))
	{
		return 26;
	}
	if(str_match2(str,"w27",3))
	{
		return 27;
	}
	if(str_match2(str,"w28",3))
	{
		return 28;
	}
	if(str_match2(str,"w29",3))
	{
		return 29;
	}
	if(str_match2(str,"w30",3))
	{
		return 30;
	}
	if(str_match2(str,"wzr",3))
	{
		return 31;
	}
	if(str_match2(str,"wsp",3))
	{
		return 63;
	}
	if(str_match2(str,"w0",2))
	{
		return 0;
	}
	if(str_match2(str,"w1",2))
	{
		return 1;
	}
	if(str_match2(str,"w2",2))
	{
		return 2;
	}
	if(str_match2(str,"w3",2))
	{
		return 3;
	}
	if(str_match2(str,"w4",2))
	{
		return 4;
	}
	if(str_match2(str,"w5",2))
	{
		return 5;
	}
	if(str_match2(str,"w6",2))
	{
		return 6;
	}
	if(str_match2(str,"w7",2))
	{
		return 7;
	}
	if(str_match2(str,"w8",2))
	{
		return 8;
	}
	if(str_match2(str,"w9",2))
	{
		return 9;
	}
	return -1;
}
int parse_reg64(char **str)
{
	if(str_match2(str,"x10",3))
	{
		return 10;
	}
	if(str_match2(str,"x11",3))
	{
		return 11;
	}
	if(str_match2(str,"x12",3))
	{
		return 12;
	}
	if(str_match2(str,"x13",3))
	{
		return 13;
	}
	if(str_match2(str,"x14",3))
	{
		return 14;
	}
	if(str_match2(str,"x15",3))
	{
		return 15;
	}
	if(str_match2(str,"x16",3))
	{
		return 16;
	}
	if(str_match2(str,"x17",3))
	{
		return 17;
	}
	if(str_match2(str,"x18",3))
	{
		return 18;
	}
	if(str_match2(str,"x19",3))
	{
		return 19;
	}
	if(str_match2(str,"x20",3))
	{
		return 20;
	}
	if(str_match2(str,"x21",3))
	{
		return 21;
	}
	if(str_match2(str,"x22",3))
	{
		return 22;
	}
	if(str_match2(str,"x23",3))
	{
		return 23;
	}
	if(str_match2(str,"x24",3))
	{
		return 24;
	}
	if(str_match2(str,"x25",3))
	{
		return 25;
	}
	if(str_match2(str,"x26",3))
	{
		return 26;
	}
	if(str_match2(str,"x27",3))
	{
		return 27;
	}
	if(str_match2(str,"x28",3))
	{
		return 28;
	}
	if(str_match2(str,"x29",3))
	{
		return 29;
	}
	if(str_match2(str,"x30",3))
	{
		return 30;
	}
	if(str_match2(str,"xzr",3))
	{
		return 31;
	}
	if(str_match2(str,"sp",2))
	{
		return 63;
	}
	if(str_match2(str,"x0",2))
	{
		return 0;
	}
	if(str_match2(str,"x1",2))
	{
		return 1;
	}
	if(str_match2(str,"x2",2))
	{
		return 2;
	}
	if(str_match2(str,"x3",2))
	{
		return 3;
	}
	if(str_match2(str,"x4",2))
	{
		return 4;
	}
	if(str_match2(str,"x5",2))
	{
		return 5;
	}
	if(str_match2(str,"x6",2))
	{
		return 6;
	}
	if(str_match2(str,"x7",2))
	{
		return 7;
	}
	if(str_match2(str,"x8",2))
	{
		return 8;
	}
	if(str_match2(str,"x9",2))
	{
		return 9;
	}
	return -1;
}
int parse_hreg(char **str)
{
	if(str_match2(str,"s10",3))
	{
		return 10;
	}
	if(str_match2(str,"s11",3))
	{
		return 11;
	}
	if(str_match2(str,"s12",3))
	{
		return 12;
	}
	if(str_match2(str,"s13",3))
	{
		return 13;
	}
	if(str_match2(str,"s14",3))
	{
		return 14;
	}
	if(str_match2(str,"s15",3))
	{
		return 15;
	}
	if(str_match2(str,"s16",3))
	{
		return 16;
	}
	if(str_match2(str,"s17",3))
	{
		return 17;
	}
	if(str_match2(str,"s18",3))
	{
		return 18;
	}
	if(str_match2(str,"s19",3))
	{
		return 19;
	}
	if(str_match2(str,"s20",3))
	{
		return 20;
	}
	if(str_match2(str,"s21",3))
	{
		return 21;
	}
	if(str_match2(str,"s22",3))
	{
		return 22;
	}
	if(str_match2(str,"s23",3))
	{
		return 23;
	}
	if(str_match2(str,"s24",3))
	{
		return 24;
	}
	if(str_match2(str,"s25",3))
	{
		return 25;
	}
	if(str_match2(str,"s26",3))
	{
		return 26;
	}
	if(str_match2(str,"s27",3))
	{
		return 27;
	}
	if(str_match2(str,"s28",3))
	{
		return 28;
	}
	if(str_match2(str,"s29",3))
	{
		return 29;
	}
	if(str_match2(str,"s30",3))
	{
		return 30;
	}
	if(str_match2(str,"s31",3))
	{
		return 31;
	}
	if(str_match2(str,"s0",2))
	{
		return 0;
	}
	if(str_match2(str,"s1",2))
	{
		return 1;
	}
	if(str_match2(str,"s2",2))
	{
		return 2;
	}
	if(str_match2(str,"s3",2))
	{
		return 3;
	}
	if(str_match2(str,"s4",2))
	{
		return 4;
	}
	if(str_match2(str,"s5",2))
	{
		return 5;
	}
	if(str_match2(str,"s6",2))
	{
		return 6;
	}
	if(str_match2(str,"s7",2))
	{
		return 7;
	}
	if(str_match2(str,"s8",2))
	{
		return 8;
	}
	if(str_match2(str,"s9",2))
	{
		return 9;
	}
	return -1;
}
int parse_freg(char **str)
{
	if(str_match2(str,"d10",3))
	{
		return 10;
	}
	if(str_match2(str,"d11",3))
	{
		return 11;
	}
	if(str_match2(str,"d12",3))
	{
		return 12;
	}
	if(str_match2(str,"d13",3))
	{
		return 13;
	}
	if(str_match2(str,"d14",3))
	{
		return 14;
	}
	if(str_match2(str,"d15",3))
	{
		return 15;
	}
	if(str_match2(str,"d16",3))
	{
		return 16;
	}
	if(str_match2(str,"d17",3))
	{
		return 17;
	}
	if(str_match2(str,"d18",3))
	{
		return 18;
	}
	if(str_match2(str,"d19",3))
	{
		return 19;
	}
	if(str_match2(str,"d20",3))
	{
		return 20;
	}
	if(str_match2(str,"d21",3))
	{
		return 21;
	}
	if(str_match2(str,"d22",3))
	{
		return 22;
	}
	if(str_match2(str,"d23",3))
	{
		return 23;
	}
	if(str_match2(str,"d24",3))
	{
		return 24;
	}
	if(str_match2(str,"d25",3))
	{
		return 25;
	}
	if(str_match2(str,"d26",3))
	{
		return 26;
	}
	if(str_match2(str,"d27",3))
	{
		return 27;
	}
	if(str_match2(str,"d28",3))
	{
		return 28;
	}
	if(str_match2(str,"d29",3))
	{
		return 29;
	}
	if(str_match2(str,"d30",3))
	{
		return 30;
	}
	if(str_match2(str,"d31",3))
	{
		return 31;
	}
	if(str_match2(str,"d0",2))
	{
		return 0;
	}
	if(str_match2(str,"d1",2))
	{
		return 1;
	}
	if(str_match2(str,"d2",2))
	{
		return 2;
	}
	if(str_match2(str,"d3",2))
	{
		return 3;
	}
	if(str_match2(str,"d4",2))
	{
		return 4;
	}
	if(str_match2(str,"d5",2))
	{
		return 5;
	}
	if(str_match2(str,"d6",2))
	{
		return 6;
	}
	if(str_match2(str,"d7",2))
	{
		return 7;
	}
	if(str_match2(str,"d8",2))
	{
		return 8;
	}
	if(str_match2(str,"d9",2))
	{
		return 9;
	}
	return -1;
}
int parse_qreg(char **str)
{
	if(str_match2(str,"q10",3))
	{
		return 10;
	}
	if(str_match2(str,"q11",3))
	{
		return 11;
	}
	if(str_match2(str,"q12",3))
	{
		return 12;
	}
	if(str_match2(str,"q13",3))
	{
		return 13;
	}
	if(str_match2(str,"q14",3))
	{
		return 14;
	}
	if(str_match2(str,"q15",3))
	{
		return 15;
	}
	if(str_match2(str,"q16",3))
	{
		return 16;
	}
	if(str_match2(str,"q17",3))
	{
		return 17;
	}
	if(str_match2(str,"q18",3))
	{
		return 18;
	}
	if(str_match2(str,"q19",3))
	{
		return 19;
	}
	if(str_match2(str,"q20",3))
	{
		return 20;
	}
	if(str_match2(str,"q21",3))
	{
		return 21;
	}
	if(str_match2(str,"q22",3))
	{
		return 22;
	}
	if(str_match2(str,"q23",3))
	{
		return 23;
	}
	if(str_match2(str,"q24",3))
	{
		return 24;
	}
	if(str_match2(str,"q25",3))
	{
		return 25;
	}
	if(str_match2(str,"q26",3))
	{
		return 26;
	}
	if(str_match2(str,"q27",3))
	{
		return 27;
	}
	if(str_match2(str,"q28",3))
	{
		return 28;
	}
	if(str_match2(str,"q29",3))
	{
		return 29;
	}
	if(str_match2(str,"q30",3))
	{
		return 30;
	}
	if(str_match2(str,"q31",3))
	{
		return 31;
	}
	if(str_match2(str,"q0",2))
	{
		return 0;
	}
	if(str_match2(str,"q1",2))
	{
		return 1;
	}
	if(str_match2(str,"q2",2))
	{
		return 2;
	}
	if(str_match2(str,"q3",2))
	{
		return 3;
	}
	if(str_match2(str,"q4",2))
	{
		return 4;
	}
	if(str_match2(str,"q5",2))
	{
		return 5;
	}
	if(str_match2(str,"q6",2))
	{
		return 6;
	}
	if(str_match2(str,"q7",2))
	{
		return 7;
	}
	if(str_match2(str,"q8",2))
	{
		return 8;
	}
	if(str_match2(str,"q9",2))
	{
		return 9;
	}
	return -1;
}
struct ins_args
{
	char reg1;
	char reg2;
	char reg3;
	char reg4;
	int pad;
	unsigned long imm;
};
int get_ins_args(char *input,char *format,struct ins_args *args)
{
	char *word;
	while(word=read_word(&format))
	{
		if(!strcmp(word,"X1"))
		{
			if((args->reg1=parse_reg64(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"X2"))
		{
			if((args->reg2=parse_reg64(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"X3"))
		{
			if((args->reg3=parse_reg64(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"X4"))
		{
			if((args->reg4=parse_reg64(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"W1"))
		{
			if((args->reg1=parse_reg32(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"W2"))
		{
			if((args->reg2=parse_reg32(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"W3"))
		{
			if((args->reg3=parse_reg32(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"W4"))
		{
			if((args->reg4=parse_reg32(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Q1"))
		{
			if((args->reg1=parse_qreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Q2"))
		{
			if((args->reg2=parse_qreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Q3"))
		{
			if((args->reg3=parse_qreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"Q4"))
		{
			if((args->reg4=parse_qreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"F1"))
		{
			if((args->reg1=parse_freg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"F2"))
		{
			if((args->reg2=parse_freg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"F3"))
		{
			if((args->reg3=parse_freg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"F4"))
		{
			if((args->reg4=parse_freg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"H1"))
		{
			if((args->reg1=parse_hreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"H2"))
		{
			if((args->reg2=parse_hreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"H3"))
		{
			if((args->reg3=parse_hreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"H4"))
		{
			if((args->reg4=parse_hreg(&input))==-1)
			{
				free(word);
				return -1;
			}
		}
		else if(!strcmp(word,"I"))
		{
			if(parse_const(&input,&args->imm)==-1)
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
