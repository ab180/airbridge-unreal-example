// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeIOSCore.h"
#include "AirbridgeCallbacks.h"
#include "UObject/UObjectIterator.h"

#if PLATFORM_IOS
#include "IOSAppDelegate.h"

#import "Platforms/iOS/Native/AUAppDelegate.h"
#import "Platforms/iOS/Native/AUAppSetting.h"
#import "Platforms/iOS/Native/Utils/AUHex.h"

#import <UIKit/UIKit.h>
#import <AirBridge/AirBridge.h>
#import <AirBridge/ABInAppEvent.h>
#endif

AirbridgeIOSCore::AirbridgeIOSCore() {
#if PLATFORM_IOS
    [AUAppDelegate load];
#endif
}

AirbridgeIOSCore::~AirbridgeIOSCore() {
#if PLATFORM_IOS
    [AUAppDelegate unregisterLifeCycleListener];
#endif
}

#pragma region USER

void AirbridgeIOSCore::SetUserID(const FString& Id) {
#if PLATFORM_IOS
    [AirBridge.state setUserID:Id.GetNSString()];
#endif
}

void AirbridgeIOSCore::SetUserEmail(const FString& Email) {
#if PLATFORM_IOS
    [AirBridge.state setUserEmail:Email.GetNSString()];
#endif
}

void AirbridgeIOSCore::SetUserPhone(const FString& PhoneNumber) {
#if PLATFORM_IOS
    [AirBridge.state setUserPhone:PhoneNumber.GetNSString()];
#endif
}

void AirbridgeIOSCore::SetUserAttribute(const FString& Key, const int32 Value) {
#if PLATFORM_IOS
    [AirBridge.state addUserAttributesWithKey:Key.GetNSString() value:@(Value)];
#endif
}

void AirbridgeIOSCore::SetUserAttribute(const FString& Key, const int64 Value) {
#if PLATFORM_IOS
    [AirBridge.state addUserAttributesWithKey:Key.GetNSString() value:@(Value)];
#endif
}

void AirbridgeIOSCore::SetUserAttribute(const FString& Key, const float Value) {
#if PLATFORM_IOS
    [AirBridge.state addUserAttributesWithKey:Key.GetNSString() value:@(Value)];
#endif
}

void AirbridgeIOSCore::SetUserAttribute(const FString& Key, const bool Value) {
#if PLATFORM_IOS
    [AirBridge.state addUserAttributesWithKey:Key.GetNSString() value:@(Value)];
#endif
}

void AirbridgeIOSCore::SetUserAttribute(const FString& Key, const FString& Value) {
#if PLATFORM_IOS
    NSString *key = Key.GetNSString();
    NSString *value = Value.GetNSString();
    [AirBridge.state addUserAttributesWithKey:key value:value];
#endif
}

void AirbridgeIOSCore::RemoveUserAttribute(const FString& Key) {
#if PLATFORM_IOS
    [AirBridge.state removeUserAttributes:Key.GetNSString()];
#endif
}

void AirbridgeIOSCore::ClearUserAttributes() {
#if PLATFORM_IOS
    [AirBridge.state clearUserAttributes];
#endif
}

void AirbridgeIOSCore::SetUserAlias(const FString& Key, const FString& Value) {
#if PLATFORM_IOS
    NSString *key = Key.GetNSString();
    NSString *value = Value.GetNSString();
    [AirBridge.state addUserAliasWithKey:key value:value];
#endif
}

void AirbridgeIOSCore::RemoveUserAlias(const FString& Key) {
#if PLATFORM_IOS
    [AirBridge.state removeUserAlias:Key.GetNSString()];
#endif
}

void AirbridgeIOSCore::ClearUserAlias() {
#if PLATFORM_IOS
    [AirBridge.state clearUserAlias];
#endif
}

void AirbridgeIOSCore::ClearUser() {
#if PLATFORM_IOS
    [AirBridge.state setUser:[ABUser new]];
#endif
}

#pragma endregion USER

#pragma region EVENT

void AirbridgeIOSCore::TrackEvent(const FString& Category) {
#if PLATFORM_IOS
    ABInAppEvent* event = [ABInAppEvent new];
    [event setCategory:Category.GetNSString()];
    [event send];
#endif
}

