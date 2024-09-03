// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeEditor.h"

#include "AirbridgeCommands.h"
#include "AirbridgeSettings.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "Logger/AirbridgeLogger.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "XmlEditor/AndroidManifest.h"
#include "XmlEditor/IOSInfoPlist.h"

#define LOCTEXT_NAMESPACE			"FAirbridgeEditorModule"
#define TEXT_AIRBRIDGE_MODULE		TEXT("AirbridgeUnrealSDK")
#define TEXT_ANDROID_UPL_SRC		TEXT("AirbridgeUnrealSDK/Source/AirbridgeEditor/Template/Airbridge_UPL_Android.xml")
#define TEXT_ANDROID_UPL_DEST		TEXT("AirbridgeUnrealSDK/Source/AirbridgeUnreal/Airbridge_UPL_Android.xml")
#define TEXT_IOS_UPL_SRC			TEXT("AirbridgeUnrealSDK/Source/AirbridgeEditor/Template/Airbridge_UPL_iOS.xml")
#define TEXT_IOS_UPL_DEST			TEXT("AirbridgeUnrealSDK/Source/AirbridgeUnreal/Airbridge_UPL_iOS.xml")
#define TEXT_IOS_SETTING			TEXT("AirbridgeUnrealSDK/Source/AirbridgeUnreal/Private/Platforms/iOS/Native/AUAppSetting.h")

void FAirbridgeEditor::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project", "Plugins", "AirbridgeSettings",
			LOCTEXT("RuntimeSettingsName", "Airbridge Unreal SDK"),
			LOCTEXT("RuntimeSettingsDescription", "Configure bundle(plugin)"),
			GetMutableDefault<UAirbridgeSettings>());
	}

	/** Creating Airbridge Toolbar Button */
	FAirbridgeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FAirbridgeCommands::Get().AirbridgeCommand,
		FExecuteAction::CreateRaw(this, &FAirbridgeEditor::ToolbarButtonOnClick)
	);

	ToolBarExtender = MakeShareable(new FExtender);
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	Extension = ToolBarExtender->AddToolBarExtension(
		"Content",
		EExtensionHook::Before,
		PluginCommands,
		FToolBarExtensionDelegate::CreateRaw(this, &FAirbridgeEditor::AddToolbarButton)
	);
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);

	/** Add Custom Icons */
	PluginStyleImplemented = SetupPluginStyle();
	if (PluginStyleImplemented)
	{
		FSlateStyleRegistry::RegisterSlateStyle(*PluginStyle);
	}
}

void FAirbridgeEditor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AirbridgeSettings");
	}
}

