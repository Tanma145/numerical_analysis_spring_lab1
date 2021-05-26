#pragma once
#include "Dirichlet_Problem_Non_Standard.h"
#include <Eigen/Dense>
#include <iostream>
#define M_PI 3.14159265358979323846

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Dirichlet_Problem_Solution_Non_Standard
{
private:
	double precision;
	int iterations_max;
public:
	double residual; //Невязка
	double precision_cur;
	int iterations_cur;
	Dirichlet_Problem_Non_Standard problem;
	MatrixXd matrix;
	MatrixXd matrix2;
	double x_step, y_step;
	int x_grid, y_grid;
	Dirichlet_Problem_Solution_Non_Standard();
	Dirichlet_Problem_Solution_Non_Standard(const Dirichlet_Problem_Solution_Non_Standard&);
	Dirichlet_Problem_Solution_Non_Standard(int, int, Dirichlet_Problem_Non_Standard);

	void setPrecision(double);
	void setIterations(int);

	void exact_solution();
	void initial_approximation();
	void SOR(double); //метод верхней реллаксации
	void Fixed_Point_Iteration();
	void Chebyshev_Iteration_Method(int);
};

Dirichlet_Problem_Solution_Non_Standard::Dirichlet_Problem_Solution_Non_Standard() {
	x_grid = 0;
	y_grid = 0;
	x_step = 0;
	y_step = 0;
}

Dirichlet_Problem_Solution_Non_Standard::Dirichlet_Problem_Solution_Non_Standard(const Dirichlet_Problem_Solution_Non_Standard& copy) {
	x_step = copy.x_step;
	y_step = copy.y_step;
	x_grid = copy.x_grid;
	y_grid = copy.y_grid;
}

Dirichlet_Problem_Solution_Non_Standard::Dirichlet_Problem_Solution_Non_Standard(int _x_grid, int _y_grid, Dirichlet_Problem_Non_Standard _problem){
	Dirichlet_Problem_Non_Standard a(_problem);
	problem = a;

	x_grid = _x_grid;
	y_grid = _y_grid;

	matrix.resize(y_grid + 1, x_grid + 1);
	matrix2.resize(y_grid + 1, x_grid + 1);
	x_step = (problem.x_max - problem.x_min) / (double)x_grid;
	y_step = (problem.y_max - problem.y_min) / (double)y_grid;

	for (int i = 0; i <= x_grid; i++)
		for (int j = 0; j <= y_grid; j++){

			if (problem.in_region(problem.x_min + i * x_step, problem.y_min + j * y_step) || problem.on_edge(problem.x_min + i * x_step, problem.y_min + j * y_step))
				matrix2(i, j) = problem.exact(problem.x_min + i * x_step, problem.y_min + j * y_step);
			else
				matrix2(i, j) = 0;

			if (problem.on_edge(problem.x_min + i * x_step, problem.y_min + j * y_step))
				matrix(i, j) = problem.exact(problem.x_min + i * x_step, problem.y_min + j * y_step);
			else
				matrix(i, j) = 0;
		}
}

void Dirichlet_Problem_Solution_Non_Standard::setPrecision(double eps) {
	precision = eps;
}

void Dirichlet_Problem_Solution_Non_Standard::setIterations(int n) {
	iterations_max = n;
}

void Dirichlet_Problem_Solution_Non_Standard::exact_solution() {
	for (int j = 0; j <= matrix2.cols() - 1; j++)
		for (int i = matrix2.rows() - 1; i >= 0; i--) {
			matrix2(i, j) = problem.exact(problem.x_min + j * x_step, problem.y_min + i * y_step);
		}
}

inline void Dirichlet_Problem_Solution_Non_Standard::initial_approximation() {

}

inline void Dirichlet_Problem_Solution_Non_Standard::SOR(double omega) {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);

	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);

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
				if (problem.in_region(problem.x_min + i * x_step, problem.y_min + j * y_step)) {

					v_old = solution(i, j);
					v_new = -omega * (h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)));
					v_new += (1 - omega) * a2 * solution(i, j) + omega * laplacian_grid(i, j);
					v_new /= a2;
					eps_cur = abs(v_old - v_new);
					if (eps_cur > eps_max)
						eps_max = eps_cur;
					solution(i, j) = v_new;
				}
			}
		iterations++;
		if (eps_max < precision || iterations >= iterations_max) {
			precision_cur = eps_max;
			flag = false;
		}
	}
	iterations_cur = iterations;
	matrix = solution;

	//невязка
	double res, res_max = 0;
	for (int j = 1; j <= solution.cols() - 2; j++)
		for (int i = solution.rows() - 2; i >= 1; i--) {
			res = abs(a2 * solution(i, j) + h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)) - laplacian_grid(i, j));
			if (res > res_max)
				res_max = res;
		}
	residual = res;
}

