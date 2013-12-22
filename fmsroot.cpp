// fmsroot.cpp - root finding
#include <exception>
#include <iostream>

void test_root1d(void);

int main()
{
	try {
		test_root1d();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}