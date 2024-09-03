// Copyright © 2023 ab180. All rights reserved.

#include "UtilsBlueprintFunction.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#elif PLATFORM_IOS
#import "iOS/SGToast.h"
#endif

FColor DarkYellow(153, 153, 0, 255);

void UUtilsBlueprintFunction::ShowToast(const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleShowToast",
			"(Ljava/lang/String;)V", false);
		jstring JString = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JString);
	}
#elif PLATFORM_IOS
	[[SGToast singleton] message:Msg.GetNSString() duration:(float)1.0];
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "[Toast] " + Msg);
#endif
}

void UUtilsBlueprintFunction::LogVerbose(const FString& Tag, const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleLogVerbose",
			"(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringTag, JStringMsg);
	}
#elif PLATFORM_IOS
	// TODO("Not yet implemented")
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DarkYellow,
		FString::Printf(TEXT("[LogVerbose][%s] %s"), *Tag, *Msg));
#endif
}
    
void UUtilsBlueprintFunction::LogDebug(const FString& Tag, const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleLogDebug",
			"(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringTag, JStringMsg);
	}
#elif PLATFORM_IOS
	// TODO("Not yet implemented")
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DarkYellow,
		FString::Printf(TEXT("[LogDebug][%s] %s"), *Tag, *Msg));
#endif
}
    
void UUtilsBlueprintFunction::LogInfo(const FString& Tag, const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleLogInfo",
			"(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringTag, JStringMsg);
	}
#elif PLATFORM_IOS
	// TODO("Not yet implemented")
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DarkYellow,
		FString::Printf(TEXT("[LogInfo][%s] %s"), *Tag, *Msg));
#endif
}
    
void UUtilsBlueprintFunction::LogWarn(const FString& Tag, const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleLogWarn",
			"(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringTag, JStringMsg);
	}
#elif PLATFORM_IOS
	// TODO("Not yet implemented")
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DarkYellow,
		FString::Printf(TEXT("[LogWarn][%s] %s"), *Tag, *Msg));
#endif
}
    
void UUtilsBlueprintFunction::LogError(const FString& Tag, const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleLogError",
			"(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringTag, JStringMsg);
	}
#elif PLATFORM_IOS
	// TODO("Not yet implemented")
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DarkYellow,
		FString::Printf(TEXT("[LogError][%s] %s"), *Tag, *Msg));
#endif
}
    
void UUtilsBlueprintFunction::LogAssert(const FString& Tag, const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"sampleLogAssert",
			"(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringTag, JStringMsg);
	}
#elif PLATFORM_IOS
	// TODO("Not yet implemented")
#else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DarkYellow,
		FString::Printf(TEXT("[LogAssert][%s] %s"), *Tag, *Msg));
#endif
}

FString UUtilsBlueprintFunction::MapToString(const TMap<FString, FString>& Map)
{
	// Build the string representation of the map
	FString MapString = "{";
	for (const auto& Pair : Map)
	{
		MapString += FString::Printf(TEXT("(%s, %s)"), *Pair.Key, *Pair.Value);
	}
	MapString += "}";
	return MapString;
}