// secant.h - secant method of finding roots
#pragma once
#include <array>
#include "root.h"

namespace root {
namespace _1d {

	template<class T>
	inline std::array<point<T>,2> secant(const std::function<T(T)>& f, const std::array<point<T>,2>& ab)
	{
		T a = ab[0].x;
		T fa = ab[0].y;
		T b = ab[1].x;
		T fb = ab[1].y;
		T c = b - fb*(b - a)/(fb - fa);
		T fc = f(c);

		std::array<point<T>,2> bc_ = {point<T>(b,fb),point<T>(c,fc)};
		
		return bc_;
	}

} // namespace _1d
} // namespace root