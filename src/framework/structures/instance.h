//
// Created by romanov.da on 29.01.2024.
//

#ifndef SIMPLEX_ALGORITHM_INSTANCE_H
#define SIMPLEX_ALGORITHM_INSTANCE_H


#include <vector>

enum class Sign
{
    LESS_EQUAL, EQUAL, MORE_EQUAL
};

struct Instance
{
    std::vector<std::vector<double>> a;
    std::vector<double> b;
    std::vector<double> c;
    double c0;
    Instance(std::vector<std::vector<double>> a, std::vector<double> b, std::vector<double> c, double c0, Sign sign)
    {

    };
    size_t row()
    {
        return a.size();
    };
    size_t col()
    {
        return a[0].size();
    };
    std::tuple<size_t, size_t> shape()
    {
        return std::tuple<size_t, size_t>{row(), col()};
    };
};

#endif //SIMPLEX_ALGORITHM_INSTANCE_H
