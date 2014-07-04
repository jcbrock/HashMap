#include <iostream>
#include "gtest/gtest.h"

//currently just running tests....
int main(int argc, char **argv)
{
	std::cout << "Running main() from gtest_main.cc\n";

	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

	system("pause");
	return 0;
}