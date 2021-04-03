#pragma once
#include <math.h>
#include <array>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../Dirichlet_Problem/Dirichlet_Problem_Solution.h"

namespace Graph {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ZedGraph;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox_precision;
	protected:
	private: System::Windows::Forms::TextBox^ textBox_max_iterations;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox_y_grid;

	private: System::Windows::Forms::TextBox^ textBox_x_grid;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::DataGridView^ dataGridView_exact;
	private: System::Windows::Forms::DataGridView^ dataGridView_numerical;
	private: System::Windows::Forms::DataGridView^ dataGridView_error;
	private: System::Windows::Forms::Button^ button_solve;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox_precision_cur;
	private: System::Windows::Forms::TextBox^ textBox_iterations_cur;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ textBox_error_max;
	private: System::Windows::Forms::Label^ label11;



	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox_precision = (gcnew System::Windows::Forms::TextBox());
			this->textBox_max_iterations = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox_y_grid = (gcnew System::Windows::Forms::TextBox());
			this->textBox_x_grid = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->dataGridView_exact = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView_numerical = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView_error = (gcnew System::Windows::Forms::DataGridView());
			this->button_solve = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox_precision_cur = (gcnew System::Windows::Forms::TextBox());
			this->textBox_iterations_cur = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox_error_max = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_exact))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_numerical))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_error))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox_precision
			// 
			this->textBox_precision->Location = System::Drawing::Point(163, 98);
			this->textBox_precision->Name = L"textBox_precision";
			this->textBox_precision->Size = System::Drawing::Size(100, 20);
			this->textBox_precision->TabIndex = 0;
			this->textBox_precision->Text = L"1e-8";
			// 
			// textBox_max_iterations
			// 
			this->textBox_max_iterations->Location = System::Drawing::Point(163, 133);
			this->textBox_max_iterations->Name = L"textBox_max_iterations";
			this->textBox_max_iterations->Size = System::Drawing::Size(100, 20);
			this->textBox_max_iterations->TabIndex = 1;
			this->textBox_max_iterations->Text = L"200";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 92);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(141, 26);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Максимально допустимая\r\nпогрешность метода";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 127);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(145, 26);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Максимальное количество\r\nитераций\r\n";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(36, 174);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(121, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Число разбиений по X";
			// 
			// textBox_y_grid
			// 
			this->textBox_y_grid->Location = System::Drawing::Point(163, 197);
			this->textBox_y_grid->Name = L"textBox_y_grid";
			this->textBox_y_grid->Size = System::Drawing::Size(100, 20);
			this->textBox_y_grid->TabIndex = 5;
			this->textBox_y_grid->Text = L"20";
			// 
			// textBox_x_grid
			// 
			this->textBox_x_grid->Location = System::Drawing::Point(163, 171);
			this->textBox_x_grid->Name = L"textBox_x_grid";
			this->textBox_x_grid->Size = System::Drawing::Size(100, 20);
			this->textBox_x_grid->TabIndex = 4;
			this->textBox_x_grid->Text = L"20";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(36, 200);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(121, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Число разбиений по Y";
			// 
			// dataGridView_exact
			// 
			this->dataGridView_exact->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_exact->Location = System::Drawing::Point(273, 32);
			this->dataGridView_exact->Name = L"dataGridView_exact";
			this->dataGridView_exact->Size = System::Drawing::Size(452, 473);
			this->dataGridView_exact->TabIndex = 8;
			// 
			// dataGridView_numerical
			// 
			this->dataGridView_numerical->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_numerical->Location = System::Drawing::Point(731, 32);
			this->dataGridView_numerical->Name = L"dataGridView_numerical";
			this->dataGridView_numerical->Size = System::Drawing::Size(452, 473);
			this->dataGridView_numerical->TabIndex = 9;
			// 
			// dataGridView_error
			// 
			this->dataGridView_error->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_error->Location = System::Drawing::Point(1189, 32);
			this->dataGridView_error->Name = L"dataGridView_error";
			this->dataGridView_error->Size = System::Drawing::Size(452, 473);
			this->dataGridView_error->TabIndex = 10;
			// 
			// button_solve
			// 
			this->button_solve->Location = System::Drawing::Point(174, 223);
			this->button_solve->Name = L"button_solve";
			this->button_solve->Size = System::Drawing::Size(75, 23);
			this->button_solve->TabIndex = 11;
			this->button_solve->Text = L"Решить";
			this->button_solve->UseVisualStyleBackColor = true;
			this->button_solve->Click += gcnew System::EventHandler(this, &MyForm::button_solve_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(269, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(153, 20);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Истинное решение";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(727, 9);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(164, 20);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Численное решение";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(1185, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(338, 20);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Разность истинного и численного решения";
			// 
			// textBox_precision_cur
			// 
			this->textBox_precision_cur->Location = System::Drawing::Point(138, 298);
			this->textBox_precision_cur->Name = L"textBox_precision_cur";
			this->textBox_precision_cur->Size = System::Drawing::Size(125, 20);
			this->textBox_precision_cur->TabIndex = 15;
			// 
			// textBox_iterations_cur
			// 
			this->textBox_iterations_cur->Location = System::Drawing::Point(163, 333);
			this->textBox_iterations_cur->Name = L"textBox_iterations_cur";
			this->textBox_iterations_cur->Size = System::Drawing::Size(100, 20);
			this->textBox_iterations_cur->TabIndex = 16;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(12, 301);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(120, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Достигнутая точность";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(12, 330);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(133, 26);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Достигнутое количество\r\nитераций";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(12, 370);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(146, 26);
			this->label10->TabIndex = 20;
			this->label10->Text = L"Максимальная глобальная\r\nпогрешность";
			// 
			// textBox_error_max
			// 
			this->textBox_error_max->Location = System::Drawing::Point(163, 370);
			this->textBox_error_max->Name = L"textBox_error_max";
			this->textBox_error_max->Size = System::Drawing::Size(100, 20);
			this->textBox_error_max->TabIndex = 19;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(76, 16);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(128, 39);
			this->label11->TabIndex = 21;
			this->label11->Text = L"u(x, y) = exp(1 - x^2 - y^2)\r\n-1 <= x <= 1\r\n-1 <= y <= 1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1655, 525);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->textBox_error_max);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox_iterations_cur);
			this->Controls->Add(this->textBox_precision_cur);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button_solve);
			this->Controls->Add(this->dataGridView_error);
			this->Controls->Add(this->dataGridView_numerical);
			this->Controls->Add(this->dataGridView_exact);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox_y_grid);
			this->Controls->Add(this->textBox_x_grid);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox_max_iterations);
			this->Controls->Add(this->textBox_precision);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_exact))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_numerical))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_error))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
	private: System::Void button_solve_Click(System::Object^ sender, System::EventArgs^ e) {
		dataGridView_exact->Columns->Clear();
		dataGridView_numerical->Columns->Clear();
		dataGridView_error->Columns->Clear();
		int n = Convert::ToInt32(textBox_x_grid->Text);
		int m = Convert::ToInt32(textBox_y_grid->Text);
		int max_iterations = Convert::ToInt32(textBox_max_iterations->Text);
		double precision = Convert::ToDouble(textBox_precision->Text);
		double error_max = 0;

		Dirichlet_Problem_Square problem(-1, 1, -1, 1);
		problem.set_exact(test_exact);
		problem.set_laplacian(test_laplacian);
		problem.set_x_min_edge(test_x_min_edge);
		problem.set_x_max_edge(test_x_max_edge);
		problem.set_y_min_edge(test_y_min_edge);
		problem.set_y_max_edge(test_y_max_edge);
		
		Dirichlet_Problem_Solution answer(n, m, problem);
		answer.setIterations(max_iterations);
		answer.setPrecision(precision);
		answer.exact_solution();
		answer.Zeidel();

		for (int i = 0; i < answer.matrix.cols(); i++) {
			char* col_name = "Column";
			col_name += i;
			dataGridView_exact->Columns->Add(Convert::ToString(col_name), Convert::ToString(i));
			dataGridView_numerical->Columns->Add(Convert::ToString(col_name), Convert::ToString(i));
			dataGridView_error->Columns->Add(Convert::ToString(col_name), Convert::ToString(i));
		}
		for (int i = 0; i < answer.matrix.rows(); i++) {
			dataGridView_exact->Rows->Add();
			dataGridView_numerical->Rows->Add();
			dataGridView_error->Rows->Add();
			for (int j = 0; j < answer.matrix.cols(); j++) {
				dataGridView_exact->Rows[i]->Cells[j]->Value = answer.matrix2(i, j);
				dataGridView_numerical->Rows[i]->Cells[j]->Value = answer.matrix(i, j);
				double error = abs(answer.matrix2(i, j) - answer.matrix(i, j));
				if (error > error_max)
					error_max = error;
				dataGridView_error->Rows[i]->Cells[j]->Value = error;
			}
		}
		textBox_precision_cur->Text = Convert::ToString(answer.precision_cur);
		textBox_iterations_cur->Text = Convert::ToString(answer.iterations_cur);
		textBox_error_max->Text = Convert::ToString(error_max);
	}
};
}
