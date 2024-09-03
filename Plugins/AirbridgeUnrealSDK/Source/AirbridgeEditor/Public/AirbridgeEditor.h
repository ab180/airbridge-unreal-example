// Copyright © 2023 ab180. All rights reserved.

#pragma once

class FSlateStyleSet;

class FAirbridgeEditor : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	bool PluginStyleImplemented = false;
	TSharedPtr<FSlateStyleSet> PluginStyle;
	TSharedPtr<FUICommandList> PluginCommands;
	TSharedPtr<FExtender> ToolBarExtender;
	TSharedPtr<const FExtensionBase> Extension;

	void UpdateAndroidManifest() const;
	void UpdateIOSAppSetting() const;
	
	void AddToolbarButton(FToolBarBuilder& Builder) const;
	void ToolbarButtonOnClick() const;
	
	bool SetupPluginStyle();
};