void FAirbridgeEditor::UpdateAndroidManifest() const
{
	const FString MetaDataPrefix = "airbridge==";
	
	const FString AndroidUPLSrcPath = FPaths::ProjectPluginsDir().Append(TEXT_ANDROID_UPL_SRC);
	const FString AndroidUPLDestPath = FPaths::ProjectPluginsDir().Append(TEXT_ANDROID_UPL_DEST);

	FAndroidManifest *AndroidManifest = new FAndroidManifest(AndroidUPLSrcPath);

	const UAirbridgeSettings* PluginSettings = GetMutableDefault<UAirbridgeSettings>();
	
	AndroidManifest->SetPermission("android.permission.INTERNET");
	AndroidManifest->SetPermission("android.permission.ACCESS_NETWORK_STATE");
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.app_name", MetaDataPrefix + PluginSettings->AppName);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.app_token", MetaDataPrefix + PluginSettings->AppToken);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.sdk_signature_secret_id", MetaDataPrefix + PluginSettings->SdkSignatureSecretID);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.sdk_signature_secret", MetaDataPrefix + PluginSettings->SdkSignatureSecret);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.log_level", EAirbridgeLogLevelHelper::GetAndroidLogLevel(PluginSettings->LogLevel));
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.custom_domain", PluginSettings->CustomDomain);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.session_timeout_seconds", PluginSettings->SessionTimeoutSeconds);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.user_info_hash_enabled", PluginSettings->UserInfoHashEnabled);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.location_collection_enabled", PluginSettings->LocationCollectionEnabled);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.track_airbridge_link_only", PluginSettings->TrackAirbridgeLinkOnly);
	AndroidManifest->SetAppMetadata("co.ab180.airbridge.sdk.auto_start_tracking_enabled", PluginSettings->AutoStartTrackingEnabled);
	AndroidManifest->SetContentProvider("co.ab180.airbridge.ue.AirbridgeContentProvider", "${applicationId}.co.ab180.airbridge.ue.AirbridgeContentProvider", false);

	TArray<FString> IntentFilterCategories;
	IntentFilterCategories.Emplace(TEXT("android.intent.category.DEFAULT"));
	IntentFilterCategories.Emplace(TEXT("android.intent.category.BROWSABLE"));
	
	// "{http, https}://{appname}.airbridge.io" intent filter
	AndroidManifest->SetUEGameActivityIntentFilter(true,
		"android.intent.action.VIEW",
		IntentFilterCategories,
		"http",
		TCHAR_TO_ANSI(*(PluginSettings->AppName + ".airbridge.io"))
	);
	AndroidManifest->SetUEGameActivityIntentFilter(true,
			"android.intent.action.VIEW",
			IntentFilterCategories,
			"https",
			TCHAR_TO_ANSI(*(PluginSettings->AppName + ".airbridge.io"))
	);
	// "{http, https}://{appname}.deeplink.page" intent filter
	AndroidManifest->SetUEGameActivityIntentFilter(true,
	"android.intent.action.VIEW",
	IntentFilterCategories,
	"http",
	TCHAR_TO_ANSI(*(PluginSettings->AppName + ".deeplink.page"))
	);
	AndroidManifest->SetUEGameActivityIntentFilter(true,
			"android.intent.action.VIEW",
			IntentFilterCategories,
			"https",
			TCHAR_TO_ANSI(*(PluginSettings->AppName + ".deeplink.page"))
	);
	// "{custom scheme}://" intent filter
	if (PluginSettings->AndroidURIScheme != "")
	{
		AndroidManifest->SetUEGameActivityIntentFilter(false,
			"android.intent.action.VIEW",
			IntentFilterCategories,
			TCHAR_TO_ANSI(*PluginSettings->AndroidURIScheme)
		);
	}
	// "{http, https}://{custom domain}" intent filter
	if (PluginSettings->CustomDomain != "")
	{
		AndroidManifest->SetUEGameActivityIntentFilter(true,
			"android.intent.action.VIEW",
			IntentFilterCategories,
			"http",
			TCHAR_TO_ANSI(*PluginSettings->CustomDomain)
		);
		AndroidManifest->SetUEGameActivityIntentFilter(true,
				"android.intent.action.VIEW",
				IntentFilterCategories,
				"https",
				TCHAR_TO_ANSI(*PluginSettings->CustomDomain)
		);
	}
	
	AndroidManifest->Save(AndroidUPLDestPath);
	
	delete AndroidManifest;
}

