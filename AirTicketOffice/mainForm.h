#pragma once
#include "common.h"
#include "work_with_tables.h"

namespace AirTicketOffice {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text::RegularExpressions;

	/// <summary>
	/// Сводка для mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	public:
		mainForm(void)
		{
			InitializeComponent();
			// todo: вызов нужной функции в зависимости от роли
			
			asMainManager (flightsTable, planesTable, planeParamTable, tabControl1);
			FillCombo("SELECT model FROM airlines.plane_parametrs","model",delPlaneParamModelComboBox);
			FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlanesParamModelComboBox);
			FillCombo("SELECT model FROM airlines.plane_parametrs","model",addPlaneModelComboBox);
			FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlaneModelComboBox);
			FillCombo("SELECT id_plane FROM airlines.planes","id_plane",updPlaneIdComboBox);
			FillCombo("SELECT id_plane FROM airlines.planes","id_plane",delPlaneIdComboBox);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~mainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  mainGrid;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  usersPage;
	private: System::Windows::Forms::TabPage^  tellersPage;
	private: System::Windows::Forms::TabPage^  managersPage;

	private: System::Windows::Forms::TabPage^  adminsPage;
	private: System::Windows::Forms::TabControl^  orgTab;
	private: System::Windows::Forms::TabPage^  manageFlights;
	private: System::Windows::Forms::DataGridView^  flightsTable;
	private: System::Windows::Forms::TabPage^  managePlanes;
	private: System::Windows::Forms::DataGridView^  planesTable;
	private: System::Windows::Forms::DataGridView^  planeParamTable;

	private: System::Windows::Forms::TabPage^  cargoPage;
	private: System::Windows::Forms::GroupBox^  planesParamGroupBox;
	private: System::Windows::Forms::GroupBox^  planesGroupBox;
	private: System::Windows::Forms::Button^  addPlanesParamButton;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::TextBox^  planesParamModelTextBox;
	private: System::Windows::Forms::NumericUpDown^  spotNumericUpDown;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  addPlanesParametrsGroupBox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  updatePlanesParamButton;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  newPlanesParamModelTextBox;
	private: System::Windows::Forms::NumericUpDown^  newSpotNumericUpDown;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ComboBox^  delPlaneParamModelComboBox;

	private: System::Windows::Forms::Button^  deletePlanesParametrsButton;
	private: System::Windows::Forms::ComboBox^  updPlanesParamModelComboBox;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  addPlaneCompanyTextBox;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ComboBox^  addPlaneModelComboBox;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  addPlaneButton;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Button^  updPlaneButton;


	private: System::Windows::Forms::TextBox^  updPlaneCompanyTextBox;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ComboBox^  updPlaneModelComboBox;
	private: System::Windows::Forms::ComboBox^  updPlaneIdComboBox;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Button^  deletePlaneButton;
	private: System::Windows::Forms::ComboBox^  delPlaneIdComboBox;
	private: System::Windows::Forms::Label^  label12;



	protected: 

	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->mainGrid = (gcnew System::Windows::Forms::DataGridView());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->usersPage = (gcnew System::Windows::Forms::TabPage());
			this->tellersPage = (gcnew System::Windows::Forms::TabPage());
			this->cargoPage = (gcnew System::Windows::Forms::TabPage());
			this->managersPage = (gcnew System::Windows::Forms::TabPage());
			this->orgTab = (gcnew System::Windows::Forms::TabControl());
			this->manageFlights = (gcnew System::Windows::Forms::TabPage());
			this->flightsTable = (gcnew System::Windows::Forms::DataGridView());
			this->managePlanes = (gcnew System::Windows::Forms::TabPage());
			this->planesParamGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->delPlaneParamModelComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->deletePlanesParametrsButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->updPlanesParamModelComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->updatePlanesParamButton = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->newPlanesParamModelTextBox = (gcnew System::Windows::Forms::TextBox());
			this->newSpotNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->addPlanesParametrsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->spotNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->planesParamModelTextBox = (gcnew System::Windows::Forms::TextBox());
			this->addPlanesParamButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->planesGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->deletePlaneButton = (gcnew System::Windows::Forms::Button());
			this->delPlaneIdComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->updPlaneButton = (gcnew System::Windows::Forms::Button());
			this->updPlaneCompanyTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->updPlaneModelComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->updPlaneIdComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->addPlaneCompanyTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->addPlaneModelComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->addPlaneButton = (gcnew System::Windows::Forms::Button());
			this->planeParamTable = (gcnew System::Windows::Forms::DataGridView());
			this->planesTable = (gcnew System::Windows::Forms::DataGridView());
			this->adminsPage = (gcnew System::Windows::Forms::TabPage());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainGrid))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->usersPage->SuspendLayout();
			this->managersPage->SuspendLayout();
			this->orgTab->SuspendLayout();
			this->manageFlights->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->flightsTable))->BeginInit();
			this->managePlanes->SuspendLayout();
			this->planesParamGroupBox->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->newSpotNumericUpDown))->BeginInit();
			this->addPlanesParametrsGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->spotNumericUpDown))->BeginInit();
			this->planesGroupBox->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->planeParamTable))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->planesTable))->BeginInit();
			this->SuspendLayout();
			// 
			// mainGrid
			// 
			this->mainGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->mainGrid->Location = System::Drawing::Point(31, 16);
			this->mainGrid->Name = L"mainGrid";
			this->mainGrid->Size = System::Drawing::Size(240, 150);
			this->mainGrid->TabIndex = 0;
			this->mainGrid->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::mainGrid_CellContentClick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->usersPage);
			this->tabControl1->Controls->Add(this->tellersPage);
			this->tabControl1->Controls->Add(this->cargoPage);
			this->tabControl1->Controls->Add(this->managersPage);
			this->tabControl1->Controls->Add(this->adminsPage);
			this->tabControl1->Location = System::Drawing::Point(-1, 1);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(839, 484);
			this->tabControl1->TabIndex = 1;
			this->tabControl1->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &mainForm::tabControl1_Selecting);
			// 
			// usersPage
			// 
			this->usersPage->Controls->Add(this->mainGrid);
			this->usersPage->Location = System::Drawing::Point(4, 22);
			this->usersPage->Name = L"usersPage";
			this->usersPage->Padding = System::Windows::Forms::Padding(3);
			this->usersPage->Size = System::Drawing::Size(831, 458);
			this->usersPage->TabIndex = 0;
			this->usersPage->Text = L"Заказ билета";
			this->usersPage->UseVisualStyleBackColor = true;
			// 
			// tellersPage
			// 
			this->tellersPage->Location = System::Drawing::Point(4, 22);
			this->tellersPage->Name = L"tellersPage";
			this->tellersPage->Padding = System::Windows::Forms::Padding(3);
			this->tellersPage->Size = System::Drawing::Size(831, 458);
			this->tellersPage->TabIndex = 1;
			this->tellersPage->Text = L"Управление билетами";
			this->tellersPage->UseVisualStyleBackColor = true;
			// 
			// cargoPage
			// 
			this->cargoPage->Location = System::Drawing::Point(4, 22);
			this->cargoPage->Name = L"cargoPage";
			this->cargoPage->Size = System::Drawing::Size(831, 458);
			this->cargoPage->TabIndex = 4;
			this->cargoPage->Text = L"Управление грузами";
			this->cargoPage->UseVisualStyleBackColor = true;
			// 
			// managersPage
			// 
			this->managersPage->Controls->Add(this->orgTab);
			this->managersPage->Location = System::Drawing::Point(4, 22);
			this->managersPage->Name = L"managersPage";
			this->managersPage->Size = System::Drawing::Size(831, 458);
			this->managersPage->TabIndex = 2;
			this->managersPage->Text = L"Рейсы и самолеты";
			this->managersPage->UseVisualStyleBackColor = true;
			// 
			// orgTab
			// 
			this->orgTab->Controls->Add(this->manageFlights);
			this->orgTab->Controls->Add(this->managePlanes);
			this->orgTab->Location = System::Drawing::Point(0, 3);
			this->orgTab->Name = L"orgTab";
			this->orgTab->SelectedIndex = 0;
			this->orgTab->Size = System::Drawing::Size(828, 455);
			this->orgTab->TabIndex = 1;
			// 
			// manageFlights
			// 
			this->manageFlights->Controls->Add(this->flightsTable);
			this->manageFlights->Location = System::Drawing::Point(4, 22);
			this->manageFlights->Name = L"manageFlights";
			this->manageFlights->Padding = System::Windows::Forms::Padding(3);
			this->manageFlights->Size = System::Drawing::Size(820, 429);
			this->manageFlights->TabIndex = 0;
			this->manageFlights->Text = L"Управление рейсами";
			this->manageFlights->UseVisualStyleBackColor = true;
			// 
			// flightsTable
			// 
			this->flightsTable->AllowUserToAddRows = false;
			this->flightsTable->AllowUserToDeleteRows = false;
			this->flightsTable->AllowUserToResizeColumns = false;
			this->flightsTable->AllowUserToResizeRows = false;
			this->flightsTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->flightsTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->flightsTable->Location = System::Drawing::Point(211, 6);
			this->flightsTable->MultiSelect = false;
			this->flightsTable->Name = L"flightsTable";
			this->flightsTable->ReadOnly = true;
			this->flightsTable->RowHeadersVisible = false;
			this->flightsTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->flightsTable->Size = System::Drawing::Size(586, 192);
			this->flightsTable->TabIndex = 1;
			// 
			// managePlanes
			// 
			this->managePlanes->Controls->Add(this->planesParamGroupBox);
			this->managePlanes->Controls->Add(this->planesGroupBox);
			this->managePlanes->Controls->Add(this->planeParamTable);
			this->managePlanes->Controls->Add(this->planesTable);
			this->managePlanes->Location = System::Drawing::Point(4, 22);
			this->managePlanes->Name = L"managePlanes";
			this->managePlanes->Padding = System::Windows::Forms::Padding(3);
			this->managePlanes->Size = System::Drawing::Size(820, 429);
			this->managePlanes->TabIndex = 1;
			this->managePlanes->Text = L"Управление самолетами";
			this->managePlanes->UseVisualStyleBackColor = true;
			// 
			// planesParamGroupBox
			// 
			this->planesParamGroupBox->Controls->Add(this->groupBox2);
			this->planesParamGroupBox->Controls->Add(this->groupBox1);
			this->planesParamGroupBox->Controls->Add(this->addPlanesParametrsGroupBox);
			this->planesParamGroupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->planesParamGroupBox->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->planesParamGroupBox->Location = System::Drawing::Point(5, 219);
			this->planesParamGroupBox->Name = L"planesParamGroupBox";
			this->planesParamGroupBox->Size = System::Drawing::Size(542, 194);
			this->planesParamGroupBox->TabIndex = 3;
			this->planesParamGroupBox->TabStop = false;
			this->planesParamGroupBox->Text = L"Параметры cамолета";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->delPlaneParamModelComboBox);
			this->groupBox2->Controls->Add(this->deletePlanesParametrsButton);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox2->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->groupBox2->Location = System::Drawing::Point(351, 19);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(181, 169);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Удаление";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label6->Location = System::Drawing::Point(6, 23);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(172, 13);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Модель самолета для удаления:";
			// 
			// delPlaneParamModelComboBox
			// 
			this->delPlaneParamModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->delPlaneParamModelComboBox->FormattingEnabled = true;
			this->delPlaneParamModelComboBox->Location = System::Drawing::Point(9, 39);
			this->delPlaneParamModelComboBox->Name = L"delPlaneParamModelComboBox";
			this->delPlaneParamModelComboBox->Size = System::Drawing::Size(121, 21);
			this->delPlaneParamModelComboBox->TabIndex = 10;
			this->delPlaneParamModelComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// deletePlanesParametrsButton
			// 
			this->deletePlanesParametrsButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->deletePlanesParametrsButton->Location = System::Drawing::Point(9, 140);
			this->deletePlanesParametrsButton->Name = L"deletePlanesParametrsButton";
			this->deletePlanesParametrsButton->Size = System::Drawing::Size(75, 23);
			this->deletePlanesParametrsButton->TabIndex = 9;
			this->deletePlanesParametrsButton->Text = L"Удалить";
			this->deletePlanesParametrsButton->UseVisualStyleBackColor = true;
			this->deletePlanesParametrsButton->Click += gcnew System::EventHandler(this, &mainForm::deletePlanesParametrsButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->updPlanesParamModelComboBox);
			this->groupBox1->Controls->Add(this->updatePlanesParamButton);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->newPlanesParamModelTextBox);
			this->groupBox1->Controls->Add(this->newSpotNumericUpDown);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->groupBox1->Location = System::Drawing::Point(144, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 169);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Редактирование";
			// 
			// updPlanesParamModelComboBox
			// 
			this->updPlanesParamModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlanesParamModelComboBox->FormattingEnabled = true;
			this->updPlanesParamModelComboBox->Location = System::Drawing::Point(9, 39);
			this->updPlanesParamModelComboBox->Name = L"updPlanesParamModelComboBox";
			this->updPlanesParamModelComboBox->Size = System::Drawing::Size(121, 21);
			this->updPlanesParamModelComboBox->TabIndex = 11;
			this->updPlanesParamModelComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updatePlanesParamButton
			// 
			this->updatePlanesParamButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updatePlanesParamButton->Location = System::Drawing::Point(9, 140);
			this->updatePlanesParamButton->Name = L"updatePlanesParamButton";
			this->updatePlanesParamButton->Size = System::Drawing::Size(75, 23);
			this->updatePlanesParamButton->TabIndex = 6;
			this->updatePlanesParamButton->Text = L"Заменить";
			this->updatePlanesParamButton->UseVisualStyleBackColor = true;
			this->updatePlanesParamButton->Click += gcnew System::EventHandler(this, &mainForm::button1_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label5->Location = System::Drawing::Point(6, 111);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(97, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Количество мест:";
			// 
			// newPlanesParamModelTextBox
			// 
			this->newPlanesParamModelTextBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->newPlanesParamModelTextBox->Location = System::Drawing::Point(9, 78);
			this->newPlanesParamModelTextBox->Name = L"newPlanesParamModelTextBox";
			this->newPlanesParamModelTextBox->Size = System::Drawing::Size(121, 20);
			this->newPlanesParamModelTextBox->TabIndex = 6;
			// 
			// newSpotNumericUpDown
			// 
			this->newSpotNumericUpDown->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->newSpotNumericUpDown->Location = System::Drawing::Point(109, 109);
			this->newSpotNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->newSpotNumericUpDown->Name = L"newSpotNumericUpDown";
			this->newSpotNumericUpDown->Size = System::Drawing::Size(41, 20);
			this->newSpotNumericUpDown->TabIndex = 7;
			this->newSpotNumericUpDown->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label4->Location = System::Drawing::Point(6, 62);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(135, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Новая модель самолета:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label3->Location = System::Drawing::Point(6, 23);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(165, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Модель самолета для замены:";
			// 
			// addPlanesParametrsGroupBox
			// 
			this->addPlanesParametrsGroupBox->Controls->Add(this->label1);
			this->addPlanesParametrsGroupBox->Controls->Add(this->spotNumericUpDown);
			this->addPlanesParametrsGroupBox->Controls->Add(this->planesParamModelTextBox);
			this->addPlanesParametrsGroupBox->Controls->Add(this->addPlanesParamButton);
			this->addPlanesParametrsGroupBox->Controls->Add(this->label2);
			this->addPlanesParametrsGroupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->addPlanesParametrsGroupBox->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->addPlanesParametrsGroupBox->Location = System::Drawing::Point(6, 19);
			this->addPlanesParametrsGroupBox->Name = L"addPlanesParametrsGroupBox";
			this->addPlanesParametrsGroupBox->Size = System::Drawing::Size(131, 169);
			this->addPlanesParametrsGroupBox->TabIndex = 6;
			this->addPlanesParametrsGroupBox->TabStop = false;
			this->addPlanesParametrsGroupBox->Text = L"Добавление";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Location = System::Drawing::Point(6, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(101, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Модель самолета:";
			// 
			// spotNumericUpDown
			// 
			this->spotNumericUpDown->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->spotNumericUpDown->Location = System::Drawing::Point(9, 79);
			this->spotNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->spotNumericUpDown->Name = L"spotNumericUpDown";
			this->spotNumericUpDown->Size = System::Drawing::Size(41, 20);
			this->spotNumericUpDown->TabIndex = 5;
			this->spotNumericUpDown->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::numericUpDown1_KeyPress);
			// 
			// planesParamModelTextBox
			// 
			this->planesParamModelTextBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->planesParamModelTextBox->Location = System::Drawing::Point(9, 40);
			this->planesParamModelTextBox->Name = L"planesParamModelTextBox";
			this->planesParamModelTextBox->Size = System::Drawing::Size(106, 20);
			this->planesParamModelTextBox->TabIndex = 0;
			// 
			// addPlanesParamButton
			// 
			this->addPlanesParamButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->addPlanesParamButton->Location = System::Drawing::Point(6, 140);
			this->addPlanesParamButton->Name = L"addPlanesParamButton";
			this->addPlanesParamButton->Size = System::Drawing::Size(75, 23);
			this->addPlanesParamButton->TabIndex = 4;
			this->addPlanesParamButton->Text = L"Добавить";
			this->addPlanesParamButton->UseVisualStyleBackColor = true;
			this->addPlanesParamButton->Click += gcnew System::EventHandler(this, &mainForm::addPlanesParamButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label2->Location = System::Drawing::Point(6, 63);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Количество мест:";
			// 
			// planesGroupBox
			// 
			this->planesGroupBox->Controls->Add(this->groupBox5);
			this->planesGroupBox->Controls->Add(this->groupBox4);
			this->planesGroupBox->Controls->Add(this->groupBox3);
			this->planesGroupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->planesGroupBox->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->planesGroupBox->Location = System::Drawing::Point(6, 6);
			this->planesGroupBox->Name = L"planesGroupBox";
			this->planesGroupBox->Size = System::Drawing::Size(541, 190);
			this->planesGroupBox->TabIndex = 2;
			this->planesGroupBox->TabStop = false;
			this->planesGroupBox->Text = L"Сведения о самолете";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->deletePlaneButton);
			this->groupBox5->Controls->Add(this->delPlaneIdComboBox);
			this->groupBox5->Controls->Add(this->label12);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox5->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->groupBox5->Location = System::Drawing::Point(350, 19);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(181, 165);
			this->groupBox5->TabIndex = 9;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Удаление";
			// 
			// deletePlaneButton
			// 
			this->deletePlaneButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->deletePlaneButton->Location = System::Drawing::Point(9, 136);
			this->deletePlaneButton->Name = L"deletePlaneButton";
			this->deletePlaneButton->Size = System::Drawing::Size(75, 23);
			this->deletePlaneButton->TabIndex = 17;
			this->deletePlaneButton->Text = L"Удалить";
			this->deletePlaneButton->UseVisualStyleBackColor = true;
			this->deletePlaneButton->Click += gcnew System::EventHandler(this, &mainForm::deletePlaneButton_Click);
			// 
			// delPlaneIdComboBox
			// 
			this->delPlaneIdComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->delPlaneIdComboBox->FormattingEnabled = true;
			this->delPlaneIdComboBox->Location = System::Drawing::Point(9, 32);
			this->delPlaneIdComboBox->Name = L"delPlaneIdComboBox";
			this->delPlaneIdComboBox->Size = System::Drawing::Size(121, 21);
			this->delPlaneIdComboBox->Sorted = true;
			this->delPlaneIdComboBox->TabIndex = 17;
			this->delPlaneIdComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label12->Location = System::Drawing::Point(6, 16);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(144, 13);
			this->label12->TabIndex = 15;
			this->label12->Text = L"№ самолета для удаления:";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->updPlaneButton);
			this->groupBox4->Controls->Add(this->updPlaneCompanyTextBox);
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->label10);
			this->groupBox4->Controls->Add(this->updPlaneModelComboBox);
			this->groupBox4->Controls->Add(this->updPlaneIdComboBox);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox4->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->groupBox4->Location = System::Drawing::Point(143, 19);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(200, 165);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Редактирование";
			// 
			// updPlaneButton
			// 
			this->updPlaneButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlaneButton->Location = System::Drawing::Point(9, 136);
			this->updPlaneButton->Name = L"updPlaneButton";
			this->updPlaneButton->Size = System::Drawing::Size(75, 23);
			this->updPlaneButton->TabIndex = 14;
			this->updPlaneButton->Text = L"Заменить";
			this->updPlaneButton->UseVisualStyleBackColor = true;
			this->updPlaneButton->Click += gcnew System::EventHandler(this, &mainForm::button1_Click_1);
			// 
			// updPlaneCompanyTextBox
			// 
			this->updPlaneCompanyTextBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlaneCompanyTextBox->Location = System::Drawing::Point(9, 112);
			this->updPlaneCompanyTextBox->Name = L"updPlaneCompanyTextBox";
			this->updPlaneCompanyTextBox->Size = System::Drawing::Size(118, 20);
			this->updPlaneCompanyTextBox->TabIndex = 14;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label11->Location = System::Drawing::Point(9, 56);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(135, 13);
			this->label11->TabIndex = 14;
			this->label11->Text = L"Новая модель самолета:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label10->Location = System::Drawing::Point(9, 96);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(61, 13);
			this->label10->TabIndex = 14;
			this->label10->Text = L"Компания:";
			// 
			// updPlaneModelComboBox
			// 
			this->updPlaneModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlaneModelComboBox->FormattingEnabled = true;
			this->updPlaneModelComboBox->Location = System::Drawing::Point(9, 72);
			this->updPlaneModelComboBox->Name = L"updPlaneModelComboBox";
			this->updPlaneModelComboBox->Size = System::Drawing::Size(121, 21);
			this->updPlaneModelComboBox->TabIndex = 16;
			this->updPlaneModelComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updPlaneIdComboBox
			// 
			this->updPlaneIdComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlaneIdComboBox->FormattingEnabled = true;
			this->updPlaneIdComboBox->Location = System::Drawing::Point(9, 32);
			this->updPlaneIdComboBox->Name = L"updPlaneIdComboBox";
			this->updPlaneIdComboBox->Size = System::Drawing::Size(121, 21);
			this->updPlaneIdComboBox->Sorted = true;
			this->updPlaneIdComboBox->TabIndex = 15;
			this->updPlaneIdComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label9->Location = System::Drawing::Point(9, 16);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(153, 13);
			this->label9->TabIndex = 14;
			this->label9->Text = L"№ самолета для изменения:";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->addPlaneCompanyTextBox);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->addPlaneModelComboBox);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->addPlaneButton);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox3->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->groupBox3->Location = System::Drawing::Point(5, 19);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(131, 165);
			this->groupBox3->TabIndex = 7;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Добавление";
			// 
			// addPlaneCompanyTextBox
			// 
			this->addPlaneCompanyTextBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->addPlaneCompanyTextBox->Location = System::Drawing::Point(6, 72);
			this->addPlaneCompanyTextBox->Name = L"addPlaneCompanyTextBox";
			this->addPlaneCompanyTextBox->Size = System::Drawing::Size(119, 20);
			this->addPlaneCompanyTextBox->TabIndex = 8;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label8->Location = System::Drawing::Point(6, 57);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(61, 13);
			this->label8->TabIndex = 13;
			this->label8->Text = L"Компания:";
			// 
			// addPlaneModelComboBox
			// 
			this->addPlaneModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->addPlaneModelComboBox->FormattingEnabled = true;
			this->addPlaneModelComboBox->Location = System::Drawing::Point(6, 33);
			this->addPlaneModelComboBox->Name = L"addPlaneModelComboBox";
			this->addPlaneModelComboBox->Size = System::Drawing::Size(121, 21);
			this->addPlaneModelComboBox->TabIndex = 12;
			this->addPlaneModelComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label7->Location = System::Drawing::Point(6, 17);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(101, 13);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Модель самолета:";
			// 
			// addPlaneButton
			// 
			this->addPlaneButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->addPlaneButton->Location = System::Drawing::Point(4, 136);
			this->addPlaneButton->Name = L"addPlaneButton";
			this->addPlaneButton->Size = System::Drawing::Size(75, 23);
			this->addPlaneButton->TabIndex = 4;
			this->addPlaneButton->Text = L"Добавить";
			this->addPlaneButton->UseVisualStyleBackColor = true;
			this->addPlaneButton->Click += gcnew System::EventHandler(this, &mainForm::addPlaneButton_Click);
			// 
			// planeParamTable
			// 
			this->planeParamTable->AllowUserToAddRows = false;
			this->planeParamTable->AllowUserToDeleteRows = false;
			this->planeParamTable->AllowUserToResizeRows = false;
			this->planeParamTable->BackgroundColor = System::Drawing::SystemColors::ControlLightLight;
			this->planeParamTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->planeParamTable->Location = System::Drawing::Point(561, 219);
			this->planeParamTable->MultiSelect = false;
			this->planeParamTable->Name = L"planeParamTable";
			this->planeParamTable->ReadOnly = true;
			this->planeParamTable->RowHeadersVisible = false;
			this->planeParamTable->Size = System::Drawing::Size(253, 194);
			this->planeParamTable->TabIndex = 1;
			this->planeParamTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::planeParamTable_CellClick);
			// 
			// planesTable
			// 
			this->planesTable->AllowUserToAddRows = false;
			this->planesTable->AllowUserToDeleteRows = false;
			this->planesTable->AllowUserToResizeRows = false;
			this->planesTable->BackgroundColor = System::Drawing::SystemColors::ControlLightLight;
			this->planesTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->planesTable->Location = System::Drawing::Point(561, 6);
			this->planesTable->MultiSelect = false;
			this->planesTable->Name = L"planesTable";
			this->planesTable->ReadOnly = true;
			this->planesTable->RowHeadersVisible = false;
			this->planesTable->Size = System::Drawing::Size(253, 190);
			this->planesTable->TabIndex = 0;
			this->planesTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::planesTable_CellClick);
			// 
			// adminsPage
			// 
			this->adminsPage->Location = System::Drawing::Point(4, 22);
			this->adminsPage->Name = L"adminsPage";
			this->adminsPage->Size = System::Drawing::Size(831, 458);
			this->adminsPage->TabIndex = 3;
			this->adminsPage->Text = L"Управление пользователями";
			this->adminsPage->UseVisualStyleBackColor = true;
			// 
			// mainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(835, 481);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"mainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"mainForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &mainForm::mainForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &mainForm::mainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainGrid))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->usersPage->ResumeLayout(false);
			this->managersPage->ResumeLayout(false);
			this->orgTab->ResumeLayout(false);
			this->manageFlights->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->flightsTable))->EndInit();
			this->managePlanes->ResumeLayout(false);
			this->planesParamGroupBox->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->newSpotNumericUpDown))->EndInit();
			this->addPlanesParametrsGroupBox->ResumeLayout(false);
			this->addPlanesParametrsGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->spotNumericUpDown))->EndInit();
			this->planesGroupBox->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->planeParamTable))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->planesTable))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void mainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 Application::Exit();
			 }
	private: System::Void mainForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void mainGrid_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 }
	private: System::Void tabControl1_Selecting(System::Object^  sender, System::Windows::Forms::TabControlCancelEventArgs^  e) {
				    if (e->TabPageIndex == 3){
						//e->Cancel = true;
            }
			 }
