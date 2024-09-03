#pragma once

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AirBridge/AirBridge.h>

@interface AUAppDelegate : NSObject <UIApplicationDelegate>

+(void)unregisterLifeCycleListener;

@end