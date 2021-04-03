#pragma once
#include "Dirichlet_Problem_Square.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Dirichlet_Problem_Solution
{
private:
	double precision;
	double iterations_max;
public:
	double residual;
	double precision_cur;
	double iterations_cur;
	Dirichlet_Problem_Square problem;
	MatrixXd matrix;
	MatrixXd matrix2;
	double x_step, y_step;
	int x_grid, y_grid;
	Dirichlet_Problem_Solution();
	Dirichlet_Problem_Solution(const Dirichlet_Problem_Solution&);
	Dirichlet_Problem_Solution(int, int, Dirichlet_Problem_Square);

	void setPrecision(double);
	void setIterations(int);

	void exact_solution();
	void Zeidel();
};

Dirichlet_Problem_Solution::Dirichlet_Problem_Solution() {
	x_grid = 0;
	y_grid = 0;
	x_step = 0;
	y_step = 0;
}

Dirichlet_Problem_Solution::Dirichlet_Problem_Solution(const Dirichlet_Problem_Solution& copy) {
	x_step = copy.x_step;
	y_step = copy.y_step;
	x_grid = copy.x_grid;
	y_grid = copy.y_grid;
}

Dirichlet_Problem_Solution::Dirichlet_Problem_Solution(int _x_grid, int _y_grid, Dirichlet_Problem_Square _problem)
{
	Dirichlet_Problem_Square a(_problem);
	problem = a;
	x_grid = _x_grid;
	y_grid = _y_grid;
	matrix.resize(y_grid + 1, x_grid + 1);
	matrix2.resize(y_grid + 1, x_grid + 1);
	x_step = (problem.x_max - problem.x_min) / (double)x_grid;
	y_step = (problem.y_max - problem.y_min) / (double)y_grid;

	for (int i = 0; i <= x_grid; i++) {
		matrix(0, i) = problem.get_y_min_edge(problem.x_min + i * x_step);
		matrix(y_grid, i) = problem.get_y_max_edge(problem.x_min + i * x_step);
	}
	for (int i = 0; i <= y_grid; i++) {
		matrix(i, 0) = problem.get_x_min_edge(problem.y_min + i * y_step);
		matrix(i, x_grid) = problem.get_x_max_edge(problem.y_min + i * y_step);
	}
}

void Dirichlet_Problem_Solution::setPrecision(double eps) {
	precision = eps;
}

void Dirichlet_Problem_Solution::setIterations(int n) {
	iterations_max = n;
}

void Dirichlet_Problem_Solution::exact_solution() {
	for (int j = 0; j <= matrix2.cols() - 1; j++)
		for (int i = matrix2.rows() - 1; i >= 0; i--) {
			matrix2(i, j) = problem.get_exact(problem.x_min + j * x_step, problem.y_min + i * y_step);
		}
}

void Dirichlet_Problem_Solution::Zeidel() {
	MatrixXd laplacian_grid(x_grid + 1, y_grid + 1);
	MatrixXd solution(matrix);
	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.get_laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);
	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;

	int iterations = 0; // ������� �������� 
	double eps_max = 0; // ������� �������� �������� 
	double eps_cur = 0; // ��� �������� �������� �������� �������� 
	double a2, k2, h2; // ��������� �������� ������� (-A) 

	double v_old; // ������ �������� ������������� ���������� ������� v 
	double v_new; // ����� �������� ������������� ���������� ������� v 
	bool f = true; // ������� ��������� 

	h2 = 1 / (x_step * x_step);
	k2 = 1 / (y_step * y_step);
	a2 = -2 * (h2 + k2);
	while (f) {
		eps_max = 0;
		for (int j = 1; j <= solution.cols() - 2; j++)
			for (int i = solution.rows() - 2; i >=1; i--) {
				v_old = solution(i, j);
				v_new = -(k2 * (solution(i + 1, j) + solution(i - 1, j)) + h2 * (solution(i, j + 1) + solution(i, j - 1)));
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

	/*
	int m = y_grid - 1;
	int n = x_grid - 1;
	MatrixXd F((y_grid - 1), (x_grid - 1));

	for (int j = 1; j < m; j++)
		for (int i = 1; i < n; i++) {
			double x_i, y_i, sum = 0;
			x_i = problem.x_min + i * x_step;
			y_i = problem.y_min + j * y_step;

			if (j == 1)
				sum += k2 * problem.y_min_edge(x_i);
			else
				if (j == m - 1)
					sum += k2 * problem.y_max_edge(x_i);
			if (i == 1)
				sum += h2 * problem.x_min_edge(y_i);
			else
				if (i == n - 1)
					sum += h2 * problem.x_max_edge(y_i);
			F(i, j) = -laplacian_grid(i, j) - sum - 8;
		}

	double rs = 0;
	for (int j = 1; j < m; j++)
	{
		for (int i = 1; i < n; i++)
		{
			double r;
			double mult;

			if (j != 1 && j != m - 1)
			{
				if (i != 1 && i != n - 1)
					mult = k2 * solution(i, j -1) + h2 * solution(i - 1, j) + a2 * solution(i, j) + h2 * solution(i + 1, j) + k2 * solution(i, j + 1);
				else
					if (i == 1)
						mult = k2 * solution(i, j -1) + a2 * solution(i, j) + h2 * solution(i + 1, j) + k2 * solution(i, j + 1);
					else
						if (i == n - 1)
							mult = k2 * solution(i, j -1) + h2 * solution(i - 1, j) + a2 * solution(i, j) + k2 * solution(i, j + 1);
			}
			else
				if (j == 1)
				{
					if (i == 1)
						mult = a2 * solution(i, j) + h2 * solution(i + 1, j) + k2 * solution(i, j + 1);
					else
						if (i != n - 1)
							mult = h2 * solution(i - 1, j) + a2 * solution(i, j) + h2 * solution(i + 1, j) + k2 * solution(i, j + 1);
						else
							if (i == n - 1)
								mult = h2 * solution(i - 1, j) + a2 * solution(i, j) + k2 * solution(i, j + 1);
				}
				else
					if (j == m - 1)
					{
						if (i == 1)
							mult = k2 * solution(i, j -1) + a2 * solution(i, j) + h2 * solution(i + 1, j);
						else
							if (i != n - 1)
								mult = k2 * solution(i, j -1) + h2 * solution(i - 1, j) + a2 * solution(i, j) + h2 * solution(i + 1, j);
							else
								if (i == n - 1)
									mult = k2 * solution(i, j -1) + h2 * solution(i - 1, j) + a2 * solution(i, j);
					}

			r = abs(mult - F(i, j));
			rs += r * r;
		}
	}
	residual = sqrt(rs);
	*/
}

