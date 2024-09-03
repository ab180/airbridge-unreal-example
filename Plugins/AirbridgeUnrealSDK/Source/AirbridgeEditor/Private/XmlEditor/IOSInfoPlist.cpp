// Copyright © 2023 ab180. All rights reserved.

#include "IOSInfoPlist.h"
#include "Logger/AirbridgeLogger.h"

#if WITH_EDITOR

FIOSInfoPlist::FIOSInfoPlist(const FString& Filename): XmlDoc(false)
{
	XmlDoc.LoadFile(TCHAR_TO_ANSI(*Filename));

	// Finding element named "iosPListUpdates"
	tinyxml2::XMLElement *RootElement = XmlDoc.FirstChildElement();
	tinyxml2::XMLElement *Element = RootElement->FirstChildElement();
	while (Element)
	{
		if (Element->Name() == IosPListUpdatesTag)
		{
			XmlIosPListUpdates = Element;
			break;
		}
		Element = Element->NextSiblingElement();
	}
}

void FIOSInfoPlist::SetDeeplink(const FString& URIScheme, const FString& UniversalLinks)
{
	if (URIScheme.IsEmpty() && UniversalLinks.IsEmpty())
	{
		return;
	}

	tinyxml2::XMLElement *DictElement = XmlDoc.NewElement(AddElementsTag);
	DictElement->SetAttribute(TagAttrKey, DictTag);
	XmlIosPListUpdates->InsertFirstChild(DictElement);

	tinyxml2::XMLElement *Element = XmlDoc.NewElement(KeyTag);
	Element->SetText(CFBundleURLTypes);
	DictElement->InsertFirstChild(Element);

	tinyxml2::XMLElement *ArrayElement = XmlDoc.NewElement(ArrayTag);
	DictElement->InsertEndChild(ArrayElement);

	DictElement = XmlDoc.NewElement(DictTag);
	ArrayElement->InsertFirstChild(DictElement);

	if (!URIScheme.IsEmpty())
	{
		Element = XmlDoc.NewElement(KeyTag);
		Element->SetText(CFBundleURLSchemes);
		DictElement->InsertFirstChild(Element);

		ArrayElement = XmlDoc.NewElement(ArrayTag);
		DictElement->InsertEndChild(ArrayElement);

		Element = XmlDoc.NewElement(StringTag);
		Element->SetText(TCHAR_TO_ANSI(*URIScheme));
		ArrayElement->InsertFirstChild(Element);
	}

	if (!UniversalLinks.IsEmpty())
	{
		Element = XmlDoc.NewElement(KeyTag);
		Element->SetText(CFBundleURLName);
		DictElement->InsertEndChild(Element);

		Element = XmlDoc.NewElement(StringTag);
		Element->SetText(TCHAR_TO_ANSI(*UniversalLinks));
		DictElement->InsertEndChild(Element);
	}
}

bool FIOSInfoPlist::Save(const FString& Filename) const
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
			return true;	// Successfully saved
		}
		else
		{
			UE_LOG(LogAirbridge, Error, TEXT("Something broken while update ios app setting file."));
		}
	}
	else
	{
		UE_LOG(LogAirbridge, Error, TEXT("Can not write to file because it was not found."));
		UE_LOG(LogAirbridge, Error, TEXT("Expected file location: %s"), *Filename);
	}
	return false;
}

#endif