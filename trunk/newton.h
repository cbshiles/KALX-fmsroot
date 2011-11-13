// newton.h - Newton method of finding roots.
#pragma once
#include <array>
#include "root.h"
#include "quadratic.h"

namespace root {
namespace _1d {

	template<class T>
	inline T newton(T x, T f, T df)
	{
		return x - f/df;
	}

	template<class T>
	inline T newton(T x, T f, T df, T ddf)
	{
		T a = ddf/2;
		T b = df - x*ddf;
		T c = f - x*df + x*x*ddf/2;

		return same_sign(f, df) ? quadratic(a, b, c).second : quadratic(a, b, c).first;
	}

} // namespace _1d
} // namespace root