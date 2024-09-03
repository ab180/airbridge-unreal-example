// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeWebInterface.h"

#include "AirbridgeUnreal.h"
#include "Airbridge/AirbridgePrivateConstants.h"
#include "Utils/NumberUtils.h"

//////////////////////////////////////////////////////////////////////////
// AirbridgeWebInterfaceDefault

const FString AirbridgeWebInterfaceDefault::GetScript() { return TEXT(""); }

void AirbridgeWebInterfaceDefault::Handle(const FString& Message)
{
}

//////////////////////////////////////////////////////////////////////////
// AirbridgeWebInterfaceImpl

AirbridgeWebInterfaceImpl* AirbridgeWebInterfaceImpl::Init(
	const FString& InWebToken, const AirbridgePostCommandFunction& InPostCommandFunction
)
{
	WebToken = InWebToken;
	PostCommandFunction = InPostCommandFunction;

	return this;
}

const FString AirbridgeWebInterfaceImpl::GetScript()
{
	constexpr int32 JsonSchemaVersion = 4;
	const FString SdkVersion = "1.3.6";

	return FString::Printf(
		TEXT(
			"AirbridgeNative = { };\n"
			"AirbridgeNative.postCommand = function (argument) {\n"
			"    %s\n"
			"};\n"
			"AirbridgeNative.getWebToken = function () {\n"
			"    return \"%s\";\n"
			"};\n"
			"AirbridgeNative.getJsonSchemaVersion = function () {\n"
			"    return %d;\n"
			"};\n"
			"AirbridgeNative.getSdkVersion = function () {\n"
			"    return \"%s\";\n"
			"};\n"
			"AirbridgeNative.setUser = function (payload) {\n"
			"    AirbridgeNative.postCommand(JSON.stringify({\n"
			"        method: \"setUser\"\n,"
			"        payload: payload\n"
			"    }))\n"
			"};\n"
			"AirbridgeNative.clearUser = function () {\n"
			"    AirbridgeNative.postCommand(JSON.stringify({\n"
			"        method: \"clearUser\"\n,"
			"        payload: { }\n"
			"    }))\n"
			"};\n"
			"AirbridgeNative.trackEvent = function (payload) {\n"
			"    AirbridgeNative.postCommand(JSON.stringify({\n"
			"        method: \"trackEvent\"\n,"
			"        payload: payload\n"
			"    }))\n"
			"};\n"
		),
		*PostCommandFunction("argument"),
		*WebToken,
		JsonSchemaVersion,
		*SdkVersion
	);
}

