// tzhange.cpp - test Zhang root finding algorithm
#include <iostream>
#include "zhang.h"

using namespace std;
using namespace root;

template<class T>
void test_zhang(void)
{
	T x0 = 1., x1 = 2.;
	auto F = [](T x) { return x*x - 2; };

	for (size_t i = 0; i < 10; ++i) {
		size_t n = 1;
		_1d::zhang_(x0, x1, F, 0, n);
//		cout << "x0 = " << x0 << " x1 = " << x1 << endl;
	}
}

void fms_test_zhang(void)
{
	test_zhang<double>();
}