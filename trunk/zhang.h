// zhang.h - Zhangs modification of the Brent method
// http://cscjournals.org/csc/manuscript/Journals/IJEA/volume2/Issue1/IJEA-7.pdf
// Copyright (c) 2012 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "root.h"
#include "newton.h"
#include "secant.h"

namespace root {
namespace _1d {

	template<class T, class F>
	inline T zhang_(T& x0, T& x1, const F& f, typename root::ulp_traits<T>::integer ulps, size_t& iter)
	{
		while (iter-- && ulp(x1, x0) > ulps) {
			T x, x_, f0, f1, fx, fx_;

			f0 = f(x0);
			f1 = f(x1);
			if (same_sign(f0, f1))
				return error_nan(ROOT_SAME_SIGN);

			x = (x0 + x1)/2;
			fx = f(x);
			if (f0 != fx && f1 != fx) {
				x_ = inverse_quadratic(x0, x1, x, f0, f1, fx);
			}
			else {
				x_ = inverse_secant(x0, x1, f0, f1);
			}
			fx_ = f(x_);
			if (x > x_)
				std::swap(x, x_);
			if (same_sign(fx, fx_)) {
				if (same_sign(fx_, f1))
					x1 = x_;
				else
					x0 = x;
			}
			else {
				x0 = x_;
				x1 = x;
			}
		}

		return x1;
	}

	template<class T, class F>
	inline T zhang(T& x0, T& x1, const F& f, typename root::ulp_traits<T>::integer ulps = 0, size_t iter = std::numeric_limits<size_t>::max())
	{
		return zhang_(x0, x1, f, ulps, iter);
	}

} // namespace _1d
} // namespace root
