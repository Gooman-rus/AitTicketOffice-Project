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
			
			String^ r;
			switch(currRole)
			{
				case 1:
					r = "Пользователь"; 
					asUser(tabControl1, false);
					break;
				case 2:
					r = "Менеджер по билетам"; 
					asTeller(tabControl1, false);
					break;
				case 3:
					r = "Менеджер грузов"; 
					asCargoManager(tabControl1, false);
					break;
				case 4:
					r = "Организационный менеджер"; 
					asMainManager (flightsTable, planesTable, planeParamTable, tabControl1, false);
					FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",
						delPlaneParamModelComboBox);
					CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
					CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
					CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
					FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",
						updPlaneIdComboBox);
					CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
					CopyCombo(addFlightPlaneId,updPlaneIdComboBox);
					FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
						updFlightId);
					break;
				case 5:
					r = "Администратор";	
					asMainManager (flightsTable, planesTable, 
								   planeParamTable, tabControl1, true);
					FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",
						delPlaneParamModelComboBox);
					CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
					CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
					CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
					FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",
						updPlaneIdComboBox);
					CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
					CopyCombo(addFlightPlaneId,updPlaneIdComboBox);
					CopyCombo(updFlightPlaneId,updPlaneIdComboBox);
					FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
						updFlightId);
					CopyCombo(delFlightId,updFlightId);
					break;
				default: r = "Stop hacking my programm!";break;
			}
			this->Text = "AirTicketOffice - " + r; // заголовок окна
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
private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::GroupBox^  groupBox9;
private: System::Windows::Forms::GroupBox^  groupBox8;
private: System::Windows::Forms::GroupBox^  groupBox7;
private: System::Windows::Forms::DateTimePicker^  addFlightArrivalTime;

private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::DateTimePicker^  addFlightDepartTime;

private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::TextBox^  addFlightArrive;
private: System::Windows::Forms::TextBox^  addFlightDepart;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::ComboBox^  addFlightPlaneId;
private: System::Windows::Forms::Button^  addFlightButton;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::ComboBox^  updFlightId;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Button^  updFlightButton;
private: System::Windows::Forms::DateTimePicker^  updFlightArrivalDate;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::TextBox^  updFlightDest;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::TextBox^  updFlightDep;
private: System::Windows::Forms::DateTimePicker^  updFlightDepDate;
private: System::Windows::Forms::ComboBox^  updFlightPlaneId;
private: System::Windows::Forms::ComboBox^  delFlightId;
private: System::Windows::Forms::Button^  delFlightButton;

