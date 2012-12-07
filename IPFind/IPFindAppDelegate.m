//
//  IPFindAppDelegate.m
//  IPFind
//
//  Created by XiangBo Kong on 11-9-29.
//  Copyright 2011年 macdevshanghai.com. All rights reserved.
//

#import "IPFindAppDelegate.h"
#import "IPSearch.h"
@implementation IPFindAppDelegate

@synthesize window = _window;
@synthesize area = _area;
@synthesize ip = _ip;
#pragma func
//This method is invoked when the Hello button or return key is touched
- (void)hello:(id)sender
{
    [self.ip resignFirstResponder];
    NSString *nameString = self.ip.text;
	IPAddress * myIPAddress=[IPAddress ipaddress];
    if ([nameString length] == 0) {    //Nothing was typed
        //nameString = @"202.199.96.100";
		myIPAddress.ipstring=@"202.199.96.100";
	    NSString *greeting = [NSString stringWithFormat:@"%@",myIPAddress.findlocation ];
		self.area.text = greeting;
    } else if([nameString length] >16){
        
		NSString *greeting = @"IPaddr is too lang";
		self.area.text = greeting;
	} else {
	    NSArray *iparray=[nameString componentsSeparatedByString:@"."];
		//NSMutableString *nameStringtmp;
		if([iparray count] >4){
	        NSString *greeting = @"IPaddr is not validity";
			self.area.text = greeting;
		} else if([iparray count] == 4){
			myIPAddress.ipstring=nameString;
			NSString *greeting = [NSString stringWithFormat:@"%@",myIPAddress.findlocation ];
			self.area.text = greeting;
		} else if([iparray count]==3) {
		    myIPAddress.ipstring=[NSString stringWithFormat:@"%@.0",nameString];
		    NSString *greeting = [NSString stringWithFormat:@"%@",myIPAddress.findlocation ];
			self.area.text = greeting;
		} else if([iparray count]==2) {
			myIPAddress.ipstring=[NSString stringWithFormat:@"%@.0.0",nameString];
		    NSString *greeting = [NSString stringWithFormat:@"%@",myIPAddress.findlocation ];
			self.area.text = greeting;
		} else {
			myIPAddress.ipstring=[NSString stringWithFormat:@"%@.0.0.0",nameString];
		    NSString *greeting = [NSString stringWithFormat:@"%@",myIPAddress.findlocation ];
			self.area.text = greeting;
		}
        
	}
    
	//myIPAddress.ipstring=nameString;
	//NSString *greeting = [NSString stringWithFormat:@"%@",myIPAddress.findlocation ];
    
    //self.label.text = greeting;
}
// Do the equivalent of touching the Hello button when return is touched
- (void)textFieldDidEndEditing:(UITextField *)theTextField
{
    [self hello: theTextField];
}

// Sent when the return key on the keyboard is touched
- (BOOL)textFieldShouldReturn:(UITextField *)theTextField
{
    [theTextField resignFirstResponder];
    return YES;
}
#pragma -

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

- (void)dealloc
{
    [_window release];
    [super dealloc];
}

@end
