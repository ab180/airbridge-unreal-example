// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "AirbridgeUnreal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AirbridgeBlueprint.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UAirbridgeBlueprint : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

#pragma region USER
	
	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserID(const FString& Id);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserEmail(const FString& Email);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserPhone(const FString& PhoneNumber);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserIntAttribute(const FString& Key, const int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserLongAttribute(const FString& Key, const int64 Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserFloatAttribute(const FString& Key, const float Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserBooleanAttribute(const FString& Key, const bool Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserStringAttribute(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void RemoveUserAttribute(const FString& Key);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void ClearUserAttributes();

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void SetUserAlias(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void RemoveUserAlias(const FString& Key);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void ClearUserAlias();

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|User")
	static void ClearUser();

#pragma endregion USER

#pragma region EVENT
	
	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Event")
	static void TrackEvent(
		UPARAM(DisplayName = "Category") const FString& EventCategory,
		const UAirbridgeEventOption* EventOption = nullptr
	);

#pragma endregion EVENT

#pragma region PLACEMENT

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Placement")
	static void Click(const FString& TrackingLink);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Placement")
	static void Impression(const FString& TrackingLink);

#pragma endregion PLACEMENT

#pragma region CALLBACK

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Callback")
	static void SetDeeplinkCallback();

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Callback")
	static void SetAttributionCallback();

#pragma endregion CALLBACK

#pragma region DEVICE

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Device")
	static void SetDeviceAlias(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Device")
	static void RemoveDeviceAlias(const FString& Key);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Device")
	static void ClearDeviceAlias();

#pragma endregion DEVICE

#pragma region ADVANCED

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Advanced")
	static void StartTracking();

	UFUNCTION(BlueprintCallable, Category = "Airbridge Unreal SDK|Advanced")
	static void RegisterPushToken(const FString& Token);

#pragma endregion ADVANCED
};