private: System::Windows::Forms::Label^  label26;




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
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->delFlightButton = (gcnew System::Windows::Forms::Button());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->delFlightId = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->updFlightId = (gcnew System::Windows::Forms::ComboBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->updFlightButton = (gcnew System::Windows::Forms::Button());
			this->updFlightArrivalDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->updFlightDest = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->updFlightDep = (gcnew System::Windows::Forms::TextBox());
			this->updFlightDepDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->updFlightPlaneId = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->addFlightButton = (gcnew System::Windows::Forms::Button());
			this->addFlightArrivalTime = (gcnew System::Windows::Forms::DateTimePicker());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->addFlightDepartTime = (gcnew System::Windows::Forms::DateTimePicker());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->addFlightArrive = (gcnew System::Windows::Forms::TextBox());
			this->addFlightDepart = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->addFlightPlaneId = (gcnew System::Windows::Forms::ComboBox());
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
			this->groupBox6->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox7->SuspendLayout();
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
			this->manageFlights->Controls->Add(this->groupBox6);
			this->manageFlights->Controls->Add(this->flightsTable);
			this->manageFlights->Location = System::Drawing::Point(4, 22);
			this->manageFlights->Name = L"manageFlights";
			this->manageFlights->Padding = System::Windows::Forms::Padding(3);
			this->manageFlights->Size = System::Drawing::Size(820, 429);
			this->manageFlights->TabIndex = 0;
			this->manageFlights->Text = L"Управление рейсами";
			this->manageFlights->UseVisualStyleBackColor = true;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->groupBox9);
			this->groupBox6->Controls->Add(this->groupBox8);
			this->groupBox6->Controls->Add(this->groupBox7);
			this->groupBox6->Location = System::Drawing::Point(3, 204);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(811, 222);
			this->groupBox6->TabIndex = 2;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Рейсы";
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->delFlightButton);
			this->groupBox9->Controls->Add(this->label26);
			this->groupBox9->Controls->Add(this->delFlightId);
			this->groupBox9->Location = System::Drawing::Point(543, 19);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(262, 197);
			this->groupBox9->TabIndex = 1;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Удаление";
			// 
			// delFlightButton
			// 
			this->delFlightButton->Location = System::Drawing::Point(185, 168);
			this->delFlightButton->Name = L"delFlightButton";
			this->delFlightButton->Size = System::Drawing::Size(71, 23);
			this->delFlightButton->TabIndex = 18;
			this->delFlightButton->Text = L"Удалить";
			this->delFlightButton->UseVisualStyleBackColor = true;
			this->delFlightButton->Click += gcnew System::EventHandler(this, &mainForm::delFlightButton_Click);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(3, 16);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(132, 13);
			this->label26->TabIndex = 18;
			this->label26->Text = L"№ Рейса для изменения";
			// 
			// delFlightId
			// 
			this->delFlightId->FormattingEnabled = true;
			this->delFlightId->Location = System::Drawing::Point(6, 36);
			this->delFlightId->Name = L"delFlightId";
			this->delFlightId->Size = System::Drawing::Size(86, 21);
			this->delFlightId->Sorted = true;
			this->delFlightId->TabIndex = 17;
			this->delFlightId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->label25);
			this->groupBox8->Controls->Add(this->updFlightId);
			this->groupBox8->Controls->Add(this->label24);
			this->groupBox8->Controls->Add(this->label23);
			this->groupBox8->Controls->Add(this->label22);
			this->groupBox8->Controls->Add(this->updFlightButton);
			this->groupBox8->Controls->Add(this->updFlightArrivalDate);
			this->groupBox8->Controls->Add(this->label19);
			this->groupBox8->Controls->Add(this->label20);
			this->groupBox8->Controls->Add(this->updFlightDest);
			this->groupBox8->Controls->Add(this->label21);
			this->groupBox8->Controls->Add(this->updFlightDep);
			this->groupBox8->Controls->Add(this->updFlightDepDate);
			this->groupBox8->Controls->Add(this->updFlightPlaneId);
			this->groupBox8->Location = System::Drawing::Point(278, 19);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(259, 197);
			this->groupBox8->TabIndex = 1;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Редактирование";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(6, 20);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(132, 13);
			this->label25->TabIndex = 17;
			this->label25->Text = L"№ Рейса для изменения";
			// 
			// updFlightId
			// 
			this->updFlightId->FormattingEnabled = true;
			this->updFlightId->Location = System::Drawing::Point(9, 36);
			this->updFlightId->Name = L"updFlightId";
			this->updFlightId->Size = System::Drawing::Size(86, 21);
			this->updFlightId->Sorted = true;
			this->updFlightId->TabIndex = 16;
			this->updFlightId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(162, 20);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(70, 13);
			this->label24->TabIndex = 12;
			this->label24->Text = L"№ самолета";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(133, 60);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(99, 13);
			this->label23->TabIndex = 12;
			this->label23->Text = L"Пункт назначения";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(3, 60);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(105, 13);
			this->label22->TabIndex = 12;
			this->label22->Text = L"Пункт отправления";
			// 
			// updFlightButton
			// 
			this->updFlightButton->Location = System::Drawing::Point(182, 168);
			this->updFlightButton->Name = L"updFlightButton";
			this->updFlightButton->Size = System::Drawing::Size(71, 23);
			this->updFlightButton->TabIndex = 12;
			this->updFlightButton->Text = L"Заменить";
			this->updFlightButton->UseVisualStyleBackColor = true;
			this->updFlightButton->Click += gcnew System::EventHandler(this, &mainForm::updFlightButton_Click);
			// 
			// updFlightArrivalDate
			// 
			this->updFlightArrivalDate->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->updFlightArrivalDate->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->updFlightArrivalDate->Location = System::Drawing::Point(9, 158);
			this->updFlightArrivalDate->Name = L"updFlightArrivalDate";
			this->updFlightArrivalDate->Size = System::Drawing::Size(142, 20);
			this->updFlightArrivalDate->TabIndex = 15;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(113, 72);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(19, 25);
			this->label19->TabIndex = 12;
			this->label19->Text = L"-";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(6, 140);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(92, 13);
			this->label20->TabIndex = 14;
			this->label20->Text = L"Время прибытия";
			// 
			// updFlightDest
			// 
			this->updFlightDest->Location = System::Drawing::Point(136, 77);
			this->updFlightDest->Name = L"updFlightDest";
			this->updFlightDest->Size = System::Drawing::Size(116, 20);
			this->updFlightDest->TabIndex = 12;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(6, 101);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(108, 13);
			this->label21->TabIndex = 13;
			this->label21->Text = L"Время отправления";
			// 
			// updFlightDep
			// 
			this->updFlightDep->Location = System::Drawing::Point(9, 76);
			this->updFlightDep->Name = L"updFlightDep";
			this->updFlightDep->Size = System::Drawing::Size(104, 20);
			this->updFlightDep->TabIndex = 12;
			// 
			// updFlightDepDate
			// 
			this->updFlightDepDate->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->updFlightDepDate->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->updFlightDepDate->Location = System::Drawing::Point(9, 117);
			this->updFlightDepDate->Name = L"updFlightDepDate";
			this->updFlightDepDate->Size = System::Drawing::Size(142, 20);
			this->updFlightDepDate->TabIndex = 12;
			// 
			// updFlightPlaneId
			// 
			this->updFlightPlaneId->FormattingEnabled = true;
			this->updFlightPlaneId->Location = System::Drawing::Point(161, 36);
			this->updFlightPlaneId->Name = L"updFlightPlaneId";
			this->updFlightPlaneId->Size = System::Drawing::Size(71, 21);
			this->updFlightPlaneId->Sorted = true;
			this->updFlightPlaneId->TabIndex = 12;
			this->updFlightPlaneId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->addFlightButton);
			this->groupBox7->Controls->Add(this->addFlightArrivalTime);
			this->groupBox7->Controls->Add(this->label18);
			this->groupBox7->Controls->Add(this->label17);
			this->groupBox7->Controls->Add(this->addFlightDepartTime);
			this->groupBox7->Controls->Add(this->label16);
			this->groupBox7->Controls->Add(this->label15);
			this->groupBox7->Controls->Add(this->label14);
			this->groupBox7->Controls->Add(this->addFlightArrive);
			this->groupBox7->Controls->Add(this->addFlightDepart);
			this->groupBox7->Controls->Add(this->label13);
			this->groupBox7->Controls->Add(this->addFlightPlaneId);
			this->groupBox7->Location = System::Drawing::Point(6, 19);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(266, 197);
			this->groupBox7->TabIndex = 0;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Добавление";
			// 
			// addFlightButton
			// 
			this->addFlightButton->Location = System::Drawing::Point(189, 168);
			this->addFlightButton->Name = L"addFlightButton";
			this->addFlightButton->Size = System::Drawing::Size(71, 23);
			this->addFlightButton->TabIndex = 11;
			this->addFlightButton->Text = L"Добавить";
			this->addFlightButton->UseVisualStyleBackColor = true;
			this->addFlightButton->Click += gcnew System::EventHandler(this, &mainForm::addFlightButton_Click);
			// 
			// addFlightArrivalTime
			// 
			this->addFlightArrivalTime->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->addFlightArrivalTime->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->addFlightArrivalTime->Location = System::Drawing::Point(6, 158);
			this->addFlightArrivalTime->Name = L"addFlightArrivalTime";
			this->addFlightArrivalTime->Size = System::Drawing::Size(142, 20);
			this->addFlightArrivalTime->TabIndex = 10;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(6, 140);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(92, 13);
			this->label18->TabIndex = 9;
			this->label18->Text = L"Время прибытия";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(6, 101);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(108, 13);
			this->label17->TabIndex = 8;
			this->label17->Text = L"Время отправления";
			// 
			// addFlightDepartTime
			// 
			this->addFlightDepartTime->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->addFlightDepartTime->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->addFlightDepartTime->Location = System::Drawing::Point(6, 117);
			this->addFlightDepartTime->Name = L"addFlightDepartTime";
			this->addFlightDepartTime->Size = System::Drawing::Size(142, 20);
			this->addFlightDepartTime->TabIndex = 7;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(123, 70);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(19, 25);
			this->label16->TabIndex = 6;
			this->label16->Text = L"-";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(145, 60);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(99, 13);
			this->label15->TabIndex = 5;
			this->label15->Text = L"Пункт назначения";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(2, 60);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(105, 13);
			this->label14->TabIndex = 4;
			this->label14->Text = L"Пункт отправления";
			// 
			// addFlightArrive
			// 
			this->addFlightArrive->Location = System::Drawing::Point(148, 76);
			this->addFlightArrive->Name = L"addFlightArrive";
			this->addFlightArrive->Size = System::Drawing::Size(112, 20);
			this->addFlightArrive->TabIndex = 3;
			// 
			// addFlightDepart
			// 
			this->addFlightDepart->Location = System::Drawing::Point(5, 76);
			this->addFlightDepart->Name = L"addFlightDepart";
			this->addFlightDepart->Size = System::Drawing::Size(112, 20);
			this->addFlightDepart->TabIndex = 2;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 20);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(70, 13);
			this->label13->TabIndex = 1;
			this->label13->Text = L"№ самолета";
			// 
			// addFlightPlaneId
			// 
			this->addFlightPlaneId->FormattingEnabled = true;
			this->addFlightPlaneId->Location = System::Drawing::Point(6, 36);
			this->addFlightPlaneId->Name = L"addFlightPlaneId";
			this->addFlightPlaneId->Size = System::Drawing::Size(71, 21);
			this->addFlightPlaneId->Sorted = true;
			this->addFlightPlaneId->TabIndex = 0;
			this->addFlightPlaneId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
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
			this->flightsTable->Size = System::Drawing::Size(603, 192);
			this->flightsTable->TabIndex = 1;
			this->flightsTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::flightsTable_CellClick);
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
			this->delPlaneParamModelComboBox->DropDownHeight = 72;
			this->delPlaneParamModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->delPlaneParamModelComboBox->FormattingEnabled = true;
			this->delPlaneParamModelComboBox->IntegralHeight = false;
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
			this->updPlanesParamModelComboBox->DropDownHeight = 72;
			this->updPlanesParamModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlanesParamModelComboBox->FormattingEnabled = true;
			this->updPlanesParamModelComboBox->IntegralHeight = false;
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
			this->delPlaneIdComboBox->DropDownHeight = 72;
			this->delPlaneIdComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->delPlaneIdComboBox->FormattingEnabled = true;
			this->delPlaneIdComboBox->IntegralHeight = false;
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
			this->updPlaneModelComboBox->DropDownHeight = 72;
			this->updPlaneModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlaneModelComboBox->FormattingEnabled = true;
			this->updPlaneModelComboBox->IntegralHeight = false;
			this->updPlaneModelComboBox->Location = System::Drawing::Point(9, 72);
			this->updPlaneModelComboBox->Name = L"updPlaneModelComboBox";
			this->updPlaneModelComboBox->Size = System::Drawing::Size(121, 21);
			this->updPlaneModelComboBox->TabIndex = 16;
			this->updPlaneModelComboBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updPlaneIdComboBox
			// 
			this->updPlaneIdComboBox->DropDownHeight = 72;
			this->updPlaneIdComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->updPlaneIdComboBox->FormattingEnabled = true;
			this->updPlaneIdComboBox->IntegralHeight = false;
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
			this->addPlaneModelComboBox->DropDownHeight = 72;
			this->addPlaneModelComboBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->addPlaneModelComboBox->FormattingEnabled = true;
			this->addPlaneModelComboBox->IntegralHeight = false;
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
			this->groupBox6->ResumeLayout(false);
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
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
			 myReader = executeReq("INSERT INTO "+PREFIX+".plane_parametrs (model,spot_num) VALUES('"
								   +planesParamModelTextBox->Text+"',"+spotNumericUpDown->Value+")");
			 loadData("select * from "+PREFIX+".plane_parametrs", planeParamTable);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",delPlaneParamModelComboBox);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",updPlanesParamModelComboBox);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",addPlaneModelComboBox);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",updPlaneModelComboBox);
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
			 myReader = executeReq("UPDATE "+PREFIX+".plane_parametrs SET model='"+newPlanesParamModelTextBox->Text+"', spot_num ="+newSpotNumericUpDown->Value+" WHERE model = '"+updPlanesParamModelComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".plane_parametrs", planeParamTable);
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
			 //FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",updPlanesParamModelComboBox);
			 //FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",addPlaneModelComboBox);
			 //FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",updPlaneModelComboBox);
			 updatePlanesParamButton->Enabled = true;
		 }


