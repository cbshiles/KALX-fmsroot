// main.cpp
#include <iostream>
#include <iomanip>
#include "root.h"

using namespace std;

void fms_test_bisect(void);
void fms_test_bracket(void);
void fms_test_quadratic(void);
void fms_test_secant(void);
//void fms_test_root(void);
void fms_test_newton(void);
//void fms_test_zhang(void);

int
main()
{
	try {
		fms_test_bisect();
		fms_test_bracket();
		fms_test_quadratic();
		fms_test_secant();
//		fms_test_root();
		fms_test_newton();
//		fms_test_zhang();
	}
	catch (const std::exception ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}