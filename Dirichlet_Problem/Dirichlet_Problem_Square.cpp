#include "Dirichlet_Problem_Square.h"

double Dirichlet_Problem_Square::exact(double x, double y)
{
    return exp(1 - x* x - y * y);
}

double Dirichlet_Problem_Square::laplacian(double x, double y)
{
    return 4 * exp(1 - x * x - y * y) * (x*x + y*y - 1);
}

double Dirichlet_Problem_Square::x_min_edge(double y)
{
    return exp(- y * y);
}

double Dirichlet_Problem_Square::x_max_edge(double y)
{
    return exp(- y * y);
}

double Dirichlet_Problem_Square::y_min_edge(double x)
{
    return exp(-x * x);
}

double Dirichlet_Problem_Square::y_max_edge(double x)
{
    return exp(-x * x);
}

Dirichlet_Problem_Square::Dirichlet_Problem_Square(const Dirichlet_Problem_Square& copy)
{
    x_min = copy.x_min;
    x_max = copy.x_max;
    y_min = copy.y_min;
    y_max = copy.y_max;
}

Dirichlet_Problem_Square::Dirichlet_Problem_Square(double x1, double x2, double y1, double y2){
    x_min = x1;
    x_max = x2;
    y_min = y1;
    y_max = y2;
}