private: System::Void addPlanesParamButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 addPlanesParamButton->Enabled = false;
			 if(planesParamModelTextBox->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Модель' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addPlanesParamButton->Enabled = true;
				 return;
			 }
			 if(spotNumericUpDown->Value>500)
			 {
				 MessageBox::Show("Количество мест не может быть больше 500.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addPlanesParamButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 2;
			 myReader = executeReq("INSERT INTO airlines.plane_parametrs (model,spot_num) VALUES('"
								   +planesParamModelTextBox->Text+"',"+spotNumericUpDown->Value+")");
			 loadData("select * from airlines.plane_parametrs", planeParamTable);
			 FillCombo("SELECT model FROM airlines.plane_parametrs","model",delPlaneParamModelComboBox);
			 FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlanesParamModelComboBox);
			 FillCombo("SELECT model FROM airlines.plane_parametrs","model",addPlaneModelComboBox);
			 FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlaneModelComboBox);
			 addPlanesParamButton->Enabled = true;
		 }
private: System::Void numericUpDown1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 Regex^ rx = gcnew Regex("[0-9]");//регулярное выражение для цифр,
			 //которое содержит только буквы
			 String^ c1 = e->KeyChar.ToString();
			 int i = (int)e->KeyChar;
			 if (!(i == 8 || rx->IsMatch(c1)))
			 {
				 // запрет ввода любых символов, кроме цифр
				 e->Handled = true;
			 }
		 }

