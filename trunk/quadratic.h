// quadratic.h - Real roots of a x^2 + b x + c = 0
#pragma once
#include <array>
#include "root.h"

namespace root {
namespace _1d {

	template<class T>
	inline std::pair<T,T> quadratic(T a, T b, T c)
	{
		T x0, x1;
		T one(static_cast<T>(1));
		T half(static_cast<T>(0.5));

		x0 = x1 = std::numeric_limits<T>::quiet_NaN();

		if (a == 0 && b != 0) {
			x0 = -c/b;
		}
		else {
			T d = b*b - 4*a*c;
			if (d > 0) {
				if (b == 0) {
					T r = fabs(sqrt(d)/(2*a));
					x0 = -r;
					x1 = r;
				}
				else {
					T s = b > 0 ? one : -one;
					T t = -half * (b + s*sqrt(d));
					T r1 = t/a;
					T r2 = c/t;
					if (r1 < r2) {
						x0 = r1;
						x1 = r2;
					}
					else {
						x0 = r2;
						x1 = r1;
					}
				}
			}
			else if (d == 0) {
				x0 = -half*b/a;
			}
		}

		return std::make_pair(x0, x1);
	}

} // namespace _1d
} // namespace root