private: System::Void deletePlanesParametrsButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ q = "Уверены, что хотите удалить?";
			 String^ p = "Подтверждение удаления"; 
			 System::Windows::Forms::DialogResult res;
			 res = MessageBox::Show(q,p,MessageBoxButtons::YesNo,MessageBoxIcon::Question);
			 if (res == System::Windows::Forms::DialogResult::Yes) {

			 deletePlanesParametrsButton->Enabled = false;
			 if (delPlaneParamModelComboBox->Text->Length==0)
			 {
				 MessageBox::Show("Введите модель, которую нужно удалить", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 deletePlanesParametrsButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 2;
			 myReader = executeReq("DELETE FROM "+PREFIX+".plane_parametrs where model='"+delPlaneParamModelComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".plane_parametrs", planeParamTable);
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
			 //FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",updPlanesParamModelComboBox);
			 //FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",addPlaneModelComboBox);
			 //FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",updPlaneModelComboBox);
			 deletePlanesParametrsButton->Enabled = true;
			 }
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
			 myReader = executeReq("INSERT INTO "+PREFIX+".planes (model,company) VALUES('"+
								   addPlaneModelComboBox->Text+"','"+addPlaneCompanyTextBox->Text+"')");
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",updPlaneIdComboBox);
			 CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
			 CopyCombo(addFlightPlaneId,updPlaneIdComboBox);
			 CopyCombo(updFlightPlaneId,updPlaneIdComboBox);
			 //FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",delPlaneIdComboBox);
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
			 myReader = executeReq("UPDATE "+PREFIX+".planes SET model='"+
						updPlaneModelComboBox->Text+"', company ='"+
						updPlaneCompanyTextBox->Text+"' WHERE id_plane = '"+updPlaneIdComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 updPlaneButton->Enabled = true;
		 }
private: System::Void planesTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			  updPlaneIdComboBox->Text = planesTable->CurrentRow->Cells[0]->Value->ToString();
			  delPlaneIdComboBox->Text = planesTable->CurrentRow->Cells[0]->Value->ToString();
			  updPlaneModelComboBox->Text = planesTable->CurrentRow->Cells[1]->Value->ToString();
			  updPlaneCompanyTextBox->Text = planesTable->CurrentRow->Cells[2]->Value->ToString();
		 }
private: System::Void deletePlaneButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ q = "Уверены, что хотите удалить?";
			 String^ p = "Подтверждение удаления"; 
			 System::Windows::Forms::DialogResult res;
			 res = MessageBox::Show(q,p,MessageBoxButtons::YesNo,MessageBoxIcon::Question);
			 if (res == System::Windows::Forms::DialogResult::Yes) {
				 
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
			 myReader = executeReq("DELETE FROM "+PREFIX+".planes where id_plane='"+delPlaneIdComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",updPlaneIdComboBox);
			 //FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",delPlaneIdComboBox);
			 CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
			 CopyCombo(addFlightPlaneId,updPlaneIdComboBox);
			 CopyCombo(updFlightPlaneId,updPlaneIdComboBox);
			 deletePlaneButton->Enabled = true;
			 }
		 }
private: System::Void addPlaneModelComboBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 e->Handled = true;
		 }
