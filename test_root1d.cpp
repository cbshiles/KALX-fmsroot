// test_root1d.cpp - test 1d root finding
#include <cassert>
#define ensure assert
#include <functional>
#include "root1d.h"

using namespace fms;

void test_root1d(void)
{
	root1d<double> r([](const double& x) { return x*x - 2; });
	r.bracket(1, .1);

	double eps = 1e-8;
	while (!r.residual(eps)) {
		r.secant();
	}

	ensure (fabs(r.y[0]) < eps);
}