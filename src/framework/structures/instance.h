//
// Created by romanov.da on 29.01.2024.
//

#ifndef SIMPLEX_ALGORITHM_INSTANCE_H
#define SIMPLEX_ALGORITHM_INSTANCE_H


#include <vector>

enum class Sign
{
    LESS_EQUAL = 0,
    EQUAL = 1,
    MORE_EQUAL = 2
};

using LPFloat = double;
using Vector = std::vector<LPFloat>;
using Matrix = std::vector<Vector>;

struct Instance
{
private:
    Matrix a_;
    Vector b_;
    Vector c_;
    LPFloat c0_;
    Sign sign_;

public:
    [[nodiscard]] Matrix const& getA() const
    {
        return a_;
    }

    [[nodiscard]] Vector const& getB() const
    {
        return b_;
    }

    [[nodiscard]] Vector const& getC() const
    {
        return c_;
    }

    [[nodiscard]] LPFloat const& getC0() const
    {
        return c0_;
    }

    [[nodiscard]] Sign const& getSign() const
    {
        return sign_;
    }

    Instance(Matrix a, Vector b, Vector c, LPFloat c0, Sign sign)
	: a_(std::move(a))
	, b_(std::move(b))
	, c_(std::move(c)),
	c0_(c0),
	sign_(sign) {}

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
};


#endif //SIMPLEX_ALGORITHM_INSTANCE_H
