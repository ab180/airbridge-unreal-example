// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeJNI.h"

#if PLATFORM_ANDROID

void AirbridgeJNI::SetString(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<FString>& AirbridgeString)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		if (AirbridgeString.NonNull())
		{
			jstring Jstring = Env->NewStringUTF(TCHAR_TO_UTF8(*AirbridgeString.Get()));
			
			jmethodID Jmethod = Env->GetMethodID(Jclass, Setter, "(Ljava/lang/String;)V");
			FJavaWrapper::CallVoidMethod(Env, Jobject, Jmethod, Jstring);
		}
	}
}

void AirbridgeJNI::SetBoolean(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<bool>& AirbridgeBoolean)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		if (AirbridgeBoolean.NonNull())
		{
			jclass JbooleanClass = Env->FindClass("java/lang/Boolean");
			jmethodID JbooleanConstructor = Env->GetMethodID(JbooleanClass, "<init>", "(Z)V");
			jobject Jboolean = Env->NewObject(JbooleanClass, JbooleanConstructor, AirbridgeBoolean.Get());
			
			jmethodID Jmethod = Env->GetMethodID(Jclass, Setter, "(Ljava/lang/Boolean;)V");
			FJavaWrapper::CallVoidMethod(Env, Jobject, Jmethod, Jboolean);
		}
	}
}

void AirbridgeJNI::SetNumber(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<double>& AirbridgeNumber)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		if (AirbridgeNumber.NonNull())
		{
			jmethodID JdoubleToNumberMethod = FJavaWrapper::FindMethod(Env,
				FJavaWrapper::GameActivityClassID,
				"airbridgeToNumber",
				"(D)Ljava/lang/Number;",
				false);
			jobject Jnumber = FJavaWrapper::CallObjectMethod(Env,
				FJavaWrapper::GameActivityThis,
				JdoubleToNumberMethod,
				AirbridgeNumber.Get());

			jmethodID Jmethod = Env->GetMethodID(Jclass, Setter, "(Ljava/lang/Number;)V");
			FJavaWrapper::CallVoidMethod(Env, Jobject, Jmethod, Jnumber);
		}
	}
}

void AirbridgeJNI::SetInteger(jclass Jclass, jobject Jobject, const char *Setter, const FAirbridgeType<int32>& AirbridgeInteger)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		if (AirbridgeInteger.NonNull())
		{
			jclass JIntegerClass = Env->FindClass("java/lang/Integer");
			jmethodID JIntegerConstructor = Env->GetMethodID(JIntegerClass, "<init>", "(I)V");
			jobject Jinteger = Env->NewObject(JIntegerClass, JIntegerConstructor, AirbridgeInteger.Get());
			
			jmethodID Jmethod = Env->GetMethodID(Jclass, Setter, "(Ljava/lang/Integer;)V");
			FJavaWrapper::CallVoidMethod(Env, Jobject, Jmethod, Jinteger);
		}
	}
}

/**
 * @brief Convert Java Map<String, String> to C++ Unreal Engine's TMap<FString, FString>
 */
bool AirbridgeJNI::JavaMapToUnrealTMap(JNIEnv *Env, jobject Map, TMap<FString, FString>& TMapOut)
{
	// Get Map class
	jclass clsMap = Env->FindClass("java/util/Map");
	if (clsMap == nullptr) { return false; }
	
	// Get "entrySet" method of Map class
	jmethodID entrySet = Env->GetMethodID(clsMap, "entrySet", "()Ljava/util/Set;");
	if (entrySet == nullptr) { return false; }

	// Get Set<Map.Entry<String, String>> of Java Object Map
	jobject set = Env->CallObjectMethod(Map, entrySet);
	if (set == nullptr) { return false; }

	// Obtain an iterator over the Set
	jclass clsSet = Env->FindClass("java/util/Set");
	if (clsSet == nullptr) { return false; }
	jmethodID iterator = Env->GetMethodID(clsSet, "iterator", "()Ljava/util/Iterator;");
	if (iterator == nullptr) { return false; }
	jobject iter = Env->CallObjectMethod(set, iterator);
	if (iter == nullptr) { return false; }

	// Get the Iterator method IDs
	jclass clsIterator = Env->FindClass("java/util/Iterator");
	if (clsIterator == nullptr) { return false; }
	jmethodID hasNext = Env->GetMethodID(clsIterator, "hasNext", "()Z");
	if (hasNext == nullptr) { return false; }
	jmethodID next = Env->GetMethodID(clsIterator, "next", "()Ljava/lang/Object;");
	if (next == nullptr) { return false; }

	// Get the Entry class method IDs
	jclass clsEntry = Env->FindClass("java/util/Map$Entry");
	if (clsEntry == nullptr) { return false; }
	jmethodID getKey = Env->GetMethodID(clsEntry, "getKey", "()Ljava/lang/Object;");
	if (getKey == nullptr) { return false; }
	jmethodID getValue = Env->GetMethodID(clsEntry, "getValue", "()Ljava/lang/Object;");
	if (getValue == nullptr) { return false; }

	// Iterate over the entry Set
	while (Env->CallBooleanMethod(iter, hasNext))
	{
		jobject entry = Env->CallObjectMethod(iter, next);
		jstring jKey = (jstring) Env->CallObjectMethod(entry, getKey);
		jstring jValue = (jstring) Env->CallObjectMethod(entry, getValue);
		const char* c_key_string = Env->GetStringUTFChars(jKey, nullptr);
		if (!c_key_string)
		{	// Out of memory
			return false;
		}
		const char* c_value_string = Env->GetStringUTFChars(jValue, nullptr);
		if (!c_value_string)
		{	// Out of memory
			Env->ReleaseStringUTFChars(jKey, c_key_string);
			return false;
		}
		
		TMapOut.Add(FString(c_key_string), FString(c_value_string));

		Env->DeleteLocalRef(entry);
		Env->ReleaseStringUTFChars(jKey, c_key_string);
		Env->DeleteLocalRef(jKey);
		Env->ReleaseStringUTFChars(jValue, c_value_string);
		Env->DeleteLocalRef(jValue);
	}
	return true;
}

