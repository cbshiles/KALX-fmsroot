// error_nan.h - Embed error codes in NaNs
// Copyright (c) 2012 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include <limits>

template<class T>
inline T error_nan(char c1)
{
	union { T x; char c[sizeof(T)]; } xc;
	
	xc.x = std::numeric_limits<T>::quiet_NaN();
	xc.c[1] = c1;

	return xc.x;
}
template<class T>
inline char error_nan(T x)
{
	union { T x; char c[sizeof(T)]; } xc;

	xc.x = x;

	return xc.c[1];
}