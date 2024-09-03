// Copyright © 2023 ab180. All rights reserved.

#include "NumberUtils.h"

bool NumberUtils::IsConvertibleToInt32(const double Value)
{
	const int32 Int32Value = static_cast<int32>(Value);
	return (Value == static_cast<double>(Int32Value));
}

bool NumberUtils::IsConvertibleToInt64(const double Value)
{
	const int64 Int64Value = static_cast<int64>(Value);
	return (Value == static_cast<double>(Int64Value));
}