//
//  IPSearch.m
//  filestrings
//
//  Created by yarshure on 08-3-28.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "IPSearch.h"


@implementation IPAddress

@synthesize ipstring;
@synthesize arealocation;



+(id) ipaddress
{
	return [[IPAddress alloc] init];
}

- (NSNumber * ) ip2int
{
   	unsigned int searchip=0;
	//NSNumber *ipAsObject;
	
	NSArray *myarray=[self.ipstring componentsSeparatedByString:@"."];
	for(id loopItem in myarray) {
		searchip = searchip*256+[loopItem  intValue];
	}
	return [NSNumber numberWithInteger:searchip];
}
- (NSString *)findlocation
{
	NSBundle * mainBundle = [NSBundle mainBundle];
	NSString *IPDBfile=[mainBundle pathForResource:@"QQWry" ofType:@"Dat"];
	NSData *myData=[NSData dataWithContentsOfMappedFile:IPDBfile];
	const void *start,*save;
	save=[myData bytes];
    start=save;
	unsigned char *firstip,*lastip;
	GetOffset(save,&firstip,&lastip);
	unsigned int total=(lastip-firstip)/7+1;
	Search_Bin(&firstip,&lastip,[self.ip2int unsignedIntValue]);
	start=firstip;
	unsigned char *end[5];
	char area[96];
	unsigned int startip,endip,tmpip;
	memcpy((unsigned char *)&startip, start,4);
	memset(end, 0 ,sizeof(end));
	memcpy(end, start+4,3);
	memcpy((unsigned char *)&tmpip, end,4);
	memcpy((unsigned char *)&endip, save+tmpip,4);
	memset(area, 0 ,sizeof(area));
	FindDsr(save, tmpip,area);
	CFStringRef arealocation=CFStringCreateWithCString(NULL,area, kCFStringEncodingEUC_CN);
    //[location setObjectValue:arealocation];
	return arealocation;
}
@end
