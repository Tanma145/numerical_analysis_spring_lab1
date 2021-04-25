#include "Dirichlet_Problem_Solution.h"
#include <conio.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	setlocale(LC_ALL, "Russian"); 
	Dirichlet_Problem_Square_Test problem(-1, 1, -1, 1);
	int n = 2;
	int m = 2;
	Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Test> answer(n, m, problem);

	int max_iterations = 1000;
	double precision = 0.5e-7;
	answer.setIterations(max_iterations);
	answer.setPrecision(precision);
	answer.exact_solution();

	answer.Chebyshev_Iteration_Method(1);
	_getch();
}