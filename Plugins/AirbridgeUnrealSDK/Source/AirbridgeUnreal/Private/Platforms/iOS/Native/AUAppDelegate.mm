#import "AUAppDelegate.h"
#import "AUAppSetting.h"

#include "AirbridgeIOSCore.h"
#include "AirbridgeUnrealModule.h"

#define IOS_CORE_POINTER	(static_cast<AirbridgeIOSCore*>(FAirbridgeUnrealModule::Get().GetAirbridge().Get()))

@implementation AUAppDelegate

static AUAppDelegate *AUAppDelegateInstance = nil;

-(id)init
{
    self = [super init];
    return self;
}

+(void)load
{
    [super load];
    if (AUAppDelegateInstance == nil)
    {
        AUAppDelegateInstance = [[AUAppDelegate alloc] init];
        [AUAppDelegateInstance registerLifeCycleListener];
    }
}

+(AUAppDelegate *)getInstance
{
    return AUAppDelegateInstance;
}

-(void)registerLifeCycleListener
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didFinishLaunching:)
                                                 name:UIApplicationDidFinishLaunchingNotification
                                               object:nil];
}

+(void)unregisterLifeCycleListener
{
    if (AUAppDelegateInstance != nil)
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:UIApplicationDidFinishLaunchingNotification
                                                      object:nil];
    }
}

-(void)didFinishLaunching:(NSNotification *)notification
{
    [[AirBridge state] setSDKDevelopmentPlatform:@"unreal"];
    
    // AUAppSetting.h 파일에 저장된 세팅 값들을 사용한다.
    AirBridge.autoStartTrackingEnabled = autoStartTrackingEnabled;
    AirBridge.setting.trackingAuthorizeTimeout = trackingAuthorizeTimeoutSeconds * 1000;
  
    [AirBridge setSessionTimeout:sessionTimeoutSeconds * 1000];
    [AirBridge setLogLevel:(ABLogLevel)logLevel];
    [AirBridge setIsUserInfoHashed:userInfoHashEnabled];
    [AirBridge setIsTrackAirbridgeDeeplinkOnly:trackAirbridgeLinkOnly];
    [AirBridge setAutoStartTrackingEnabled:autoStartTrackingEnabled];
    
    if (sdkSignatureSecretID.length != 0 && sdkSignatureSecret.length != 0) {
        [AirBridge setSDKSignatureSecretWithID:sdkSignatureSecretID secret:sdkSignatureSecret];
    }
    
    [AirBridge getInstance:appToken
                   appName:appName
         withLaunchOptions:notification.userInfo];
    
    // Deeplink Callback 설정
    [AirBridge.deeplink setDeeplinkCallback:^(NSString* deeplink) {
    
        IOS_CORE_POINTER->StartDeeplink = FString(deeplink);
        if (IOS_CORE_POINTER->DidSetDeeplinkCallback) 
        {
            IOS_CORE_POINTER->UnrealBroadcastDeeplink();
        }
    }];
    
    // Attribution Callback 설정
    [AirBridge.setting setAttributionCallback:^(NSDictionary<NSString *,NSString *> * _Nonnull attribution) {
        
        TMap<FString, FString> AttributionResult;
        for (NSString *key in [attribution allKeys]) {
            AttributionResult.Emplace(key, attribution[key]);
        }
        IOS_CORE_POINTER->ReceivedAttribution = AttributionResult;
        if (IOS_CORE_POINTER->DidSetAttributionCallback) 
        {
            IOS_CORE_POINTER->UnrealBroadcastAttribution();
        }
    }];
}

@end