private: System::Void addFlightButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 addFlightButton->Enabled = false;
			 if(addFlightPlaneId->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Номер самолета' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addFlightButton->Enabled = true;
				 return;
			 }
			 if(addFlightDepart->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт отправления' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addFlightButton->Enabled = true;
				 return;
			 }
			 if(addFlightArrive->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт назначения' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addFlightButton->Enabled = true;
				 return;
			 }
			 if(addFlightArrivalTime->Value.Date <= addFlightDepartTime->Value.Date)
			 {
				 MessageBox::Show("Дата прибытия должна быть позже даты отправления", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addFlightButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 4;
			 myReader = executeReq("INSERT INTO "+PREFIX+".flights (id_plane,departure,destination,departure_date,arrival_date) VALUES("+
				 addFlightPlaneId->Text+",'"+addFlightDepart->Text+"','"+addFlightArrive->Text+"','"+addFlightDepartTime->Text+"','"+addFlightArrivalTime->Text+"')");
			 loadData("select * from "+PREFIX+".flights", flightsTable);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
				 updFlightId);
			 CopyCombo(delFlightId,updFlightId);
			 addFlightButton->Enabled = true;
		 }
private: System::Void updFlightButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 updFlightButton->Enabled = false;
			 if(updFlightId->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Номер рейса' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 if(updFlightPlaneId->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Номер самолета' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 if(updFlightDep->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт отправления' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 if(updFlightDest->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт назначения' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 if(updFlightArrivalDate->Value.Date <= updFlightDepDate->Value.Date)
			 {
				 MessageBox::Show("Дата прибытия должна быть позже даты отправления", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 4;
			 myReader = executeReq("UPDATE "+PREFIX+".flights SET id_plane="+updFlightPlaneId->Text+
				 ", departure ='"+updFlightDep->Text+"', destination ='"+updFlightDest->Text+
				 "', departure_date = '"+updFlightDepDate->Text+
				 "', arrival_date ='"+updFlightArrivalDate->Text+"' WHERE id_flight = "+updFlightId->Text+";");
			 loadData("select * from "+PREFIX+".flights", flightsTable);
			 //FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",delPlaneIdComboBox);
			 updFlightButton->Enabled = true;
		 }
private: System::Void flightsTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 updFlightId->Text = flightsTable->CurrentRow->Cells[0]->Value->ToString();
			 updFlightPlaneId->Text = flightsTable->CurrentRow->Cells[1]->Value->ToString();
			 updFlightDep->Text = flightsTable->CurrentRow->Cells[2]->Value->ToString();
			 updFlightDest->Text = flightsTable->CurrentRow->Cells[3]->Value->ToString();
			 updFlightDepDate->Text = flightsTable->CurrentRow->Cells[4]->Value->ToString();
			 updFlightArrivalDate->Text = flightsTable->CurrentRow->Cells[5]->Value->ToString();
			 delFlightId->Text = flightsTable->CurrentRow->Cells[0]->Value->ToString();
		 }
private: System::Void delFlightButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 delFlightButton->Enabled = false;
			 if(delFlightId->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер рейса' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 delFlightButton->Enabled = true;
				 return;
			 }
			 numTab = 4;
			 MySqlDataReader^ myReader;
			 myReader = executeReq("DELETE FROM "+PREFIX+".flights where id_flight="+delFlightId->Text+";");
			 loadData("select * from "+PREFIX+".flights", flightsTable);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
				 updFlightId);
			 CopyCombo(delFlightId,updFlightId);
			 delFlightButton->Enabled = true;
		 }
};
}
