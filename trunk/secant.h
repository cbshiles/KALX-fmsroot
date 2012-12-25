// secant.h - secant method of finding roots
#pragma once
#include <array>
#include "root.h"

namespace root {
namespace _1d {

	template<class T>
	inline T inverse_secant(T x0, T x1, T y0, T y1)
	{
		return x1 - y1*(x1 - x0)/(y1 - y0);
	}

	template<class T, class F>
	inline T secant_(T& x0, T& x1, const F& f, typename root::ulp_traits<T>::integer ulps, size_t& iter)
	{
		T f0 = f(x0);
		T f1 = f(x1);

		while (iter-- && ulp(x1, x0) >= ulps && abs(ulp(y1, 0)) >= ulps) {
			T x = inverse_secant(x0, x1, f0, f1);
			x0 = x1;
			f0 = f1;
			x1 = x;
			f1 = f(x1);
		}

		return x1;
	}

	template<class T, class F>
	inline T secant(T& x0, T& x1, const F& f, typename root::ulp_traits<T>::integer ulps = 0, size_t iter = std::numeric_limits<size_t>::max())
	{
		return secant_(x0, x1, f, ulps, iter);
	}

} // namespace _1d
} // namespace root