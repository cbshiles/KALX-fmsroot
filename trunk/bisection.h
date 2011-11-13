// bisection.h - bisection method of finding roots
#pragma once
#include <array>
#include "root.h"

namespace root {
namespace _1d {

	template<class T>
	inline std::array<point<T>,2> bisect(const std::function<T(T)>& f, const std::array<point<T>,2>& ab)
	{
		T a = ab[0].x;
		T fa = ab[0].y;
		T b = ab[1].x;
		T fb = ab[1].y;

		ensure (!same_sign(fa, fb));

		T c = (a + b)/2;
		T fc = f(c);

		if (same_sign(fa, fc)) {
			a = c;
			fa = fc;
		}
		else {
			b = c;
			fb = fc;
		}

		std::array<point<T>,2> ab_ = {point<T>(a,fa),point<T>(b,fb)};
		
		return ab_;
	}

} // namespace _1d
} // namespace root