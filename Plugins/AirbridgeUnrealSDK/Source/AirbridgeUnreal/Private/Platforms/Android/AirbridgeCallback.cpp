// Copyright © 2023 ab180. All rights reserved.

#if PLATFORM_ANDROID
#include "AirbridgeAndroidCore.h"
#include "AirbridgeUnrealModule.h"
#include "Platforms/Android/Util/AirbridgeJNI.h"

#define ANDROID_CORE_POINTER	(static_cast<AirbridgeAndroidCore*>(FAirbridgeUnrealModule::Get().GetAirbridge().Get()))

extern "C" {
	/*
	 * Class:     co_ab180_airbridge_ue_AirbridgeUECallback
	 * Method:    onSuccess
	 * Signature: (Landroid/net/Uri;)V
	 */
	JNIEXPORT void JNICALL Java_co_ab180_airbridge_ue_AirbridgeUECallback_onSuccess
	(JNIEnv *Env, jobject Obj, jobject Uri)
	{
		jclass clsNetUri = Env->GetObjectClass(Uri);
		jmethodID toString = Env->GetMethodID(clsNetUri, "toString", "()Ljava/lang/String;");
		jstring jUriString = (jstring)Env->CallObjectMethod(Uri, toString);

		//convert to c-string from java-string
		//In other words, copy java-string to heap memory on native
		const char* c_uri_string = Env->GetStringUTFChars(jUriString, nullptr);

		ANDROID_CORE_POINTER->StartDeeplink = FString(c_uri_string);
		
		if (ANDROID_CORE_POINTER->DidSetDeeplinkCallback)
		{
			ANDROID_CORE_POINTER->UnrealBroadcastDeeplink();
		}
		
		//release heap memory
		(Env)->ReleaseStringUTFChars(jUriString, c_uri_string);
	}
	/*
	 * Class:     co_ab180_airbridge_ue_AirbridgeUECallback
	 * Method:    onFailure
	 * Signature: (Ljava/lang/Throwable;)V
	 */
	JNIEXPORT void JNICALL Java_co_ab180_airbridge_ue_AirbridgeUECallback_onFailure
	(JNIEnv *Env, jobject Obj, jthrowable Throwable)
	{
		
	}
	/*
	 * Class:     co_ab180_airbridge_ue_AirbridgeUECallback
	 * Method:    onComplete
	 * Signature: ()V
	 */
	JNIEXPORT void JNICALL Java_co_ab180_airbridge_ue_AirbridgeUECallback_onComplete
	(JNIEnv *Env, jobject Obj)
	{
	
	}
	/*
	 * Class:     co_ab180_airbridge_ue_UEOnAttributionResultReceiveListener
	 * Method:    onAttributionResultReceived
	 * Signature: (Ljava/util/Map;)V
	 */
	JNIEXPORT void JNICALL Java_co_ab180_airbridge_ue_UEOnAttributionResultReceiveListener_onAttributionResultReceived
	(JNIEnv *Env, jobject Obj, jobject Map)
	{
		if (Map == nullptr) return;
		
		TMap<FString, FString> AttributionResult;
		if (AirbridgeJNI::JavaMapToUnrealTMap(Env, Map, AttributionResult))
		{
			ANDROID_CORE_POINTER->ReceivedAttribution = AttributionResult;

			if (ANDROID_CORE_POINTER->DidSetAttributionCallback)
			{
				ANDROID_CORE_POINTER->UnrealBroadcastAttribution();	
			}
		}
	}
}
#endif