#include "src/framework/structures/instance.h"
#include "src/framework/structures/instance_generator.h"
#include "src/framework/utility.h"
#include "src/framework/solver/solver.h"


#include <iostream>


void test_2()
{
	std::cout << "Test 2\n";
	auto inst_1 = InstanceGen::generate<Sign::LESS_EQUAL>(6, 3);
	auto inst = inst_1.toEqual();
	std::cout << inst;
	Solver::solve(inst);
	std::cout << inst;
}

void test_3()
{
	std::cout << "Test 3\n";
	Instance<Sign::EQUAL> inst = {{{2, 1, 3}, {1, -3, 1}, {1, 11, 3}}, {1, -3, 11}, {1, -1, 0}, 1};
	std::cout << inst;
	Solver::solve(inst);
	std::cout << inst;
}

void test_4()
{
	std::cout << "Test 4\n";
	Instance<Sign::EQUAL> inst = {{{2.0, -1, 0, -2, 1, 0}, {3, 2, 1, -3, 0, 0}, {-1, 3, 0, 4, 0, 1}},
			{16, 18, 24.0},
			{2.0, 3, 0, -1, 0, 0},
			0};
	std::cout << inst;
	Solver::solve(inst);
	std::cout << inst;
}

int main()
{
//	test_2();
	test_3();
	test_4();
	return 0;
}