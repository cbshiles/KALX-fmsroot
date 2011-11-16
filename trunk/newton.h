// newton.h - Newton method of finding roots.
#pragma once
#include <array>
#include "root.h"
#include "quadratic.h"

namespace root {
namespace _1d {

	template<class T>
	inline T newton(const T& x, const T& f, const T& df)
	{
		return x - f/df;
	}

	template<class T>
	inline T newton(const T& x, const T& f, T df, const T& ddf)
	{
		T a = ddf/2;
		T b = df - x*ddf;
		T c = f - x*df + x*x*ddf/2;

		return same_sign(f, df) ? quadratic(a, b, c).second : quadratic(a, b, c).first;
	}
	template<class T>
	inline T newton(const T& x, const T* f)
	{
		T a = f[2]/2;
		T b = f[1] - x*f[2];
		T c = f[0] - x*f[1] + x*x*f[2]/2;

		return same_sign(f, df) ? quadratic(a, b, c).second : quadratic(a, b, c).first;
	}
	// for use with dual numbers
	template<class T>
	inline T newton_2(const T& x, const T* f)
	{
		T a = f[2]/2;
		T b = f[1] - x*f[2];
		T c = f[0] - x*f[1] + x*x*f[2];

		return same_sign(f, df) ? quadratic(a, b, c).second : quadratic(a, b, c).first;
	}

} // namespace _1d
} // namespace root