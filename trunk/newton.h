// newton.h - Newton method of finding roots.
// Copyright (c) 2012 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "root.h"
#include "quadratic.h"

namespace root {
namespace _1d {

	// linear interpolation
	template<class T>
	inline T newton(T x, T f, T df)
	{
		return x - f/df;
	}
	// quadratic interpolation
	template<class T>
	inline T newton(T x, T f, T df, T ddf)
	{
		T a = ddf/2;
		T b = df - x*ddf;
		T c = f - x*df + x*x*ddf/2;

		return same_sign(f, df) ? quadratic(a, b, c).second : quadratic(a, b, c).first;
	}
	template<class T>
	inline T newton(T x, const T* f)
	{
		return newton(x, f[0], f[1], f[2]);
	}

	template<class T, class F, class dF>
	inline T newton_(T& x, const F& f, const dF& df, size_t& iter, typename root::ulp_traits<T>::integer ulps)
	{
		T x_(x);

		do {
			x = x_;
			x_ = newton(x, f(x), df(x));
		} while (iter-- && abs(ulp(x_, x)) > ulps);

		return x_;
	}
	template<class T, class F, class dF>
	inline T newton(T x, const F& f, const dF& df, size_t iter = std::numeric_limits<size_t>::max(), typename root::ulp_traits<T>::integer ulps = 0)
	{
		return newton_(x, f, df, iter, ulps);
	}

} // namespace _1d
} // namespace root