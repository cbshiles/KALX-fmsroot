// tnewton.cpp - test Newton root finding
#include "ensure.h"
#include "newton.h"
//#include "../fmsdual/dual.h"

//using namespace dual;
using namespace root::_1d;

template<class T>
void test_newton(void)
{
	T eps = std::numeric_limits<T>::epsilon();
	T x = 1, x_;
	T a = 2., b = 3.;

	auto f = [a,b](T x) { return a + b*x; };
	x_ = newton(2*a, f(2*a), b);
	ensure (fabs(x_ + a/b) <= 2*eps);

	auto F = [](T x) { return x*x - 2; };
	auto dF = [](T x) { return 2*x; };
	size_t iter = 10;

	x_ = newton(2*a, F(2*a), dF(2*a), a);
	ensure (fabs(x_ - sqrt(2.)) <= eps);

	x_ = newton_(x, F, dF, iter, 10); // oscillates if ulps = 0
	ensure (fabs(x_ - sqrt(2.)) <= eps);

	x = 5;
	x_ = newton(x, F, dF, 100, 2); // oscillates if ulps = 0
	ensure (fabs(x_ - sqrt(2.)) <= eps);
}

void
fms_test_newton(void)
{
	test_newton<double>();
	test_newton<float>();
}