// main.cpp
#include <iostream>

void fms_test_root(void);
void fms_test_newton(void);

int
main()
{
	try {
		fms_test_root();
		fms_test_newton();
	}
	catch (const std::exception ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}