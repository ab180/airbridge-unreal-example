// Copyright © 2023 ab180. All rights reserved.

#include "Airbridge/Container/AirbridgeMap.h"

#include "Airbridge/Container/AirbridgeList.h"
#include "Utils/NumberUtils.h"
#if PLATFORM_ANDROID
#include "Platforms/Android/Util/AirbridgeJNI.h"
#endif

UAirbridgeMap* UAirbridgeMap::CreateObject()
{
	return NewObject<UAirbridgeMap>(GetTransientPackage(), StaticClass());
}

UAirbridgeMap* UAirbridgeMap::CreateObject(const TSharedPtr<FJsonObject> JsonObject)
{
	UAirbridgeMap* AirbridgeMap = CreateObject();
	if (JsonObject.IsValid())
	{
		for (const auto& Element : JsonObject->Values)
		{
			TSharedPtr<FJsonValue> JsonValue = Element.Value;
			if (JsonValue.IsValid())
			{
				AirbridgeMap->Set(Element.Key, JsonValue.Get());
			}
		}	
	}
	return AirbridgeMap;
}
	
UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const FString& Value)
{
	this->MapOfString.Emplace(Key, Value);
	return this;
}

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const char* Value)
{
	return Set(Key, FString(Value));
}

#if PLATFORM_TCHAR_IS_CHAR16
UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const char16_t* Value)
{
	return Set(Key, FString(Value));
}
#else
UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const wchar_t* Value)
{
	return Set(Key, FString(Value));
}
#endif

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const int32 Value)
{
	this->MapOfInteger.Emplace(Key, Value);
	return this;
}

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const double Value)
{
	this->MapOfNumber.Emplace(Key, Value);
	return this;
}

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const bool Value)
{
	this->MapOfBoolean.Emplace(Key, Value);
	return this;
}

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, UAirbridgeList* Value)
{
	this->MapOfList.Emplace(Key, Value);
	return this;
}

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, UAirbridgeMap* Value)
{
	this->MapOfMap.Emplace(Key, Value);
	return this;
}

UAirbridgeMap* UAirbridgeMap::Set(const FString& Key, const FJsonValue* Value)
{
	switch (Value->Type)
	{
	case EJson::String:
		return Set(Key, Value->AsString());
	case EJson::Number:	// support int32 and double
		if (NumberUtils::IsConvertibleToInt32(Value->AsNumber()))
			return Set(Key, static_cast<int32>(Value->AsNumber()));	// int32
		else
			return Set(Key, Value->AsNumber());	// double
	case EJson::Boolean:
		return Set(Key, Value->AsBool());
	case EJson::Array:
		return Set(Key, UAirbridgeList::CreateObject(Value->AsArray()));
	case EJson::Object:
		return Set(Key, CreateObject(Value->AsObject()));
	default:	// EJson::None or EJson::Null
		break;
	}
	return this;
}

UAirbridgeMap* UAirbridgeMap::SetString(const FString& Key, const FString& Value)
{
	return Set(Key, Value);
}

UAirbridgeMap* UAirbridgeMap::SetInteger(const FString& Key, const int32 Value)
{
	return Set(Key, Value);
}

UAirbridgeMap* UAirbridgeMap::SetFloat(const FString& Key, const float Value)
{
	return Set(Key, static_cast<double>(Value));
}

UAirbridgeMap* UAirbridgeMap::SetBoolean(const FString& Key, const bool Value)
{
	return Set(Key, Value);
}

UAirbridgeMap* UAirbridgeMap::SetList(const FString& Key, UAirbridgeList* Value)
{
	return Set(Key, Value);
}

UAirbridgeMap* UAirbridgeMap::SetMap(const FString& Key, UAirbridgeMap* Value)
{
	return Set(Key, Value);
}

