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

	private: System::Windows::Forms::DataGridView^ dataGridView_numerical;
	private: System::Windows::Forms::DataGridView^ dataGridView_double;

	private: System::Windows::Forms::Button^ button_solve;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox_precision_cur;
	private: System::Windows::Forms::TextBox^ textBox_iterations_cur;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;


	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::DataGridView^ dataGridView_error;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBox_optimal_SOR;
	private: System::Windows::Forms::ComboBox^ comboBox_method;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ textBox_error_max;
	private: System::Windows::Forms::ComboBox^ comboBox_initial_approximation;

	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBox_residual;
	private: System::Windows::Forms::TextBox^ textBox_optimal_SOR2;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ textBox_residual2;
	private: System::Windows::Forms::TextBox^ textBox_iterations_cur2;
	private: System::Windows::Forms::TextBox^ textBox_precision_cur2;
	private: System::Windows::Forms::TextBox^ textBox_max_iterations2;
	private: System::Windows::Forms::TextBox^ textBox_precision2;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ textBox_max_point;
	private: System::Windows::Forms::TextBox^ textBox_residual02;

	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ textBox_residual0;




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
			this->dataGridView_numerical = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView_double = (gcnew System::Windows::Forms::DataGridView());
			this->button_solve = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox_precision_cur = (gcnew System::Windows::Forms::TextBox());
			this->textBox_iterations_cur = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->dataGridView_error = (gcnew System::Windows::Forms::DataGridView());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox_optimal_SOR = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_method = (gcnew System::Windows::Forms::ComboBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox_error_max = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_initial_approximation = (gcnew System::Windows::Forms::ComboBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox_residual = (gcnew System::Windows::Forms::TextBox());
			this->textBox_optimal_SOR2 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox_residual2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_iterations_cur2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_precision_cur2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_max_iterations2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_precision2 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox_max_point = (gcnew System::Windows::Forms::TextBox());
			this->textBox_residual02 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox_residual0 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_numerical))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_double))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_error))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox_precision
			// 
			this->textBox_precision->Location = System::Drawing::Point(212, 257);
			this->textBox_precision->Name = L"textBox_precision";
			this->textBox_precision->Size = System::Drawing::Size(125, 20);
			this->textBox_precision->TabIndex = 0;
			this->textBox_precision->Text = L"0,5e-6";
			// 
			// textBox_max_iterations
			// 
			this->textBox_max_iterations->Location = System::Drawing::Point(212, 292);
			this->textBox_max_iterations->Name = L"textBox_max_iterations";
			this->textBox_max_iterations->Size = System::Drawing::Size(125, 20);
			this->textBox_max_iterations->TabIndex = 1;
			this->textBox_max_iterations->Text = L"1000";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 257);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(54, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Точность";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 287);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(145, 26);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Максимальное количество\r\nитераций\r\n";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 86);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(121, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Число разбиений по X";
			// 
			// textBox_y_grid
			// 
			this->textBox_y_grid->Location = System::Drawing::Point(212, 109);
			this->textBox_y_grid->Name = L"textBox_y_grid";
			this->textBox_y_grid->Size = System::Drawing::Size(256, 20);
			this->textBox_y_grid->TabIndex = 5;
			this->textBox_y_grid->Text = L"20";
			// 
			// textBox_x_grid
			// 
			this->textBox_x_grid->Location = System::Drawing::Point(212, 83);
			this->textBox_x_grid->Name = L"textBox_x_grid";
			this->textBox_x_grid->Size = System::Drawing::Size(256, 20);
			this->textBox_x_grid->TabIndex = 4;
			this->textBox_x_grid->Text = L"20";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 112);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(121, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Число разбиений по Y";
			// 
			// dataGridView_numerical
			// 
			this->dataGridView_numerical->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView_numerical->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_numerical->Location = System::Drawing::Point(524, 60);
			this->dataGridView_numerical->Name = L"dataGridView_numerical";
			this->dataGridView_numerical->Size = System::Drawing::Size(452, 473);
			this->dataGridView_numerical->TabIndex = 9;
			// 
			// dataGridView_double
			// 
			this->dataGridView_double->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView_double->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_double->Location = System::Drawing::Point(982, 60);
			this->dataGridView_double->Name = L"dataGridView_double";
			this->dataGridView_double->Size = System::Drawing::Size(452, 473);
			this->dataGridView_double->TabIndex = 10;
			// 
			// button_solve
			// 
			this->button_solve->Location = System::Drawing::Point(212, 135);
			this->button_solve->Name = L"button_solve";
			this->button_solve->Size = System::Drawing::Size(256, 20);
			this->button_solve->TabIndex = 11;
			this->button_solve->Text = L"Решить";
			this->button_solve->UseVisualStyleBackColor = true;
			this->button_solve->Click += gcnew System::EventHandler(this, &MyForm::button_solve_Click);
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(520, 37);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(164, 20);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Численное решение";
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(978, 37);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(399, 20);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Численное решение, полученное на двойной сетке";
			// 
			// textBox_precision_cur
			// 
			this->textBox_precision_cur->Location = System::Drawing::Point(212, 403);
			this->textBox_precision_cur->Name = L"textBox_precision_cur";
			this->textBox_precision_cur->ReadOnly = true;
			this->textBox_precision_cur->Size = System::Drawing::Size(125, 20);
			this->textBox_precision_cur->TabIndex = 15;
			// 
			// textBox_iterations_cur
			// 
			this->textBox_iterations_cur->Location = System::Drawing::Point(212, 436);
			this->textBox_iterations_cur->Name = L"textBox_iterations_cur";
			this->textBox_iterations_cur->ReadOnly = true;
			this->textBox_iterations_cur->Size = System::Drawing::Size(125, 20);
			this->textBox_iterations_cur->TabIndex = 16;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(12, 403);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(120, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Достигнутая точность";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(12, 432);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(133, 26);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Достигнутое количество\r\nитераций";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(12, 15);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(265, 65);
			this->label11->TabIndex = 21;
			this->label11->Text = L"f(x, y) = |x^2 - y2|\r\nmu_1(y) = -y^2 +1 mu_2(y) = (1 - y^2)exp(y)\r\nmu_3(x) = 1 - "
				L"x^2 mu_4(x) = 1 - x^2\r\n-1 <= x <= 1\r\n-1 <= y <= 1";
			// 
			// dataGridView_error
			// 
			this->dataGridView_error->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView_error->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_error->Location = System::Drawing::Point(1440, 60);
			this->dataGridView_error->Name = L"dataGridView_error";
			this->dataGridView_error->Size = System::Drawing::Size(452, 473);
			this->dataGridView_error->TabIndex = 22;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(1436, 37);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(236, 20);
			this->label5->TabIndex = 23;
			this->label5->Text = L"Разность численных решений";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(212, 344);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(256, 20);
			this->button1->TabIndex = 29;
			this->button1->Text = L"Оптимальный параметр МВР";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(12, 321);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(98, 13);
			this->label12->TabIndex = 28;
			this->label12->Text = L"Параметр метода";
			// 
			// textBox_optimal_SOR
			// 
			this->textBox_optimal_SOR->Location = System::Drawing::Point(212, 318);
			this->textBox_optimal_SOR->Name = L"textBox_optimal_SOR";
			this->textBox_optimal_SOR->Size = System::Drawing::Size(125, 20);
			this->textBox_optimal_SOR->TabIndex = 27;
			this->textBox_optimal_SOR->Text = L"1";
			// 
			// comboBox_method
			// 
			this->comboBox_method->FormattingEnabled = true;
			this->comboBox_method->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Метод Зейделя", L"Метод верхней релакцсации",
					L"Метод простой итерации", L"Метод с чебышёвским набором параметров"
			});
			this->comboBox_method->Location = System::Drawing::Point(212, 161);
			this->comboBox_method->Name = L"comboBox_method";
			this->comboBox_method->Size = System::Drawing::Size(256, 21);
			this->comboBox_method->TabIndex = 26;
			this->comboBox_method->Text = L"Выбрать метод решения";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(12, 514);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(129, 26);
			this->label10->TabIndex = 31;
			this->label10->Text = L"Максимальная разница\r\nчисленных решений";
			// 
			// textBox_error_max
			// 
			this->textBox_error_max->Location = System::Drawing::Point(212, 514);
			this->textBox_error_max->Name = L"textBox_error_max";
			this->textBox_error_max->ReadOnly = true;
			this->textBox_error_max->Size = System::Drawing::Size(256, 20);
			this->textBox_error_max->TabIndex = 30;
			// 
			// comboBox_initial_approximation
			// 
			this->comboBox_initial_approximation->FormattingEnabled = true;
			this->comboBox_initial_approximation->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Нулевое", L"Линейная интерполяция вдоль X" });
			this->comboBox_initial_approximation->Location = System::Drawing::Point(212, 188);
			this->comboBox_initial_approximation->Name = L"comboBox_initial_approximation";
			this->comboBox_initial_approximation->Size = System::Drawing::Size(256, 21);
			this->comboBox_initial_approximation->TabIndex = 32;
			this->comboBox_initial_approximation->Text = L"Выбрать начально приближение";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(12, 491);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(86, 13);
			this->label13->TabIndex = 34;
			this->label13->Text = L"Норма невязки";
			// 
			// textBox_residual
			// 
			this->textBox_residual->Location = System::Drawing::Point(212, 488);
			this->textBox_residual->Name = L"textBox_residual";
			this->textBox_residual->ReadOnly = true;
			this->textBox_residual->Size = System::Drawing::Size(125, 20);
			this->textBox_residual->TabIndex = 33;
			// 
			// textBox_optimal_SOR2
			// 
			this->textBox_optimal_SOR2->Location = System::Drawing::Point(343, 318);
			this->textBox_optimal_SOR2->Name = L"textBox_optimal_SOR2";
			this->textBox_optimal_SOR2->Size = System::Drawing::Size(125, 20);
			this->textBox_optimal_SOR2->TabIndex = 35;
			this->textBox_optimal_SOR2->Text = L"1";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(218, 241);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(119, 13);
			this->label14->TabIndex = 36;
			this->label14->Text = L"Для выбранной сетки";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(349, 241);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(105, 13);
			this->label15->TabIndex = 37;
			this->label15->Text = L"Для двойной сетки";
			// 
			// textBox_residual2
			// 
			this->textBox_residual2->Location = System::Drawing::Point(343, 488);
			this->textBox_residual2->Name = L"textBox_residual2";
			this->textBox_residual2->ReadOnly = true;
			this->textBox_residual2->Size = System::Drawing::Size(125, 20);
			this->textBox_residual2->TabIndex = 40;
			// 
			// textBox_iterations_cur2
			// 
			this->textBox_iterations_cur2->Location = System::Drawing::Point(343, 436);
			this->textBox_iterations_cur2->Name = L"textBox_iterations_cur2";
			this->textBox_iterations_cur2->ReadOnly = true;
			this->textBox_iterations_cur2->Size = System::Drawing::Size(125, 20);
			this->textBox_iterations_cur2->TabIndex = 39;
			// 
			// textBox_precision_cur2
			// 
			this->textBox_precision_cur2->Location = System::Drawing::Point(343, 403);
			this->textBox_precision_cur2->Name = L"textBox_precision_cur2";
			this->textBox_precision_cur2->ReadOnly = true;
			this->textBox_precision_cur2->Size = System::Drawing::Size(125, 20);
			this->textBox_precision_cur2->TabIndex = 38;
			// 
			// textBox_max_iterations2
			// 
			this->textBox_max_iterations2->Location = System::Drawing::Point(343, 292);
			this->textBox_max_iterations2->Name = L"textBox_max_iterations2";
			this->textBox_max_iterations2->Size = System::Drawing::Size(125, 20);
			this->textBox_max_iterations2->TabIndex = 42;
			this->textBox_max_iterations2->Text = L"1000";
			// 
			// textBox_precision2
			// 
			this->textBox_precision2->Location = System::Drawing::Point(343, 257);
			this->textBox_precision2->Name = L"textBox_precision2";
			this->textBox_precision2->Size = System::Drawing::Size(125, 20);
			this->textBox_precision2->TabIndex = 41;
			this->textBox_precision2->Text = L"0,5e-6";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(218, 543);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(103, 13);
			this->label16->TabIndex = 44;
			this->label16->Text = L"достигнута в точке";
			// 
			// textBox_max_point
			// 
			this->textBox_max_point->Location = System::Drawing::Point(343, 540);
			this->textBox_max_point->Name = L"textBox_max_point";
			this->textBox_max_point->ReadOnly = true;
			this->textBox_max_point->Size = System::Drawing::Size(125, 20);
			this->textBox_max_point->TabIndex = 43;
			// 
			// textBox_residual02
			// 
			this->textBox_residual02->Location = System::Drawing::Point(343, 462);
			this->textBox_residual02->Name = L"textBox_residual02";
			this->textBox_residual02->ReadOnly = true;
			this->textBox_residual02->Size = System::Drawing::Size(125, 20);
			this->textBox_residual02->TabIndex = 47;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(12, 465);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(142, 13);
			this->label17->TabIndex = 46;
			this->label17->Text = L"Норма начальной невязки";
			// 
			// textBox_residual0
			// 
			this->textBox_residual0->Location = System::Drawing::Point(212, 462);
			this->textBox_residual0->Name = L"textBox_residual0";
			this->textBox_residual0->ReadOnly = true;
			this->textBox_residual0->Size = System::Drawing::Size(125, 20);
			this->textBox_residual0->TabIndex = 45;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1904, 649);
			this->Controls->Add(this->textBox_residual02);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->textBox_residual0);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->textBox_max_point);
			this->Controls->Add(this->textBox_max_iterations2);
			this->Controls->Add(this->textBox_precision2);
			this->Controls->Add(this->textBox_residual2);
			this->Controls->Add(this->textBox_iterations_cur2);
			this->Controls->Add(this->textBox_precision_cur2);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->textBox_optimal_SOR2);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->textBox_residual);
			this->Controls->Add(this->comboBox_initial_approximation);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->textBox_error_max);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->textBox_optimal_SOR);
			this->Controls->Add(this->comboBox_method);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->dataGridView_error);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox_iterations_cur);
			this->Controls->Add(this->textBox_precision_cur);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button_solve);
			this->Controls->Add(this->dataGridView_double);
			this->Controls->Add(this->dataGridView_numerical);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox_y_grid);
			this->Controls->Add(this->textBox_x_grid);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox_max_iterations);
			this->Controls->Add(this->textBox_precision);
			this->Name = L"MyForm";
			this->Text = L"Задача Дирихле для уравнения Пуассона. Вариант 3. Основная задача.";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_numerical))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_double))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_error))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_solve_Click(System::Object^ sender, System::EventArgs^ e) {
		dataGridView_numerical->Columns->Clear();
		dataGridView_double->Columns->Clear();
		dataGridView_error->Columns->Clear();

		double error_max = 0;

		//услолия задачи
		Dirichlet_Problem_Square_Test problem(-1, 1, -1, 1);

		//параметры метода
		int n = Convert::ToInt32(textBox_x_grid->Text);
		int m = Convert::ToInt32(textBox_y_grid->Text);
		Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Main> answer(n, m, problem);
		Dirichlet_Problem_Solution<Dirichlet_Problem_Square_Main> answer_double(2 * n, 2 * m, problem);

		int max_iterations  = Convert::ToInt32(textBox_max_iterations->Text);
		int max_iterations2 = Convert::ToInt32(textBox_max_iterations2->Text);
		double precision    = Convert::ToDouble(textBox_precision->Text);
		double precision2   = Convert::ToDouble(textBox_precision2->Text);
		answer.setIterations(max_iterations);
		answer.setPrecision(precision);
		answer_double.setIterations(max_iterations2);
		answer_double.setPrecision(precision2);

		//Выбор начального приближения
		int selectedIndexIA = comboBox_initial_approximation->SelectedIndex;
		switch (selectedIndexIA) {
		case 0:
			answer.initial_approximation_zero();
			answer_double.initial_approximation_zero();
			break;
		case 1:
			answer.initial_approximation_LI_x();
			answer_double.initial_approximation_LI_x();
			break;
		default:
			answer.initial_approximation_zero();
			answer_double.initial_approximation_zero();
			break;
		}
		textBox_residual0->Text = Convert::ToString(answer.calculate_residual());
		textBox_residual02->Text = Convert::ToString(answer_double.calculate_residual());
		

		//параметр метода
		double omega = Convert::ToDouble(textBox_optimal_SOR->Text);
		double omega2 = Convert::ToDouble(textBox_optimal_SOR2->Text);
		//выбор метода
		int selectedIndex = comboBox_method->SelectedIndex;
		switch (selectedIndex) {
		case 0:
			answer.Zeidel();
			answer_double.Zeidel();
			break;
		case 1:
			answer.SOR(       omega );
			answer_double.SOR(omega2);
			break;
		case 2:
			answer.Fixed_Point_Iteration();
			answer_double.Fixed_Point_Iteration();
			break;
		case 3:
			answer.Chebyshev_Iteration_Method(       (int)omega );
			answer_double.Chebyshev_Iteration_Method((int)omega2);
			break;
		}

		// Подготовка таблиц
		for (int i = 0; i < answer.matrix.cols(); i++) {
			char* col_name = "Column";
			col_name += i;
			double xx = round((i * answer.x_step + answer.problem.x_min) * 1e6) / 1e6;
			dataGridView_numerical->Columns->Add(Convert::ToString(col_name), Convert::ToString(xx));
			dataGridView_double->Columns->Add(   Convert::ToString(col_name), Convert::ToString(xx));
			dataGridView_error->Columns->Add(    Convert::ToString(col_name), Convert::ToString(xx));
		}

		// Заполнение таблиц
		double x_of_max, y_of_max;
		for (int i = 0; i < answer.matrix.rows(); i++) {
			dataGridView_numerical->Rows->Add();
			dataGridView_double->Rows->Add();
			dataGridView_error->Rows->Add();
			for (int j = 0; j < answer.matrix.cols(); j++) {
				dataGridView_numerical->Rows[i]->Cells[j]->Value = answer.matrix(i, j);
				dataGridView_double->Rows[i]->Cells[j]->Value = answer_double.matrix(2 * i, 2 * j);
				double error = abs(answer_double.matrix(2 * i, 2 * j ) - answer.matrix(i, j));
				if (error > error_max) {
					error_max = error;
					x_of_max = answer.problem.x_min + answer.x_step * j;
					y_of_max = answer.problem.y_min + answer.y_step * i;
				}
				dataGridView_error->Rows[i]->Cells[j]->Value = error;
			}
		}
		textBox_precision_cur->Text   = Convert::ToString(       answer.precision_cur);
		textBox_precision_cur2->Text  = Convert::ToString(answer_double.precision_cur);
		textBox_iterations_cur->Text  = Convert::ToString(       answer.iterations_cur);
		textBox_iterations_cur2->Text = Convert::ToString(answer_double.iterations_cur);
		textBox_residual->Text        = Convert::ToString(       answer.residual);
		textBox_residual2->Text       = Convert::ToString(answer_double.residual);
		textBox_error_max->Text       = Convert::ToString(error_max);
		x_of_max = round((x_of_max) * 1e6) / 1e6;
		y_of_max = round((y_of_max) * 1e6) / 1e6;
		textBox_max_point->Text = "";
		textBox_max_point->Text += "(";
		textBox_max_point->Text += x_of_max;
		textBox_max_point->Text += "; ";
		textBox_max_point->Text += y_of_max;
		textBox_max_point->Text += ")";
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int n = Convert::ToInt32(textBox_x_grid->Text);
		int m = Convert::ToInt32(textBox_y_grid->Text);
		double lambda = 2 * n * n / (double)(n * n + m * m) * pow(sin(0.5 * PI / n), 2) + 2 * m * m / (double)(n * n + m * m) * pow(sin(0.5 * PI / m), 2);
		double omega = 2 / (1 + sqrt(lambda * (2 - lambda)));
		textBox_optimal_SOR->Text = Convert::ToString(omega);

		n = 2 * n;
		m = 2 * m;
		double lambda2 = 2 * n * n / (double)(n * n + m * m) * pow(sin(0.5 * PI / n), 2) + 2 * m * m / (double)(n * n + m * m) * pow(sin(0.5 * PI / m), 2);
		double omega2 = 2 / (1 + sqrt(lambda2 * (2 - lambda2)));
		textBox_optimal_SOR2->Text = Convert::ToString(omega2);
	}
};
}
