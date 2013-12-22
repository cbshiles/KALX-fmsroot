// test_root1d.cpp - test 1d root finding
#include <cassert>
#define ensure assert
#include <functional>
#include "root1d.h"
#include "../xll8/xll/utility/random.h"

using namespace fms;

void test_step1d(void)
{
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
	root1d<double> r([](const double& x) { return x*x - 2; });

	r.bracket(1, .1);
	n = r.size();
	double eps = 1e-8;
	while (!r.residual(eps)) {
		r.secant();
	}
	n = r.size();
	ensure (fabs(r.y[0]) < eps);

	r.clear();
	r.bracket(2, .0001);
	n = r.size();
	double delta = 1e-15;
	while (!r.delta(delta)) {
		r.secant();
	}
	n = r.size();
	ensure (fabs(r.x[0] - r.x[1]) < delta);

	root1d<double> r2([](const double& x) { return x*x - 2; }, [](const double& x) { return 2*x; });
	r2.bracket(1,.1);
	n = r2.size();
	while (!r2.residual(eps))
		r2.newton();
	n = r2.size();

	r.clear();
	r.bracket(1, 0.1);
	r.brent([eps,&r]() { return r.residual(eps); });
	ensure (fabs(r.y[0]) < eps);
}