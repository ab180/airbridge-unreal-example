// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Airbridge/AirbridgeType.h"
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

/**
 *
 */
class AirbridgeJNI
{
public:
	static void SetString(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<FString>& AirbridgeString);
	static void SetBoolean(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<bool>& AirbridgeBoolean);
	static void SetNumber(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<double>& AirbridgeNumber);
	static void SetInteger(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<int32>& AirbridgeInteger);

	static bool JavaMapToUnrealTMap(JNIEnv *Env, jobject Map, TMap<FString, FString>& TMapOut);

	static void SetMapString(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, const FString& Value);
	static void SetMapInteger(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, int32 Value);
	static void SetMapNumber(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, double Value);
	static void SetMapBoolean(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, bool Value);

	static void AddListString(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, const FString& Value);
	static void AddListInteger(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, int32 Value);
	static void AddListNumber(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, double Value);
	static void AddListBoolean(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, bool Value);

private:
	static jobject MakeIntegerObject(JNIEnv *Env, int32 Value);
	static jobject MakeNumberObject(JNIEnv *Env, double Value);
	static jobject MakeBooleanObject(JNIEnv *Env, bool Value);
};
#endif