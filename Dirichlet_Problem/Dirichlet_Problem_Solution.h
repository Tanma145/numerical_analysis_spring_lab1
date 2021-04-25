#pragma once
#include "Dirichlet_Problem_Square_Test.h"
#include "Dirichlet_Problem_Square_Main.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

template <class Dirichlet_Problem_Square_Type>
class Dirichlet_Problem_Solution
{
private:
	double precision;
	int iterations_max;
public:
	double residual; //Невязка
	double precision_cur;
	int iterations_cur;
	Dirichlet_Problem_Square_Type problem;
	MatrixXd matrix;
	MatrixXd matrix2;
	double x_step, y_step;
	int x_grid, y_grid;
	Dirichlet_Problem_Solution();
	Dirichlet_Problem_Solution(const Dirichlet_Problem_Solution&);
	Dirichlet_Problem_Solution(int, int, Dirichlet_Problem_Square_Type);

	void setPrecision(double);
	void setIterations(int);

	void exact_solution();
	void initial_approximation();
	void Zeidel();
	void SOR(double); //метод верхней реллаксации
	void Fixed_Point_Iteration();
	void Chebyshev_Iteration_Method();
	void Chebyshev_Iteration_Method(int);
};

template <class Dirichlet_Problem_Square_Type>
Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Dirichlet_Problem_Solution() {
	x_grid = 0;
	y_grid = 0;
	x_step = 0;
	y_step = 0;
}

template <class Dirichlet_Problem_Square_Type>
Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Dirichlet_Problem_Solution(const Dirichlet_Problem_Solution& copy) {
	x_step = copy.x_step;
	y_step = copy.y_step;
	x_grid = copy.x_grid;
	y_grid = copy.y_grid;
}

template <class Dirichlet_Problem_Square_Type>
Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Dirichlet_Problem_Solution(int _x_grid, int _y_grid, Dirichlet_Problem_Square_Type _problem)
{
	Dirichlet_Problem_Square_Type a(_problem);
	problem = a;

	x_grid = _x_grid;
	y_grid = _y_grid;

	matrix.resize(y_grid + 1, x_grid + 1);
	matrix2.resize(y_grid + 1, x_grid + 1);
	x_step = (problem.x_max - problem.x_min) / (double)x_grid;
	y_step = (problem.y_max - problem.y_min) / (double)y_grid;

	for (int i = 0; i <= x_grid; i++) {
		matrix(0, i) = problem.y_min_edge(problem.x_min + i * x_step);
		matrix(y_grid, i) = problem.y_max_edge(problem.x_min + i * x_step);
	}
	for (int i = 0; i <= y_grid; i++) {
		matrix(i, 0) = problem.x_min_edge(problem.y_min + i * y_step);
		matrix(i, x_grid) = problem.x_max_edge(problem.y_min + i * y_step);
	}
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::setPrecision(double eps) {
	precision = eps;
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::setIterations(int n) {
	iterations_max = n;
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::exact_solution() {
	for (int j = 0; j <= matrix2.cols() - 1; j++)
		for (int i = matrix2.rows() - 1; i >= 0; i--) {
			matrix2(i, j) = problem.exact(problem.x_min + j * x_step, problem.y_min + i * y_step);
		}
}

template<class Dirichlet_Problem_Square_Type>
inline void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::initial_approximation(){

}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Zeidel() {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);

	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);

	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = 1 / (x_step * x_step);
	k2 = 1 / (y_step * y_step);
	a2 = -2 * (h2 + k2);

	while (f) {
		eps_max = 0;
		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = solution.rows() - 2; i >=1; i--) {
				v_old = solution(i, j);
				v_new = -(h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)));
				v_new = v_new + laplacian_grid(i, j);
				v_new = v_new / a2;

				eps_cur = abs(v_old - v_new);
				if (eps_cur > eps_max)
					eps_max = eps_cur;
				solution(i, j) = v_new;
			}
		iterations++;
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
		}
	}
	iterations_cur = iterations;
	matrix = solution;

	VectorXd error(4);
	error(0) = (-90 * solution(1, 1) +  9 * solution(2, 1) + 36 * solution(1, 2)) / 4.0 + 155 / 16.0;
	error(1) = (  9 * solution(1, 1) - 90 * solution(2, 1) + 36 * solution(2, 2)) / 4.0 + 155 / 16.0;
	error(2) = ( 36 * solution(1, 1) - 90 * solution(1, 2) +  9 * solution(2, 2)) / 4.0 + 155 / 16.0;
	error(3) = ( 36 * solution(2, 1) +  9 * solution(1, 2) - 90 * solution(2, 2)) / 4.0 + 155 / 16.0;
	residual = error.norm();
}

