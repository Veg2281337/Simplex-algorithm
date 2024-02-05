#ifndef SIMPLEX_ALGORITHM_INSTANCEGENERATOR_H
#define SIMPLEX_ALGORITHM_INSTANCEGENERATOR_H

#include "src/framework/structures/instance.h"

#include <random>
#include <vector>


class InstanceGen {
    Instance generate(size_t n, size_t m)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);
        std::vector<std::vector<double>> a(n, std::vector<double>(m, 0));
        std::vector<double> b(n, 0);
        std::vector<double> c(m, 0);
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < m; ++j)
            {
                a[i][j] =dis(gen);
            };
        };
        for (size_t i = 0; i < n; ++i)
        {
            b[i] =dis(gen);
        };
        for (size_t j = 0; j < m; ++j)
        {
            c[j] =dis(gen);
        };
        double c0 = dis(gen);
        return Instance(
                a, b, c, c0,
                Sign::LESS_EQUAL
        );;
    };
};

#endif //SIMPLEX_ALGORITHM_INSTANCEGENERATOR_H