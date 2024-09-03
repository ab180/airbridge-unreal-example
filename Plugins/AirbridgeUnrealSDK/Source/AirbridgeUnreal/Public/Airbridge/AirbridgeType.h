// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Wrapper Classes for Null-Handling
 *
 *	Supported data types:
 *							- FString
 *							- int32
 *							- double
 *							- bool
 */
template <typename T>
class AIRBRIDGEUNREAL_API FAirbridgeType
{
public:
	FAirbridgeType() = default;
	FAirbridgeType(const T& Value) { Set(Value); }
	
	FAirbridgeType& operator=(const T& Value)
	{
		Set(Value);
		return *this;
	}

	operator T() const { return _Value; }
	
	const T& Get() const { return _Value; }
	
	bool NonNull() const { return _NonNull; }

#if PLATFORM_IOS
	NSString* GetNSString() const
	{
		static_assert(std::is_same<T, FString>::value, "[FAirbridgeType] T must be a string type");
		if (_NonNull)
		{
			return _Value.GetNSString();
		}
		return nil;
	}

	NSNumber* GetNSNumber() const
	{
		const bool IsInt32 = std::is_same<T, int32>::value;
		const bool IsDouble = std::is_same<T, double>::value;
		const bool IsBool = std::is_same<T, bool>::value;
		
		static_assert(IsInt32 || IsDouble || IsBool,
			"[FAirbridgeType] T must be a numeric type (e.g. int32, double, bool)");
		
		if (IsInt32 && _NonNull)
			return [[NSNumber alloc] initWithInt:_Value];
		if (IsDouble && _NonNull)
			return [[NSNumber alloc] initWithDouble:_Value];
		if (IsBool && _NonNull)
			return [[NSNumber alloc] initWithBool:_Value];
		return nil;
	}
#endif

private:
	void Set(const T& Value)
	{
		this->_Value = Value;
		this->_NonNull = true;
	}
	
	T _Value;
	bool _NonNull = false;
};