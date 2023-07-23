char outc_buf[65536];
int outc_x;
void outc(char c)
{
	int n;
	if(outc_x==65536)
	{
		write(fdo,outc_buf,outc_x);
		outc_x=0;
	}
	outc_buf[outc_x]=c;
	++outc_x;
}
void out_flush(void)
{
	if(outc_x)
	{
		write(fdo,outc_buf,outc_x);
	}
}
void outs(char *str)
{
	while(*str)
	{
		outc(*str);
		++str;
	}
}
void out_label(char *label)
{
	outs("@");
	outs(label);
	outs("\n");
}
void out_label_name(char *label)
{
	outs(label);
}
void out_num64(unsigned long int n)
{
	char *str;
	str=str_i_app(0,n);
	outs(str);
	free(str);
}
void out_num32(unsigned long int n)
{
	out_num64(n&0xffffffff);
}
void out_num16(unsigned long int n)
{
	out_num64(n&0xffff);
}
void out_num8(unsigned long int n)
{
	out_num64(n&0xff);
}
void out_num(int class,unsigned long int n)
{
	if(class==1||class==2)
	{
		out_num8(n);
	}
	else if(class==3||class==4)
	{
		out_num16(n);
	}
	else if(class==5||class==6)
	{
		out_num32(n);
	}
	else if(class==7||class==8)
	{
		out_num64(n);
	}
	else if(class==10)
	{
		out_num64(n);
	}
	else if(class==9)
	{
		float n2;
		n2=*(double *)&n;
		out_num32(*(unsigned int *)&n2);
	}
}
char *sgetc(char *str,char *ret)
{
	int x;
	if(str[0]=='\\')
	{
		if(str[1]=='\\')
		{
			*ret='\\';
			return str+2;
		}
		else if(str[1]=='n')
		{
			*ret='\n';
			return str+2;
		}
		else if(str[1]=='t')
		{
			*ret='\t';
			return str+2;
		}
		else if(str[1]=='v')
		{
			*ret='\v';
			return str+2;
		}
		else if(str[1]=='r')
		{
			*ret='\r';
			return str+2;
		}
		else if(str[1]=='\'')
		{
			*ret='\'';
			return str+2;
		}
		else if(str[1]=='\"')
		{
			*ret='\"';
			return str+2;
		}
		else if(str[1]=='\?')
		{
			*ret='\?';
			return str+2;
		}
		else if(str[1]>='0'&&str[1]<='7')
		{
			x=1;
			*ret=0;
			while(str[x]>='0'&&str[x]<='7')
			{
				*ret=(*ret<<3)+(str[x]-'0');
				++x;
			}
			return str+x;
		}
		else if(str[1]=='x')
		{
			x=2;
			*ret=0;
			while(1)
			{
				if(str[x]>='0'&&str[x]<='9')
				{
					*ret=*ret*16+(str[x]-'0');
				}
				else if(str[x]>='A'&&str[x]<='F')
				{
					*ret=*ret*16+(str[x]-'A'+10);
				}
				else if(str[x]>='a'&&str[x]<='f')
				{
					*ret=*ret*16+(str[x]-'a'+10);
				}
				else
				{
					break;
				}
				++x;
			}
			return str+x;
		}
		else
		{
			*ret='\\';
			return str+1;
		}
	}
	else
	{
		*ret=str[0];
		return str+1;
	}
}
void out_str(char *str)
{
	char c[2];
	c[1]=0;
	str=str+1;
	while(*str&&*str!='\"')
	{
		str=sgetc(str,c);
		outs(c);
	}
}
void out_reg64(int reg)
{
	char *s;
	s=xstrdup("x");
	s=str_i_app(s,reg);
	outs(s);
	free(s);
}
void out_reg32(int reg)
{
	char *s;
	s=xstrdup("w");
	s=str_i_app(s,reg);
	outs(s);
	free(s);
}
void out_reg_size(int reg,int class,int ld)
{
	int reg64;
	reg64=0;
	if(ld&&class&1&&class<=6)
	{
		outs("s");
		if(class>4)
		{
			outs("w");
		}
		reg64=1;
	}
	if(class==1||class==2)
	{
		outs("b ");
		if(reg64)
		{
			out_reg64(reg);
		}
		else
		{
			out_reg32(reg);
		}
	}
	if(class==3||class==4)
	{
		outs("h ");
		if(reg64)
		{
			out_reg64(reg);
		}
		else
		{
			out_reg32(reg);
		}
	}
	if(class==5||class==6||class==9)
	{
		outs(" ");
		if(reg64)
		{
			out_reg64(reg);
		}
		else
		{
			out_reg32(reg);
		}
	}
	if(class==7||class==8||class==10)
	{
		outs(" ");
		out_reg64(reg);
	}
}
