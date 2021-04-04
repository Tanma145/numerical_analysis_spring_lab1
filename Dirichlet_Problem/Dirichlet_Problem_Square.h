#pragma once
#include <cmath>

//main task

//class
class Dirichlet_Problem_Square
{
private:
public:
    double x_min, x_max, y_min, y_max;
    Dirichlet_Problem_Square();
	Dirichlet_Problem_Square(const Dirichlet_Problem_Square &copy);
	Dirichlet_Problem_Square(double, double, double, double);
    
    virtual double exact(double x, double y) = 0; //истинное решение есть только у тестовой задачи и было бы хорошо оставить этот метод только в соответствующем классе, 
                                                //но так как он зачем-то используется в Dirichlet_Problem_Solution приходится оставлять его здесь
    virtual double laplacian(double x, double y) = 0;
    virtual double x_min_edge(double y) = 0;
    virtual double x_max_edge(double y) = 0;
    virtual double y_min_edge(double x) = 0;
    virtual double y_max_edge(double x) = 0;
};

//constructors
Dirichlet_Problem_Square::Dirichlet_Problem_Square()
{
    x_min = -1;
    x_max = 1;
    y_min = -1;
    y_max = 1;
}
Dirichlet_Problem_Square::Dirichlet_Problem_Square(const Dirichlet_Problem_Square& copy)
{
    x_min = copy.x_min;
    x_max = copy.x_max;
    y_min = copy.y_min;
    y_max = copy.y_max;

}
Dirichlet_Problem_Square::Dirichlet_Problem_Square(double x1, double x2, double y1, double y2) {
    x_min = x1;
    x_max = x2;
    y_min = y1;
    y_max = y2;
}

