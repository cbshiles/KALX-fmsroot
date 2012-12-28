// tbracket.cpp - test bracket routine
// Copyright (c) 2012-2013 KALX, LLC. All rights reserved. No warranty is made.
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
	ensure (x0 == -2 && x1 == -1); // already bracketed

	x0 = -3; x1 = -2;
	m = _1d::bracket<T>(x0, x1, F, 0);
	ensure (!same_sign(F(x0), F(x1)));
	ensure (fabs(m - (F(x1) - F(x0))/(x1 - x0)) <= eps);

	auto G = [](T x) { return 2 - x*x; };

	x0 = 2; x1 = 3;
	m = _1d::bracket<T>(x0, x1, G, 0);
	ensure (!same_sign(G(x0), G(x1)));
	ensure (fabs(m - (G(x1) - G(x0))/(x1 - x0)) <= eps);

	x0 = -3; x1 = -2;
	m = _1d::bracket<T>(x0, x1, G, 0);
	ensure (!same_sign(G(x0), G(x1)));
	ensure (fabs(m - (G(x1) - G(x0))/(x1 - x0)) <= eps);


	auto H = [eps](T x) { return x*x - eps; };
	x0 = -1; x1 = 1; 
	T a = 0;
	size_t iter = 100;
	m = _1d::bracket_<T>(x0, x1, H, a, iter);
}

void fms_test_bracket(void)
{
	test_bracket<double>();
	test_bracket<float>();
}