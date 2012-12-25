// tquadratic.cpp - test roots of quadratic equation
#include <iostream>
#include <functional>
#include <random>
#include "ensure.h"
#include "quadratic.h"

using namespace std;
using namespace root;

std::default_random_engine rng;

template<class T>
void test_quadratic(size_t n = 100)
{
	T eps = std::numeric_limits<T>::epsilon();
	auto u = std::bind(std::uniform_real_distribution<T>(0,100), rng);

	while (n--) {
		T a, b, c;
		a = u();
		b = u();
		c = b + u();
		// a(x - b)(x - c) = ax^2 - a*(b+c)x + abc
		std::pair<T,T> x = _1d::quadratic(a, -a*(b+c), a*b*c);
		ensure (fabs(x.first - b) < 1000*eps);
		ensure (fabs(x.second - c) < 1000*eps);
	}
}

void fms_test_quadratic(void)
{
	test_quadratic<double>();
	test_quadratic<float>();
}