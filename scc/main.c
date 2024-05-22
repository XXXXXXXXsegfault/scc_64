void error(int line,int col,char *msg)
{
	char *str;
	str=xstrdup("line ");
	str=str_i_app(str,line);
	str=str_s_app(str," column ");
	str=str_i_app(str,col);
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
#include "load_file.c"
#include "parse/parse.c"
#include "translate/translate.c"

void scc_run(void)
{
	struct syntax_tree *root;
	struct label_tab *node,*p;
	int index;
	l_global_init();
	expr_global_init();
	type_global_init();
	parse_global_init();
	load_file();
	p_current_word=l_words_head;
	root=parse_file();
	translate_file(root);
	node=label_use;
	while(node)
	{
		index=name_hash(node->name);
		p=label_def[index];
		while(p)
		{
			if(!strcmp(p->name,node->name))
			{
				goto Defined;
			}
			p=p->next;
		}
		error(node->line,node->col,"label not defined.");
Defined:
		node=node->next;
	}
	out_flush();
}
