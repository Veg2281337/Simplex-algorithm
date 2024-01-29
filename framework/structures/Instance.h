//
// Created by romanov.da on 29.01.2024.
//

#ifndef SIMPLEX_ALGORITHM_INSTANCE_H
#define SIMPLEX_ALGORITHM_INSTANCE_H


#include <vector>


struct Instance
{
    std::vector<std::vector<double>> a;
    std::vector<double> b;
    std::vector<double> c;
};


#endif //SIMPLEX_ALGORITHM_INSTANCE_H
