struct file_tab
{
	void *fp;
	long type;
} file_tab[1021];
int _open(char *str,int flags,int mode)
{
	void *fp;
	int x,type,l;
	x=0;
	while(x<1021&&file_tab[x].fp)
	{
		++x;
	}
	if(x==1021)
	{
		return -1;
	}
	if(flags==0)
	{
		fp=fopen(str,"rb");
		if(fp==0)
		{
			return -1;
		}
		type=0;
	}
	else
	{
		fp=fopen(str,"wb");
		if(fp==0)
		{
			return -1;
		}
		type=1;
	}
	file_tab[x].fp=fp;
	file_tab[x].type=type;
	return x+3;
}
int _close(int fd)
{
	if(fd<3)
	{
		return -1;
	}
	fd-=3;
	if(fd>=1021||file_tab[fd].fp==0)
	{
		return -1;
	}
	fclose(file_tab[fd].fp);
	file_tab[fd].fp=0;
	return 0;
}
int _read(int fd,void *buf,int size)
{
	int n;
	void *fp;
	if(fd<3)
	{
		return -1;
	}
	else
	{
		fp=file_tab[fd-3].fp;
		if(fp==0||file_tab[fd-3].type!=0)
		{
			return -1;
		}
	}
	n=fread(buf,1,size,fp);
	if(n)
	{
		return n;
	}
	if(ferror(fp))
	{
		clearerr(fp);
		return -1;
	}
	return 0;
}
int _write(int fd,void *buf,int size)
{
	int n;
	void *fp;
	if(fd<3)
	{
		MessageBoxA(0,buf,"Error",0);
		return size;
	}
	else
	{
		fp=file_tab[fd-3].fp;
		if(fp==0||file_tab[fd-3].type!=1)
		{
			return -1;
		}
	}
	n=fwrite(buf,1,size,fp);
	if(n)
	{
		return n;
	}
	if(ferror(fp))
	{
		clearerr(fp);
		return -1;
	}
	return 0;
}
#define open _open
#define close _close
#define read _read
#define write _write
