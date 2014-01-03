// root1d.h - One dimensional root finding
#pragma once
#include <algorithm>
#include <functional>
#include <limits>
#include <deque>

namespace fms {

	// next approximation
	namespace step1d {

		// a and b bracket 0
		template<class X = double>
		inline bool bracket0(const X& a, const X& b)
		{
			return std::signbit(a) != std::signbit(b);
		}

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
			ensure (x0 != x1);
			ensure (y1 != y0);

			return newton(x0, y0, (y1 - y0)/(x1 - x0));
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
		// y = (a - b x)/(1 + c x)
		template<class X = double>
		inline X hyperbola(X x0, X y0, X x1, X y1, X x2, X y2)
		{
			X dx0 = x1 - x2;
			X dx1 = x2 - x0;
			X dx2 = x0 - x1;

			return (x0*y1*y2*dx0 + x1*y2*y0*dx1 + x2*y0*y1*dx2)/(y1*y2*dx0 + y2*y0*dx1 + y0*y1*dx2);
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
		// push if better guess
		bool push(X x0, X y0 = std::numeric_limits<X>::quiet_NaN())
		{
			if (_isnan(y0))
				y0 = f(x0);

			if (size() == 0 || fabs(y0) < fabs(y[0])) {
				x.push_front(x0);
				y.push_front(y0);

				return true;
			}

			return false;
		}

		bool bracketed() const
		{
			return size() < 2 ? false : step1d::bracket0(y[0], y[1]);
		}


		//
		// convergence criteria
		//

		// for roots near 0
		bool interval(const X& abs, X rel = 0) const
		{
			X min_ = bracketed() ? 0 : (std::min)(fabs(x[0]), fabs(x[1]));

			return size() > 1 && fabs(x[0] - x[1]) < abs + rel*min_; 
		}
		// test abscissa
		bool delta(const X& abs, X rel = 0) const
		{
			return size() > 1 && fabs(x[0] - x[1]) < abs + rel*x[0];
		}
		// test ordinant
		bool residual(X eps) const
		{
			return size() > 0 && (eps ? fabs(y[0]) < eps : 1 + y[0] == 1);
		}

		//
		// next approximation
		//

		bool bisect()
		{
			ensure (bracketed());

			return push(step1d::bisect(x[0], x[1]));
		}
		bool newton(const X& m = 0)
		{
			return m ? push(step1d::newton(x[0], y[0], m)) : df ? push(step1d::newton(x[0], y[0], df(x[0]))) : false; 
		}
		bool secant()
		{
			return size() > 1 && push(step1d::secant(x[0], y[0], x[1], y[1]));
		}
		bool inverse_quadratic()
		{
			return size() > 2 && push(step1d::inverse_quadratic(x[0], y[0], x[1], y[1], x[2], y[2]));
		}
		bool hyperbola()
		{
			return size() > 2 && push(step1d::hyperbola(x[0], y[0], x[1], y[1], x[2], y[2]));
		}

		bool improve(X dx = 0)
		{
			bool better(false);

			if (dx == 0) {
				ensure (size() > 1);
				dx = (x[1] - x[0])/2;
			}

			if (bracketed()) {
				better = hyperbola() || newton() || secant() || bisect();
			}

			X yp = f(x[0] + dx);
			X ym = f(x[0] - dx);

			if (fabs(yp) < fabs(ym)) {
				better |= newton((yp - y[0])/dx);
				if (!better)
					better |= push(x[0] + dx, yp);
			}
			else {
				better |= newton((y[0] - ym)/dx);
				if (!better)
					better |= push(x[0] - dx, ym);
			}

			if (better) {
				ensure (fabs(x[0] - x[1]) <= dx || fabs(y[0]) < fabs(y[1]));
			}

			return better;
		}

		X solve(const X& x0, const X& dx, const std::function<bool()>& done)
		{
			ensure (push(x0));
			ensure (improve(dx));

			while (!done()) {
				ensure (improve());
			}

			return x[0];
		}
	}; // root1d
} // fms