void FAirbridgeEditor::UpdateIOSAppSetting() const
{
	const UAirbridgeSettings* PluginSettings = GetMutableDefault<UAirbridgeSettings>();

	// iOS UPL 파일 업데이트
	FIOSInfoPlist *IOSInfoPlist = new FIOSInfoPlist(FPaths::ProjectPluginsDir().Append(TEXT_IOS_UPL_SRC));
	IOSInfoPlist->SetDeeplink(PluginSettings->IOSURIScheme, PluginSettings->CustomDomain);
	bool isSuccess = IOSInfoPlist->Save(FPaths::ProjectPluginsDir().Append(TEXT_IOS_UPL_DEST));
	delete IOSInfoPlist;
	if (!isSuccess) { return; }

	// iOS Airbridge 옵션 설정 값 세팅
	FString Path = FPaths::ProjectPluginsDir().Append(TEXT_IOS_SETTING);
	
	const FString Content = FString("#ifndef AUAppSetting_h\n")
		+ "#define AUAppSetting_h\n"
		+ "\n"
		+ "static NSString* appName = @\"" + PluginSettings->AppName + "\";\n"
		+ "static NSString* appToken = @\"" + PluginSettings->AppToken + "\";\n"
		+ "static NSString* sdkSignatureSecretID = @\"" + PluginSettings->SdkSignatureSecretID + "\";\n"
		+ "static NSString* sdkSignatureSecret = @\"" + PluginSettings->SdkSignatureSecret + "\";\n"
		+ "static NSUInteger logLevel = " + FString::FromInt(EAirbridgeLogLevelHelper::GetIOSLogLevel(PluginSettings->LogLevel)) + ";\n"
		+ "static NSString* appScheme = @\"" + PluginSettings->IOSURIScheme + "\";\n"
		+ "static NSInteger sessionTimeoutSeconds = " + FString::FromInt(PluginSettings->SessionTimeoutSeconds) + ";\n"
		+ "static BOOL autoStartTrackingEnabled = " + (PluginSettings->AutoStartTrackingEnabled ? "true" : "false") + ";\n"
		+ "static BOOL userInfoHashEnabled = " + (PluginSettings->UserInfoHashEnabled ? "true" : "false") + ";\n"
		+ "static BOOL trackAirbridgeLinkOnly = " + (PluginSettings->TrackAirbridgeLinkOnly ? "true" : "false") + ";\n"
		+ "static NSInteger trackingAuthorizeTimeoutSeconds = " + FString::FromInt(PluginSettings->IOSTrackingAuthorizeTimeoutSeconds) + ";\n"
		+ "\n"
		+ "#endif\n";

	// Use FileManager to deal with the file.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	
	// Always first check if the file that you want to manipulate exist.
	if (FileManager.FileExists(*Path))
	{
		if (FFileHelper::SaveStringToFile(Content, *Path))
		{
			UE_LOG(LogAirbridge, Display, TEXT("Updated iOS Settings"));
		}
		else
		{
			UE_LOG(LogAirbridge, Error, TEXT("Something broken while update ios app setting file."));
		}
	}
	else
	{
		UE_LOG(LogAirbridge, Error, TEXT("Can not write to file because it was not found."));
		UE_LOG(LogAirbridge, Error, TEXT("Expected file location: %s"), *Path);
	}
}

void FAirbridgeEditor::AddToolbarButton(FToolBarBuilder& Builder) const
{
	const FSlateIcon IconBrush = FSlateIcon(
		PluginStyle->GetStyleSetName(),
		"Icon.AirbridgeUnrealSDK",
		"Icon.AirbridgeUnrealSDK.small"
	);
	
	Builder.AddToolBarButton(FAirbridgeCommands::Get().AirbridgeCommand,
		NAME_None,
		FText::FromString("Airbridge"),
		FText::FromString("Update iOS Setting & Update Android Manifest"),
		IconBrush,
		NAME_None); 
}

void FAirbridgeEditor::ToolbarButtonOnClick() const
{
	UpdateAndroidManifest();
	UpdateIOSAppSetting();
}

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush( PluginStyle->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

bool FAirbridgeEditor::SetupPluginStyle()
{
	FString RootDirectory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectPluginsDir() + TEXT_AIRBRIDGE_MODULE));
	
	// Is it in the project plugin folder?
	if (!FPaths::DirectoryExists(RootDirectory))
	{
		// No valid directory found, therefor no style will be registered or implemented
		return false;
	}
	
	// Create a new style set
	PluginStyle = MakeShareable(new FSlateStyleSet("AirbridgeUnrealSDKModuleStyle"));
		
	// Set the content Root directory of our plugin in order to access the images
	PluginStyle->SetContentRoot(RootDirectory);

	// Common sizes for icons and thumbnails
	const FVector2D Icon40x40(40.f, 40.f);
	const FVector2D Icon16x16(16.0f, 16.0f);

	// Set the images
	PluginStyle->Set("Icon.AirbridgeUnrealSDK", new IMAGE_BRUSH(TEXT("Resources/Icon40"), Icon40x40));
	PluginStyle->Set("Icon.AirbridgeUnrealSDK.small", new IMAGE_BRUSH(TEXT("Resources/Icon16"), Icon16x16));
	
	return true;
}

#undef IMAGE_BRUSH

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAirbridgeEditor, AirbridgeEditor)