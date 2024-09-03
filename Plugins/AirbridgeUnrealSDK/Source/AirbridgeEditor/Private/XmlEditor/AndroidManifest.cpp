// Copyright © 2023 ab180. All rights reserved.

#include "AndroidManifest.h"
#include "Logger/AirbridgeLogger.h"

#if WITH_EDITOR

FAndroidManifest::FAndroidManifest(const FString& Filename): XmlDoc(false)
{
	XmlDoc.LoadFile(TCHAR_TO_ANSI(*Filename));

	// Finding element named "androidManifestUpdates"
	tinyxml2::XMLElement *RootElement = XmlDoc.FirstChildElement();
	tinyxml2::XMLElement *Element = RootElement->FirstChildElement();
	while (Element)
	{
		if (Element->Name() == AndroidManifestUpdatesTag)
		{
			XmlAndroidManifestUpdates = Element;
			break;
		}
		Element = Element->NextSiblingElement();
	}
	if (!XmlAndroidManifestUpdates)
	{
		return;
	}
	
	Element = XmlAndroidManifestUpdates->FirstChildElement();
	while (Element)
	{
		// Finding element named "addPermission"
		if (Element->Name() == AddPermissionTag)
		{
			XmlPermissions.Emplace(Element);
		}

		// Finding element named "addElements" with tag "application"
		if ((Element->Name() == AddElementsTag) && (Element->Attribute(TCHAR_TO_ANSI(*TagAttrKey)) == ApplicationTag))
		{
			XmlAddApplicationElements = Element;
		}

		// Finding element named "loopElements" with tag "activity"
		if ((Element->Name() == LoopElementsTag) && (Element->Attribute(TCHAR_TO_ANSI(*TagAttrKey)) == ActivityTag))
		{
			XmlLoopActivityElements = Element;
		}
		
		Element = Element->NextSiblingElement();
	}
	if (!XmlAddApplicationElements || !XmlLoopActivityElements)
	{
		return;
	}

	// Finding element named "meta-data"
	Element = XmlAddApplicationElements->FirstChildElement();
	while (Element)
	{
		if (Element->Name() == MetadataTag)
		{
			XmlMetaData.Emplace(Element);
		}
		Element = Element->NextSiblingElement();
	}

	// Finding element named "loopElements" with tag "$"
	//<if condition="...">
	//    <true>
	//        <addElements tag="$">
	//            ...
	//        </addElements>
	//    </true>
	//</if>
	Element = XmlLoopActivityElements->FirstChildElement();
	while (Element)
	{
		if (IsEqual(Element->Name(), "if"))
		{
			if (Element->FirstChildElement()->FirstChildElement()->Name() == AddElementsTag)
			{
				XmlGameActivities.Emplace(Element->FirstChildElement()->FirstChildElement());
			}
		}
		Element = Element->NextSiblingElement();
	}
}

void FAndroidManifest::SetPermission(const char* Permission)
{
	for (const auto& XmlPermission : XmlPermissions)
	{
		if (IsEqual(XmlPermission->Attribute(TCHAR_TO_ANSI(*NameAttrKey)), Permission))
		{
			return;
		}
	}
	
	tinyxml2::XMLElement *Element = XmlDoc.NewElement(TCHAR_TO_ANSI(*AddPermissionTag));
	Element->SetAttribute(TCHAR_TO_ANSI(*NameAttrKey), Permission);
	XmlAndroidManifestUpdates->InsertEndChild(Element);
}

void FAndroidManifest::SetAppMetadata(const char* Name, const char* Value)
{
	for (const auto& XmlMetaDatum : XmlMetaData)
	{
		if (IsEqual(XmlMetaDatum->Attribute(TCHAR_TO_ANSI(*NameAttrKey)), Name))
		{
			XmlMetaDatum->SetAttribute(TCHAR_TO_ANSI(*ValueAttrKey), Value);
			return;
		}
	}

	tinyxml2::XMLElement *Element = XmlDoc.NewElement(TCHAR_TO_ANSI(*MetadataTag));
	Element->SetAttribute(TCHAR_TO_ANSI(*NameAttrKey), Name);
	Element->SetAttribute(TCHAR_TO_ANSI(*ValueAttrKey), Value);
	XmlAddApplicationElements->InsertEndChild(Element);
}

