// root1d.h - One dimensional root finding
#pragma once
#include <algorithm>
//#include <functional>
#include <limits>
#include <deque>

namespace fms {

	// next approximation
	namespace step1d {

		template<class X = double>
		inline X bisect(X x0, X x1)
		{
			return (x0 + x1)/2;
		}
		template<class X = double>
		inline X newton(X x0, X y0, X m)
		{
			return x0 - y0/m;
		}
		template<class X = double>
		inline X secant(X x0, X y0, X x1, X y1)
		{
			ensure (y1 != y0);

			return (x0*y1 - x1*y0)/(y1 - y0);
		}
		template<class X = double>
		inline X inverse_quadratic(X x0, X y0, X x1, X y1, X x2, X y2)
		{
			X dy0 = y1 - y2;
			X dy1 = y2 - y0;
			X dy2 = y0 - y1;

			ensure (dy0 != 0);
			ensure (dy1 != 0);
			ensure (dy2 != 0);

			return x0*y1*y2/(dy1*dy2) + x1*y2*y0/(dy2*dy0) + x2*y0*y1/(dy0*dy1);
		}
	} // step1d

	template<class X>
	class root1d {
	public:
		std::function<X(const X&)> f, df;
		std::deque<X> x;
		std::deque<X> y;
		root1d(const std::function<X(const X&)>& _f)
			: f(_f)
		{ }
		root1d(const std::function<X(const X&)>& _f, const std::function<X(const X&)>& _df)
			: f(_f), df(_df)
		{ }
		root1d(const root1d&) = default;
		root1d& operator=(const root1d&) = default;
		~root1d()
		{ }

		size_t size() const
		{
			ensure (x.size() == y.size());

			return x.size();
		}
		void clear()
		{
			x.clear();
			y.clear();
		}

		void push(X x0, X y0 = std::numeric_limits<X>::quiet_NaN())
		{
			x.push_front(x0);
			if (_isnan(y0))
				y0 = f(x0);
			y.push_front(y0);
		}

		bool bracketed() const
		{
			return y.size() < 2 ? false : y[0]*y[1] < 0;
		}
		
		// returns abcissa
		const X& bracket()
		{
			ensure (size() > 0);

			if (bracketed())
				return x[0];

			if (interval(std::numeric_limits<X>::epsilon()))
				return x[0];

			ensure (size() > 1);

			if (fabs(y[0]) < fabs(y[1]))
				push(2*x[0] - x[1]);
			else
				push(2*x[1] - x[0]);

			if (y[1] != y[2]) {
				// maybe secant is better
				X x_ = step1d::secant(x[1], y[1], x[2], y[2]);
				X y_ = f(x_);

				if (fabs(y_) < fabs(y[0])) {
					x[0] = x_;
					y[0] = y_;
				}
			}

			return bracket();
		}
		const X& bracket(const X& x0, const X& dx)
		{
			push (x0);

			X yp = f(x[0] + dx);
			X ym = f(x[0] - dx);

			if (fabs(yp) < fabs(ym))
				push(x[0] + dx, yp);
			else
				push(x[0] - dx, ym);

			ensure (size() > 1);

			return bracket();
		}

		//
		// convergence criteria
		//

		// for roots near 0
		bool interval(const X& abs, X rel = 0) const
		{
			ensure (size() > 1);

			X min_ = x[0]*x[1] < 0 ? 0 : (std::min)(fabs(x[0]), fabs(x[1]));

			return fabs(x[0] - x[1]) < abs + rel*min_; 
		}
		// test abscissa
		bool delta(const X& abs, X rel = 0) const
		{
			ensure (size() > 1);

			return fabs(x[0] - x[1]) < abs + rel*x[0];
		}
		// test ordinant
		bool residual(X eps) const
		{
			ensure (size() > 0);

			return eps ? fabs(y[0]) < eps : 1 + y[0] == 1;
		}

		//
		// next approximation
		//

		void bisect()
		{
			ensure (bracketed());
			ensure (size() > 1);

			push(step1d::bisect(x[0], x[1]));

			if (!bracketed()) {
				std::swap(x[1], x[2]);
				std::swap(y[1], y[2]);

				ensure (bracketed());
			}
		}
		void newton(const X& m = 0)
		{
			ensure (size() > 0);
			ensure (m || df);

			push(step1d::newton(x[0], y[0], m ? m : df(x[0]))); 
		}
		void secant()
		{
			ensure (size() > 1);

			push(step1d::secant(x[0], y[0], x[1], y[1]));
		}
		void inverse_quadratic()
		{
			ensure (size() > 2);

			push(step1d::inverse_quadratic(x[0], y[0], x[1], y[1], x[2], y[2]));
		}
		/*
		// done
		// step
		const X& brent()
		{
			return 0;
		}
		*/

	}; // root1d
} // fms