#if PLATFORM_ANDROID
void* UAirbridgeMap::CreateJavaObject() const
{
	jobject jHashMap = NULL;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jclass hashMapClazz = Env->FindClass("java/util/HashMap");
		jmethodID hashMapConstructID = Env->GetMethodID(hashMapClazz, "<init>", "()V");
		jmethodID hashMapPutID = Env->GetMethodID(hashMapClazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

		jHashMap = Env->NewObject(hashMapClazz, hashMapConstructID);
		
		if (MapOfString.Num() != 0)
		{
			for (auto& Element : MapOfString)
			{
				AirbridgeJNI::SetMapString(Env, jHashMap, hashMapPutID, Element.Key, Element.Value);
			}
		}
		if (MapOfInteger.Num() != 0)
		{
			for (auto& Element : MapOfInteger)
			{
				AirbridgeJNI::SetMapInteger(Env, jHashMap, hashMapPutID, Element.Key, Element.Value);
			}
		}
		if (MapOfNumber.Num() != 0)
		{
			for (auto& Element : MapOfNumber)
			{
				AirbridgeJNI::SetMapNumber(Env, jHashMap, hashMapPutID, Element.Key, Element.Value);
			}
		}
		if (MapOfBoolean.Num() != 0)
		{
			for (auto& Element : MapOfBoolean)
			{
				AirbridgeJNI::SetMapBoolean(Env, jHashMap, hashMapPutID, Element.Key, Element.Value);
			}
		}
		if (MapOfList.Num() != 0)
		{
			for (auto& Element : MapOfList)
			{
				if (jobject jValue = (jobject) Element.Value->CreateJavaObject())
				{
					jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Element.Key));
					FJavaWrapper::CallObjectMethod(Env, jHashMap, hashMapPutID, jKey, jValue);
				
					Env->DeleteLocalRef(jKey); jKey = NULL;
					Env->DeleteLocalRef(jValue); jValue = NULL;
				}
			}
		}
		if (MapOfMap.Num() != 0)
		{
			for (auto& Element : MapOfMap)
			{
				if (jobject jValue = (jobject) Element.Value->CreateJavaObject())
				{
					jstring jKey = Env->NewStringUTF(TCHAR_TO_UTF8(*Element.Key));
					FJavaWrapper::CallObjectMethod(Env, jHashMap, hashMapPutID, jKey, jValue);
				
					Env->DeleteLocalRef(jKey); jKey = NULL;
					Env->DeleteLocalRef(jValue); jValue = NULL;
				}
			}
		}
	}
	return jHashMap;
}
#elif PLATFORM_IOS
NSDictionary * UAirbridgeMap::ConvertToNSDictionary() const
{
    NSMutableDictionary *mutableDictionary = [NSMutableDictionary dictionary];
    if (MapOfString.Num() != 0)
    {
        for (auto& Element : MapOfString)
        {
            [mutableDictionary setObject:Element.Value.GetNSString() forKey:Element.Key.GetNSString()];
        }
    }
    if (MapOfInteger.Num() != 0)
    {
        for (auto& Element : MapOfInteger)
        {
            NSNumber* object = [[NSNumber alloc] initWithInt:Element.Value];
            [mutableDictionary setObject:object forKey:Element.Key.GetNSString()];
        }
    }
    if (MapOfNumber.Num() != 0)
    {
        for (auto& Element : MapOfNumber)
        {
            NSNumber* object = [[NSNumber alloc] initWithDouble:Element.Value];
            [mutableDictionary setObject:object forKey:Element.Key.GetNSString()];
        }
    }
    if (MapOfBoolean.Num() != 0)
    {
        for (auto& Element : MapOfBoolean)
        {
            NSNumber* object = [[NSNumber alloc] initWithBool:Element.Value];
            [mutableDictionary setObject:object forKey:Element.Key.GetNSString()];
        }
    }
    if (MapOfList.Num() != 0)
    {
        for (auto& Element : MapOfList)
        {
            [mutableDictionary setObject:Element.Value->ConvertToNSArray() forKey:Element.Key.GetNSString()];
        }
    }
	if (MapOfMap.Num() != 0)
	{
		for (auto& Element : MapOfMap)
		{
			[mutableDictionary setObject:Element.Value->ConvertToNSDictionary() forKey:Element.Key.GetNSString()];
		}
	}
    NSDictionary *dictionary = [NSDictionary dictionaryWithDictionary:mutableDictionary];
    return dictionary;
}
#endif