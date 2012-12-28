// bisection.h - bisection method of finding roots
// Copyright (c) 2012-2013 KALX, LLC. All rights reserved. No warranty is made
#pragma once
#include "root.h"

namespace root {
namespace _1d {

	template<class T, class F>
	inline T bisect_(T x0, T x1, const F& f, typename root::ulp_traits<T>::integer ulps, size_t& iter)
	{
		T f0 = f(x0);
		T f1 = f(x1);
		T x = (x0 + x1)/2;
		T fx = f(x);
	
		while (iter-- && ulp(x, x0) > ulps && ulp(x1, x) > ulps) {

			if (same_sign(f0, f1))
				return error_nan<T>(ROOT_SAME_SIGN);

			if (same_sign(f0, fx)) {
				x0 = x;
				f0 = fx;
			}
			else {
				x1 = x;
				f1 = fx;
			}

			x = (x0 + x1)/2;
			fx = f(x);
		}

		return ulp(x, x0) <= ulps ? x0 : x1;
	}

	template<class T, class F>
	inline T bisect(T x0, T x1, const F& f, typename root::ulp_traits<T>::integer ulps = 0, size_t iter = std::numeric_limits<size_t>::max())
	{
		return bisect_(x0, x1, f, ulps, iter);
	}

} // namespace _1d
} // namespace root