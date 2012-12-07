static const char rcid[] = "$Header: /opt/src/cvsroot/dnsgroup/IPsearch.c,v 1.2 2005/06/22 07:22:21 dev Exp $";
#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include <string.h>
#include <errno.h>
#include "IPsearchc.h"

int Mmap(char *dbfile, unsigned char **start,int  *filesize)
{
    int fd;
    struct stat sb;
    fd= open(dbfile,O_RDWR);
    fstat(fd,&sb); /*取得文件大小*/
    *start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
    if(*start == MAP_FAILED) {/*判断是否映射成功*/
	perror("mmap error\n");
	printf("error mmap\n"); 
	return -1;
    }
    *filesize = sb.st_size;
    close(fd);
    return 0;
}
int GetOffset(unsigned char *start, unsigned char **Startaddr, unsigned char **Endaddr)
{
    unsigned int StartOffset;
    unsigned int  EndOffset;
    memcpy((unsigned char *)&StartOffset, start, 4);
    memcpy((unsigned char *)&EndOffset,  start+4,4);
    *Startaddr = start + StartOffset;
    *Endaddr   = start +EndOffset;
    return 0;
}

int  int2ip(unsigned int i,unsigned char *ipaddress){
    sprintf(ipaddress,"%d.%d.%d.%d",i/(256*256*256), (i%(256*256*256))/(256*256),(i%(256*256))/(256), i%256);
    return 0;
}
int bin2ip(unsigned char *s,unsigned char *ipaddress) {
    sprintf(ipaddress,"%d.%d.%d.%d",s[3],s[2],s[1],s[0]);
    return 0;
}

int ip2bin(unsigned int *searchip, unsigned char *src)
{
    unsigned char *p;
    int  i=0 ,j;
    p =src;

    *searchip =0;
    for(j = 0;j<=strlen(src)-1;) {
	i =0;
	while((0x2e != (unsigned int)*p) && (j <= strlen(src)-2)) {
	    i = 10* i + (unsigned int)*p -0x30;
	    p++;
	    j++;
	}
	*searchip = *searchip * 256+i;
	p++;j++;
    }

    //printf("searchip :%d:%s\n",*searchip,src);

    return 0;
}

int Search_Bin(unsigned char **start,unsigned  char **end  , unsigned int key)
{//二分查找,相等的几率几乎很小，所以不要判断等于
    char *mid;
    unsigned int startip,midip,endip;
    while((*end - *start) !=7) {
	memcpy((unsigned char *)&startip,*start,4);
	memcpy((unsigned char *)&endip,  *end,4);
	if( startip == key) {
	    return 0;
	}
	if( endip   == key ) {
	    *start  = *end;
	    return 0;
	}
	if(((*end-*start)/7)%2 ==0) { 
	    mid = *start+(*end-*start)/2;
	}
	else {
	    mid = *start+ (*end-*start+7)/2;
	}
	memcpy((unsigned char *)&midip,mid,4);
	if(midip == key) {
	    *start = mid;
	    return 0;
	} else {
	    if(midip <key ) {
		*start = mid;
	    } else {
		*end = mid;
	    }
	}
    }
    return 0;
}//Search_Bin

int FindDsr(char *save,int offset, char *area )
{
    unsigned int addr, addr1;
    unsigned char buf[5];
    unsigned char *p,*dsr;
    p = area;
    offset +=4;
    dsr = save + offset;

    memset(buf, 0, sizeof(buf));
    if(0x01 == (unsigned int)*dsr) {

	memcpy(buf,dsr+1, 3);
	memcpy((unsigned char *)&addr, buf, 4);

	if(0x02 == (unsigned int)*(save+addr)) {
	    dsr =  save +addr;
	    memset(buf, 0, sizeof(buf));
	    memcpy(buf, (dsr+1), 3);
	    memcpy((unsigned char *)&addr1, buf, 4);

	    strncpy(p, save+addr1,strlen(save+addr1));
	    p += strlen(save+addr1);
	    *p++ =0x20;//note here 

	    if((0x02 == (unsigned int)*(dsr+4)) ) {
		memset(buf, 0, sizeof(buf));
		memcpy(buf, (dsr+5), 3);
		memcpy((unsigned char *)&addr1, buf, 4);
		strcpy(p, save+addr1);
	    }
	    else {
		strcpy(p, dsr+4);
	    }
	    return 0;
	} else {

	    if((0x01 == (unsigned int)*(save+addr)) ) {
		memset(buf, 0, sizeof(buf));
		memcpy(buf, (save+addr+1), 3);
		memcpy((unsigned char *)&addr1, buf, 4);
		strncpy(p, save+addr1,strlen(save+addr));
		p += strlen(save+addr);
		*p++ =0x20;// note this 
		strcpy(p,save+addr1+strlen(save+addr)+1);
	    } else {
		strncpy(p, save+addr,strlen(save+addr));
		p += strlen(save+addr);
		*p++ =0x20;//this 
		dsr = save+addr+strlen(save+addr)+1;
		if(0x02 == (unsigned int)*dsr)  {
		    memset(buf, 0, sizeof(buf));
		    memcpy(buf, (dsr+1), 3);
		    memcpy((unsigned char *)&addr1, buf, 4);
		    strcpy(p, save+addr1);
		} else {
		    strcpy(p, save+addr+strlen(save+addr)+1);
		}
		return 0;
	    }
	}
	return 0;
    }
    if(0x02 == (unsigned int)*dsr) {

	memcpy(buf,dsr+1, 3);
	memcpy((unsigned char *)&addr, buf, 4);

	strcpy(p, save+addr);
	p += strlen(p);
	*p++ =0x20;// this 
	if(0x02 == (unsigned int)*(dsr+4)) {
	    memcpy(buf,dsr+5, 3);
	    memcpy((unsigned char *)&addr, buf, 4);
	    strcpy(p, save+addr);
	    return 0;
	}
	strcpy(p, dsr+4);
	return 0;
    }
    strncpy(p, dsr ,strlen(dsr));
    p += strlen(dsr);
    *p++ =0x20;//this 
    if(0x2 == (unsigned int)*(dsr+strlen(dsr)+1)) {
	memcpy(buf, dsr+strlen(dsr)+2, 3);
	memcpy((unsigned char *)&addr, buf,4);
	strcpy(p , save+addr);
    } else {
	strcpy(p, dsr+strlen(dsr)+1);
    }
    return 0;
}
