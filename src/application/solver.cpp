#include "src/framework/structures/instance.h"
#include "src/framework/instance_generator/instance_generator.h"
#include "src/framework/utility.h"

#include <iostream>

void test_1()
{
	Instance inst = Instance(
		{{1, 2}, {3, 4}, {5, 6}},
		{1, -2, 3},
		{-6, -7},
		-10.0,
		Sign::EQUAL
	);

	std::cout << inst;
}

void test_2()
{
	auto inst = InstanceGen::generate(5, 5);
	std::cout << inst;
}

int main()
{
	test_1();
	test_2();
    return 0;
}