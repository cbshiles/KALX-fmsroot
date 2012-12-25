// tbisect.cpp - test bisection
#include <iostream>
#include <iomanip>
#include "ensure.h"
#include "bisect.h"

using namespace std;
using namespace root;

template<class T>
void test_bisect(void)
{
	ulp_traits<T>::integer ulps = 0;
	size_t iter = 1000;

	T r = _1d::bisect_<T>(1., 2., [](T x) { return x*x - 2; }, ulps, iter);
	ensure (fabs(r - sqrt(2.)) <= std::numeric_limits<T>::epsilon());

	r = _1d::bisect<T>(1., 2., [](T x) { return x*x - 2; });
	ensure (fabs(r - sqrt(2.)) <= std::numeric_limits<T>::epsilon());

	// one iteration
	r = _1d::bisect<T>(1., 2., [](T x) { return x*x - 2; }, 0, 1);
	ensure (r == (1. + 2.)/2);

	r = _1d::bisect<T>(2., 3., [](T x) { return x*x - 2; }, 0, 1);
	ensure (_isnan(r));
	ensure (error_nan(r) == ROOT_SAME_SIGN);
}

void fms_test_bisect(void)
{
	test_bisect<double>();
	test_bisect<float>();
}