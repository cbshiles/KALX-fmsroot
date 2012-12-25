// tbracket.cpp - test bracket routine
#include "ensure.h"
#include "bracket.h"

using namespace root;

template<class T>
void test_bracket(void)
{
	T eps = std::numeric_limits<T>::epsilon();
	T x0 = 2., x1 = 3.;

	auto F = [](T x) { return x*x - 2; };
	T m;
	m = _1d::bracket<T>(x0, x1, F, 0);

	ensure (!same_sign(F(x0), F(x1)));
	ensure (fabs(m - (F(x1) - F(x0))/(x1 - x0)) <= eps);

	x0 = 0.; x1 = 1.;
	m = _1d::bracket<T>(x0, x1, F, 0);

	ensure (!same_sign(F(x0), F(x1)));
	ensure (fabs(m - (F(x1) - F(x0))/(x1 - x0)) <= eps);

	x0 = -2; x1 = -1;
	m = _1d::bracket<T>(x0, x1, F, 0);
	ensure (x0 == -2 && x1 == -1);

	x0 = -3; x1 = -2;
	m = _1d::bracket<T>(x0, x1, F, 0);
	ensure (!same_sign(F(x0), F(x1)));
	ensure (fabs(m - (F(x1) - F(x0))/(x1 - x0)) <= eps);
}

void fms_test_bracket(void)
{
	test_bracket<double>();
	test_bracket<float>();
}