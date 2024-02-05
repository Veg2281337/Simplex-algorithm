//
// Created by romanov.da on 29.01.2024.
//

#ifndef SIMPLEX_ALGORITHM_INSTANCE_H
#define SIMPLEX_ALGORITHM_INSTANCE_H


#include <vector>

enum class Sign
{
    LESS_EQUAL,
    EQUAL,
    MORE_EQUAL
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

    Instance(Matrix a, Vector b, Vector c, LPFloat c0, Sign sign) : a_(a), b_(b), c_(c), c0_(c0), sign_(sign) {}
    [[nodiscard]] size_t const& row() const
    {
        return a_.size();
    };
    [[nodiscard]] size_t const& col() const
    {
        return a_[0].size();
    };
    [[nodiscard]] std::tuple<size_t, size_t> const& shape() const
    {
        return std::tuple<size_t, size_t>{row(), col()};
    };

};


#endif //SIMPLEX_ALGORITHM_INSTANCE_H
