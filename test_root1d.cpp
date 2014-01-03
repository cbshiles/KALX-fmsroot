// test_root1d.cpp - test 1d root finding
#include <cassert>
#define ensure assert
#include <functional>
#include "root1d.h"
#include "../xll8/xll/utility/random.h"

using namespace fms;

void test_step1d(void)
{
	ensure (step1d::bracket0(-1.,1.));
	ensure (step1d::bracket0(1.,-1.));
	ensure (!step1d::bracket0(-1.,-1.));
	ensure (!step1d::bracket0(1.,1.));

	double x0 = 1, y0 = 2, x1 = 3, y1 = 4;

	ensure (step1d::bisect(x0, x1) == (x0 + x1)/2);
	ensure (step1d::newton(x0, y0, 2.) == x0 - y0/2);
	ensure (step1d::secant(x0, y0, x1, y1) == step1d::newton(x0, y0, (y1 - y0)/(x1 - x0)));
	ensure (step1d::secant(x0, y0, x1, y1) == step1d::newton(x1, y1, (y1 - y0)/(x1 - x0)));

	random::default_random_engine().seed(::time_t(0));
	for (int i = 0; i < 10; ++i) {
		double x0, x1, x2, y0, y1, y2;
		
		x0 = random::uniform_real();
		x1 = random::uniform_real();
		x2 = random::uniform_real();

		y0 = sqrt(x0);
		y1 = sqrt(x1);
		y2 = sqrt(x2);

		double dx = (std::min)(fabs(x0 - x1), std::min(fabs(x1 - x2), fabs(x2 - x0)));
		double r = step1d::inverse_quadratic(x0, y0, x1, y1, x2, y2);
		ensure (fabs(r) < 1e-13 / dx);
	}
}

void test_root1d(void)
{
	test_step1d();

	size_t n;
	root1d<double> r([](const double& x) { return x*x - 5; });

	r.push(1.);
	bool better;
	while (!r.residual(1e-11))
		better = r.improve(.1);
	n = r.size();

	r.clear();
	double x0;
	x0 = r.solve(1, .1, [&r]() { return r.residual(1e-11); });
	ensure (fabs(r.y[0]) < 1e-11);
	n = r.size();

	r.clear();
	x0 = r.solve(2, .1, [&r]() { return r.residual(1e-11); });
	ensure (fabs(r.y[0]) < 1e-11);
	n = r.size();

	r.clear();
	x0 = r.solve(1, .01, [&r]() { return r.residual(1e-11); });
	ensure (fabs(r.y[0]) < 1e-11);
	n = r.size();

	r.clear();
	x0 = r.solve(10, .1, [&r]() { return r.residual(1e-11); });
	ensure (fabs(r.y[0]) < 1e-11);
	n = r.size();
}