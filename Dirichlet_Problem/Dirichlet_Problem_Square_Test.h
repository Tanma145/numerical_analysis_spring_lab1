#pragma once
#include "Dirichlet_Problem_Square.h"
class Dirichlet_Problem_Square_Test : public Dirichlet_Problem_Square{
public:
    Dirichlet_Problem_Square_Test() : Dirichlet_Problem_Square() {}
    Dirichlet_Problem_Square_Test(const Dirichlet_Problem_Square& copy) : Dirichlet_Problem_Square(copy) {}
    Dirichlet_Problem_Square_Test(double x1, double x2, double y1, double y2) : Dirichlet_Problem_Square(x1, x2, y1, y2) {}

    double exact(double, double);
    double laplacian(double x, double y);
    double x_min_edge(double y);
    double x_max_edge(double y);
    double y_min_edge(double x);
    double y_max_edge(double x);
};

inline double Dirichlet_Problem_Square_Test::exact(double x, double y) {
    return exp(1 - x * x - y * y);
}

inline double Dirichlet_Problem_Square_Test::laplacian(double x, double y)
{
    return 4 * exp(1 - x * x - y * y) * (x * x + y * y - 1);
}

inline double Dirichlet_Problem_Square_Test::x_min_edge(double y)
{
    return exp(- y * y);
}

inline double Dirichlet_Problem_Square_Test::x_max_edge(double y)
{
    return exp(- y * y);
}

inline double Dirichlet_Problem_Square_Test::y_min_edge(double x)
{
    return exp(- x * x);
}

inline double Dirichlet_Problem_Square_Test::y_max_edge(double x)
{
    return exp(- x * x);
}