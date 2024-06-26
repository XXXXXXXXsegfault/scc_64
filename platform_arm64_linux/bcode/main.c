long int current_line;
void error(int line,char *msg)
{
	char *str;
	str=xstrdup("line ");
	str=str_i_app(str,line);
	str=str_s_app(str,": error: ");
	str=str_s_app(str,msg);
	str=str_c_app(str,'\n');
	write(2,str,strlen(str));
	exit(2);
}
int name_hash(char *str)
{
	unsigned int hash;
	hash=0;
	while(*str)
	{
		hash=(hash<<11|hash>>21)+*str;
		++str;
	}
	return hash%1021;
}
int readc(void)
{
	return stream_getc();
}
char *read_line(void)
{
	char *str;
	char c;
	int x;
	str=0;
	x=0;
	while((c=readc())!=-1)
	{
		if(c=='\n')
		{
			if(str==0)
			{
				str=xstrdup(" ");
			}
			break;
		}
		str=str_c_app2(str,x,c);
		++x;
	}
	++current_line;
	return str;
}
long int slen(char *str)
{
	int c;
	long int l;
	l=0;
	if(*str=='\"')
	{
		l=1;
		while(str[l])
		{
			if(str[l]=='\"')
			{
				++l;
				break;
			}
			if(str[l]=='\\')
			{
				++l;
				if(str[l]==0)
				{
					error(current_line,"string not complete.");
				}
			}
			++l;
		}
		return l;
	}
	while(c=*str)
	{
		if(c==32||c=='\t'||c=='\v'||c=='\r')
		{
			break;
		}
		++l;
		++str;
	}
	return l;
}
char *snext(char *str)
{
	long int l;
	if(!str)
	{
		return 0;
	}
	l=slen(str);
	str+=l;
	while(*str==32||*str=='\t'||*str=='\v'||*str=='\r')
	{
		++str;
	}
	if(*str==0)
	{
		return 0;
	}
	return str;
}
char *sdup(char *str)
{
	char *ret;
	long int l;
	if(str==0)
	{
		return 0;
	}
	l=slen(str);
	if(l==0)
	{
		return 0;
	}
	ret=xmalloc(l+1);
	memcpy(ret,str,l);
	ret[l]=0;
	return ret;
}
#include "out.c"
#include "fg.c"
#include "gencode.c"

void bcode_run(void)
{
	char *str;
	struct ins *node;
	while(str=read_line())
	{
		ins_add(str);
		free(str);
	}
	load_global_vars();
	load_labels();
	load_branches();
	load_local_vars();
	reg_init();
	write_msg();
	node=ins_head;
	while(node)
	{
		gen_code(node);
		node=node->next;
	}
	write_msg2();

	outs(".datasize ");
	out_num64(data_size);
	outs("\n");
	out_flush();
}
