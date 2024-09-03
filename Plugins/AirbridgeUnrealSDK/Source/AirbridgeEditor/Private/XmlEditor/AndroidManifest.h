// Copyright © 2023 ab180. All rights reserved.

#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "ThirdParty/tinyxml/tinyxml2.h"

class FAndroidManifest
{
private:
	const FString AndroidManifestUpdatesTag = "androidManifestUpdates";
	const FString AddPermissionTag = "addPermission";
	const FString AddElementsTag = "addElements";
	const FString LoopElementsTag = "loopElements";
	const FString ApplicationTag = "application";
	const FString ActivityTag = "activity";
	const FString MetadataTag = "meta-data";
	const FString ContentProviderTag = "provider";
	const FString IntentFilterTag = "intent-filter";

	const FString ActionTag = "action";
	const FString CategoryTag = "category";
	const FString DataTag = "data";

	const FString TagAttrKey = "tag";
	const FString NameAttrKey = "android:name";
	const FString ValueAttrKey = "android:value";
	const FString AuthoritiesAttrKey = "android:authorities";
	const FString ExportedAttrKey = "android:exported";

	const FString AutoVerifyAttrKey = "android:autoVerify";
	const FString HostAttrKey = "android:host";
	const FString SchemeAttrKey = "android:scheme";
	const FString PathAttrKey = "android:path";

public:
	FAndroidManifest(const FString& Filename);
	~FAndroidManifest() = default;
	
	void SetPermission(const char* Permission);

	void SetAppMetadata(const char* Name, const char* Value);
	void SetAppMetadata(const FString& Name, const FString& Value);
	void SetAppMetadata(const FString& Name, const bool Value);
	void SetAppMetadata(const FString& Name, const int32 Value);

	void SetContentProvider(const char* Name, const char* Authorities, const bool Exported);
	
	void SetUEGameActivityIntentFilter(const bool AutoVerify, const char* Action, const TArray<FString>& Categories,
		const char* Scheme, const char* Host = "", const char* Path = "");
	
	void Save(const FString& Filename) const;

private:
	bool IsEqual(const char* CStringA, const char* CStringB);
	
private:
	tinyxml2::XMLDocument XmlDoc;
	
	tinyxml2::XMLElement *XmlAndroidManifestUpdates = nullptr;
	tinyxml2::XMLElement *XmlAddApplicationElements = nullptr;
	tinyxml2::XMLElement *XmlLoopActivityElements = nullptr;
	TArray<tinyxml2::XMLElement*> XmlPermissions;
	TArray<tinyxml2::XMLElement*> XmlMetaData;
	TArray<tinyxml2::XMLElement*> XmlGameActivities;
};

#endif