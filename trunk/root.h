// root.h - Root finding routines.
// Copyright (c) 2012 KALX, LLC. All rights reserved. No warranty is made.
// Returns NaN with embedded error code on failure.
// Use method_ to pass references to get details of root finding method.
// Use method to pick up recommended default values.
#pragma once
#include <cmath>
#include <limits>
#include "error_nan.h"
#include "ulp.h"

namespace root {

	// possbile error codes for rootfinding functions
	enum root_error_code {
		ROOT_SAME_SIGN = 1, // must start with bracketed values
	};

	// recommended value for difference quotient denominator
	template<class T>
	inline T sqrt_epsilon(const T& x = 1)
	{
		return sqrt(x*std::numeric_limits<T>::epsilon());
	}

	template<class T>
	inline bool same_sign(const T& x, const T& y)
	{
		return x == _copysign(x, y);
	}

} // namespace root