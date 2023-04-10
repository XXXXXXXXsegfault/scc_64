struct name_tab
{
	struct name_tab *next;
	char *name;
	unsigned long addr;
} *dllname_tab[1021],*funname_tab[1021];
char *name_seg;
unsigned long name_seg_size;
struct function_tab
{
	char *dllname;
	unsigned long dllname_addr;
	unsigned long funname_ptr;
	unsigned long num_funs;
	char **funname;
	unsigned long *funname_addr;
	struct lines **l;
} *function_tab;
unsigned long function_tab_size;
unsigned long import_tab_off;
unsigned long *function_addr_tab,function_addr_tab_size;
unsigned int size_imports;
unsigned long size_align(unsigned long size);
unsigned long nametab_add(struct name_tab **tab,char *name)
{
	struct name_tab *node;
	int hash,l;
	static unsigned long addr;
	char *new_name_seg;
	hash=name_hash(name);
	node=tab[hash];
	while(node)
	{
		if(!strcmp(node->name,name))
		{
			return node->addr;
		}
		node=node->next;
	}
	node=xmalloc(sizeof(*node));
	node->next=tab[hash];
	tab[hash]=node;
	node->name=xstrdup(name);
	node->addr=addr;
	l=strlen(name)+3;
	addr+=l;
	new_name_seg=xmalloc(name_seg_size+l);
	memcpy(new_name_seg,name_seg,name_seg_size);
	memcpy(new_name_seg+name_seg_size+2,name,l-2);
	new_name_seg[name_seg_size]=0;
	new_name_seg[name_seg_size+1]=0;
	name_seg_size+=l;
	free(name_seg);
	name_seg=new_name_seg;
	return node->addr;
}
void function_tab_add(char *dllname,char *funname,struct lines *l)
{
	unsigned long x;
	struct function_tab *t1;
	char **t2;
	unsigned long *t3;
	struct lines **t4;
	x=0;
	while(x<function_tab_size)
	{
		if(!strcmp(function_tab[x].dllname,dllname))
		{
			break;
		}
		++x;
	}
	if(x==function_tab_size)
	{
		t1=xmalloc(sizeof(*t1)*(function_tab_size+1));
		memcpy(t1,function_tab,function_tab_size*sizeof(*t1));
		memset(t1+x,0,sizeof(*t1));
		t1[x].dllname=xstrdup(dllname);
		t1[x].dllname_addr=nametab_add(dllname_tab,dllname);
		free(function_tab);
		function_tab=t1;
		++function_tab_size;
	}
	t1=function_tab+x;
	t2=xmalloc(sizeof(void *)*(t1->num_funs+1));
	t3=xmalloc(sizeof(long)*(t1->num_funs+1));
	t4=xmalloc(sizeof(void *)*(t1->num_funs+1));
	if(t1->num_funs)
	{
		memcpy(t2,t1->funname,sizeof(void *)*t1->num_funs);
		memcpy(t3,t1->funname_addr,sizeof(long)*t1->num_funs);
		memcpy(t4,t1->l,sizeof(void *)*t1->num_funs);
		free(t1->funname);
		free(t1->funname_addr);
		free(t1->l);
	}
	t2[t1->num_funs]=xstrdup(funname);
	t3[t1->num_funs]=nametab_add(funname_tab,funname);
	t4[t1->num_funs]=l;
	t1->funname=t2;
	t1->funname_addr=t3;
	t1->l=t4;
	++t1->num_funs;
}
void dll_import_write(void)
{
	unsigned int rdata_addr;
	struct lines *l;
	int x,y;
	unsigned long val,*t1;
	rdata_addr=data_addr-0x400000+size_align(data_size);
	l=lines_head;
	while(l)
	{
		if(l->import_dll)
		{
			function_tab_add(l->import_dll,l->import_fun,l);
		}
		l=l->next;
	}
	if(!function_tab_size)
	{
		return;
	}
	y=0;
	while(y<function_tab_size)
	{
		function_tab[y].funname_ptr=import_tab_off;
		x=0;
		while(x<function_tab[y].num_funs)
		{
			val=rdata_addr+import_tab_off+0x400000;
			memcpy(function_tab[y].l[x]->ins_buf+1,&val,4);
			t1=xmalloc(sizeof(long)*(function_addr_tab_size+1));
			memcpy(t1,function_addr_tab,sizeof(long)*function_addr_tab_size);
			t1[function_addr_tab_size]=function_tab[y].funname_addr[x];
			++function_addr_tab_size;
			free(function_addr_tab);
			function_addr_tab=t1;
			import_tab_off+=8;
			++x;
		}
		t1=xmalloc(sizeof(long)*(function_addr_tab_size+1));
		memcpy(t1,function_addr_tab,sizeof(long)*function_addr_tab_size);
		t1[function_addr_tab_size]=0xffffffffffffffff;
		++function_addr_tab_size;
		free(function_addr_tab);
		function_addr_tab=t1;
		++y;
		import_tab_off+=8;
	}
	size_imports=import_tab_off*2+20*(function_tab_size+1);
	x=0;
	while(x<function_addr_tab_size)
	{
		if(function_addr_tab[x]==0xffffffffffffffff)
		{
			function_addr_tab[x]=0;
		}
		else
		{
			function_addr_tab[x]+=size_imports+rdata_addr;
		}
		++x;
	}
	y=0;
	while(y<function_tab_size)
	{
		x=0;
		function_tab[y].dllname_addr+=size_imports+rdata_addr+2;
		function_tab[y].funname_ptr+=import_tab_off+rdata_addr;
		while(x<function_tab[y].num_funs)
		{
			function_tab[y].funname_addr[x]+=size_imports;
			++x;
		}
		++y;
	}
	size_imports+=name_seg_size;
}
