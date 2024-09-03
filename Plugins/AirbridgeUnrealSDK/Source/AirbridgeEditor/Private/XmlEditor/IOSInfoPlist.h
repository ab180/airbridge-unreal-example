// Copyright © 2023 ab180. All rights reserved.

#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "ThirdParty/tinyxml/tinyxml2.h"

class FIOSInfoPlist
{
private:
	const FString IosPListUpdatesTag = "iosPListUpdates";
	
	const char* AddElementsTag = "addElements";
	const char* DictTag = "dict";
	const char* ArrayTag = "array";
	const char* KeyTag = "key";
	const char* StringTag = "string";

	const char* TagAttrKey = "tag";

	const char* CFBundleURLTypes = "CFBundleURLTypes";
	const char* CFBundleURLSchemes = "CFBundleURLSchemes";
	const char* CFBundleURLName = "CFBundleURLName";
	
public:
	FIOSInfoPlist(const FString& Filename);
	~FIOSInfoPlist() = default;
	
	void SetDeeplink(const FString& URIScheme, const FString& UniversalLinks);
	bool Save(const FString& Filename) const;

private:
	tinyxml2::XMLDocument XmlDoc;
	tinyxml2::XMLElement *XmlIosPListUpdates = nullptr;
};

#endif