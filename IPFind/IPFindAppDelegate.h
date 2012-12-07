//
//  IPFindAppDelegate.h
//  IPFind
//
//  Created by XiangBo Kong on 11-9-29.
//  Copyright 2011年 macdevshanghai.com. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface IPFindAppDelegate : NSObject <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UITextField *ip;
@property (nonatomic, retain) IBOutlet UILabel *area;
- (IBAction)hello:(id)sender;
@end
