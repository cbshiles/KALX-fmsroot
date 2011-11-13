// bracket.h - bracket a root
#pragma once
#include <array>
#include "root.h"

namespace root {
namespace _1d {

	template<class T>
	inline std::array<point<T>,2> bracket(const std::function<T(T)>& f, const std::array<point<T>,2>& ab)
	{
		T a = ab[0].x;
		T fa = ab[0].y;
		T b = ab[1].x;
		T fb = ab[1].y;
		T dx = b - a;

		ensure (dx > 0);
		ensure (same_sign(fa, fb));

		if ((fa > 0 && fa > fb) || (fa < 0 && fa < fb)) {
			a = b;
			fa = fb;
			b = b + 2*dx;
			fb = f(b);
		}
		else {
			b = a;
			fb = fa;
			a = a - 2*dx;
			fa = f(a);
		}

		std::array<point<T>,2> ab_ = {point<T>(a,fa),point<T>(b,fb)};
		
		return ab_;
	}

} // namespace _1d
} // namespace root