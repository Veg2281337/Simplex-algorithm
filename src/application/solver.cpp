#include "src/framework/structures/instance.h"
#include "src/framework/instance_generator/instance_generator.h"
#include "src/framework/utility.h"

#include <iostream>


int main()
{
	Instance inst = Instance(
		{{1, 2}, {3, 4}, {5, 6}},
		{1, -2, 3},
		{-6, -7},
		-10.0,
		Sign::EQUAL
	);

	std::cout << inst;
    return 0;
}