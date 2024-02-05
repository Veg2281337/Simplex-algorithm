#ifndef SIMPLEX_ALGORITHM_SRC_FRAMEWORK_UTILITY_H
#define SIMPLEX_ALGORITHM_SRC_FRAMEWORK_UTILITY_H

#include "src/framework/structures/instance.h"

#include <iostream>
#include <cmath>

std::ostream& operator << (std::ostream &os, Instance const& inst)
{
	auto [n, m] = inst.shape();
	auto c = inst.getC();
	auto c0 = inst.getC0();
	auto a = inst.getA();
	auto b = inst.getB();

	os << "Linear Programming Problem:\n";
	os << m << " variables, " << n << " rows.\n";

	for (size_t i = 0; i < m; ++i)
	{
		os << (i > 0 ? std::abs(c[i]) : c[i]) << " * x" << i + 1 << (i < m - 1 ? (c[i + 1] < 0 ? " - " : " + ") : "");
	}
	os << (c0 < 0 ? " - " : " + ") << std::abs(c0) << " -> max\n";

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			os << (i > 0 ? std::abs(a[i][j]) : a[i][j]) << " * x" << i + 1 << (j < m - 1 ? (a[i][j + 1] < 0 ? " - " : " + ") : "");
		}
		switch (inst.getSign())
		{
			case Sign::LESS_EQUAL: os << " <= "; break;
			case Sign::EQUAL: os << " == "; break;
			case Sign::MORE_EQUAL: os << " >= "; break;
		}
		os << b[i] << "\n";
	}
	os << "x >= 0";

	return os;
}


#endif //SIMPLEX_ALGORITHM_SRC_FRAMEWORK_UTILITY_H