template<class Dirichlet_Problem_Square_Type>
inline void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::SOR(double omega){
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);

	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);

	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool flag = true; // условие остановки 

	h2 = 1 / (x_step * x_step);
	k2 = 1 / (y_step * y_step);
	a2 = -2 * (h2 + k2);

	while (flag) {
		eps_max = 0;
		for (int j = 1; j < solution.cols() - 1; j++)
			for (int i = 1; i < solution.rows() - 1; i++) {
				v_old = solution(i, j);
				v_new = - omega * (h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)));
				v_new += (1 - omega) * a2 * solution(i, j) + omega * laplacian_grid(i, j);
				v_new /= a2;
				eps_cur = abs(v_old - v_new);
				if (eps_cur > eps_max)
					eps_max = eps_cur;
				solution(i, j) = v_new;
			}
		iterations++;
		if (eps_max < precision || iterations >= iterations_max){
			precision_cur = eps_max;
			flag = false;
		}
	}
	iterations_cur = iterations;
	matrix = solution;
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Fixed_Point_Iteration() {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);
	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = -problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);
	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;  //нужно поменять начальное приближение

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = -1 / (x_step * x_step);
	k2 = -1 / (y_step * y_step);
	a2 = -2 * (h2 + k2);

	double tau = (1 / a2);
	//double tau = 0.5;

	while (f) {
		eps_max = 0;
		solution_prev = solution;
		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = 1; i <= solution.rows() - 2; i++) {
				v_old = solution_prev(i, j);

				double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j)) + k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
				double b_ij = laplacian_grid(i, j);
				v_new = solution_prev(i, j) + tau * (b_ij - tmp);

				eps_cur = abs(v_old - v_new);
				if (eps_cur > eps_max)
					eps_max = eps_cur;
				solution(i, j) = v_new;
			}
		iterations++;
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
		}
	}
	iterations_cur = iterations;
	matrix = solution;
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Chebyshev_Iteration_Method() {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);
	MatrixXd real_solution;

	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = -problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);
	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;  //нужно поменять начальное приближение

	real_solution = solution;
	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = -1 / (x_step * x_step);
	k2 = -1 / (y_step * y_step);
	a2 = -2 * (h2 + k2);

	//double tau = (1 / a2);
	const double MyPi = 3.141592653589793;
	int k = 2;
	double tau0 = 1.0 / (a2 + a2 * cos((MyPi / (2 * k)) * (1 + 2 * 0))); //чекнуть формулы
	double tau1 = 1.0 / (a2 + a2 * cos((MyPi / (2 * k)) * (1 + 2 * 1)));

	while (f) {
		real_solution = solution;

		eps_max = 0;
		solution_prev = solution;
		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = 1; i <= solution.rows() - 2; i++) {
				v_old = solution_prev(i, j);

				double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j)) + k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
				double b_ij = laplacian_grid(i, j);
				v_new = solution_prev(i, j) + tau0 * (b_ij - tmp);

				eps_cur = abs(v_old - v_new);
				if (eps_cur > eps_max)
					eps_max = eps_cur;
				solution(i, j) = v_new;
			}
		iterations++;
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
			break;
		}

		eps_max = 0;
		solution_prev = solution;
		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = 1; i <= solution.rows() - 2; i++) {
				v_old = solution_prev(i, j);

				double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j)) + k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
				double b_ij = laplacian_grid(i, j);
				v_new = solution_prev(i, j) + tau1 * (b_ij - tmp);

				eps_cur = abs(v_old - v_new);
				if (eps_cur > eps_max)
					eps_max = eps_cur;
				solution(i, j) = v_new;
			}
		iterations++;
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
		}
	}
	iterations_cur = iterations;
	matrix = real_solution;
}


template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Chebyshev_Iteration_Method(int k) {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);
	MatrixXd real_solution;

	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);
	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;  //нужно поменять начальное приближение

	real_solution = solution;
	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = 1 / (x_step * x_step);
	k2 = 1 / (y_step * y_step);
	a2 = -2 * (h2 + k2);

	//double tau = (1 / a2);
	const double MyPi = 3.141592653589793;
	VectorXd tau(k); //
	for (int i = 0; i < k; i++) {
		tau(i) = 1.0 / (a2 + a2 * cos((MyPi / (2 * k)) * (1 + 2 * i)));
		//tau(i) = 1 / a2;
	}
	//double ss = tau(0);
	//double o0 = tau(1);

	int c = 0;
	while (f) {

		for (int s = 0; s < k; s++){
			eps_max = 0;
			solution_prev = solution;

			for (int j = 1; j <= solution.cols() - 2; j++) {
				for (int i = 1; i <= solution.rows() - 2; i++) {
					v_old = solution_prev(i, j);

					double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j)) + k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
					double b_ij = laplacian_grid(i, j);
					v_new = solution_prev(i, j) +  (b_ij - tmp) * tau(s);

					eps_cur = fabs(v_old - v_new);
					if (eps_cur > eps_max)
						eps_max = eps_cur;

					solution(i, j) = v_new;
				}
			}
			c++;
			//std::cout << c << std::endl;
			//std::cout << solution << std::endl << std::endl;
		}
		//real_solution = solution;

		iterations++;
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
		}
	}
	//std::cout << matrix2 << std::endl << std::endl;
	iterations_cur = iterations;
	matrix = solution;
}

