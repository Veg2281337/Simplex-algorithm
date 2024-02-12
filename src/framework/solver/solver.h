#ifndef SIMPLEX_ALGORITHM_SRC_FRAMEWORK_SOLVER_SOLVER_H
#define SIMPLEX_ALGORITHM_SRC_FRAMEWORK_SOLVER_SOLVER_H

#include "src/framework/structures/instance.h"

struct Solver
{
	static void solve(Instance<Sign::EQUAL>& inst)
	{
		firstPhase(inst);
		secondPhase(inst);
	}

private:
	static void firstPhase(Instance<Sign::EQUAL>& inst)
	{
		if (inst.basis().empty())
		{
			inst.initBasis();
		}
		inst.makeBPositive();

		auto f_inst = getInstForFirstPhase(inst);
		performSimplexMethod(f_inst);
		inst.changeBasis(f_inst.basis());
	}

	static Instance<Sign::EQUAL> getInstForFirstPhase(Instance<Sign::EQUAL> const& inst)
	{
		Matrix a = inst.a();
		Vector c = Vector(inst.col() + inst.row());
		LPFloat c0 = 0;

		for (size_t i = 0; i < inst.row(); ++i)
		{
			a[i].resize(inst.col() + inst.row());
			a[i][inst.col() + i] = 1;
		}

		for (size_t i = 0; i < inst.row(); ++i)
		{
			for (size_t j = 0; j < inst.col(); ++j)
			{
				c[j] += a[i][j];
			}
			c0 += inst.b()[i];
		}

		return {a, inst.b(), c, -c0};
	}

	static void secondPhase(Instance<Sign::EQUAL>& inst)
	{
		performSimplexMethod(inst);
	}

	static void performSimplexMethod(Instance<Sign::EQUAL>& inst)
	{
		Basis basis;
		auto [n, m] = inst.shape();

		while (true)
		{
			size_t best_to = 0;
			LPFloat best_value = inst.c()[0];
			for (size_t j = 1; j < m; ++j)
			{
				if (best_value < inst.c()[j])
				{
					best_to = j;
					best_value = inst.c()[j];
				}
			}
			if (best_value <= 0)
			{
				break;
			}

			size_t best_from = SIZE_MAX;
			best_value = -1;
			for (size_t i = 0; i < n; ++i)
			{
				if (inst.a()[i][best_to] <= 0)
				{
					continue;
				}
				auto cur_value = inst.b()[i] / inst.a()[i][best_to];
				if (best_from == SIZE_MAX or best_value > cur_value)
				{
					best_from = i;
					best_value = cur_value;
				}
			}
			if (best_from == SIZE_MAX)
			{
				std::cout << "Unbounded problem\n";
				std::abort();
			}
			inst.gaussStep(best_from, best_to);
		}
	}
};

#endif //SIMPLEX_ALGORITHM_SRC_FRAMEWORK_SOLVER_SOLVER_H
