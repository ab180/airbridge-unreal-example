// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeAndroidCore.h"
#include "AirbridgeCallbacks.h"
#include "UObject/UObjectIterator.h"
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android/log.h>
#endif

AirbridgeAndroidCore::AirbridgeAndroidCore()
{
}

AirbridgeAndroidCore::~AirbridgeAndroidCore()
{
}

void AirbridgeAndroidCore::CallVoidMethod(const ANSICHAR* MethodName)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, MethodName, "()V", false);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
    }
#endif
}

void AirbridgeAndroidCore::CallStringParamMethod(const ANSICHAR* MethodName, const FString& Param)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            MethodName, "(Ljava/lang/String;)V", false);
        jstring JString = Env->NewStringUTF(TCHAR_TO_UTF8(*Param));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JString);
    }
#endif
}

#pragma region USER

void AirbridgeAndroidCore::SetUserID(const FString& Id)
{
    CallStringParamMethod("airbridgeSetUserId", Id);
}

void AirbridgeAndroidCore::SetUserEmail(const FString& Email)
{
    CallStringParamMethod("airbridgeSetUserEmail", Email);
}

void AirbridgeAndroidCore::SetUserPhone(const FString& PhoneNumber)
{
    CallStringParamMethod("airbridgeSetUserPhone", PhoneNumber);
}

void AirbridgeAndroidCore::SetUserAttribute(const FString& Key, const int32 Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetUserAttribute", "(Ljava/lang/String;I)V", false);
        jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jKey, Value);
    }
#endif
}

void AirbridgeAndroidCore::SetUserAttribute(const FString& Key, const int64 Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetUserAttribute", "(Ljava/lang/String;J)V", false);
        jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jKey, Value);
    }
#endif
}

void AirbridgeAndroidCore::SetUserAttribute(const FString& Key, const float Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetUserAttribute", "(Ljava/lang/String;F)V", false);
        jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jKey, Value);
    }
#endif
}

void AirbridgeAndroidCore::SetUserAttribute(const FString& Key, const bool Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetUserAttribute", "(Ljava/lang/String;Z)V", false);
        jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jKey, Value);
    }
#endif
}

void AirbridgeAndroidCore::SetUserAttribute(const FString& Key, const FString& Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetUserAttribute", "(Ljava/lang/String;Ljava/lang/String;)V", false);
        jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        jstring jValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jKey, jValue);
    }
#endif
}

void AirbridgeAndroidCore::RemoveUserAttribute(const FString& Key)
{
    CallStringParamMethod("airbridgeRemoveUserAttribute", Key);
}

void AirbridgeAndroidCore::ClearUserAttributes()
{
    CallVoidMethod("airbridgeClearUserAttributes");
}

void AirbridgeAndroidCore::SetUserAlias(const FString& Key, const FString& Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetUserAlias", "(Ljava/lang/String;Ljava/lang/String;)V", false);
        jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        jstring jValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jKey, jValue);
    }
#endif
}

void AirbridgeAndroidCore::RemoveUserAlias(const FString& Key)
{
    CallStringParamMethod("airbridgeRemoveUserAlias", Key);
}

void AirbridgeAndroidCore::ClearUserAlias()
{
    CallVoidMethod("airbridgeClearUserAlias");
}

void AirbridgeAndroidCore::ClearUser()
{
    CallVoidMethod("airbridgeClearUser");
}

#pragma endregion USER

#pragma region EVENT

void AirbridgeAndroidCore::TrackEvent(const FString& Category)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jclass airbridgeEventClass = FAndroidApplication::FindJavaClass("co/ab180/airbridge/event/Event");
        jmethodID airbridgeEventConstructor = Env->GetMethodID(airbridgeEventClass, "<init>", "(Ljava/lang/String;)V");
		
        jstring jCategory = Env->NewStringUTF(TCHAR_TO_UTF8(*Category));
        
        if (jobject airbridgeEvent = Env->NewObject(airbridgeEventClass, airbridgeEventConstructor, jCategory))
        {
            jmethodID Method = FJavaWrapper::FindMethod(Env,
                FJavaWrapper::GameActivityClassID,
                "airbridgeTrackEvent",
                "(Lco/ab180/airbridge/event/Event;)V", false);
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, airbridgeEvent);
        }
    }
#endif
}

void AirbridgeAndroidCore::TrackEvent(const FString& Category, const UAirbridgeEventOption& EventOption)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        if (jobject airbridgeEvent = (jobject) EventOption.CreateJavaObject(Category))
        {
            jmethodID Method = FJavaWrapper::FindMethod(Env,
                FJavaWrapper::GameActivityClassID,
                "airbridgeTrackEvent",
                "(Lco/ab180/airbridge/event/Event;)V", false);
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, airbridgeEvent);
        }
    }
#endif
}

#pragma endregion EVENT

#pragma region PLACEMENT

void AirbridgeAndroidCore::Click(const FString& TrackingLink)
{
    CallStringParamMethod("airbridgeClick", TrackingLink);
}

void AirbridgeAndroidCore::Impression(const FString& TrackingLink)
{
    CallStringParamMethod("airbridgeImpression", TrackingLink);
}

#pragma endregion PLACEMENT

#pragma region CALLBACK

void AirbridgeAndroidCore::SetDeeplinkCallback()
{
    DidSetDeeplinkCallback.AtomicSet(true);
    if (!StartDeeplink.IsEmpty())
    {
        UnrealBroadcastDeeplink();
    }
}

void AirbridgeAndroidCore::SetAttributionCallback()
{
    DidSetAttributionCallback.AtomicSet(true);
    if (ReceivedAttribution.Num() != 0)
    {
        UnrealBroadcastAttribution();
    }
}

#pragma endregion CALLBACK

#pragma region DEVICE

void AirbridgeAndroidCore::SetDeviceAlias(const FString& Key, const FString& Value)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jmethodID Method = FJavaWrapper::FindMethod(Env,
            FJavaWrapper::GameActivityClassID,
            "airbridgeSetDeviceAlias", "(Ljava/lang/String;Ljava/lang/String;)V", false);
        jstring JStringKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
        jstring JStringValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringKey, JStringValue);
    }
#endif
}

void AirbridgeAndroidCore::RemoveDeviceAlias(const FString& Key)
{
    CallStringParamMethod("airbridgeRemoveDeviceAlias", Key);
}

void AirbridgeAndroidCore::ClearDeviceAlias()
{
    CallVoidMethod("airbridgeClearDeviceAlias");
}

#pragma endregion DEVICE

#pragma region ADVANCED
	
void AirbridgeAndroidCore::StartTracking()
{
    CallVoidMethod("airbridgeStartTracking");
}

void AirbridgeAndroidCore::RegisterPushToken(const FString& Token)
{
    CallStringParamMethod("airbridgeRegisterPushToken", Token);
}

#pragma endregion ADVANCED

// Send Deeplink Url to Unreal Engine GameMode Objects
void AirbridgeAndroidCore::UnrealBroadcastDeeplink()
{
    for (TObjectIterator<UAirbridgeCallbacks> Itr; Itr; ++Itr)
    {
        Itr->OnDeeplinkReceived.Broadcast(StartDeeplink);
    }
    StartDeeplink.Reset();
}

// Send Attribution Data to Unreal Engine GameMode Objects
void AirbridgeAndroidCore::UnrealBroadcastAttribution()
{
    for (TObjectIterator<UAirbridgeCallbacks> Itr; Itr; ++Itr)
    {
        Itr->OnAttributionReceived.Broadcast(FAirbridgeAttribution {ReceivedAttribution});
    }
    ReceivedAttribution.Reset();
}