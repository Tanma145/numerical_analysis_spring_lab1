#pragma once
#include <math.h>
#include <array>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../Dirichlet_Problem/Dirichlet_Problem_Solution.h"
#define PI 3.141592653589793

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
	private: System::Windows::Forms::ComboBox^ comboBox_method;
	private: System::Windows::Forms::TextBox^ textBox_optimal_SOR;


	private: System::Windows::Forms::Label^ label12;

	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBox_residual;
	private: System::Windows::Forms::ComboBox^ comboBox_initial_approximation;
	private: System::Windows::Forms::Button^ button1;







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
			this->comboBox_method = (gcnew System::Windows::Forms::ComboBox());
			this->textBox_optimal_SOR = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox_residual = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_initial_approximation = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_exact))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_numerical))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_error))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox_precision
			// 
			this->textBox_precision->Location = System::Drawing::Point(185, 66);
			this->textBox_precision->Name = L"textBox_precision";
			this->textBox_precision->Size = System::Drawing::Size(125, 20);
			this->textBox_precision->TabIndex = 0;
			this->textBox_precision->Text = L"0,5e-6";
			// 
			// textBox_max_iterations
			// 
			this->textBox_max_iterations->Location = System::Drawing::Point(185, 101);
			this->textBox_max_iterations->Name = L"textBox_max_iterations";
			this->textBox_max_iterations->Size = System::Drawing::Size(125, 20);
			this->textBox_max_iterations->TabIndex = 1;
			this->textBox_max_iterations->Text = L"1000";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 69);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(54, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"��������";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 95);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(145, 26);
			this->label2->TabIndex = 3;
			this->label2->Text = L"������������ ����������\r\n��������\r\n";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 142);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(121, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"����� ��������� �� X";
			// 
			// textBox_y_grid
			// 
			this->textBox_y_grid->Location = System::Drawing::Point(185, 165);
			this->textBox_y_grid->Name = L"textBox_y_grid";
			this->textBox_y_grid->Size = System::Drawing::Size(125, 20);
			this->textBox_y_grid->TabIndex = 5;
			this->textBox_y_grid->Text = L"20";
			// 
			// textBox_x_grid
			// 
			this->textBox_x_grid->Location = System::Drawing::Point(185, 139);
			this->textBox_x_grid->Name = L"textBox_x_grid";
			this->textBox_x_grid->Size = System::Drawing::Size(125, 20);
			this->textBox_x_grid->TabIndex = 4;
			this->textBox_x_grid->Text = L"20";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 168);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(121, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"����� ��������� �� Y";
			// 
			// dataGridView_exact
			// 
			this->dataGridView_exact->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_exact->Location = System::Drawing::Point(316, 32);
			this->dataGridView_exact->Name = L"dataGridView_exact";
			this->dataGridView_exact->Size = System::Drawing::Size(452, 473);
			this->dataGridView_exact->TabIndex = 8;
			// 
			// dataGridView_numerical
			// 
			this->dataGridView_numerical->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_numerical->Location = System::Drawing::Point(774, 32);
			this->dataGridView_numerical->Name = L"dataGridView_numerical";
			this->dataGridView_numerical->Size = System::Drawing::Size(452, 473);
			this->dataGridView_numerical->TabIndex = 9;
			// 
			// dataGridView_error
			// 
			this->dataGridView_error->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_error->Location = System::Drawing::Point(1232, 32);
			this->dataGridView_error->Name = L"dataGridView_error";
			this->dataGridView_error->Size = System::Drawing::Size(452, 473);
			this->dataGridView_error->TabIndex = 10;
			// 
			// button_solve
			// 
			this->button_solve->Location = System::Drawing::Point(185, 191);
			this->button_solve->Name = L"button_solve";
			this->button_solve->Size = System::Drawing::Size(125, 23);
			this->button_solve->TabIndex = 11;
			this->button_solve->Text = L"������";
			this->button_solve->UseVisualStyleBackColor = true;
			this->button_solve->Click += gcnew System::EventHandler(this, &MyForm::button_solve_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(312, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(153, 20);
			this->label5->TabIndex = 12;
			this->label5->Text = L"�������� �������";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(770, 9);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(164, 20);
			this->label6->TabIndex = 13;
			this->label6->Text = L"��������� �������";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(1228, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(338, 20);
			this->label7->TabIndex = 14;
			this->label7->Text = L"�������� ��������� � ���������� �������";
			// 
			// textBox_precision_cur
			// 
			this->textBox_precision_cur->Location = System::Drawing::Point(185, 348);
			this->textBox_precision_cur->Name = L"textBox_precision_cur";
			this->textBox_precision_cur->ReadOnly = true;
			this->textBox_precision_cur->Size = System::Drawing::Size(125, 20);
			this->textBox_precision_cur->TabIndex = 15;
			// 
			// textBox_iterations_cur
			// 
			this->textBox_iterations_cur->Location = System::Drawing::Point(185, 392);
			this->textBox_iterations_cur->Name = L"textBox_iterations_cur";
			this->textBox_iterations_cur->ReadOnly = true;
			this->textBox_iterations_cur->Size = System::Drawing::Size(125, 20);
			this->textBox_iterations_cur->TabIndex = 16;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(12, 351);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(120, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L"����������� ��������";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(12, 388);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(133, 26);
			this->label9->TabIndex = 18;
			this->label9->Text = L"����������� ����������\r\n��������";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(12, 433);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(146, 26);
			this->label10->TabIndex = 20;
			this->label10->Text = L"������������ ����������\r\n�����������";
			// 
			// textBox_error_max
			// 
			this->textBox_error_max->Location = System::Drawing::Point(185, 435);
			this->textBox_error_max->Name = L"textBox_error_max";
			this->textBox_error_max->ReadOnly = true;
			this->textBox_error_max->Size = System::Drawing::Size(125, 20);
			this->textBox_error_max->TabIndex = 19;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(12, 15);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(175, 39);
			this->label11->TabIndex = 21;
			this->label11->Text = L"u(x, y) = exp(1 - x^2 - y^2)\r\n-1 <= x <= 1\r\n-1 <= y <= 1";
			// 
			// comboBox_method
			// 
			this->comboBox_method->FormattingEnabled = true;
			this->comboBox_method->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"����� �������", L"����� ������� �����������",
					L"����� ������� ��������", L"����� � ����������� ������� ����������"
			});
			this->comboBox_method->Location = System::Drawing::Point(15, 220);
			this->comboBox_method->Name = L"comboBox_method";
			this->comboBox_method->Size = System::Drawing::Size(295, 21);
			this->comboBox_method->TabIndex = 22;
			this->comboBox_method->Text = L"������� ����� �������";
			// 
			// textBox_optimal_SOR
			// 
			this->textBox_optimal_SOR->Location = System::Drawing::Point(185, 279);
			this->textBox_optimal_SOR->Name = L"textBox_optimal_SOR";
			this->textBox_optimal_SOR->Size = System::Drawing::Size(125, 20);
			this->textBox_optimal_SOR->TabIndex = 23;
			this->textBox_optimal_SOR->Text = L"1";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(12, 282);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(98, 13);
			this->label12->TabIndex = 24;
			this->label12->Text = L"�������� ������";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(12, 488);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(86, 13);
			this->label13->TabIndex = 27;
			this->label13->Text = L"����� �������";
			// 
			// textBox_residual
			// 
			this->textBox_residual->Location = System::Drawing::Point(185, 485);
			this->textBox_residual->Name = L"textBox_residual";
			this->textBox_residual->ReadOnly = true;
			this->textBox_residual->Size = System::Drawing::Size(125, 20);
			this->textBox_residual->TabIndex = 26;
			// 
			// comboBox_initial_approximation
			// 
			this->comboBox_initial_approximation->FormattingEnabled = true;
			this->comboBox_initial_approximation->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"�������", L"�������� ������������ ����� X" });
			this->comboBox_initial_approximation->Location = System::Drawing::Point(15, 247);
			this->comboBox_initial_approximation->Name = L"comboBox_initial_approximation";
			this->comboBox_initial_approximation->Size = System::Drawing::Size(295, 21);
			this->comboBox_initial_approximation->TabIndex = 28;
			this->comboBox_initial_approximation->Text = L"������� ��������� �����������";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(185, 305);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(125, 37);
			this->button1->TabIndex = 25;
			this->button1->Text = L"����������� �������� ���";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1696, 595);
			this->Controls->Add(this->comboBox_initial_approximation);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->textBox_residual);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->textBox_optimal_SOR);
			this->Controls->Add(this->comboBox_method);
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

		double error_max = 0;

		//������� ������
		Dirichlet_Problem_Square_Test problem(-1, 1, -1, 1);

		//������� ����� ������
		int n = Convert::ToInt32(textBox_x_grid->Text);
		int m = Convert::ToInt32(textBox_y_grid->Text);
		Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Test> answer(n, m, problem);

		//���-�� �������� � ��������
		int max_iterations = Convert::ToInt32(textBox_max_iterations->Text);
		double precision = Convert::ToDouble(textBox_precision->Text);
		answer.setIterations(max_iterations);
		answer.setPrecision(precision);
		answer.exact_solution();

		//����� ���������� �����������
		int selectedIndex_IA = comboBox_initial_approximation->SelectedIndex;
		switch (selectedIndex_IA) {
		case 0:
			answer.initial_approximation_zero();
			break;
		case 1:
			answer.initial_approximation_linear_inerpolation_x();
			break;

		//�������� ������
		double omega = Convert::ToDouble(textBox_optimal_SOR->Text);

		//����� ������
		int selectedIndex = comboBox_method->SelectedIndex;
		switch (selectedIndex) {
		case 0:
			answer.Zeidel();
			break;
		case 1:
			answer.SOR(omega);
			break;
		case 2:
			answer.Fixed_Point_Iteration();
			break;
		case 3:
			answer.Chebyshev_Iteration_Method((int)omega);
			break;
		}

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
		textBox_residual->Text = Convert::ToString(answer.residual);
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int n = Convert::ToInt32(textBox_x_grid->Text);
		int m = Convert::ToInt32(textBox_y_grid->Text);
		double h = 2 / (double)n;
		double k = 2 / (double)m;
		double lambda = 2 * k * k / (h * h + k * k) * pow(sin(PI * h / 4), 2) + 2 * h * h / (h * h + k * k) * pow(sin(PI * k / 4), 2);
		double omega = 2 / (1 + sqrt(lambda * (2 - lambda)));
		textBox_optimal_SOR->Text = Convert::ToString(omega);
	}
};
}
