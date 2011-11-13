// tnewton.cpp - test Newton root finding
#include "newton.h"
#include "../fmsdual/dual.h"

using namespace dual;
using namespace root::_1d;

template<class T>
void
fms_test_square_root(void)
{
	size_t n;
	T a = 2;
	std::function<T(T)> F = [a](T x) { return x*x - a; };
	T x(1), x_, f, df;

	n = 0;
	do {
		++n;
		f = F(x);
		df = 2*x;
		x_ = newton(x, f, df);
	} while (fabs(f) > sqrt(std::numeric_limits<T>::epsilon()) && (x = x_));

	x_ = newton<T>(1, F(1), 2, 2).second;
	ensure (fabs(F(x_)) < 10*std::numeric_limits<T>::epsilon());
}

void
fms_test_newton(void)
{
//	fms_test_square_root<float>();
	fms_test_square_root<double>();
}