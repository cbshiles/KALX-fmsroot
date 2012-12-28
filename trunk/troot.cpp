// troot.cpp - test root finding routines
#include <functional>
#include "root.h"
//#include "bisect.h"
//#include "bracket.h"
//#include "newton.h"

using namespace root;

void
fms_test_same_sign(void)
{
	ensure (same_sign(1,1));
	ensure (!same_sign(1,-1));
	ensure (!same_sign(-1,1));
	ensure (same_sign(-1,-1));
//	ensure (!same_sign(0,-0));
}

void
fms_test_quadratic(void)
{
	double x0, x1;
	double a, b, c;
	std::pair<double,double> x;

	x0 = 1;
	x1 = 2;
	a = 1;
	b = -(x0 + x1);
	c = x0*x1;

	x = quadratic(a, b, c);
	ensure (x.first == x0);
	ensure (x.second == x1);

	x0 = 3;
	x1 = 3;
	a = 1;
	b = -(x0 + x1);
	c = x0*x1;

	x = quadratic(a, b, c);
	ensure (x.first == x0);
	ensure (_isnan(x.second));

	a = 1;
	b = 0;
	c = 1;

	x = quadratic(a, b, c);
	ensure (_isnan(x.first));
	ensure (_isnan(x.second));

}

void
fms_test_root_1d_bracket(void)
{
	double c = 2;
	std::function<double(double)> f = [c](double x) { return x*x - c; };

	std::array<point<double>,2> ab = {point<double>(3,f(3)), point<double>(4,f(4))};

	while (ab[0].y * ab[1].y > 0)
		ab = bracket(f, ab);

	ensure (ab[0].y * ab[1].y < 0);

	long long eps, eps_(0); 
	for (eps = ulp(ab[0].y, ab[1].y); eps != eps_; eps_ = eps, eps = ulp(ab[0].y, ab[1].y))
		ab = bisect(f, ab);

	ensure (ab[0].x + std::numeric_limits<double>::epsilon() == ab[1].x);
}

void
fms_test_root(void)
{
	fms_test_quadratic();
	fms_test_root_1d_bracket();
	fms_test_same_sign();
}