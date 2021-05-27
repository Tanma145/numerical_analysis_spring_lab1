#pragma once
#include "Dirichlet_Problem_Square_Test.h"
#include "Dirichlet_Problem_Square_Main.h"
#include <Eigen/Dense>
#include <iostream>
#define M_PI 3.14159265358979323846

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
	double laplacian_grid(int, int);

	void exact_solution();
	void initial_approximation_zero();
	void initial_approximation_LI_x();
	void Zeidel();
	void SOR(double); //метод верхней реллаксации
	void Fixed_Point_Iteration();
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

	x_grid = _x_grid - 1;
	y_grid = _y_grid - 1;

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

template<class Dirichlet_Problem_Square_Type>
inline double Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::laplacian_grid(int i, int j)
{
	return problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::exact_solution() {
	for (int j = 0; j <= matrix2.cols() - 1; j++)
		for (int i = matrix2.rows() - 1; i >= 0; i--) {
			matrix2(i, j) = problem.exact(problem.x_min + j * x_step, problem.y_min + i * y_step);
		}
}
//НАЧАЛЬНЫЕ ПРИБЛИЖЕНИЯ
template<class Dirichlet_Problem_Square_Type>
inline void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::initial_approximation_zero()
{
	for (int i = 1; i < matrix.rows() - 1; i++)
		for (int j = 1; j < matrix.cols() - 1; j++)
			matrix(i, j) = 0;

}

template<class Dirichlet_Problem_Square_Type>
inline void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::initial_approximation_LI_x()
{
	double z1, z2;
	for (int i = 1; i < matrix.rows() - 1; i++) {
		z1 = matrix(i, 0);
		z1 = matrix(i, matrix.cols() - 1);
		for (int j = 1; j < matrix.cols() - 1; j++)
			matrix(i, j) = 0.5 * j * x_step * (z2 - z1) + z1;
	}

}

//МЕТОДЫ
template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Zeidel() {
	MatrixXd solution(matrix);

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = x_grid * x_grid / 4.0;
	k2 = y_grid * y_grid / 4.0;
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

	// Норма невязки
	double res, res_max = 0;
	for (int i = 1; i < matrix.rows() - 1; i++)
		for (int j = 1; j < matrix.cols() - 1; j++) {
			res = abs(a2 * solution(i, j) + h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)) - laplacian_grid(i, j));
			if (res > res_max)
				res_max = res;
		}
	residual = res_max;
}

template<class Dirichlet_Problem_Square_Type>
inline void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::SOR(double omega){
	MatrixXd solution(matrix);

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool flag = true; // условие остановки 

	h2 = x_grid * x_grid / 4.0;
	k2 = y_grid * y_grid / 4.0;
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

	// Норма невязки
	double res, res_max = 0;
	for (int i = 1; i < matrix.rows() - 1; i++)
		for (int j = 1; j < matrix.cols() - 1; j++) {
			double f = laplacian_grid(i, j);
			double b = a2 * solution(i, j);
			double bh = h2 * (solution(i + 1, j) + solution(i - 1, j));
			double bk = k2 * (solution(i, j + 1) + solution(i, j - 1));
			res = abs(b + bh + bk - f);
			if (res > res_max)
				res_max = res;
		}
	residual = res_max;
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Fixed_Point_Iteration() {
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = x_grid * x_grid / 4.0;
	k2 = y_grid * y_grid / 4.0;
	a2 = - 2 * (h2 + k2);

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
				v_old = solution_prev(i, j);

				double tmp = a2 * solution_prev(i, j) + h2 * (solution_prev(i + 1, j) + solution_prev(i - 1, j)) + k2 * (solution_prev(i, j + 1) + solution_prev(i, j - 1));
				double b_ij = laplacian_grid(i, j);
				v_new = solution_prev(i, j) - tau * (b_ij - tmp);

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

	// Норма невязки
	double res, res_max = 0;
	for (int i = 1; i < matrix.rows() - 1; i++)
		for (int j = 1; j < matrix.cols() - 1; j++) {
			res = abs(a2 * solution(i, j) + h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)) - laplacian_grid(i, j));
			if (res > res_max)
				res_max = res;
		}
	residual = res_max;
}

template <class Dirichlet_Problem_Square_Type>
void Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Type>::Chebyshev_Iteration_Method(int k) {
	MatrixXd solution(matrix);
	MatrixXd solution_prev(matrix);
	MatrixXd k_solution (solution);

	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = true; // условие остановки 

	h2 = x_grid * x_grid / 4.0;
	k2 = y_grid * y_grid / 4.0;
	a2 = - 2 * (h2 + k2);

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
		tau(i) = 2.0 / ((eig_val_max + eig_val_min) + (eig_val_max - eig_val_min) * cos((M_PI / (double) (2 * k)) * (1 + 2 * i))); //всё впорядке 
	}

	while (f) {
		//if (iterations % k == 0)
			eps_max = 0;
		solution_prev = solution;

		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = 1; i <= solution.rows() - 2; i++) {
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

	// Норма невязки
	double res, res_max = 0;
	for (int i = 1; i < matrix.rows() - 1; i++)
		for (int j = 1; j < matrix.cols() - 1; j++) {
			res = abs(a2 * solution(i, j) + h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)) - laplacian_grid(i, j));
			if (res > res_max)
				res_max = res;
		}
	residual = res_max;
}

