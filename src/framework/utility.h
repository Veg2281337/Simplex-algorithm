#ifndef SIMPLEX_ALGORITHM_SRC_FRAMEWORK_UTILITY_H
#define SIMPLEX_ALGORITHM_SRC_FRAMEWORK_UTILITY_H

#include "src/framework/structures/instance.h"

#include <iostream>
#include <cmath>

template<Sign sign>
std::ostream& operator<<(std::ostream& os, Instance<sign> const& inst)
{
	auto [n, m] = inst.shape();
	auto c = inst.c();
	auto c0 = inst.c0();
	auto a = inst.a();
	auto b = inst.b();

	os << "Linear Programming Problem:\n";
	os << m << " variables, " << n << " rows.\n";

	for (size_t i = 0; i < m; ++i)
	{
		os << (i > 0 ? std::abs(c[i]) : c[i]) << " * x" << i + 1 << (i < m - 1 ? (c[i + 1] < 0 ? " - " : " + ") : "");
	}
	os << (c0 < 0 ? " - " : " + ") << std::abs(c0) << " -> max\nSubject to:\n";

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			os << (j > 0 ? std::abs(a[i][j]) : a[i][j]) << " * x" << j + 1
			   << (j < m - 1 ? (a[i][j + 1] < 0 ? " - " : " + ") : "");
		}
		switch (inst.sign())
		{
			case Sign::LESS_EQUAL:
				os << " <= ";
				break;
			case Sign::EQUAL:
				os << " == ";
				break;
			case Sign::MORE_EQUAL:
				os << " >= ";
				break;
		}
		os << b[i] << "\n";
	}
	os << "x >= 0\n\n";

	return os;
}

#endif //SIMPLEX_ALGORITHM_SRC_FRAMEWORK_UTILITY_H
