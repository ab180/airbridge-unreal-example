// Copyright © 2023 ab180. All rights reserved.

#include "Airbridge/AirbridgeEventOption.h"
#if PLATFORM_ANDROID
#include "Platforms/Android/Util/AirbridgeJNI.h"
#endif

UAirbridgeEventOption* UAirbridgeEventOption::CreateObject()
{
	return NewObject<UAirbridgeEventOption>(GetTransientPackage(), StaticClass());
}
	
UAirbridgeEventOption* UAirbridgeEventOption::SetAction(const FString& Action)
{
	this->Action = Action;
	return this;
}

UAirbridgeEventOption* UAirbridgeEventOption::SetLabel(const FString& Label)
{
	this->Label = Label;
	return this;
}

UAirbridgeEventOption* UAirbridgeEventOption::SetValue(const double Value)
{
	this->Value = Value;
	return this;
}

UAirbridgeEventOption* UAirbridgeEventOption::SetValue(const float Value)
{
	return SetValue(static_cast<double>(Value));
}

UAirbridgeEventOption* UAirbridgeEventOption::SetCustomAttributes(UAirbridgeMap* CustomAttributes)
{
	this->CustomAttributes = CustomAttributes;
	return this;
}

UAirbridgeEventOption* UAirbridgeEventOption::SetSemanticAttributes(UAirbridgeMap* SemanticAttributes)
{
	this->SemanticAttributes = SemanticAttributes;
	return this;
}

#if PLATFORM_ANDROID
void* UAirbridgeEventOption::CreateJavaObject(const FString& Category) const
{
	jobject airbridgeEvent = NULL;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jclass airbridgeEventClass = FAndroidApplication::FindJavaClass("co/ab180/airbridge/event/Event");
		jmethodID airbridgeEventConstructor = Env->GetMethodID(airbridgeEventClass, "<init>", "(Ljava/lang/String;)V");
		
		jstring jCategory = Env->NewStringUTF(TCHAR_TO_UTF8(*Category));
		airbridgeEvent = Env->NewObject(airbridgeEventClass, airbridgeEventConstructor, jCategory);

		AirbridgeJNI::SetString(airbridgeEventClass, airbridgeEvent, "setAction", Action);
		AirbridgeJNI::SetString(airbridgeEventClass, airbridgeEvent, "setLabel", Label);
		AirbridgeJNI::SetNumber(airbridgeEventClass, airbridgeEvent, "setValue", Value);
		
		if (CustomAttributes != nullptr)
		{
			jmethodID setCustomAttributesMethod = FJavaWrapper::FindMethod(Env,
				FJavaWrapper::GameActivityClassID,
				"airbridgeSetCustomAttributes",
				"(Lco/ab180/airbridge/event/Event;Ljava/util/HashMap;)V", false);
			if (jobject customAttributes = (jobject) CustomAttributes->CreateJavaObject())
			{
				FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis,
					setCustomAttributesMethod, airbridgeEvent, customAttributes);
			}
		}
		if (SemanticAttributes != nullptr)
		{
			jmethodID setSemanticAttributesMethod = FJavaWrapper::FindMethod(Env,
				FJavaWrapper::GameActivityClassID,
				"airbridgeSetSemanticAttributes",
				"(Lco/ab180/airbridge/event/Event;Ljava/util/HashMap;)V", false);
			if (jobject semanticAttributes = (jobject) SemanticAttributes->CreateJavaObject())
			{
				FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis,
					setSemanticAttributesMethod, airbridgeEvent, semanticAttributes);
			}
		}
	}
	return airbridgeEvent;
}
#endif