void AirbridgeJNI::SetMapString(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, const FString& Value)
{
	jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
	jstring jValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
	FJavaWrapper::CallObjectMethod(Env, HashMapObj, HashMapPutID, jKey, jValue);
	
	Env->DeleteLocalRef(jKey); jKey = NULL;
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::SetMapInteger(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, int32 Value)
{
	jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
	jobject jValue = MakeIntegerObject(Env, Value);
	FJavaWrapper::CallObjectMethod(Env, HashMapObj, HashMapPutID, jKey, jValue);
				
	Env->DeleteLocalRef(jKey); jKey = NULL;
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::SetMapNumber(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, double Value)
{
	jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
	jobject jValue = MakeNumberObject(Env, Value);
	FJavaWrapper::CallObjectMethod(Env, HashMapObj, HashMapPutID, jKey, jValue);
				
	Env->DeleteLocalRef(jKey); jKey = NULL;
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::SetMapBoolean(JNIEnv *Env, jobject HashMapObj, jmethodID HashMapPutID, const FString& Key, bool Value)
{
	jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
	jobject jValue = MakeBooleanObject(Env, Value);
	FJavaWrapper::CallObjectMethod(Env, HashMapObj, HashMapPutID, jKey, jValue);
				
	Env->DeleteLocalRef(jKey); jKey = NULL;
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::AddListString(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, const FString& Value)
{
	jstring jValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
	FJavaWrapper::CallBooleanMethod(Env, ArrayListObj, ArrayListAddID, jValue);
	
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::AddListInteger(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, int32 Value)
{
	jobject jValue = MakeIntegerObject(Env, Value);
	FJavaWrapper::CallBooleanMethod(Env, ArrayListObj, ArrayListAddID, jValue);
	
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::AddListNumber(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, double Value)
{
	jobject jValue = MakeNumberObject(Env, Value);
	FJavaWrapper::CallBooleanMethod(Env, ArrayListObj, ArrayListAddID, jValue);
	
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

void AirbridgeJNI::AddListBoolean(JNIEnv *Env, jobject ArrayListObj, jmethodID ArrayListAddID, bool Value)
{
	jobject jValue = MakeBooleanObject(Env, Value);
	FJavaWrapper::CallBooleanMethod(Env, ArrayListObj, ArrayListAddID, jValue);
	
	Env->DeleteLocalRef(jValue); jValue = NULL;
}

jobject AirbridgeJNI::MakeIntegerObject(JNIEnv *Env, int32 Value)
{
	jclass clazz = Env->FindClass("java/lang/Integer");
	jmethodID integerConstructID = Env->GetMethodID(clazz, "<init>", "(I)V");
	return Env->NewObject(clazz, integerConstructID, Value);
}

jobject AirbridgeJNI::MakeNumberObject(JNIEnv *Env, double Value)
{
	jmethodID numberConstructID = FJavaWrapper::FindMethod(Env, 
		FJavaWrapper::GameActivityClassID, 
		"airbridgeToNumber", 
		"(D)Ljava/lang/Number;", 
		false);
	return FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, numberConstructID, Value);
}

jobject AirbridgeJNI::MakeBooleanObject(JNIEnv *Env, bool Value)
{
	jclass clazz = Env->FindClass("java/lang/Boolean");
	jmethodID booleanConstructID = Env->GetMethodID(clazz, "<init>", "(Z)V");
	return Env->NewObject(clazz, booleanConstructID, Value);
}

#endif