void FAndroidManifest::SetAppMetadata(const FString& Name, const FString& Value)
{
	SetAppMetadata(TCHAR_TO_ANSI(*Name), TCHAR_TO_ANSI(*Value));
}
void FAndroidManifest::SetAppMetadata(const FString& Name, const bool Value)
{
	SetAppMetadata(TCHAR_TO_ANSI(*Name), Value ? "true" : "false");
}
void FAndroidManifest::SetAppMetadata(const FString& Name, const int32 Value)
{
	const FString IntAsString = FString::FromInt(Value);
	SetAppMetadata(TCHAR_TO_ANSI(*Name), TCHAR_TO_ANSI(*IntAsString));
}

void FAndroidManifest::SetContentProvider(const char* Name, const char* Authorities, const bool Exported)
{
	tinyxml2::XMLElement *Element = XmlAddApplicationElements->FirstChildElement();
	while (Element)
	{
		if (Element->Name() == ContentProviderTag)
		{
			if (IsEqual(Element->Attribute(TCHAR_TO_ANSI(*NameAttrKey)), Name))
			{
				Element->SetAttribute(TCHAR_TO_ANSI(*AuthoritiesAttrKey), Authorities);
				Element->SetAttribute(TCHAR_TO_ANSI(*ExportedAttrKey), Exported ? "true" : "false");
				return;
			}
		}
		Element = Element->NextSiblingElement();
	}
	
	Element = XmlDoc.NewElement(TCHAR_TO_ANSI(*ContentProviderTag));
	Element->SetAttribute(TCHAR_TO_ANSI(*NameAttrKey), Name);
	Element->SetAttribute(TCHAR_TO_ANSI(*AuthoritiesAttrKey), Authorities);
	Element->SetAttribute(TCHAR_TO_ANSI(*ExportedAttrKey), Exported ? "true" : "false");
	XmlAddApplicationElements->InsertEndChild(Element);
}

void FAndroidManifest::SetUEGameActivityIntentFilter(
	const bool AutoVerify, const char* Action, const TArray<FString>& Categories,
	const char* Scheme, const char* Host, const char* Path)
{
	if (IsEqual(Scheme, ""))
	{
		return;
	}

	for (const auto& XmlGameActivity : XmlGameActivities)
	{
		tinyxml2::XMLElement *IntentFilterElement = XmlDoc.NewElement(TCHAR_TO_ANSI(*IntentFilterTag));
		IntentFilterElement->SetAttribute(TCHAR_TO_ANSI(*AutoVerifyAttrKey), AutoVerify ? "true" : "false");
	
		tinyxml2::XMLElement *Element = XmlDoc.NewElement(TCHAR_TO_ANSI(*ActionTag));
		Element->SetAttribute(TCHAR_TO_ANSI(*NameAttrKey), Action);
		IntentFilterElement->InsertEndChild(Element);

		for (const auto& Category : Categories)
		{
			Element = XmlDoc.NewElement(TCHAR_TO_ANSI(*CategoryTag));
			Element->SetAttribute(TCHAR_TO_ANSI(*NameAttrKey), TCHAR_TO_ANSI(*Category));
			IntentFilterElement->InsertEndChild(Element);
		}

		Element = XmlDoc.NewElement(TCHAR_TO_ANSI(*DataTag));
		Element->SetAttribute(TCHAR_TO_ANSI(*SchemeAttrKey), Scheme);
		if (!IsEqual(Host, ""))
		{
			Element->SetAttribute(TCHAR_TO_ANSI(*HostAttrKey), Host);
		}
		if (!IsEqual(Path, ""))
		{
			Element->SetAttribute(TCHAR_TO_ANSI(*PathAttrKey), Path);
		}
		IntentFilterElement->InsertEndChild(Element);

		XmlGameActivity->InsertEndChild(IntentFilterElement);
	}
}

void FAndroidManifest::Save(const FString& Filename) const
{
	tinyxml2::XMLPrinter Printer;
	XmlDoc.Print(&Printer);
	
	FString StringToWrite(Printer.CStr());

	// Use FileManager to deal with the file.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	
	// Always first check if the file that you want to manipulate exist.
	if (FileManager.FileExists(*Filename))
	{
		if (FFileHelper::SaveStringToFile(StringToWrite, *Filename))
		{
			UE_LOG(LogAirbridge, Display, TEXT("Updated AndroidManifest.xml"));
		}
		else
		{
			UE_LOG(LogAirbridge, Error, TEXT("Something broken while creating android manifest file."));
		}
	}
	else
	{
		UE_LOG(LogAirbridge, Error, TEXT("Can not write to file because it was not found."));
		UE_LOG(LogAirbridge, Error, TEXT("Expected file location: %s"), *Filename);
	}
}

bool FAndroidManifest::IsEqual(const char* CStringA, const char* CStringB)
{
	const FString FStringA(CStringA);
	const FString FStringB(CStringB);
	return  FStringA == FStringB;
}

#endif