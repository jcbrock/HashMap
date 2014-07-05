#include <iostream>
#include "gtest/gtest.h"
#include <unordered_map>
#include <string>

//currently just running tests....
int main(int argc, char **argv)
{
	std::unordered_map<int, int> foobar;
	auto foo = foobar[0];

	std::unordered_map<std::string, std::string> foobar2;
	auto foo2 = foobar2["hi"];

	std::cout << "Running main() from gtest_main.cc\n";

	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

	system("pause");
	return 0;
}