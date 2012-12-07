/*  rcid[] = "$Header: /opt/src/cvsroot/dnsgroup/IPsearch.h,v 1.1 2005/06/09 17:08:52 dev Exp $"; */


typedef struct {
    unsigned char *endaddr;
    char country[20];
    char area[40];
}IPADDR;

typedef struct {
    unsigned char  *startaddr;
    unsigned char *offset;
}STARTIP;

typedef struct {
    unsigned char *firstaddr;
    unsigned char *lastaddr;
}OFFSET;
	
int Mmap(char *dbfile, unsigned char **start,int *filesize);
int GetOffset(unsigned char *start, unsigned char **Startaddr, unsigned char **Endaddr);
int int2ip(unsigned int i,unsigned char *ipaddress);
int bin2ip(unsigned char *s,unsigned char *ipaddress);
int ip2bin(unsigned int *searchip, unsigned char *src);
int Search_Bin(unsigned char **start,unsigned  char **end  , unsigned int key);
int FindDsr(char *save,int offset, char *area);