void Dirichlet_Problem_Solution_Non_Standard::Fixed_Point_Iteration() {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);
	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = -problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);

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

	double eig_val_min = (4.0 / (x_step * x_step))
		* sin(M_PI / (2 * x_grid))
		* sin(M_PI / (2 * x_grid))
		+ (4.0 / (y_step * y_step))
		* sin(M_PI / (2 * y_grid))
		* sin(M_PI / (2 * y_grid));

	double eig_val_max = (4.0 / (x_step * x_step))
		* sin((M_PI * (x_grid - 1)) / (2 * x_grid))
		* sin((M_PI * (x_grid - 1)) / (2 * x_grid))
		+ (4.0 / (y_step * y_step))
		* sin((M_PI * (y_grid - 1)) / (2 * y_grid))
		* sin((M_PI * (y_grid - 1)) / (2 * y_grid));


	double tau = 2.0 / (eig_val_min + eig_val_max);
	//double tau = 0.5;

	while (f) {
		eps_max = 0;
		solution_prev = solution;
		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = 1; i <= solution.rows() - 2; i++) {
				if (problem.in_region(problem.x_min + i * x_step, problem.y_min + j * y_step)) {
					v_old = solution_prev(i, j);

					double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j)) + k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
					double b_ij = laplacian_grid(i, j);
					v_new = solution_prev(i, j) + tau * (b_ij - tmp);

					eps_cur = abs(v_old - v_new);
					if (eps_cur > eps_max)
						eps_max = eps_cur;
					solution(i, j) = v_new;
				}
			}
		iterations++;
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
		}
	}
	iterations_cur = iterations;
	matrix = solution;

	//невязка
	double res, res_max = 0;
	for (int j = 1; j <= solution.cols() - 2; j++)
		for (int i = solution.rows() - 2; i >= 1; i--) {
			res = abs(a2 * solution(i, j) + h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)) - laplacian_grid(i, j));
			if (res > res_max)
				res_max = res;
		}
	residual = res;
}

void Dirichlet_Problem_Solution_Non_Standard::Chebyshev_Iteration_Method(int k) {
	MatrixXd laplacian_grid(y_grid + 1, x_grid + 1);
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);
	MatrixXd k_solution;

	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);

	k_solution = solution;
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

	double eig_val_min = (4.0 / (x_step * x_step))
		* sin(M_PI / (2 * x_grid))
		* sin(M_PI / (2 * x_grid))
		+ (4.0 / (y_step * y_step))
		* sin(M_PI / (2 * y_grid))
		* sin(M_PI / (2 * y_grid));

	double eig_val_max = (4.0 / (x_step * x_step))
		* sin((M_PI * (x_grid - 1)) / (2 * x_grid))
		* sin((M_PI * (x_grid - 1)) / (2 * x_grid))
		+ (4.0 / (y_step * y_step))
		* sin((M_PI * (y_grid - 1)) / (2 * y_grid))
		* sin((M_PI * (y_grid - 1)) / (2 * y_grid));

	//double tau = (1 / a2);
	//k = 1;
	VectorXd tau(k); //
	for (int i = 0; i < k; i++) {
		tau(i) = 2.0 / ((eig_val_max + eig_val_min) + (eig_val_max - eig_val_min) * cos((M_PI / (double)(2 * k)) * (1 + 2 * i))); //всё впорядке 
	}

	while (f) {
		//if (iterations % k == 0)
		eps_max = 0;
		solution_prev = solution;

		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = 1; i <= solution.rows() - 2; i++) {
				if (problem.in_region(problem.x_min + i * x_step, problem.y_min + j * y_step)) {
					v_old = solution_prev(i, j);

					double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j))
						+ k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
					double b_ij = laplacian_grid(i, j);
					v_new = solution_prev(i, j) - tau(iterations % k) * (b_ij - tmp);

					//вычисление "точности"
					//if (iterations % k == 0) 
					{
						eps_cur = abs(k_solution(i, j) - v_new);
						if (eps_cur > eps_max)
							eps_max = eps_cur;
					}

					solution(i, j) = v_new;
				}
			}

		//сохраняем последнее приближение
		if (iterations % k == 0)
			k_solution = solution;

		iterations++;

		//проверка условий выхода из цикла
		if ((eps_max < precision) || (iterations >= iterations_max)) {
			precision_cur = eps_max;
			f = false;
		}
	}
	//std::cout << matrix2 << std::endl << std::endl;
	iterations_cur = iterations;
	matrix = k_solution;

	//невязка
	double res, res_max = 0;
	for (int j = 1; j <= solution.cols() - 2; j++)
		for (int i = solution.rows() - 2; i >= 1; i--) {
			res = abs(a2 * solution(i, j) + h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)) - laplacian_grid(i, j));
			if (res > res_max)
				res_max = res;
		}
	residual = res;
}

