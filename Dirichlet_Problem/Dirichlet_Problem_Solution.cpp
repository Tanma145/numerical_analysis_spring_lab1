#include "Dirichlet_Problem_Solution.h"

Dirichlet_Problem_Solution::Dirichlet_Problem_Solution(){
	x_grid = 0;
	y_grid = 0;
	x_step = 0;
	y_step = 0;
}

Dirichlet_Problem_Solution::Dirichlet_Problem_Solution(const Dirichlet_Problem_Solution &copy){
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
	x_step = (problem.x_max - problem.x_min) /  (double) x_grid;
	y_step = (problem.y_max - problem.y_min) / (double) y_grid;

	for (int i = 0; i <= x_grid; i++) {
		matrix(0, i) = problem.y_min_edge(problem.x_min + i * x_step);
		matrix(y_grid, i) = problem.y_max_edge(problem.x_min + i * x_step);
	}
	for (int i = 0; i <= y_grid; i++) {
		matrix(i, 0) = problem.x_min_edge(problem.y_min + i * y_step);
		matrix(i, x_grid) = problem.x_max_edge(problem.y_min + i * y_step);
	}
}

void Dirichlet_Problem_Solution::setPrecision(double eps){
	precision = eps;
}

void Dirichlet_Problem_Solution::setIterations(int n){
	max_iterations = n;
}

void Dirichlet_Problem_Solution::exact_solution(){
	for (int i = 0; i < matrix2.rows(); i++)
		for (int j = 0; j < matrix2.cols(); j++)
			matrix2(i, j) = problem.exact(problem.x_min + i * x_step, problem.y_min + j * y_step);
}

void Dirichlet_Problem_Solution::Zeidel(){
	MatrixXd laplacian_grid(x_grid + 1, y_grid + 1);
	MatrixXd solution(matrix);
	for (int i = 0; i < laplacian_grid.rows(); i++)
		for (int j = 0; j < laplacian_grid.cols(); j++)
			laplacian_grid(i, j) = problem.laplacian(problem.x_min + i * x_step, problem.y_min + j * y_step);
	for (int i = 1; i < solution.rows() - 1; i++)
		for (int j = 1; j < solution.cols() - 1; j++)
			solution(i, j) = 0;


	//int Nmax = 10000; // максимальное число итераций (не менее 1) 
	//double eps = 1e-7; // минимально допустимый прирост 
	int iterations = 0; // счетчик итераций 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	double a2, k2, h2; // ненулевые элементы матрицы (-A) 

	double v_old; // старое значение преобразуемой компоненты вектора v 
	double v_new; // новое значение преобразуемой компоненты вектора v 
	bool f = false; // условие остановки 

	h2 = 1 / (x_step * x_step);
	k2 = 1 / (y_step * y_step);
	a2 = - 2 * (h2 + k2);
	while (!f){ 
		eps_max = 0;
		for (int j = 1; j < solution.cols() - 1; j++)
			for (int i = 1; i < solution.rows() - 1; i++){
				v_old = solution(i, j);
				v_new = -(h2 * (solution(i + 1, j) + solution(i - 1, j)) + k2 * (solution(i, j + 1) + solution(i, j - 1)));
				v_new = v_new + laplacian_grid(i, j);
				v_new = v_new / a2;
				eps_cur = fabs(v_old - v_new);
				if (eps_cur > eps_max) 
					eps_max = eps_cur;
				solution(i, j) = v_new;
			}
		iterations++;
		if ((eps_max < precision) or (iterations >= max_iterations))
			f = true;
	}
	matrix = solution;
}

void Dirichlet_Problem_Solution::solve(){
	MatrixXd SLE((x_grid - 1) * (y_grid - 1), (x_grid - 1) * (y_grid - 1));
	VectorXd F((x_grid - 1) * (y_grid - 1));
	double h2 = 1.0 / (x_step * x_step);
	double k2 = 1.0 / (y_step * y_step);
	double A = -2.0 * (h2 + k2);

	for (int i = 0; i < SLE.rows(); i++)
		for (int j = 0; j < SLE.cols(); j++)
			SLE(i, j) = 0;


	for (int i = 0; i < y_grid - 1; i++) {
		SLE(i * (x_grid - 1), i * (x_grid - 1)) = A;
		for (int j = 1; j < x_grid - 1; j++) {
			SLE(j + i * (x_grid - 1), j + i * (x_grid - 1)) = A;
			SLE(j + i * (x_grid - 1) - 1, j + i * (x_grid - 1)) = h2;
			SLE(j + i * (x_grid - 1), j + i * (x_grid - 1) - 1) = h2;
		}
		if (i > 0) {
			for (int k = 0; k < x_grid - 1; k++) {
				SLE(k + (i - 1) * (x_grid - 1), k + i * (x_grid - 1)) = k2;
				SLE(k + i * (x_grid - 1), k + (i - 1) * (x_grid - 1)) = k2;
			}
		}
	}
	for (int i = 0; i < F.size(); i++) {
		F(i) -= problem.laplacian(problem.x_min + i * x_step, problem.y_min + i * y_step);
	}

	int Nmax = 10000; // максимальное число итераций (не менее 1) 
	int S = 0; // счетчик итераций 
	double eps = 0.0000001; // минимально допустимый прирост 
	double eps_max = 0; // текущее значение прироста 
	double eps_cur = 0; // для подсчета текущего значения прироста 
	const int n = 4; //размерность системы линейных уравнений 
	double a[n][n]; // элементы матрицы A 
	double x[n]; // искомый вектор x 
	double b[n]; // вектор правой части b 
	int i, j; //индексы 
	double x_old; // старое значение преобразуемой компоненты вектора x 
	double x_new; // новое значение преобразуемой компоненты вектора x 
	bool f = false; // условие остановки 
	while (!f){ 
		eps_max = 0;
		for (i = 0; i < n; i++){ 
			x_old = x[i];
			x_new = b[i];
			for (j = 0; j < n; j++)
				if (j != i)
					x_new = x_new - a[i][j] * x[j];
			x_new = x_new / a[i][i];
			eps_cur = fabs(x_old - x_new);
			if (eps_cur > eps_max) { eps_max = eps_cur; }
			x[i] = x_new;
		}
		S = S + 1;
		if ((eps_max < eps) or (S >= Nmax)) { f = true; }
	}
}
