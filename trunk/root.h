// root.h - Root finding routines.
#pragma once
#include <array>

#ifndef ensure
#include <cassert>
#define ensure(x) assert(x)
#endif

namespace root {
namespace _1d {

	template<class T>
	bool same_sign(T x, T y)
	{
		return x == _copysign(x, y);
	}

	template<class T>
	struct point {
		T x, y;
		point(T _x, T _y)
			: x(_x), y(_y)
		{ }
	};

} // namespace _1d
} // namespace root