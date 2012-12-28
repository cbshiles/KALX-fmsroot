// bracket.h - bracket a root
// Copyright (c) 2012-2013 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "root.h"

namespace root {
namespace _1d {

	// bracket root and return slope
	template<class T, class F>
	inline T bracket_(T& x0, T& x1, const F& f, T& a, size_t& iter)
	{
		T dx = x1 - x0;
		T f0 = f(x0);
		T f1 = f(x1);

		while (iter-- && same_sign(f0, f1)) {

			if (same_sign(f1 - f0, f0)) {
				if (a == 0) {
					a = (f1 - f0)/f0;
					a = a < 1.6 ? static_cast<T>(.6) : 1/a;
				}
				x1 = x0;
				f1 = f0;
				x0 = x0 - a*dx;
				f0 = f(x0);
			}
			else {
				if (a == 0) {
					a = (f0 - f1)/f1;
					a = a < 1.6 ? static_cast<T>(.6) : 1/a;
				}
				x0 = x1;
				f0 = f1;
				x1 = x1 + a*dx;
				f1 = f(x1);
			}

			dx = x1 - x0;
		}
		
		return (f1 - f0)/dx;
	}

	template<class T, class F>
	inline T bracket(T& x0, T& x1, const F& f, T a = 0, size_t iter = std::numeric_limits<size_t>::max())
	{
		return bracket_(x0, x1, f, a, iter);
	}

} // namespace _1d
} // namespace root