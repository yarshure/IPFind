//
//  IPSearch.h
//  filestrings
//
//  Created by yarshure on 08-3-28.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

//#import <Cocoa/Cocoa.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSData.h>
#import <Foundation/NSValue.h>

@interface IPAddress : NSObject  {
           NSString * ipstring;
		   //NSNumber *ipbin;
//		   NSInteger ipint;
//		   NSData *ipbin;
		   NSString * arealocation;
}
+(id) ipaddress;

@property (copy) NSString * ipstring;
@property (copy) NSString * arealocation;
//@property (assign) NSInteger ipbin;
-(NSNumber *) ip2int;
- (NSString *)findlocation;
//-(void) bin2ip;
@end
