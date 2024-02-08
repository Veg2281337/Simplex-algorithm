#ifndef SIMPLEX_ALGORITHM_INSTANCE_H
#define SIMPLEX_ALGORITHM_INSTANCE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

enum class Sign
{
	LESS_EQUAL = 0, EQUAL = 1, MORE_EQUAL = 2
};

using LPFloat = double;
using Vector = std::vector<LPFloat>;
using Matrix = std::vector<Vector>;
using Basis = std::unordered_map<size_t, size_t>;

template<Sign sign_>
struct Instance
{
private:
	Matrix a_;
	Vector b_;
	Vector c_;
	LPFloat c0_;
	Basis basis_;

public:
	[[nodiscard]] Matrix const& a() const { return a_; }

	[[nodiscard]] Vector const& b() const { return b_; }

	[[nodiscard]] Vector const& c() const { return c_; }

	[[nodiscard]] LPFloat const& c0() const { return c0_; }

	[[nodiscard]] Sign sign() const { return sign_; }

	[[nodiscard]] Basis const& basis() const { return basis_; }

	Instance(Matrix a, Vector b, Vector c, LPFloat c0)
			: a_(std::move(a)), b_(std::move(b)), c_(std::move(c)), c0_(c0) {}

	[[nodiscard]] size_t row() const
	{
		return a_.size();
	}

	[[nodiscard]] size_t col() const
	{
		return a_[0].size();
	}

	[[nodiscard]] std::tuple<size_t, size_t> shape() const
	{
		return std::tuple<size_t, size_t>{row(), col()};
	}

	void gaussStep(size_t row_idx, size_t col_idx)
	{
		if (a_.at(row_idx).at(col_idx) == 0)
		{
			std::cout << "Zero element in gaussStep\n";
			std::abort();
		}

		LPFloat v = a_[row_idx][col_idx];
		b_[row_idx] /= v;
		for (size_t j = 0; j < col(); ++j)
		{
			a_[row_idx][j] /= v;
		}

		for (size_t i = 0; i < row(); ++i)
		{
			if (i == row_idx)
			{
				continue;
			}
			v = a_[i][col_idx];
			b_[i] -= b_[row_idx] * v;
			for (size_t j = 0; j < col(); ++j)
			{
				a_[i][j] -= a_[row_idx][j] * v;
			}
		}

		v = c_[col_idx];
		c0_ += b_[row_idx] * v;
		for (size_t j = 0; j < col(); ++j)
		{
			c_[j] -= a_[row_idx][j] * v;
		}

		basis_[row_idx] = col_idx;
	}

	void initBasis();


	void makeBPositive();

	[[nodiscard]] Instance<Sign::EQUAL> toEqual() const
	{
		if constexpr (sign_ == Sign::EQUAL)
		{
			return *this;
		}

		Matrix a = a_;

		Vector b = b_;
		for (size_t i = 0; i < row(); ++i)
		{
			if constexpr (sign_ == Sign::MORE_EQUAL)
			{
				for (size_t j = 0; j < col(); ++j)
				{
					a[i][j] *= -1;
				}
				b[i] *= -1;
			}
			a[i].resize(row() + col());
			a[i][col() + i] = 1;
		}

		return {a, b, c_, c0_};
	}

	void changeBasis(Basis const& basis)
	{
		for (auto [row_idx, col_idx]: basis)
		{
			gaussStep(row_idx, col_idx);
		}
	}

private:
	void deleteLinDependenceRow(std::unordered_set<size_t> const& lin_dep_rows)
	{
		if (!lin_dep_rows.empty())
		{
			Matrix a;
			Vector b;
			a.reserve(row() - lin_dep_rows.size());
			b.reserve(row() - lin_dep_rows.size());
			for (size_t i = 0; i < row(); ++i)
			{
				if (lin_dep_rows.find(i) == lin_dep_rows.end())
				{
					a.push_back(std::move(a_[i]));
					b.push_back(b_[i]);
				}
			}
			a_ = a;
			b_ = b;
		}
	}
};

template<>
void Instance<Sign::EQUAL>::initBasis()
{
	Basis basis;
	std::unordered_set<size_t> lin_dep_rows;
	for (size_t i = 0; i < row(); ++i)
	{
		for (size_t j = 0; j < col(); ++j)
		{
			if (a_[i][j] != 0)
			{
				basis[i] = j;
				break;
			}
		}

		if (basis.find(i) != basis.end())
		{
			gaussStep(i, basis[i]);
		}
		else
		{
			if (b_[i] == 0)
			{
				lin_dep_rows.insert(i);
			}
			else
			{
				std::cout << "Infesible problem\n";
				std::abort();
			}
		}
	}
	basis_ = std::move(basis);

	deleteLinDependenceRow(lin_dep_rows);
}

template<>
void Instance<Sign::EQUAL>::makeBPositive()
{
	for (size_t i = 0; i < row(); ++i)
	{
		if (b_[i] < 0)
		{
			for (size_t j = 0; j < col(); ++j)
			{
				a_[i][j] *= -1;
			}
			b_[i] *= -1;
		}
	}
}

#endif //SIMPLEX_ALGORITHM_INSTANCE_H