void AirbridgeWebInterfaceImpl::Handle(const FString& Message)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();

	TSharedPtr<FJsonValue> JsonValue = nullptr;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		// Return if method is not defined
		if (!JsonObject->HasField(AirbridgeConstants::Hybrid::Method)) return;

		FString PayloadString;

		const FString Method = JsonObject->GetStringField(AirbridgeConstants::Hybrid::Method);

		/** Set User */
		if (Method.Equals(AirbridgeConstants::Hybrid::SetUserMethod))
		{
			// Return if payload is not defined
			if (!JsonObject->HasField(AirbridgeConstants::Hybrid::Payload)) return;
			PayloadString = JsonObject->GetStringField(AirbridgeConstants::Hybrid::Payload);
			Reader = TJsonReaderFactory<>::Create(PayloadString);
			if (!(FJsonSerializer::Deserialize(Reader, Payload) && Payload.IsValid())) return;
			
			// Set User ID
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::UserIdKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				FAirbridgeUnreal::SetUserID(Payload->GetStringField(AirbridgeConstants::Hybrid::UserIdKey));
			}

			// Set User Email
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::UserEmailKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				FAirbridgeUnreal::SetUserEmail(Payload->GetStringField(AirbridgeConstants::Hybrid::UserEmailKey));
			}

			// Set User Phone Number
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::UserPhoneKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				FAirbridgeUnreal::SetUserPhone(Payload->GetStringField(AirbridgeConstants::Hybrid::UserPhoneKey));
			}

			// Set User Alias
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::UserAliasKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				const TSharedPtr<FJsonObject> Alias = Payload->GetObjectField(
					AirbridgeConstants::Hybrid::UserAliasKey);
				if (Alias.IsValid())
				{
					for (const auto& Element : Alias->Values)
					{
						FString FieldName = Element.Key;
						TSharedPtr<FJsonValue> FieldValue = Element.Value;
						if (FieldValue.IsValid() && FieldValue->Type == EJson::String)
						{
							FAirbridgeUnreal::SetUserAlias(FieldName, FieldValue->AsString());
						}
					}
				}
			}

			// Set User Attributes
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::UserAttributesKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				const TSharedPtr<FJsonObject> Attributes = Payload->GetObjectField(
					AirbridgeConstants::Hybrid::UserAttributesKey);
				if (Attributes.IsValid())
				{
					for (const auto& Element : Attributes->Values)
					{
						FString FieldName = Element.Key;
						TSharedPtr<FJsonValue> FieldValue = Element.Value;
						if (FieldValue.IsValid())
						{
							switch (FieldValue->Type)
							{
							case EJson::String:
								FAirbridgeUnreal::SetUserAttribute(FieldName, FieldValue->AsString());
								break;
							case EJson::Number:
								if (NumberUtils::IsConvertibleToInt64(FieldValue->AsNumber()))
								{
									if (NumberUtils::IsConvertibleToInt32(FieldValue->AsNumber()))
										FAirbridgeUnreal::SetUserAttribute(
											FieldName, static_cast<int32>(FieldValue->AsNumber()));
									else
										FAirbridgeUnreal::SetUserAttribute(
											FieldName, static_cast<int64>(FieldValue->AsNumber()));
								}
								else
								{
									// Convert a double to a float
									// be aware of the potential loss of precision when converting between data types
									FAirbridgeUnreal::SetUserAttribute(
										FieldName, static_cast<float>(FieldValue->AsNumber()));
								}
								break;
							case EJson::Boolean:
								FAirbridgeUnreal::SetUserAttribute(FieldName, FieldValue->AsBool());
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
		/** Clear User */
		else if (Method.Equals(AirbridgeConstants::Hybrid::ClearUserMethod))
		{
			FAirbridgeUnreal::ClearUser();
		}
		/** Track Event */
		else if (Method.Equals(AirbridgeConstants::Hybrid::TrackEventMethod))
		{
			// Return if payload is not defined
			if (!JsonObject->HasField(AirbridgeConstants::Hybrid::Payload)) return;
			PayloadString = JsonObject->GetStringField(AirbridgeConstants::Hybrid::Payload);
			Reader = TJsonReaderFactory<>::Create(PayloadString);
			if (!(FJsonSerializer::Deserialize(Reader, Payload) && Payload.IsValid())) return;

			// Return if event category is not defined
			if (!Payload->HasField(AirbridgeConstants::Hybrid::EventCategoryKey)) return;

			UAirbridgeEventOption* AirbridgeEventOption = UAirbridgeEventOption::CreateObject();

			// Set Action
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::EventActionKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				AirbridgeEventOption->SetAction(Payload->GetStringField(AirbridgeConstants::Hybrid::EventActionKey));
			}

			// Set Label
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::EventLabelKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				AirbridgeEventOption->SetLabel(Payload->GetStringField(AirbridgeConstants::Hybrid::EventLabelKey));
			}

			// Set Value
			JsonValue = Payload->TryGetField(AirbridgeConstants::Hybrid::EventValueKey);
			if (JsonValue != nullptr && !JsonValue->IsNull())
			{
				AirbridgeEventOption->SetValue(Payload->GetNumberField(AirbridgeConstants::Hybrid::EventValueKey));
			}

			// Set Semantic Attributes
			if (Payload->HasField(AirbridgeConstants::Hybrid::EventSemanticAttributesKey))
			{
				const TSharedPtr<FJsonObject>* SemanticAttributes;
				if (Payload->TryGetObjectField(AirbridgeConstants::Hybrid::EventSemanticAttributesKey,
				                               /*out*/ SemanticAttributes)
					&& SemanticAttributes->IsValid())
				{
					AirbridgeEventOption->SetSemanticAttributes(
						UAirbridgeMap::CreateObject(*SemanticAttributes));
				}
			}

			// Set Custom Attributes
			if (Payload->HasField(AirbridgeConstants::Hybrid::EventCustomAttributesKey))
			{
				const TSharedPtr<FJsonObject>* CustomAttributes;
				if (Payload->TryGetObjectField(AirbridgeConstants::Hybrid::EventCustomAttributesKey,
				                               /*out*/ CustomAttributes)
					&& CustomAttributes->IsValid())
				{
					AirbridgeEventOption->SetCustomAttributes(
						UAirbridgeMap::CreateObject(*CustomAttributes));
				}
			}

			// Track Event
			FAirbridgeUnreal::TrackEvent(Payload->GetStringField(AirbridgeConstants::Hybrid::EventCategoryKey),
			                             AirbridgeEventOption);
		}
	}
}
