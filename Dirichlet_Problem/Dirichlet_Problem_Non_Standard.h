#pragma once
#include "Dirichlet_Problem_Square.h"
class Dirichlet_Problem_Non_Standard : public Dirichlet_Problem_Square{
public:
    Dirichlet_Problem_Non_Standard() : Dirichlet_Problem_Square() {}
    Dirichlet_Problem_Non_Standard(const Dirichlet_Problem_Square& copy) : Dirichlet_Problem_Square(copy) {}
    Dirichlet_Problem_Non_Standard(double x1, double x2, double y1, double y2) : Dirichlet_Problem_Square(x1, x2, y1, y2) {}

    double exact(double, double);
    double laplacian(double x, double y);

    bool in_region(double x, double y);
    bool on_edge(double x, double y);
      
    double x_min_edge(double y) { return 0; }
    double x_max_edge(double y) { return 0; }
    double y_min_edge(double x) { return 0; }
    double y_max_edge(double x) { return 0; }

    //зачем писать всё это, если можно просто вызывать exact? :thinking:
    double mu1(double x);  // (  -1,    1) - (   0,    1)
    double mu2(double y);  // (   0,    1) - (   0,  0.5)
    double mu3(double x);  // (   0,  0.5) - (-0.5,  0.5)
    double mu4(double y);  // (-0.5,  0.5) - (-0.5, -0.5)
    double mu5(double x);  // (-0.5, -0.5) - ( 0.5, -0.5)
    double mu6(double y);  // ( 0.5, -0.5) - ( 0.5,    0)
    double mu7(double x);  // ( 0.5,    0) - (   1,    0)
    double mu8(double y);  // (   1,    0) - (   1,   -1)
    double mu9(double x);  // (   1,   -1) - (  -1,   -1)
    double mu10(double y); // (  -1,   -1) - (  -1,    1)
};

inline double Dirichlet_Problem_Non_Standard::exact(double x, double y) {
    return exp(1 - x * x - y * y);
}

inline double Dirichlet_Problem_Non_Standard::laplacian(double x, double y){
    return 4 * exp(1 - x * x - y * y) * (x * x + y * y - 1);
}

inline bool Dirichlet_Problem_Non_Standard::in_region(double x, double y){
    bool flag = false;
    flag = (-1   < x) && (x <  0  ) && ( 0.5 < y) && (y <  1  ) 
        || (-1   < x) && (x < -0.5) && (-0.5 < y) && (y <  0.5)
        || (-1   < x) && (x <  1  ) && (-1   < y) && (y < -0.5)
        || ( 0.5 < x) && (x <  1  ) && (-0.5 < y) && (y <  0  )
        || (-1   < x) && (x < -0.5) && ((y == 0.5) || (y == -0.5))
        || ( 0.5 < x) && (x <  1  ) && (y == -0.5);
    return flag;
}

inline bool Dirichlet_Problem_Non_Standard::on_edge(double x, double y) {
    bool flag = false;
    flag = (y ==  1  ) && (-1   <= x) && (x <=  0  )
        || (x ==  0  ) && ( 0.5 <= y) && (y <=  1  )
        || (y ==  0.5) && (-0.5 <= x) && (x <=  0  )
        || (x == -0.5) && (-0.5 <= y) && (y <=  0.5)
        || (y == -0.5) && (-0.5 <= x) && (x <=  0.5)
        || (x ==  0.5) && (-0.5 <= y) && (y <=  0  )
        || (y ==  0  ) && ( 0.5 <= x) && (x <=  1  )
        || (x ==  1  ) && (-1   <= y) && (y <=  0  )
        || (y == -1  ) && (-1   <= x) && (x <=  1  )
        || (x == -1  ) && (-1   <= y) && (y <=  1  );
    return flag;
}

inline double Dirichlet_Problem_Non_Standard::mu1(double x){
    if (-1 <= x && x <= 0)
        return exp(x * x);
    else throw - 1;
}

inline double Dirichlet_Problem_Non_Standard::mu2(double y){
    if (0.5 <= y && y <= 1)
        return exp(1 - y * y);
    else throw - 1;
}

inline double Dirichlet_Problem_Non_Standard::mu3(double x){
    if (-0.5 <= x && x <= 0)
        return exp(0.75 - x * x );
    else throw - 1;
}

inline double Dirichlet_Problem_Non_Standard::mu4(double y){
    if (-0.5 <= y && y <= 0.5)
        return exp(0.75 - y * y);
    else throw - 1;
}

inline double Dirichlet_Problem_Non_Standard::mu5(double x) {
    if (-0.5 <= x && x <= 0.5)
        return exp(0.75 - x * x);
    else throw - 1;
}

