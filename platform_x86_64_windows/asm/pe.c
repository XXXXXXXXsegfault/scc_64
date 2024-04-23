struct pe_ddir
{
	unsigned int vaddr;
	unsigned int size;
};
struct pe_section
{
	char name[8];
	unsigned int vsize;
	unsigned int vaddr;
	unsigned int dsize;
	unsigned int dataptr;
	unsigned int relocptr;
	unsigned int line_number;
	unsigned short num_reloc;
	unsigned short num_line_number;
	unsigned int characteristics;
};
struct pe_header
{
	unsigned short int mz_sign; //0x5a4d
	unsigned short int pad[29];
	unsigned int pe_off; //0x80
	unsigned int pad2[16];
	unsigned int pe_sign; //0x4550
	unsigned short machine; // 0x8664
	unsigned short num_sections; // 3
	unsigned int time;
	unsigned int p_symbols;
	unsigned int num_symbols;
	unsigned short optheader_size;
	unsigned short characteristics; //0x23
	unsigned short magic;
	unsigned char linker_ver[2];
	unsigned int code_size;
	unsigned int idata_size;
	unsigned int udata_size;
	unsigned int entry;
	unsigned int code_base;
	unsigned long image_base; //PE_BASE
	unsigned int align; // 4096
	unsigned int file_align; //4096
	unsigned short osver[2];
	unsigned short image_ver[2];
	unsigned short subsystem_ver[2];
	unsigned int win32_ver;
	unsigned int image_size;
	unsigned int headers_size; // 4096
	unsigned int checksum;
	unsigned short subsystem;
	unsigned short dll_characteristics;
	unsigned long stack_reserve;
	unsigned long stack_commit;
	unsigned long heap_reserve;
	unsigned long heap_commit;
	unsigned int loader_flags;
	unsigned int num_ddirents; // 16
	struct pe_ddir ddirents[16];
	struct pe_section sections[3];
} pe_header;
unsigned long int spos;
int save_file,checksum_stage,checksum_word,checksum_carry;
unsigned long int pe_checksum,pe_fsize;
void swrite(void *buf,unsigned long int size)
{
	unsigned char *new_data;
	if(l->ins_len+size>48)
	{
		new_data=xmalloc(l->ins_len+size);
		if(l->ins_len<=48)
		{
			memcpy(new_data,l->ins_buf,l->ins_len);
		}
		else
		{
			memcpy(new_data,l->ins_buf2,l->ins_len);
		}
		memcpy(new_data+l->ins_len,buf,size);
		free(l->ins_buf2);
		l->ins_buf2=new_data;
	}
	else
	{
		memcpy(l->ins_buf+l->ins_len,buf,size);
	}
	l->ins_len+=size;
	spos+=size;
	pc+=size;
}
void soutc(char c)
{
	swrite(&c,1);
}
char outc_buf[65536];
int outc_x;
void outc(char c)
{
	int n;
	if(!save_file)
	{
		if(checksum_stage)
		{
			checksum_word|=(unsigned int)(unsigned char)c<<8;
			checksum_stage=0;
			pe_checksum+=checksum_word+checksum_carry;
			checksum_carry=pe_checksum>>16&1;
			pe_checksum&=0xffff;
		}
		else
		{
			checksum_word=(unsigned int)(unsigned char)c;
			checksum_stage=1;
		}
		++pe_fsize;
		return;
	}
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
	if(!save_file)
	{
		return;
	}
	if(outc_x)
	{
		write(fdo,outc_buf,outc_x);
	}
	outc_x=0;
}
void c_write(void *buf,int size)
{
	char *buf1;
	buf1=buf;
	while(size)
	{
		outc(*buf1);
		++buf1;
		--size;
	}
}
void out_addr(unsigned long int addr)
{
	int x;
	x=64;
	do
	{
		x-=4;
		write(fde,"0123456789ABCDEF"+(addr>>x&0xf),1);
	}
	while(x);
	write(fde,": ",2);
}
unsigned long size_align(unsigned long size)
{
	if(size==0)
	{
		return 0;
	}
	return (size-1>>12)+1<<12;
}
unsigned long size_align2(unsigned long size)
{
	if(size==0)
	{
		return 0;
	}
	return (size-1>>9)+1<<9;
}
void file_pad(int size)
{
	static char buf[0x200];
	size=size&0x1ff;
	if(size)
	{
		size=0x200-size;
	}
	c_write(buf,size);
}
void _mkpe(void)
{
	int x;
	pe_header.mz_sign=0x5a4d;
	memcpy(pe_header.pad,"\x90\x00\x03\x00\x00\x00\x04\x00\x00\x00\xff\xff\x00\x00\xb8\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00",30);
	pe_header.pe_off=0x80;
	memcpy(pe_header.pad2,"\x0e\x1f\xba\x0e\x00\xb4\x09\xcd\x21\xb8\x01\x4c\xcd\x21This program cannot be run in DOS mode.\r\r\n$",57);
	pe_header.pe_sign=0x4550;
	pe_header.machine=0x8664;
	pe_header.num_sections=3;
	if(!size_imports)
	{
		--pe_header.num_sections;
	}
	if(!data_size)
	{
		--pe_header.num_sections;
	}
	pe_header.optheader_size=240;
	pe_header.characteristics=0x27;
	pe_header.magic=0x20b;
	pe_header.code_size=data_addr-0x1000-PE_BASE;
	pe_header.udata_size=size_align(data_size);
	pe_header.code_base=0x1000;
	pe_header.image_base=PE_BASE;
	if(!save_file)
	{
		pe_header.entry-=PE_BASE;
	}
	pe_header.align=4096;
	pe_header.file_align=512;
	pe_header.osver[0]=4;
	pe_header.subsystem_ver[0]=5;
	pe_header.subsystem_ver[1]=2;
	pe_header.image_size=data_addr+size_align(data_size)+size_align(size_imports)-PE_BASE;
	pe_header.headers_size=size_align2(sizeof(pe_header));
	if(save_file)
	{
		pe_header.checksum=pe_checksum;
	}
	pe_header.subsystem=2;
	if(generate_cui)
	{
		pe_header.subsystem=3;
	}
	pe_header.stack_reserve=0x400000;
	pe_header.stack_commit=0x1000;
	pe_header.heap_reserve=0x100000;
	pe_header.heap_commit=0x1000;
	pe_header.num_ddirents=16;
	if(size_imports)
	{
		pe_header.ddirents[1].vaddr=data_addr-PE_BASE+size_align(data_size)+size_imports-
		name_seg_size-20*(function_tab_size+1);
		pe_header.ddirents[1].size=20*(function_tab_size+1);
	}
	strcpy(pe_header.sections[0].name,".text");
	pe_header.sections[0].vsize=data_addr-PE_BASE-0x1000;
	pe_header.sections[0].vaddr=0x1000;
	pe_header.sections[0].dsize=size_align2(spos);
	pe_header.sections[0].dataptr=0x200;
	pe_header.sections[0].characteristics=0x60000020;
	x=1;
	if(data_size)
	{
		strcpy(pe_header.sections[1].name,".bss");
		pe_header.sections[1].vsize=size_align(data_size);
		pe_header.sections[1].vaddr=data_addr-PE_BASE;
		pe_header.sections[1].dsize=0;
		pe_header.sections[1].dataptr=0;
		pe_header.sections[1].characteristics=0xc0000080;
		++x;
	}
	if(size_imports)
	{
		strcpy(pe_header.sections[x].name,".idata");
		pe_header.sections[x].vsize=size_align(size_imports);
		pe_header.sections[x].vaddr=data_addr-PE_BASE+size_align(data_size);
		pe_header.sections[x].dsize=size_align2(size_imports);
		pe_header.sections[x].dataptr=0x200+size_align2(spos);
		pe_header.sections[x].characteristics=0xc0000040;
	}
	c_write(&pe_header,sizeof(pe_header));
	file_pad(sizeof(pe_header));
	l=lines_head;
	while(l)
	{
		if(l->ins_len>48)
		{
			c_write(l->ins_buf2,l->ins_len);
		}
		else
		{
			c_write(l->ins_buf,l->ins_len);
		}
		if(fde>=0)
		{
			out_addr(l->ins_pos);
			write(fde,l->str,strlen(l->str));
			write(fde,"\n",1);
		}
		l=l->next;
	}
	file_pad(spos);
	if(size_imports)
	{
		unsigned long zval;
		int x;
		unsigned long int val;
		zval=0;
		x=0;
		while(x<function_addr_tab_size)
		{
			c_write(function_addr_tab+x,8);
			++x;
		}
		x=0;
		while(x<function_addr_tab_size)
		{
			c_write(function_addr_tab+x,8);
			++x;
		}
		x=0;
		while(x<function_tab_size)
		{
			val=function_tab[x].funname_ptr;
			c_write(&val,4);
			c_write(&zval,4);
			c_write(&zval,4);
			val=function_tab[x].dllname_addr;
			c_write(&val,4);
			val=function_tab[x].funname_ptr-import_tab_off;
			c_write(&val,4);
			++x;
		}
		val=0;
		c_write(&val,4);
		c_write(&val,4);
		c_write(&val,4);
		c_write(&val,4);
		c_write(&val,4);
		c_write(name_seg,name_seg_size);
		file_pad(size_imports);
	}
	out_flush();
}
void mkpe(void)
{
	int fd;
	fd=fde;
	fde=-1;
	_mkpe();
	pe_checksum+=pe_fsize+checksum_carry;
	save_file=1;
	fde=fd;
	_mkpe();
}
