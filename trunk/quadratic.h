// quadratic.h - Real roots of a x^2 + b x + c = 0
#pragma once
#include <cmath>
#include <utility>
#include "root.h"

namespace root {
namespace _1d {

	template<class T>
	inline std::pair<T,T> quadratic(T a, T b, T c)
	{
		T x0, x1;
		T d = b*b - 4*a*c;

		x0 = x1 = std::numeric_limits<T>::quiet_NaN();

		if (a == 0 && b != 0) {
			x0 = -b/c;
		}
		else {
			if (d > 0) {
				if (b == 0) {
					T r = static_cast<T>(fabs(0.5*sqrt(d)/a));
					x0 = -r;
					x1 = r;
				}
				else {
					T s = static_cast<T>(b > 0 ? 1 : -1);
					T t = static_cast<T>(-0.5 * (b + s*sqrt(d)));
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
				x0 = static_cast<T>(-0.5*b/a);
			}
		}

		return std::make_pair(x0, x1);
	}

	template<class T>
	inline T inverse_quadratic(T x0, T x1, T x2, T y0, T y1, T y2)
	{
		return x0*y1*y2/((y0 - y1)*(y0 - y2)) + x1*y2*y1/((y1 - y0)*(y1 - y2)) + x2*y0*y1/((y2 - y0)*(y2 - y1));
	}

} // namespace _1d
} // namespace root