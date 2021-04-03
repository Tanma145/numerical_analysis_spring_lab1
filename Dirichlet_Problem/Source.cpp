#include "Dirichlet_Problem_Solution.h"
#include <conio.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	cout << "u(x, y) = 1 - (x - 1.0)^2 - (y - 0.5)^2" << endl;
	cout << "f(x, y) = 4" << endl;
	cout << "mu_1(y) = u(a, y) = -(y - 0.5)^2" << endl;
	cout << "mu_2(y) = u(b, y) = -(y - 0.5)^2" << endl;
	cout << "mu_3(x) = u(x, c) = 0.75 - (x - 1.0)^2" << endl;
	cout << "mu_4(x) = u(x, d) = 0.75 - (x - 1.0)^2" << endl;
	cout << "a = 0, b = 2, c = 0, d = 1" << endl << endl;
	int n = 3, m = 3;
	cout << "n = " << n << ", m = " << m << endl;
	Dirichlet_Problem_Square square(0, 2.0, 0, 1.0);
	Dirichlet_Problem_Solution answer(n, m, square);
	cout.precision(3);
	//cout << answer.matrix << endl << endl;

	answer.exact_solution();
	cout << "Точное решение:" << endl << answer.matrix2 << endl << endl;

	answer.setPrecision(1e-8);
	answer.setIterations(200);
	answer.Zeidel();
	cout << "Численное решение:" << endl << answer.matrix << endl << endl;
	cout << "Достигнутая точность:" << answer.precision_cur << endl;
	cout << "Количество итераций: " << answer.iterations_cur << endl;
	cout.precision(16);
	cout << "Невязка:" << answer.residual << endl;

	double error, error_max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			error = abs(answer.matrix(i, j) - answer.matrix2(i, j));
			if (error > error_max)
				error_max = error;
		}
	}
	cout << "Погрешность решения СЛАУ:" << error_max << endl;

	_getch();
}