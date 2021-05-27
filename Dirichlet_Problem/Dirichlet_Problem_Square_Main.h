#pragma once
#include "Dirichlet_Problem_Square.h"
class Dirichlet_Problem_Square_Main : public Dirichlet_Problem_Square{
public:
    Dirichlet_Problem_Square_Main() : Dirichlet_Problem_Square() {}
    Dirichlet_Problem_Square_Main(const Dirichlet_Problem_Square& copy) : Dirichlet_Problem_Square(copy) {}
    Dirichlet_Problem_Square_Main(double x1, double x2, double y1, double y2) : Dirichlet_Problem_Square(x1, x2, y1, y2) {}

    double exact(double, double);
    double laplacian(double x, double y);
    double x_min_edge(double y);
    double x_max_edge(double y);
    double y_min_edge(double x);
    double y_max_edge(double x);
};

inline double Dirichlet_Problem_Square_Main::exact(double x, double y) {
    return -2.5; //это, разумеется, не настоящее значение функции
}

inline double Dirichlet_Problem_Square_Main::laplacian(double x, double y){
    return abs(x * x - y * y);
}

inline double Dirichlet_Problem_Square_Main::x_min_edge(double y){
    return -y * y + 1;
}

inline double Dirichlet_Problem_Square_Main::x_max_edge(double y){
    return (1 - y * y) * exp(y);
}

inline double Dirichlet_Problem_Square_Main::y_min_edge(double x){
    return 1 - x * x;
}

inline double Dirichlet_Problem_Square_Main::y_max_edge(double x){
    return 1 - x * x;
}
