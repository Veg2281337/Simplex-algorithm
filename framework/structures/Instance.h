//
// Created by romanov.da on 29.01.2024.
//

#ifndef SIMPLEX_ALGORITHM_INSTANCE_H
#define SIMPLEX_ALGORITHM_INSTANCE_H


#include <vector>

enum class sign {LESS_EQUAL, EQUAL, MORE_EQUAL};

struct Instance
{

    std::vector<std::vector<double>> a;
    std::vector<double> b;
    std::vector<double> c;
    using enum sign;
    c0: double;
    Instance();
};

#endif //SIMPLEX_ALGORITHM_INSTANCE_H
