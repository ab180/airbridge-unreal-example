// Copyright © 2023 ab180. All rights reserved.

#include "Airbridge/Container/AirbridgeList.h"

#include "Airbridge/Container/AirbridgeMap.h"
#include "Utils/NumberUtils.h"
#if PLATFORM_ANDROID
#include "Platforms/Android/Util/AirbridgeJNI.h"
#endif

UAirbridgeList* UAirbridgeList::CreateObject()
{
	return NewObject<UAirbridgeList>(GetTransientPackage(), StaticClass());
}

UAirbridgeList* UAirbridgeList::CreateObject(const TArray<TSharedPtr<FJsonValue>>& JsonArray)
{
	UAirbridgeList* AirbridgeList = CreateObject();
	for (auto& JsonValue : JsonArray)
	{
		if (JsonValue.IsValid())
		{
			AirbridgeList->Add(JsonValue);
		}
	}
	return AirbridgeList;
}

UAirbridgeList* UAirbridgeList::Add(const FString& Value)
{
	this->ArrayOfString.Emplace(Value);
	return this;
}

UAirbridgeList* UAirbridgeList::Add(const char* Value)
{
	return Add(FString(Value));
}

#if PLATFORM_TCHAR_IS_CHAR16
UAirbridgeList* UAirbridgeList::Add(const char16_t* Value)
{
	return Add(FString(Value));
}
#else
UAirbridgeList* UAirbridgeList::Add(const wchar_t* Value)
{
	return Add(FString(Value));
}
#endif

UAirbridgeList* UAirbridgeList::Add(const int32 Value)
{
	this->ArrayOfInteger.Emplace(Value);
	return this;
}

UAirbridgeList* UAirbridgeList::Add(const double Value)
{
	this->ArrayOfNumber.Emplace(Value);
	return this;
}

UAirbridgeList* UAirbridgeList::Add(const bool Value)
{
	this->ArrayOfBoolean.Emplace(Value);
	return this;
}

UAirbridgeList* UAirbridgeList::Add(UAirbridgeList* Value)
{
	this->ArrayOfList.Emplace(Value);
	return this;
}

UAirbridgeList* UAirbridgeList::Add(UAirbridgeMap* Value)
{
	this->ArrayOfMap.Emplace(Value);
	return this;
}

UAirbridgeList* UAirbridgeList::Add(TSharedPtr<FJsonValue> Value)
{
	switch (Value->Type)
	{
	case EJson::String:
		return Add(Value->AsString());
	case EJson::Number:	// support int32 and double
		if (NumberUtils::IsConvertibleToInt32(Value->AsNumber()))
			return Add(static_cast<int32>(Value->AsNumber()));	// int32
		else
			return Add(Value->AsNumber());	// double
		case EJson::Boolean:
			return Add(Value->AsBool());
	case EJson::Array:
		return Add(CreateObject(Value->AsArray()));
	case EJson::Object:
		return Add(UAirbridgeMap::CreateObject(Value->AsObject()));
	default:	// EJson::None or EJson::Null
		break;
	}
	return this;
}

UAirbridgeList* UAirbridgeList::AddString(const FString& Value)
{
	return Add(Value);
}

UAirbridgeList* UAirbridgeList::AddInteger(const int32 Value)
{
	return Add(Value);
}

UAirbridgeList* UAirbridgeList::AddFloat(const float Value)
{
	return Add(static_cast<double>(Value));
}

UAirbridgeList* UAirbridgeList::AddBoolean(const bool Value)
{
	return Add(Value);
}

UAirbridgeList* UAirbridgeList::AddList(UAirbridgeList* Value)
{
	return Add(Value);
}
	
UAirbridgeList* UAirbridgeList::AddMap(UAirbridgeMap* Value)
{
	return Add(Value);
}

#if PLATFORM_ANDROID
void* UAirbridgeList::CreateJavaObject() const
{
	jobject jArrayList = NULL;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jclass arrayListClazz = Env->FindClass("java/util/ArrayList");
		jmethodID arrayListConstructID = Env->GetMethodID(arrayListClazz, "<init>", "()V");
		jmethodID arrayListAddID = Env->GetMethodID(arrayListClazz, "add", "(Ljava/lang/Object;)Z");

		jArrayList = Env->NewObject(arrayListClazz, arrayListConstructID);
		
		if (ArrayOfString.Num() != 0)
		{
			for (auto& Element : ArrayOfString)
			{
				AirbridgeJNI::AddListString(Env, jArrayList, arrayListAddID, Element);
			}
		}
		if (ArrayOfInteger.Num() != 0)
		{
			for (auto& Element : ArrayOfInteger)
			{
				AirbridgeJNI::AddListInteger(Env, jArrayList, arrayListAddID, Element);
			}
		}
		if (ArrayOfNumber.Num() != 0)
		{
			for (auto& Element : ArrayOfNumber)
			{
				AirbridgeJNI::AddListNumber(Env, jArrayList, arrayListAddID, Element);
			}
		}
		if (ArrayOfBoolean.Num() != 0)
		{
			for (auto& Element : ArrayOfBoolean)
			{
				AirbridgeJNI::AddListBoolean(Env, jArrayList, arrayListAddID, Element);
			}
		}
		if (ArrayOfList.Num() != 0)
		{
			for (auto& Element : ArrayOfList)
			{
				if (jobject jElement = (jobject) Element->CreateJavaObject())
				{
					FJavaWrapper::CallBooleanMethod(Env, jArrayList, arrayListAddID, jElement);
					Env->DeleteLocalRef(jElement); jElement = NULL;
				}
			}
		}
		if (ArrayOfMap.Num() != 0)
		{
			for (auto& Element : ArrayOfMap)
			{
				if (jobject jElement = (jobject) Element->CreateJavaObject())
				{
					FJavaWrapper::CallBooleanMethod(Env, jArrayList, arrayListAddID, jElement);
					Env->DeleteLocalRef(jElement); jElement = NULL;
				}
			}
		}
	}
	return jArrayList;
}
#elif PLATFORM_IOS
NSArray * UAirbridgeList::ConvertToNSArray() const
{
	NSMutableArray *mutableArrayList = [NSMutableArray array];
	if (ArrayOfString.Num() != 0)
	{
		for (auto& Element : ArrayOfString)
		{
			[mutableArrayList addObject:Element.GetNSString()];
		}
	}
	if (ArrayOfInteger.Num() != 0)
	{
		for (auto& Element : ArrayOfInteger)
		{
			NSNumber* object = [[NSNumber alloc] initWithInt:Element];
			[mutableArrayList addObject:object];
		}
	}
	if (ArrayOfNumber.Num() != 0)
	{
		for (auto& Element : ArrayOfNumber)
		{
			NSNumber* object = [[NSNumber alloc] initWithDouble:Element];
			[mutableArrayList addObject:object];
		}
	}
	if (ArrayOfBoolean.Num() != 0)
	{
		for (auto& Element : ArrayOfBoolean)
		{
			NSNumber* object = [[NSNumber alloc] initWithBool:Element];
			[mutableArrayList addObject:object];
		}
	}
	if (ArrayOfList.Num() != 0)
	{
		for (auto& Element : ArrayOfList)
		{
			[mutableArrayList addObject:Element->ConvertToNSArray()];
		}
	}
	if (ArrayOfMap.Num() != 0)
	{
		for (auto& Element : ArrayOfMap)
		{
			[mutableArrayList addObject:Element->ConvertToNSDictionary()];
		}
	}
	NSArray *arrayList = [NSArray arrayWithArray:mutableArrayList];
	return arrayList;
}
#endif