private: System::Void newSpotNumericUpDown_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 Regex^ rx = gcnew Regex("[0-9]");//регулярное выражение для цифр,
			 //которое содержит только буквы
			 String^ c1 = e->KeyChar.ToString();
			 int i = (int)e->KeyChar;
			 if (!(i == 8 || rx->IsMatch(c1)))
			 {
				 // запрет ввода любых символов, кроме цифр
				 e->Handled = true;
			 }
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 updatePlanesParamButton->Enabled = false;
			 if(updPlanesParamModelComboBox->Text->Length==0)
			 {
				 MessageBox::Show("Введите модель, которую нужно заменить", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updatePlanesParamButton->Enabled = true;
				 return;
			 }
			 if(newPlanesParamModelTextBox->Text->Length==0)
			 {
				 MessageBox::Show("Введите модель, которой нужно заменить старую", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updatePlanesParamButton->Enabled = true;
				 return;
			 }
			 if(newSpotNumericUpDown->Value>500)
			 {
				 MessageBox::Show("Количетсво мест не может быть больше 500.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updatePlanesParamButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 2;
			 myReader = executeReq("UPDATE airlines.plane_parametrs SET model='"+newPlanesParamModelTextBox->Text+"', spot_num ="+newSpotNumericUpDown->Value+" WHERE model = '"+updPlanesParamModelComboBox->Text+"';");
			 loadData("select * from airlines.plane_parametrs", planeParamTable);
			 loadData("select * from airlines.planes", planesTable);
			 FillCombo("SELECT model FROM airlines.plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
			 //FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlanesParamModelComboBox);
			 //FillCombo("SELECT model FROM airlines.plane_parametrs","model",addPlaneModelComboBox);
			 //FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlaneModelComboBox);
			 updatePlanesParamButton->Enabled = true;
		 }


private: System::Void deletePlanesParametrsButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 deletePlanesParametrsButton->Enabled = false;
			 if(delPlaneParamModelComboBox->Text->Length==0)
			 {
				 MessageBox::Show("Введите модель, которую нужно удалить", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 deletePlanesParametrsButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 2;
			 myReader = executeReq("DELETE FROM airlines.plane_parametrs where model='"+delPlaneParamModelComboBox->Text+"';");
			 loadData("select * from airlines.plane_parametrs", planeParamTable);
			 loadData("select * from airlines.planes", planesTable);
			 FillCombo("SELECT model FROM airlines.plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
			 //FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlanesParamModelComboBox);
			 //FillCombo("SELECT model FROM airlines.plane_parametrs","model",addPlaneModelComboBox);
			 //FillCombo("SELECT model FROM airlines.plane_parametrs","model",updPlaneModelComboBox);
			 deletePlanesParametrsButton->Enabled = true;
		 }
private: System::Void planeParamTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 updPlanesParamModelComboBox->Text = planeParamTable->CurrentRow->Cells[0]->Value->ToString();
			 newSpotNumericUpDown->Value = Convert::ToInt32(planeParamTable->CurrentRow->Cells[1]->Value->ToString(),10);
			 delPlaneParamModelComboBox->Text = planeParamTable->CurrentRow->Cells[0]->Value->ToString();
		 }
private: System::Void addPlaneButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 addPlaneButton->Enabled = false;
			 if(addPlaneModelComboBox->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Модель' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addPlaneButton->Enabled = true;
				 return;
			 }
			 if(addPlaneCompanyTextBox->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Компания' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addPlaneButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 3;
			 myReader = executeReq("INSERT INTO airlines.planes (model,company) VALUES('"+addPlaneModelComboBox->Text+"','"+addPlaneCompanyTextBox->Text+"')");
			 loadData("select * from airlines.planes", planesTable);
			 FillCombo("SELECT id_plane FROM airlines.planes","id_plane",updPlaneIdComboBox);
			 CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
			 //FillCombo("SELECT id_plane FROM airlines.planes","id_plane",delPlaneIdComboBox);
			 addPlaneButton->Enabled = true;
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 updPlaneButton->Enabled = false;
			 if(updPlaneIdComboBox->Text->Length == 0)
			 {
				 MessageBox::Show("Введите номер самолета для замены.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updPlaneButton->Enabled = true;
				 return;
			 }
			 if(updPlaneModelComboBox->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Модель' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updPlaneButton->Enabled = true;
				 return;
			 }
			 if(updPlaneCompanyTextBox->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Компания' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updPlaneButton->Enabled = true;
				 return;
			 }
			 numTab = 3;
			 MySqlDataReader^ myReader;
			 myReader = executeReq("UPDATE airlines.planes SET model='"+updPlaneModelComboBox->Text+"', company ='"+updPlaneCompanyTextBox->Text+"' WHERE id_plane = '"+updPlaneIdComboBox->Text+"';");
			 loadData("select * from airlines.planes", planesTable);
			 updPlaneButton->Enabled = true;
		 }
private: System::Void planesTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			  updPlaneIdComboBox->Text = planesTable->CurrentRow->Cells[0]->Value->ToString();
			  delPlaneIdComboBox->Text = planesTable->CurrentRow->Cells[0]->Value->ToString();
			  updPlaneModelComboBox->Text = planesTable->CurrentRow->Cells[1]->Value->ToString();
			  updPlaneCompanyTextBox->Text = planesTable->CurrentRow->Cells[2]->Value->ToString();
		 }
private: System::Void deletePlaneButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 deletePlaneButton->Enabled = false;
			 if(delPlaneIdComboBox->Text->Length == 0)
			 {
				 MessageBox::Show("Введите номер самолета для удаления.", "Ошибка",
				 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 deletePlaneButton->Enabled = true;
				 return;
			 }
			 deletePlaneButton->Enabled = true;
			 numTab = 3;
			 MySqlDataReader^ myReader;
			 myReader = executeReq("DELETE FROM airlines.planes where id_plane='"+delPlaneIdComboBox->Text+"';");
			 loadData("select * from airlines.planes", planesTable);
			 FillCombo("SELECT id_plane FROM airlines.planes","id_plane",updPlaneIdComboBox);
			 //FillCombo("SELECT id_plane FROM airlines.planes","id_plane",delPlaneIdComboBox);
			 CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
			 deletePlaneButton->Enabled = true;
		 }
private: System::Void addPlaneModelComboBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 e->Handled = true;
		 }
};
}
