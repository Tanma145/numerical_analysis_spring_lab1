#pragma once
#include <cmath>

//test_task
double test_exact(double x, double y) {
    return exp(1 - x * x - y * y);
}

double test_laplacian(double x, double y)
{
    return 4 * exp(1 - x * x - y * y) * (x * x + y * y - 1);
}

double test_x_min_edge(double y)
{
    return exp(y * y);
}

double test_x_max_edge(double y)
{
    return exp(y * y);
}

double test_y_min_edge(double x)
{
    return exp(x * x);
}

double test_y_max_edge(double x)
{
    return exp(x * x);
}

//main task
double main_exact(double x, double y) {
    return 2.5;
}

double main_laplacian(double x, double y)
{
    return abs(x * x - y * y);
}

double main_x_min_edge(double y)
{
    return -y * y + 1;
}

double main_x_max_edge(double y)
{
    return (1 - y * y) * exp(y);
}

double main_y_min_edge(double x)
{
    return 1 - x * x;
}

double main_y_max_edge(double x)
{
    return 1 - x * x;
}

//class
class Dirichlet_Problem_Square
{
private:
public:
    double x_min, x_max, y_min, y_max;
    double (*exact)(double, double);
    double (*laplacian)(double, double);
    double (*x_min_edge)(double);
    double (*x_max_edge)(double);
    double (*y_min_edge)(double);
    double (*y_max_edge)(double);

    double get_exact(double, double) const;
    double get_laplacian(double, double) const;
    double get_x_min_edge(double) const;
    double get_x_max_edge(double) const;
    double get_y_min_edge(double) const;
    double get_y_max_edge(double) const;

    void set_exact(double (*f)(double, double));
    void set_laplacian(double (*f)(double, double));
    void set_x_min_edge(double (*f)(double));
    void set_x_max_edge(double (*f)(double));
    void set_y_min_edge(double (*f)(double));
    void set_y_max_edge(double (*f)(double));

    Dirichlet_Problem_Square();
	Dirichlet_Problem_Square(const Dirichlet_Problem_Square &copy);
	Dirichlet_Problem_Square(double = 0, double = 0, double = 0, double = 0);
};

//constructors
Dirichlet_Problem_Square::Dirichlet_Problem_Square()
{
    x_min = -1;
    x_max = 1;
    y_min = -1;
    y_max = 1;

    x_min_edge = test_x_min_edge;
    x_max_edge = test_x_max_edge;
    y_min_edge = test_y_min_edge;
    y_max_edge = test_y_max_edge;
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

//get
double Dirichlet_Problem_Square::get_exact(double x, double y) const {
    return exact(x, y);
}
double Dirichlet_Problem_Square::get_laplacian(double x, double y) const {
    return laplacian(x, y);
}
double Dirichlet_Problem_Square::get_x_min_edge(double y) const {
    return x_min_edge(y);
}
double Dirichlet_Problem_Square::get_x_max_edge(double y) const {
    return x_max_edge(y);
}
double Dirichlet_Problem_Square::get_y_min_edge(double x) const {
    double a = y_min_edge(x);
    return a;
}
double Dirichlet_Problem_Square::get_y_max_edge(double x) const {
    return y_max_edge(x);
}

//set
void Dirichlet_Problem_Square::set_exact(double (*f)(double, double)) {
    exact = f;
}
void Dirichlet_Problem_Square::set_laplacian(double (*f)(double, double)) {
    laplacian = f;
}
void Dirichlet_Problem_Square::set_x_min_edge(double (*f)(double)) {
    x_min_edge = f;
}
void Dirichlet_Problem_Square::set_x_max_edge(double (*f)(double)) {
    x_max_edge = f;
}
void Dirichlet_Problem_Square::set_y_min_edge(double (*f)(double)) {
    y_min_edge = f;
}
void Dirichlet_Problem_Square::set_y_max_edge(double (*f)(double)) {
    y_max_edge = f;
}