void AirbridgeIOSCore::TrackEvent(const FString& Category, const UAirbridgeEventOption& EventOption) {
#if PLATFORM_IOS
    ABInAppEvent* event = [ABInAppEvent new];
    
    [event setCategory:Category.GetNSString()];
    [event setAction:EventOption.Action.GetNSString()];
    [event setLabel:EventOption.Label.GetNSString()];
    [event setValue:EventOption.Value.GetNSNumber()];
    if (nullptr != EventOption.CustomAttributes) {
        [event setCustoms:EventOption.CustomAttributes->ConvertToNSDictionary()];
    }
    if (nullptr != EventOption.SemanticAttributes) {
        [event setSemantics:EventOption.SemanticAttributes->ConvertToNSDictionary()];
    }
    [event send];
#endif
}

#pragma endregion EVENT

#pragma region PLACEMENT

void AirbridgeIOSCore::Click(const FString& TrackingLink) {
#if PLATFORM_IOS
    NSURL *url = [NSURL URLWithString:TrackingLink.GetNSString()];
    [AirBridge.placement click:url completion:nil];
#endif
}

void AirbridgeIOSCore::Impression(const FString& TrackingLink) {
#if PLATFORM_IOS
    NSURL *url = [NSURL URLWithString:TrackingLink.GetNSString()];
    [AirBridge.placement impression:url completion:nil];
#endif
}

#pragma endregion PLACEMENT

#pragma region CALLBACK

void AirbridgeIOSCore::SetDeeplinkCallback()
{
    DidSetDeeplinkCallback.AtomicSet(true);
    if (!StartDeeplink.IsEmpty())
    {
        UnrealBroadcastDeeplink();
    }
}

void AirbridgeIOSCore::SetAttributionCallback()
{
    DidSetAttributionCallback.AtomicSet(true);
    if (ReceivedAttribution.Num() != 0)
    {
        UnrealBroadcastAttribution();
    }
}

#pragma endregion CALLBACK

#pragma region DEVICE

void AirbridgeIOSCore::SetDeviceAlias(const FString& Key, const FString& Value) {
#if PLATFORM_IOS
    NSString *key = Key.GetNSString();
    NSString *value = Value.GetNSString();
    [AirBridge.state setDeviceAliasWithKey:key value:value];
#endif
}

void AirbridgeIOSCore::RemoveDeviceAlias(const FString& Key) {
#if PLATFORM_IOS
    [AirBridge.state removeDeviceAliasWithKey:Key.GetNSString()];
#endif
}

void AirbridgeIOSCore::ClearDeviceAlias() {
#if PLATFORM_IOS
    [AirBridge.state clearDeviceAlias];
#endif
}

#pragma endregion DEVICE

#pragma region ADVANCED

void AirbridgeIOSCore::StartTracking() {
#if PLATFORM_IOS
    [AirBridge startTracking];
#endif
}

void AirbridgeIOSCore::RegisterPushToken(const FString& Token) {
#if PLATFORM_IOS
    NSString *tokenString = Token.GetNSString();
    NSData *tokenData = [AUHex dataFromHexString:tokenString];
    [AirBridge registerPushToken:tokenData];
#endif
}

#pragma endregion ADVANCED

// Send Deeplink Url to Unreal Engine GameMode Objects
void AirbridgeIOSCore::UnrealBroadcastDeeplink()
{
    for (TObjectIterator<UAirbridgeCallbacks> Itr; Itr; ++Itr)
    {
        Itr->OnDeeplinkReceived.Broadcast(StartDeeplink);
    }
    StartDeeplink.Reset();
}

// Send Attribution Data to Unreal Engine GameMode Objects
void AirbridgeIOSCore::UnrealBroadcastAttribution()
{
    for (TObjectIterator<UAirbridgeCallbacks> Itr; Itr; ++Itr)
    {
        Itr->OnAttributionReceived.Broadcast(FAirbridgeAttribution {ReceivedAttribution});
    }
    ReceivedAttribution.Reset();
}

/////////////////////////////////////////////////////////////////////////
//MARK: - IOSAppDelegate+AirbridgeAppDelegate

#if PLATFORM_IOS

@interface IOSAppDelegate (AirbridgeAppDelegate)

@end

@implementation IOSAppDelegate (AirbridgeAppDelegate)

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id>*)options
{
    [AirBridge.deeplink handleURLSchemeDeeplink:url];

    return YES;
}

- (BOOL)application:(UIApplication*)application continueUserActivity:(NSUserActivity*)userActivity restorationHandler:(void (^)(NSArray* _Nullable))restorationHandler
{
    [AirBridge.deeplink handleUserActivity:userActivity];

    return YES;
}

@end

#endif