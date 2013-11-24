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
	using namespace System::Drawing::Printing;
	using namespace System::Text::RegularExpressions;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Сводка для mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	private:
		System::Windows::Forms::Button^ printButton;
	private: System::Windows::Forms::Button^  prntButton;
	private: System::Windows::Forms::Button^  previewButton;
	private: System::Windows::Forms::PrintPreviewDialog^  printPreviewDialog1;
			 System::Drawing::Font^ printFont;
	public:
		mainForm(void)
		{
			InitializeComponent();
			// todo: вызов нужной функции в зависимости от роли
			
			String^ r;
			MySqlDataReader^ myReader;
			myReader = executeReq("SELECT full_name FROM "+PREFIX+".passengers WHERE id_pass='"+(gcnew String(idPass))+"';");
			if(myReader->Read())
				name->Text = myReader->GetString(0);
			else 
				name->Text = gcnew String(idPass);
			loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			mainGrid->Columns[0]->HeaderText = "Номер билета";
			mainGrid->Columns[1]->HeaderText = "Номер рейса";
			mainGrid->Columns[2]->HeaderText = "Пункт отправления";
			mainGrid->Columns[3]->HeaderText = "Пункт назначения";
			mainGrid->Columns[4]->HeaderText = "Время отправления";
			mainGrid->Columns[5]->HeaderText = "Время прибытия";
			mainGrid->Columns[6]->HeaderText = "Цена";
			mainGrid->Columns[7]->HeaderText = "Дата продажи";
			mainGrid->Columns[0]->Width = 85;
			mainGrid->Columns[1]->Width = 85;
			mainGrid->Columns[2]->Width = 120;
			mainGrid->Columns[3]->Width = 120;
			mainGrid->Columns[4]->Width = 115;
			mainGrid->Columns[5]->Width = 115;
			mainGrid->Columns[6]->Width = 73;
			mainGrid->Columns[7]->Width = 85;

			switch(currRole)
			{
				case 1:
					r = "Пользователь"; 
					asUser(tabControl1,ordTable, false);
					ordTicketClass->Items->Add("A");
					ordTicketClass->Items->Add("B");
					FillCombo("SELECT distinct departure FROM "+PREFIX+".flights WHERE departure_date>curdate()","departure",ordTicketDep);
					FillCombo("SELECT distinct destination FROM "+PREFIX+".flights WHERE departure_date>curdate()","destination",ordTicketDest);
					break;
				case 2:
					r = "Менеджер по билетам"; 
					asTeller(tabControl1,ticketsTable,ordTable, false);
					FillCombo("SELECT id_pass FROM "+PREFIX+".passengers","id_pass",addTicketPass);
					FillCombo("SELECT distinct departure FROM "+PREFIX+".flights","departure",addTicketDep);
					FillCombo("SELECT distinct destination FROM "+PREFIX+".flights","destination",addTicketDest);
					CopyCombo(updTicketDep,addTicketDep);
					CopyCombo(updTicketDest,addTicketDest);
					addTicketClass->Items->Add("A");
					addTicketClass->Items->Add("B");
					CopyCombo(updTicketClass,addTicketClass);
					FillCombo("SELECT distinct id_pass FROM "+PREFIX+".tickets","id_pass",updTicketPass);
					CopyCombo(delTicketPass,updTicketPass);
					ordTicketClass->Items->Add("A");
					ordTicketClass->Items->Add("B");
					FillCombo("SELECT distinct departure FROM "+PREFIX+".flights WHERE departure_date>curdate()","departure",ordTicketDep);
					FillCombo("SELECT distinct destination FROM "+PREFIX+".flights WHERE departure_date>curdate()","destination",ordTicketDest);
					break;
				case 3:
					r = "Менеджер грузов"; 
					asCargoManager(cargoTable,tabControl1,ordTable, false);
					FillCombo("SELECT id_flight FROM "+PREFIX+".flights WHERE departure_date>curdate() AND departure_date>curtime()","id_flight",
						addCargoFlight);
					CopyCombo(updCargoFlight,addCargoFlight);
					FillCombo("SELECT id_pass FROM "+PREFIX+".passengers","id_pass",
						addCargoPass);
					CopyCombo(updCargoPass,addCargoPass);
					FillCombo("SELECT id_cargo FROM "+PREFIX+".cargo","id_cargo",updCargoId);
					CopyCombo(delCargoId,updCargoId);
					ordTicketClass->Items->Add("A");
					ordTicketClass->Items->Add("B");
					FillCombo("SELECT distinct departure FROM "+PREFIX+".flights WHERE departure_date>curdate()","departure",ordTicketDep);
					FillCombo("SELECT distinct destination FROM "+PREFIX+".flights WHERE departure_date>curdate()","destination",ordTicketDest);
					break;
				case 4:
					r = "Организационный менеджер"; 
					asMainManager (flightsTable, planesTable, planeParamTable,tariffsTable, tabControl1,ticketsTable,ordTable, false);
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
					FillCombo("SELECT id_flight FROM "+PREFIX+".flights WHERE departure_date>curdate() AND departure_date>curtime()","id_flight",
						addCargoFlight);
					CopyCombo(updCargoFlight,addCargoFlight);
					FillCombo("SELECT id_pass FROM "+PREFIX+".passengers","id_pass",
						addCargoPass);
					CopyCombo(updCargoPass,addCargoPass);
					FillCombo("SELECT id_cargo FROM "+PREFIX+".cargo","id_cargo",updCargoId);
					CopyCombo(delCargoId,updCargoId);
					FillCombo("SELECT id_pass FROM "+PREFIX+".passengers","id_pass",addTicketPass);
					FillCombo("SELECT distinct departure FROM "+PREFIX+".flights","departure",addTicketDep);
					FillCombo("SELECT distinct destination FROM "+PREFIX+".flights","destination",addTicketDest);
					CopyCombo(updTicketDep,addTicketDep);
					CopyCombo(updTicketDest,addTicketDest);
					addTicketClass->Items->Add("A");
					addTicketClass->Items->Add("B");
					CopyCombo(ordTicketClass,addTicketClass);
					CopyCombo(updTicketClass,addTicketClass);
					FillCombo("SELECT distinct id_pass FROM "+PREFIX+".tickets","id_pass",updTicketPass);
					CopyCombo(delTicketPass,updTicketPass);
					break;
				case 5:
					r = "Администратор";
					asAdmin(ctrlUsersTable);
					asMainManager(flightsTable, planesTable, 
								   planeParamTable,tariffsTable, tabControl1,ticketsTable,ordTable, true);
					asCargoManager(cargoTable,tabControl1,ordTable, true);
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
					FillCombo("SELECT id_flight FROM "+PREFIX+".flights WHERE departure_date>curdate() AND departure_date>curtime()","id_flight",
						addCargoFlight);
					CopyCombo(updCargoFlight,addCargoFlight);
					FillCombo("SELECT id_pass FROM "+PREFIX+".passengers","id_pass",
						addCargoPass);
					CopyCombo(updCargoPass,addCargoPass);
					FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
						updFlightId);
					CopyCombo(delFlightId,updFlightId);
					FillCombo("SELECT id_cargo FROM "+PREFIX+".cargo","id_cargo",updCargoId);
					CopyCombo(delCargoId,updCargoId);
					FillCombo("SELECT id_pass FROM "+PREFIX+".passengers","id_pass",addTicketPass);
					FillCombo("SELECT distinct departure FROM "+PREFIX+".flights","departure",addTicketDep);
					FillCombo("SELECT distinct destination FROM "+PREFIX+".flights","destination",addTicketDest);
					CopyCombo(updTicketDep,addTicketDep);
					CopyCombo(updTicketDest,addTicketDest);
					CopyCombo(ordTicketDep,addTicketDep);
					CopyCombo(ordTicketDest,addTicketDest);
					addTicketClass->Items->Add("A");
					addTicketClass->Items->Add("B");
					CopyCombo(updTicketClass,addTicketClass);
					CopyCombo(ordTicketClass,addTicketClass);
					FillCombo("SELECT distinct id_pass FROM "+PREFIX+".tickets","id_pass",updTicketPass);
					CopyCombo(delTicketPass,updTicketPass);
					CopyCombo(addRulesBox,updRulesBox);
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
private: System::Windows::Forms::DataGridView^  ctrlUsersTable;
private: System::Windows::Forms::GroupBox^  groupBox10;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Button^  updUserButton;
private: System::Windows::Forms::TextBox^  updNameText;





private: System::Windows::Forms::TextBox^  updPasspText;
private: System::Windows::Forms::ComboBox^  updRulesBox;




private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::TextBox^  updPasswText;
private: System::Windows::Forms::DataGridView^  cargoTable;
private: System::Windows::Forms::GroupBox^  groupBox11;
private: System::Windows::Forms::GroupBox^  groupBox12;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::ComboBox^  addCargoFlight;

private: System::Windows::Forms::ComboBox^  addCargoPass;
private: System::Windows::Forms::NumericUpDown^  addCargoWeight;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::GroupBox^  groupBox13;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  label35;



private: System::Windows::Forms::TextBox^  addCargoName;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Button^  addCargoButton;
private: System::Windows::Forms::NumericUpDown^  addCargoDimZ;

private: System::Windows::Forms::NumericUpDown^  addCargoDimY;

private: System::Windows::Forms::NumericUpDown^  addCargoDimX;
private: System::Windows::Forms::GroupBox^  groupBox14;
private: System::Windows::Forms::Label^  label45;
private: System::Windows::Forms::ComboBox^  updCargoId;
private: System::Windows::Forms::Button^  updCargoButton;

private: System::Windows::Forms::ComboBox^  updCargoPass;
private: System::Windows::Forms::NumericUpDown^  updCargoWeight;
private: System::Windows::Forms::ComboBox^  updCargoFlight;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  label44;
private: System::Windows::Forms::GroupBox^  groupBox15;
private: System::Windows::Forms::NumericUpDown^  updCargoDimZ;
private: System::Windows::Forms::NumericUpDown^  updCargoDimY;
private: System::Windows::Forms::NumericUpDown^  updCargoDimX;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::TextBox^  updCargoName;
private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::GroupBox^  groupBox16;
private: System::Windows::Forms::Label^  label46;
private: System::Windows::Forms::ComboBox^  delCargoId;
private: System::Windows::Forms::Button^  delCargoButton;
private: System::Windows::Forms::Label^  label48;
private: System::Windows::Forms::Label^  label47;
private: System::Windows::Forms::Label^  label52;
private: System::Windows::Forms::TextBox^  updFlightPrice;
private: System::Windows::Forms::Label^  label50;
private: System::Windows::Forms::Label^  label49;
private: System::Windows::Forms::TextBox^  addFlightPrice;
private: System::Windows::Forms::DataGridView^  tariffsTable;
private: System::Windows::Forms::GroupBox^  groupBox17;
private: System::Windows::Forms::GroupBox^  groupBox18;
private: System::Windows::Forms::Button^  addTicketButton;



private: System::Windows::Forms::Label^  label56;
private: System::Windows::Forms::ComboBox^  addTicketClass;
private: System::Windows::Forms::Label^  label55;
private: System::Windows::Forms::Label^  label54;
private: System::Windows::Forms::Label^  label53;
private: System::Windows::Forms::ComboBox^  addTicketDest;
private: System::Windows::Forms::ComboBox^  addTicketDep;
private: System::Windows::Forms::Label^  label51;
private: System::Windows::Forms::ComboBox^  addTicketPass;
private: System::Windows::Forms::DataGridView^  ticketsTable;

private: System::Windows::Forms::Label^  label57;
private: System::Windows::Forms::ComboBox^  addTicketDate;
private: System::Windows::Forms::GroupBox^  groupBox19;
private: System::Windows::Forms::Label^  label64;
private: System::Windows::Forms::Label^  label63;
private: System::Windows::Forms::Button^  updTicketButton;


private: System::Windows::Forms::Label^  label58;
private: System::Windows::Forms::ComboBox^  updTicketId;
private: System::Windows::Forms::ComboBox^  updTicketDate;
private: System::Windows::Forms::ComboBox^  updTicketPass;
private: System::Windows::Forms::Label^  label59;
private: System::Windows::Forms::Label^  label62;
private: System::Windows::Forms::ComboBox^  updTicketClass;
private: System::Windows::Forms::ComboBox^  updTicketDep;
private: System::Windows::Forms::Label^  label60;
private: System::Windows::Forms::ComboBox^  updTicketDest;
private: System::Windows::Forms::Label^  label61;
private: System::Windows::Forms::GroupBox^  groupBox20;
private: System::Windows::Forms::Button^  delTicketButton;
private: System::Windows::Forms::Label^  label65;
private: System::Windows::Forms::Label^  label66;
private: System::Windows::Forms::ComboBox^  delTicketPass;
private: System::Windows::Forms::ComboBox^  delTicketId;
private: System::Windows::Forms::Label^  label73;

private: System::Windows::Forms::GroupBox^  groupBox21;

private: System::Windows::Forms::Label^  label67;
private: System::Windows::Forms::ComboBox^  ordTicketDate;
private: System::Windows::Forms::Button^  ordTicketButton;


private: System::Windows::Forms::Label^  label68;
private: System::Windows::Forms::ComboBox^  ordTicketClass;


private: System::Windows::Forms::Label^  label70;
private: System::Windows::Forms::Label^  label71;
private: System::Windows::Forms::ComboBox^  ordTicketDest;
private: System::Windows::Forms::ComboBox^  ordTicketDep;
private: System::Windows::Forms::Label^  label74;
private: System::Windows::Forms::Label^  name;

private: System::Windows::Forms::DataGridView^  mainGrid;
private: System::Windows::Forms::DataGridView^  ordTable;
private: System::Windows::Forms::Label^  label72;
private: System::Windows::Forms::GroupBox^  groupBox22;
private: System::Windows::Forms::Label^  label75;
private: System::Windows::Forms::Label^  label78;
private: System::Windows::Forms::TextBox^  addPasswText;
private: System::Windows::Forms::ComboBox^  addRulesBox;
private: System::Windows::Forms::Label^  label76;
private: System::Windows::Forms::TextBox^  addPasspText;
private: System::Windows::Forms::Label^  label77;
private: System::Windows::Forms::TextBox^  addNameText;
private: System::Windows::Forms::Button^  addUserButton;
private: System::Windows::Forms::Label^  label79;
private: System::Windows::Forms::TextBox^  updNewPassp;
private: System::Windows::Forms::GroupBox^  groupBox23;
private: System::Windows::Forms::Button^  delUserButton;
private: System::Windows::Forms::Label^  label80;
private: System::Windows::Forms::TextBox^  delUserPassp;

private: System::Drawing::Printing::PrintDocument^  printDocument1;







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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(mainForm::typeid));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->usersPage = (gcnew System::Windows::Forms::TabPage());
			this->previewButton = (gcnew System::Windows::Forms::Button());
			this->prntButton = (gcnew System::Windows::Forms::Button());
			this->mainGrid = (gcnew System::Windows::Forms::DataGridView());
			this->name = (gcnew System::Windows::Forms::Label());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->groupBox21 = (gcnew System::Windows::Forms::GroupBox());
			this->ordTable = (gcnew System::Windows::Forms::DataGridView());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->ordTicketDate = (gcnew System::Windows::Forms::ComboBox());
			this->ordTicketButton = (gcnew System::Windows::Forms::Button());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->ordTicketClass = (gcnew System::Windows::Forms::ComboBox());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->ordTicketDest = (gcnew System::Windows::Forms::ComboBox());
			this->ordTicketDep = (gcnew System::Windows::Forms::ComboBox());
			this->tellersPage = (gcnew System::Windows::Forms::TabPage());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox20 = (gcnew System::Windows::Forms::GroupBox());
			this->delTicketButton = (gcnew System::Windows::Forms::Button());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->delTicketPass = (gcnew System::Windows::Forms::ComboBox());
			this->delTicketId = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox19 = (gcnew System::Windows::Forms::GroupBox());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->updTicketButton = (gcnew System::Windows::Forms::Button());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->updTicketId = (gcnew System::Windows::Forms::ComboBox());
			this->updTicketDate = (gcnew System::Windows::Forms::ComboBox());
			this->updTicketPass = (gcnew System::Windows::Forms::ComboBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->updTicketClass = (gcnew System::Windows::Forms::ComboBox());
			this->updTicketDep = (gcnew System::Windows::Forms::ComboBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->updTicketDest = (gcnew System::Windows::Forms::ComboBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->groupBox18 = (gcnew System::Windows::Forms::GroupBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->addTicketDate = (gcnew System::Windows::Forms::ComboBox());
			this->addTicketButton = (gcnew System::Windows::Forms::Button());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->addTicketClass = (gcnew System::Windows::Forms::ComboBox());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->addTicketDest = (gcnew System::Windows::Forms::ComboBox());
			this->addTicketDep = (gcnew System::Windows::Forms::ComboBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->addTicketPass = (gcnew System::Windows::Forms::ComboBox());
			this->ticketsTable = (gcnew System::Windows::Forms::DataGridView());
			this->cargoPage = (gcnew System::Windows::Forms::TabPage());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->delCargoButton = (gcnew System::Windows::Forms::Button());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->delCargoId = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->updCargoId = (gcnew System::Windows::Forms::ComboBox());
			this->updCargoButton = (gcnew System::Windows::Forms::Button());
			this->updCargoPass = (gcnew System::Windows::Forms::ComboBox());
			this->updCargoWeight = (gcnew System::Windows::Forms::NumericUpDown());
			this->updCargoFlight = (gcnew System::Windows::Forms::ComboBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->updCargoDimZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->updCargoDimY = (gcnew System::Windows::Forms::NumericUpDown());
			this->updCargoDimX = (gcnew System::Windows::Forms::NumericUpDown());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->updCargoName = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->addCargoButton = (gcnew System::Windows::Forms::Button());
			this->addCargoWeight = (gcnew System::Windows::Forms::NumericUpDown());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->addCargoDimZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->addCargoDimY = (gcnew System::Windows::Forms::NumericUpDown());
			this->addCargoDimX = (gcnew System::Windows::Forms::NumericUpDown());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->addCargoName = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->addCargoFlight = (gcnew System::Windows::Forms::ComboBox());
			this->addCargoPass = (gcnew System::Windows::Forms::ComboBox());
			this->cargoTable = (gcnew System::Windows::Forms::DataGridView());
			this->managersPage = (gcnew System::Windows::Forms::TabPage());
			this->orgTab = (gcnew System::Windows::Forms::TabControl());
			this->manageFlights = (gcnew System::Windows::Forms::TabPage());
			this->tariffsTable = (gcnew System::Windows::Forms::DataGridView());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->delFlightButton = (gcnew System::Windows::Forms::Button());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->delFlightId = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->updFlightPrice = (gcnew System::Windows::Forms::TextBox());
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
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->addFlightPrice = (gcnew System::Windows::Forms::TextBox());
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
			this->groupBox23 = (gcnew System::Windows::Forms::GroupBox());
			this->delUserButton = (gcnew System::Windows::Forms::Button());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->delUserPassp = (gcnew System::Windows::Forms::TextBox());
			this->groupBox22 = (gcnew System::Windows::Forms::GroupBox());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->addPasswText = (gcnew System::Windows::Forms::TextBox());
			this->addRulesBox = (gcnew System::Windows::Forms::ComboBox());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->addPasspText = (gcnew System::Windows::Forms::TextBox());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->addNameText = (gcnew System::Windows::Forms::TextBox());
			this->addUserButton = (gcnew System::Windows::Forms::Button());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->label79 = (gcnew System::Windows::Forms::Label());
			this->updNewPassp = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->updPasswText = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->updUserButton = (gcnew System::Windows::Forms::Button());
			this->updNameText = (gcnew System::Windows::Forms::TextBox());
			this->updPasspText = (gcnew System::Windows::Forms::TextBox());
			this->updRulesBox = (gcnew System::Windows::Forms::ComboBox());
			this->ctrlUsersTable = (gcnew System::Windows::Forms::DataGridView());
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->printPreviewDialog1 = (gcnew System::Windows::Forms::PrintPreviewDialog());
			this->tabControl1->SuspendLayout();
			this->usersPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainGrid))->BeginInit();
			this->groupBox21->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ordTable))->BeginInit();
			this->tellersPage->SuspendLayout();
			this->groupBox17->SuspendLayout();
			this->groupBox20->SuspendLayout();
			this->groupBox19->SuspendLayout();
			this->groupBox18->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ticketsTable))->BeginInit();
			this->cargoPage->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->groupBox14->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoWeight))->BeginInit();
			this->groupBox15->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoDimZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoDimY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoDimX))->BeginInit();
			this->groupBox12->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoWeight))->BeginInit();
			this->groupBox13->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoDimZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoDimY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoDimX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cargoTable))->BeginInit();
			this->managersPage->SuspendLayout();
			this->orgTab->SuspendLayout();
			this->manageFlights->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tariffsTable))->BeginInit();
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
			this->adminsPage->SuspendLayout();
			this->groupBox23->SuspendLayout();
			this->groupBox22->SuspendLayout();
			this->groupBox10->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ctrlUsersTable))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->usersPage);
			this->tabControl1->Controls->Add(this->tellersPage);
			this->tabControl1->Controls->Add(this->cargoPage);
			this->tabControl1->Controls->Add(this->managersPage);
			this->tabControl1->Controls->Add(this->adminsPage);
			this->tabControl1->Location = System::Drawing::Point(-1, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(839, 484);
			this->tabControl1->TabIndex = 1;
			this->tabControl1->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &mainForm::tabControl1_Selecting);
			// 
			// usersPage
			// 
			this->usersPage->Controls->Add(this->previewButton);
			this->usersPage->Controls->Add(this->prntButton);
			this->usersPage->Controls->Add(this->mainGrid);
			this->usersPage->Controls->Add(this->name);
			this->usersPage->Controls->Add(this->label73);
			this->usersPage->Controls->Add(this->label72);
			this->usersPage->Controls->Add(this->groupBox21);
			this->usersPage->Location = System::Drawing::Point(4, 22);
			this->usersPage->Name = L"usersPage";
			this->usersPage->Padding = System::Windows::Forms::Padding(3);
			this->usersPage->Size = System::Drawing::Size(831, 458);
			this->usersPage->TabIndex = 0;
			this->usersPage->Text = L"Заказ билета";
			this->usersPage->UseVisualStyleBackColor = true;
			// 
			// previewButton
			// 
			this->previewButton->Location = System::Drawing::Point(658, 24);
			this->previewButton->Name = L"previewButton";
			this->previewButton->Size = System::Drawing::Size(75, 23);
			this->previewButton->TabIndex = 7;
			this->previewButton->Text = L"Просмотр";
			this->previewButton->UseVisualStyleBackColor = true;
			this->previewButton->Click += gcnew System::EventHandler(this, &mainForm::previewButton_Click);
			// 
			// prntButton
			// 
			this->prntButton->Location = System::Drawing::Point(739, 24);
			this->prntButton->Name = L"prntButton";
			this->prntButton->Size = System::Drawing::Size(75, 23);
			this->prntButton->TabIndex = 6;
			this->prntButton->Text = L" Печать";
			this->prntButton->UseVisualStyleBackColor = true;
			this->prntButton->Click += gcnew System::EventHandler(this, &mainForm::prntButton_Click);
			// 
			// mainGrid
			// 
			this->mainGrid->AllowUserToAddRows = false;
			this->mainGrid->AllowUserToDeleteRows = false;
			this->mainGrid->AllowUserToResizeRows = false;
			this->mainGrid->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->mainGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->mainGrid->Location = System::Drawing::Point(13, 53);
			this->mainGrid->MultiSelect = false;
			this->mainGrid->Name = L"mainGrid";
			this->mainGrid->ReadOnly = true;
			this->mainGrid->RowHeadersVisible = false;
			this->mainGrid->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->mainGrid->Size = System::Drawing::Size(801, 166);
			this->mainGrid->TabIndex = 5;
			// 
			// name
			// 
			this->name->AutoSize = true;
			this->name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->name->Location = System::Drawing::Point(146, 3);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(20, 24);
			this->name->TabIndex = 4;
			this->name->Text = L". ";
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label73->Location = System::Drawing::Point(6, 3);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(149, 24);
			this->label73->TabIndex = 3;
			this->label73->Text = L"Здравствуйте, ";
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(15, 37);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(75, 13);
			this->label72->TabIndex = 2;
			this->label72->Text = L"Ваши заказы";
			// 
			// groupBox21
			// 
			this->groupBox21->Controls->Add(this->ordTable);
			this->groupBox21->Controls->Add(this->label74);
			this->groupBox21->Controls->Add(this->label67);
			this->groupBox21->Controls->Add(this->ordTicketDate);
			this->groupBox21->Controls->Add(this->ordTicketButton);
			this->groupBox21->Controls->Add(this->label68);
			this->groupBox21->Controls->Add(this->ordTicketClass);
			this->groupBox21->Controls->Add(this->label70);
			this->groupBox21->Controls->Add(this->label71);
			this->groupBox21->Controls->Add(this->ordTicketDest);
			this->groupBox21->Controls->Add(this->ordTicketDep);
			this->groupBox21->Location = System::Drawing::Point(9, 220);
			this->groupBox21->Name = L"groupBox21";
			this->groupBox21->Size = System::Drawing::Size(811, 232);
			this->groupBox21->TabIndex = 1;
			this->groupBox21->TabStop = false;
			this->groupBox21->Text = L"Заказ билета";
			// 
			// ordTable
			// 
			this->ordTable->AllowUserToAddRows = false;
			this->ordTable->AllowUserToDeleteRows = false;
			this->ordTable->AllowUserToResizeRows = false;
			this->ordTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ordTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->ordTable->Location = System::Drawing::Point(199, 36);
			this->ordTable->MultiSelect = false;
			this->ordTable->Name = L"ordTable";
			this->ordTable->ReadOnly = true;
			this->ordTable->RowHeadersVisible = false;
			this->ordTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->ordTable->Size = System::Drawing::Size(606, 190);
			this->ordTable->TabIndex = 25;
			this->ordTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::ordTable_CellClick);
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->Location = System::Drawing::Point(196, 20);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(40, 13);
			this->label74->TabIndex = 4;
			this->label74->Text = L"Рейсы";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(6, 100);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(103, 13);
			this->label67->TabIndex = 24;
			this->label67->Text = L"Дата Отправления";
			// 
			// ordTicketDate
			// 
			this->ordTicketDate->FormattingEnabled = true;
			this->ordTicketDate->Location = System::Drawing::Point(4, 116);
			this->ordTicketDate->Name = L"ordTicketDate";
			this->ordTicketDate->Size = System::Drawing::Size(189, 21);
			this->ordTicketDate->TabIndex = 23;
			this->ordTicketDate->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// ordTicketButton
			// 
			this->ordTicketButton->Location = System::Drawing::Point(118, 203);
			this->ordTicketButton->Name = L"ordTicketButton";
			this->ordTicketButton->Size = System::Drawing::Size(75, 23);
			this->ordTicketButton->TabIndex = 22;
			this->ordTicketButton->Text = L"Заказать";
			this->ordTicketButton->UseVisualStyleBackColor = true;
			this->ordTicketButton->Click += gcnew System::EventHandler(this, &mainForm::ordButton_Click);
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(6, 140);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(38, 13);
			this->label68->TabIndex = 21;
			this->label68->Text = L"Класс";
			// 
			// ordTicketClass
			// 
			this->ordTicketClass->FormattingEnabled = true;
			this->ordTicketClass->Location = System::Drawing::Point(4, 156);
			this->ordTicketClass->Name = L"ordTicketClass";
			this->ordTicketClass->Size = System::Drawing::Size(47, 21);
			this->ordTicketClass->TabIndex = 20;
			this->ordTicketClass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(6, 60);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(101, 13);
			this->label70->TabIndex = 18;
			this->label70->Text = L"Пункт Назначения";
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(6, 20);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(105, 13);
			this->label71->TabIndex = 17;
			this->label71->Text = L"Пункт отправления";
			// 
			// ordTicketDest
			// 
			this->ordTicketDest->FormattingEnabled = true;
			this->ordTicketDest->Location = System::Drawing::Point(4, 76);
			this->ordTicketDest->Name = L"ordTicketDest";
			this->ordTicketDest->Size = System::Drawing::Size(107, 21);
			this->ordTicketDest->TabIndex = 16;
			this->ordTicketDest->TextChanged += gcnew System::EventHandler(this, &mainForm::ordTicketDest_TextChanged);
			// 
			// ordTicketDep
			// 
			this->ordTicketDep->FormattingEnabled = true;
			this->ordTicketDep->Location = System::Drawing::Point(4, 36);
			this->ordTicketDep->Name = L"ordTicketDep";
			this->ordTicketDep->Size = System::Drawing::Size(107, 21);
			this->ordTicketDep->TabIndex = 15;
			this->ordTicketDep->TextChanged += gcnew System::EventHandler(this, &mainForm::ordTicketDep_TextChanged);
			this->ordTicketDep->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::ordTicketDep_KeyPress);
			// 
			// tellersPage
			// 
			this->tellersPage->Controls->Add(this->groupBox17);
			this->tellersPage->Controls->Add(this->ticketsTable);
			this->tellersPage->Location = System::Drawing::Point(4, 22);
			this->tellersPage->Name = L"tellersPage";
			this->tellersPage->Padding = System::Windows::Forms::Padding(3);
			this->tellersPage->Size = System::Drawing::Size(831, 458);
			this->tellersPage->TabIndex = 1;
			this->tellersPage->Text = L"Управление билетами";
			this->tellersPage->UseVisualStyleBackColor = true;
			// 
			// groupBox17
			// 
			this->groupBox17->Controls->Add(this->groupBox20);
			this->groupBox17->Controls->Add(this->groupBox19);
			this->groupBox17->Controls->Add(this->groupBox18);
			this->groupBox17->Location = System::Drawing::Point(9, 214);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Size = System::Drawing::Size(811, 238);
			this->groupBox17->TabIndex = 4;
			this->groupBox17->TabStop = false;
			this->groupBox17->Text = L"Билеты";
			// 
			// groupBox20
			// 
			this->groupBox20->Controls->Add(this->delTicketButton);
			this->groupBox20->Controls->Add(this->label65);
			this->groupBox20->Controls->Add(this->label66);
			this->groupBox20->Controls->Add(this->delTicketPass);
			this->groupBox20->Controls->Add(this->delTicketId);
			this->groupBox20->Location = System::Drawing::Point(530, 20);
			this->groupBox20->Name = L"groupBox20";
			this->groupBox20->Size = System::Drawing::Size(275, 212);
			this->groupBox20->TabIndex = 2;
			this->groupBox20->TabStop = false;
			this->groupBox20->Text = L"Удаление";
			// 
			// delTicketButton
			// 
			this->delTicketButton->Location = System::Drawing::Point(194, 183);
			this->delTicketButton->Name = L"delTicketButton";
			this->delTicketButton->Size = System::Drawing::Size(75, 23);
			this->delTicketButton->TabIndex = 26;
			this->delTicketButton->Text = L"Удалить";
			this->delTicketButton->UseVisualStyleBackColor = true;
			this->delTicketButton->Click += gcnew System::EventHandler(this, &mainForm::delTicketButton_Click);
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(146, 17);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(57, 13);
			this->label65->TabIndex = 29;
			this->label65->Text = L"№ Билета";
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(6, 17);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(70, 13);
			this->label66->TabIndex = 28;
			this->label66->Text = L"№ Паспорта";
			// 
			// delTicketPass
			// 
			this->delTicketPass->FormattingEnabled = true;
			this->delTicketPass->Location = System::Drawing::Point(6, 34);
			this->delTicketPass->Name = L"delTicketPass";
			this->delTicketPass->Size = System::Drawing::Size(106, 21);
			this->delTicketPass->TabIndex = 26;
			this->delTicketPass->TextChanged += gcnew System::EventHandler(this, &mainForm::delTicketPass_TextChanged);
			this->delTicketPass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// delTicketId
			// 
			this->delTicketId->FormattingEnabled = true;
			this->delTicketId->Location = System::Drawing::Point(140, 34);
			this->delTicketId->Name = L"delTicketId";
			this->delTicketId->Size = System::Drawing::Size(107, 21);
			this->delTicketId->TabIndex = 27;
			this->delTicketId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// groupBox19
			// 
			this->groupBox19->Controls->Add(this->label64);
			this->groupBox19->Controls->Add(this->label63);
			this->groupBox19->Controls->Add(this->updTicketButton);
			this->groupBox19->Controls->Add(this->label58);
			this->groupBox19->Controls->Add(this->updTicketId);
			this->groupBox19->Controls->Add(this->updTicketDate);
			this->groupBox19->Controls->Add(this->updTicketPass);
			this->groupBox19->Controls->Add(this->label59);
			this->groupBox19->Controls->Add(this->label62);
			this->groupBox19->Controls->Add(this->updTicketClass);
			this->groupBox19->Controls->Add(this->updTicketDep);
			this->groupBox19->Controls->Add(this->label60);
			this->groupBox19->Controls->Add(this->updTicketDest);
			this->groupBox19->Controls->Add(this->label61);
			this->groupBox19->Location = System::Drawing::Point(267, 20);
			this->groupBox19->Name = L"groupBox19";
			this->groupBox19->Size = System::Drawing::Size(256, 212);
			this->groupBox19->TabIndex = 1;
			this->groupBox19->TabStop = false;
			this->groupBox19->Text = L"Редактирование";
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->Location = System::Drawing::Point(147, 16);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(57, 13);
			this->label64->TabIndex = 25;
			this->label64->Text = L"№ Билета";
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->Location = System::Drawing::Point(7, 16);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(70, 13);
			this->label63->TabIndex = 24;
			this->label63->Text = L"№ Паспорта";
			// 
			// updTicketButton
			// 
			this->updTicketButton->Location = System::Drawing::Point(173, 183);
			this->updTicketButton->Name = L"updTicketButton";
			this->updTicketButton->Size = System::Drawing::Size(75, 23);
			this->updTicketButton->TabIndex = 15;
			this->updTicketButton->Text = L"Заменить";
			this->updTicketButton->UseVisualStyleBackColor = true;
			this->updTicketButton->Click += gcnew System::EventHandler(this, &mainForm::button1_Click_2);
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(9, 100);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(103, 13);
			this->label58->TabIndex = 23;
			this->label58->Text = L"Дата Отправления";
			// 
			// updTicketId
			// 
			this->updTicketId->FormattingEnabled = true;
			this->updTicketId->Location = System::Drawing::Point(141, 33);
			this->updTicketId->Name = L"updTicketId";
			this->updTicketId->Size = System::Drawing::Size(107, 21);
			this->updTicketId->TabIndex = 1;
			this->updTicketId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updTicketDate
			// 
			this->updTicketDate->FormattingEnabled = true;
			this->updTicketDate->Location = System::Drawing::Point(6, 118);
			this->updTicketDate->Name = L"updTicketDate";
			this->updTicketDate->Size = System::Drawing::Size(189, 21);
			this->updTicketDate->TabIndex = 22;
			this->updTicketDate->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updTicketPass
			// 
			this->updTicketPass->FormattingEnabled = true;
			this->updTicketPass->Location = System::Drawing::Point(7, 33);
			this->updTicketPass->Name = L"updTicketPass";
			this->updTicketPass->Size = System::Drawing::Size(106, 21);
			this->updTicketPass->TabIndex = 0;
			this->updTicketPass->TextChanged += gcnew System::EventHandler(this, &mainForm::updTicketPass_TextChanged);
			this->updTicketPass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Location = System::Drawing::Point(6, 142);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(38, 13);
			this->label59->TabIndex = 21;
			this->label59->Text = L"Класс";
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->Location = System::Drawing::Point(6, 57);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(105, 13);
			this->label62->TabIndex = 17;
			this->label62->Text = L"Пункт отправления";
			// 
			// updTicketClass
			// 
			this->updTicketClass->FormattingEnabled = true;
			this->updTicketClass->Location = System::Drawing::Point(6, 158);
			this->updTicketClass->Name = L"updTicketClass";
			this->updTicketClass->Size = System::Drawing::Size(47, 21);
			this->updTicketClass->TabIndex = 20;
			this->updTicketClass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updTicketDep
			// 
			this->updTicketDep->FormattingEnabled = true;
			this->updTicketDep->Location = System::Drawing::Point(6, 72);
			this->updTicketDep->Name = L"updTicketDep";
			this->updTicketDep->Size = System::Drawing::Size(107, 21);
			this->updTicketDep->TabIndex = 15;
			this->updTicketDep->TextChanged += gcnew System::EventHandler(this, &mainForm::updTicketDep_TextChanged);
			this->updTicketDep->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::updTicketDep_KeyPress);
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label60->Location = System::Drawing::Point(118, 67);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(19, 25);
			this->label60->TabIndex = 19;
			this->label60->Text = L"-";
			// 
			// updTicketDest
			// 
			this->updTicketDest->FormattingEnabled = true;
			this->updTicketDest->Location = System::Drawing::Point(141, 72);
			this->updTicketDest->Name = L"updTicketDest";
			this->updTicketDest->Size = System::Drawing::Size(107, 21);
			this->updTicketDest->TabIndex = 16;
			this->updTicketDest->TextChanged += gcnew System::EventHandler(this, &mainForm::updTicketDest_TextChanged);
			this->updTicketDest->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::updTicketDest_KeyPress);
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(138, 57);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(101, 13);
			this->label61->TabIndex = 18;
			this->label61->Text = L"Пункт Назначения";
			// 
			// groupBox18
			// 
			this->groupBox18->Controls->Add(this->label57);
			this->groupBox18->Controls->Add(this->addTicketDate);
			this->groupBox18->Controls->Add(this->addTicketButton);
			this->groupBox18->Controls->Add(this->label56);
			this->groupBox18->Controls->Add(this->addTicketClass);
			this->groupBox18->Controls->Add(this->label55);
			this->groupBox18->Controls->Add(this->label54);
			this->groupBox18->Controls->Add(this->label53);
			this->groupBox18->Controls->Add(this->addTicketDest);
			this->groupBox18->Controls->Add(this->addTicketDep);
			this->groupBox18->Controls->Add(this->label51);
			this->groupBox18->Controls->Add(this->addTicketPass);
			this->groupBox18->Location = System::Drawing::Point(6, 19);
			this->groupBox18->Name = L"groupBox18";
			this->groupBox18->Size = System::Drawing::Size(254, 213);
			this->groupBox18->TabIndex = 0;
			this->groupBox18->TabStop = false;
			this->groupBox18->Text = L"Добавление";
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(9, 101);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(103, 13);
			this->label57->TabIndex = 14;
			this->label57->Text = L"Дата Отправления";
			// 
			// addTicketDate
			// 
			this->addTicketDate->FormattingEnabled = true;
			this->addTicketDate->Location = System::Drawing::Point(6, 119);
			this->addTicketDate->Name = L"addTicketDate";
			this->addTicketDate->Size = System::Drawing::Size(189, 21);
			this->addTicketDate->TabIndex = 13;
			this->addTicketDate->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// addTicketButton
			// 
			this->addTicketButton->Location = System::Drawing::Point(173, 184);
			this->addTicketButton->Name = L"addTicketButton";
			this->addTicketButton->Size = System::Drawing::Size(75, 23);
			this->addTicketButton->TabIndex = 12;
			this->addTicketButton->Text = L"Добавить";
			this->addTicketButton->UseVisualStyleBackColor = true;
			this->addTicketButton->Click += gcnew System::EventHandler(this, &mainForm::addTicketButton_Click);
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(6, 143);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(38, 13);
			this->label56->TabIndex = 9;
			this->label56->Text = L"Класс";
			// 
			// addTicketClass
			// 
			this->addTicketClass->FormattingEnabled = true;
			this->addTicketClass->Location = System::Drawing::Point(6, 159);
			this->addTicketClass->Name = L"addTicketClass";
			this->addTicketClass->Size = System::Drawing::Size(47, 21);
			this->addTicketClass->TabIndex = 8;
			this->addTicketClass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label55->Location = System::Drawing::Point(118, 68);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(19, 25);
			this->label55->TabIndex = 7;
			this->label55->Text = L"-";
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(138, 58);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(101, 13);
			this->label54->TabIndex = 5;
			this->label54->Text = L"Пункт Назначения";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(6, 58);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(105, 13);
			this->label53->TabIndex = 4;
			this->label53->Text = L"Пункт отправления";
			// 
			// addTicketDest
			// 
			this->addTicketDest->FormattingEnabled = true;
			this->addTicketDest->Location = System::Drawing::Point(141, 73);
			this->addTicketDest->Name = L"addTicketDest";
			this->addTicketDest->Size = System::Drawing::Size(107, 21);
			this->addTicketDest->TabIndex = 3;
			this->addTicketDest->TextChanged += gcnew System::EventHandler(this, &mainForm::addTicketDest_TextChanged);
			this->addTicketDest->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addTicketDest_KeyPress);
			// 
			// addTicketDep
			// 
			this->addTicketDep->FormattingEnabled = true;
			this->addTicketDep->Location = System::Drawing::Point(6, 73);
			this->addTicketDep->Name = L"addTicketDep";
			this->addTicketDep->Size = System::Drawing::Size(107, 21);
			this->addTicketDep->TabIndex = 2;
			this->addTicketDep->TextChanged += gcnew System::EventHandler(this, &mainForm::addTicketDep_TextChanged);
			this->addTicketDep->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addTicketDep_KeyPress);
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(6, 18);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(70, 13);
			this->label51->TabIndex = 1;
			this->label51->Text = L"№ Паспорта";
			// 
			// addTicketPass
			// 
			this->addTicketPass->FormattingEnabled = true;
			this->addTicketPass->Location = System::Drawing::Point(6, 34);
			this->addTicketPass->Name = L"addTicketPass";
			this->addTicketPass->Size = System::Drawing::Size(107, 21);
			this->addTicketPass->TabIndex = 0;
			this->addTicketPass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// ticketsTable
			// 
			this->ticketsTable->AllowUserToAddRows = false;
			this->ticketsTable->AllowUserToDeleteRows = false;
			this->ticketsTable->AllowUserToResizeRows = false;
			this->ticketsTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ticketsTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->ticketsTable->Location = System::Drawing::Point(294, 12);
			this->ticketsTable->MultiSelect = false;
			this->ticketsTable->Name = L"ticketsTable";
			this->ticketsTable->ReadOnly = true;
			this->ticketsTable->RowHeadersVisible = false;
			this->ticketsTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->ticketsTable->Size = System::Drawing::Size(526, 196);
			this->ticketsTable->TabIndex = 3;
			this->ticketsTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::ticketsTable_CellClick);
			// 
			// cargoPage
			// 
			this->cargoPage->Controls->Add(this->groupBox11);
			this->cargoPage->Controls->Add(this->cargoTable);
			this->cargoPage->Location = System::Drawing::Point(4, 22);
			this->cargoPage->Name = L"cargoPage";
			this->cargoPage->Size = System::Drawing::Size(831, 458);
			this->cargoPage->TabIndex = 4;
			this->cargoPage->Text = L"Управление грузами";
			this->cargoPage->UseVisualStyleBackColor = true;
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->groupBox16);
			this->groupBox11->Controls->Add(this->groupBox14);
			this->groupBox11->Controls->Add(this->groupBox12);
			this->groupBox11->Location = System::Drawing::Point(9, 210);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(819, 236);
			this->groupBox11->TabIndex = 3;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Грузы";
			// 
			// groupBox16
			// 
			this->groupBox16->Controls->Add(this->delCargoButton);
			this->groupBox16->Controls->Add(this->label46);
			this->groupBox16->Controls->Add(this->delCargoId);
			this->groupBox16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox16->Location = System::Drawing::Point(565, 20);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(246, 209);
			this->groupBox16->TabIndex = 2;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"Удаление";
			// 
			// delCargoButton
			// 
			this->delCargoButton->Location = System::Drawing::Point(165, 174);
			this->delCargoButton->Name = L"delCargoButton";
			this->delCargoButton->Size = System::Drawing::Size(75, 23);
			this->delCargoButton->TabIndex = 23;
			this->delCargoButton->Text = L"Удалить";
			this->delCargoButton->UseVisualStyleBackColor = true;
			this->delCargoButton->Click += gcnew System::EventHandler(this, &mainForm::delCargoButton_Click);
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(6, 15);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(49, 13);
			this->label46->TabIndex = 24;
			this->label46->Text = L"№ груза";
			// 
			// delCargoId
			// 
			this->delCargoId->FormattingEnabled = true;
			this->delCargoId->Location = System::Drawing::Point(6, 33);
			this->delCargoId->Name = L"delCargoId";
			this->delCargoId->Size = System::Drawing::Size(95, 21);
			this->delCargoId->Sorted = true;
			this->delCargoId->TabIndex = 23;
			this->delCargoId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->label48);
			this->groupBox14->Controls->Add(this->label45);
			this->groupBox14->Controls->Add(this->updCargoId);
			this->groupBox14->Controls->Add(this->updCargoButton);
			this->groupBox14->Controls->Add(this->updCargoPass);
			this->groupBox14->Controls->Add(this->updCargoWeight);
			this->groupBox14->Controls->Add(this->updCargoFlight);
			this->groupBox14->Controls->Add(this->label38);
			this->groupBox14->Controls->Add(this->label44);
			this->groupBox14->Controls->Add(this->groupBox15);
			this->groupBox14->Controls->Add(this->label43);
			this->groupBox14->Controls->Add(this->updCargoName);
			this->groupBox14->Controls->Add(this->label42);
			this->groupBox14->Location = System::Drawing::Point(285, 19);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(273, 210);
			this->groupBox14->TabIndex = 1;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"Редактирование";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(80, 180);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(60, 13);
			this->label48->TabIndex = 23;
			this->label48->Text = L"в граммах";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(6, 16);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(49, 13);
			this->label45->TabIndex = 22;
			this->label45->Text = L"№ груза";
			// 
			// updCargoId
			// 
			this->updCargoId->FormattingEnabled = true;
			this->updCargoId->Location = System::Drawing::Point(7, 34);
			this->updCargoId->Name = L"updCargoId";
			this->updCargoId->Size = System::Drawing::Size(95, 21);
			this->updCargoId->Sorted = true;
			this->updCargoId->TabIndex = 21;
			this->updCargoId->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updCargoButton
			// 
			this->updCargoButton->Location = System::Drawing::Point(187, 175);
			this->updCargoButton->Name = L"updCargoButton";
			this->updCargoButton->Size = System::Drawing::Size(75, 23);
			this->updCargoButton->TabIndex = 20;
			this->updCargoButton->Text = L"Заменить";
			this->updCargoButton->UseVisualStyleBackColor = true;
			this->updCargoButton->Click += gcnew System::EventHandler(this, &mainForm::updCargoButton_Click);
			// 
			// updCargoPass
			// 
			this->updCargoPass->FormattingEnabled = true;
			this->updCargoPass->Location = System::Drawing::Point(146, 34);
			this->updCargoPass->Name = L"updCargoPass";
			this->updCargoPass->Size = System::Drawing::Size(121, 21);
			this->updCargoPass->Sorted = true;
			this->updCargoPass->TabIndex = 11;
			this->updCargoPass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// updCargoWeight
			// 
			this->updCargoWeight->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->updCargoWeight->Location = System::Drawing::Point(12, 178);
			this->updCargoWeight->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50000, 0, 0, 0});
			this->updCargoWeight->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->updCargoWeight->Name = L"updCargoWeight";
			this->updCargoWeight->Size = System::Drawing::Size(62, 20);
			this->updCargoWeight->TabIndex = 19;
			this->updCargoWeight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->updCargoWeight->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// updCargoFlight
			// 
			this->updCargoFlight->FormattingEnabled = true;
			this->updCargoFlight->Location = System::Drawing::Point(6, 75);
			this->updCargoFlight->Name = L"updCargoFlight";
			this->updCargoFlight->Size = System::Drawing::Size(96, 21);
			this->updCargoFlight->Sorted = true;
			this->updCargoFlight->TabIndex = 12;
			this->updCargoFlight->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(9, 161);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(26, 13);
			this->label38->TabIndex = 18;
			this->label38->Text = L"Вес";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(143, 18);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(68, 13);
			this->label44->TabIndex = 13;
			this->label44->Text = L"№ паспорта";
			// 
			// groupBox15
			// 
			this->groupBox15->Controls->Add(this->updCargoDimZ);
			this->groupBox15->Controls->Add(this->updCargoDimY);
			this->groupBox15->Controls->Add(this->updCargoDimX);
			this->groupBox15->Controls->Add(this->label39);
			this->groupBox15->Controls->Add(this->label40);
			this->groupBox15->Controls->Add(this->label41);
			this->groupBox15->Location = System::Drawing::Point(9, 101);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(256, 53);
			this->groupBox15->TabIndex = 17;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"Размеры (длина,ширина,высота)";
			// 
			// updCargoDimZ
			// 
			this->updCargoDimZ->Location = System::Drawing::Point(173, 24);
			this->updCargoDimZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->updCargoDimZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->updCargoDimZ->Name = L"updCargoDimZ";
			this->updCargoDimZ->Size = System::Drawing::Size(49, 20);
			this->updCargoDimZ->TabIndex = 12;
			this->updCargoDimZ->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->updCargoDimZ->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// updCargoDimY
			// 
			this->updCargoDimY->Location = System::Drawing::Point(90, 24);
			this->updCargoDimY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->updCargoDimY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->updCargoDimY->Name = L"updCargoDimY";
			this->updCargoDimY->Size = System::Drawing::Size(40, 20);
			this->updCargoDimY->TabIndex = 11;
			this->updCargoDimY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->updCargoDimY->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// updCargoDimX
			// 
			this->updCargoDimX->Location = System::Drawing::Point(6, 24);
			this->updCargoDimX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->updCargoDimX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->updCargoDimX->Name = L"updCargoDimX";
			this->updCargoDimX->Size = System::Drawing::Size(41, 20);
			this->updCargoDimX->TabIndex = 10;
			this->updCargoDimX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->updCargoDimX->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(228, 26);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(21, 13);
			this->label39->TabIndex = 5;
			this->label39->Text = L"см";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(136, 26);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(31, 13);
			this->label40->TabIndex = 4;
			this->label40->Text = L"см Х";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(53, 26);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(31, 13);
			this->label41->TabIndex = 3;
			this->label41->Text = L"см Х";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(5, 58);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(51, 13);
			this->label43->TabIndex = 14;
			this->label43->Text = L"№ рейса";
			// 
			// updCargoName
			// 
			this->updCargoName->Location = System::Drawing::Point(146, 75);
			this->updCargoName->Name = L"updCargoName";
			this->updCargoName->Size = System::Drawing::Size(121, 20);
			this->updCargoName->TabIndex = 16;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(143, 59);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(83, 13);
			this->label42->TabIndex = 15;
			this->label42->Text = L"Наименование";
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->label47);
			this->groupBox12->Controls->Add(this->addCargoButton);
			this->groupBox12->Controls->Add(this->addCargoWeight);
			this->groupBox12->Controls->Add(this->label34);
			this->groupBox12->Controls->Add(this->groupBox13);
			this->groupBox12->Controls->Add(this->addCargoName);
			this->groupBox12->Controls->Add(this->label33);
			this->groupBox12->Controls->Add(this->label32);
			this->groupBox12->Controls->Add(this->label31);
			this->groupBox12->Controls->Add(this->addCargoFlight);
			this->groupBox12->Controls->Add(this->addCargoPass);
			this->groupBox12->Location = System::Drawing::Point(6, 19);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(273, 211);
			this->groupBox12->TabIndex = 0;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Добавление";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(80, 180);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(60, 13);
			this->label47->TabIndex = 11;
			this->label47->Text = L"в граммах";
			// 
			// addCargoButton
			// 
			this->addCargoButton->Location = System::Drawing::Point(187, 175);
			this->addCargoButton->Name = L"addCargoButton";
			this->addCargoButton->Size = System::Drawing::Size(75, 23);
			this->addCargoButton->TabIndex = 10;
			this->addCargoButton->Text = L"Добавить";
			this->addCargoButton->UseVisualStyleBackColor = true;
			this->addCargoButton->Click += gcnew System::EventHandler(this, &mainForm::addCargoButton_Click);
			// 
			// addCargoWeight
			// 
			this->addCargoWeight->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->addCargoWeight->Location = System::Drawing::Point(12, 178);
			this->addCargoWeight->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50000, 0, 0, 0});
			this->addCargoWeight->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->addCargoWeight->Name = L"addCargoWeight";
			this->addCargoWeight->Size = System::Drawing::Size(62, 20);
			this->addCargoWeight->TabIndex = 9;
			this->addCargoWeight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->addCargoWeight->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(9, 161);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(26, 13);
			this->label34->TabIndex = 8;
			this->label34->Text = L"Вес";
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->addCargoDimZ);
			this->groupBox13->Controls->Add(this->addCargoDimY);
			this->groupBox13->Controls->Add(this->addCargoDimX);
			this->groupBox13->Controls->Add(this->label37);
			this->groupBox13->Controls->Add(this->label36);
			this->groupBox13->Controls->Add(this->label35);
			this->groupBox13->Location = System::Drawing::Point(9, 101);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(256, 53);
			this->groupBox13->TabIndex = 7;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"Размеры (длина,ширина,высота)";
			// 
			// addCargoDimZ
			// 
			this->addCargoDimZ->Location = System::Drawing::Point(171, 24);
			this->addCargoDimZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->addCargoDimZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->addCargoDimZ->Name = L"addCargoDimZ";
			this->addCargoDimZ->Size = System::Drawing::Size(49, 20);
			this->addCargoDimZ->TabIndex = 12;
			this->addCargoDimZ->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->addCargoDimZ->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// addCargoDimY
			// 
			this->addCargoDimY->Location = System::Drawing::Point(90, 24);
			this->addCargoDimY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->addCargoDimY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->addCargoDimY->Name = L"addCargoDimY";
			this->addCargoDimY->Size = System::Drawing::Size(40, 20);
			this->addCargoDimY->TabIndex = 11;
			this->addCargoDimY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->addCargoDimY->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// addCargoDimX
			// 
			this->addCargoDimX->Location = System::Drawing::Point(6, 24);
			this->addCargoDimX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->addCargoDimX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->addCargoDimX->Name = L"addCargoDimX";
			this->addCargoDimX->Size = System::Drawing::Size(41, 20);
			this->addCargoDimX->TabIndex = 10;
			this->addCargoDimX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->addCargoDimX->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(226, 26);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(21, 13);
			this->label37->TabIndex = 5;
			this->label37->Text = L"см";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(134, 26);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(31, 13);
			this->label36->TabIndex = 4;
			this->label36->Text = L"см Х";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(53, 26);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(31, 13);
			this->label35->TabIndex = 3;
			this->label35->Text = L"см Х";
			// 
			// addCargoName
			// 
			this->addCargoName->Location = System::Drawing::Point(6, 75);
			this->addCargoName->Name = L"addCargoName";
			this->addCargoName->Size = System::Drawing::Size(121, 20);
			this->addCargoName->TabIndex = 5;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(6, 58);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(83, 13);
			this->label33->TabIndex = 4;
			this->label33->Text = L"Наименование";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(143, 18);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(51, 13);
			this->label32->TabIndex = 3;
			this->label32->Text = L"№ рейса";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(6, 18);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(68, 13);
			this->label31->TabIndex = 2;
			this->label31->Text = L"№ паспорта";
			// 
			// addCargoFlight
			// 
			this->addCargoFlight->FormattingEnabled = true;
			this->addCargoFlight->Location = System::Drawing::Point(146, 34);
			this->addCargoFlight->Name = L"addCargoFlight";
			this->addCargoFlight->Size = System::Drawing::Size(96, 21);
			this->addCargoFlight->Sorted = true;
			this->addCargoFlight->TabIndex = 1;
			this->addCargoFlight->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// addCargoPass
			// 
			this->addCargoPass->FormattingEnabled = true;
			this->addCargoPass->Location = System::Drawing::Point(6, 34);
			this->addCargoPass->Name = L"addCargoPass";
			this->addCargoPass->Size = System::Drawing::Size(121, 21);
			this->addCargoPass->Sorted = true;
			this->addCargoPass->TabIndex = 0;
			this->addCargoPass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// cargoTable
			// 
			this->cargoTable->AllowUserToAddRows = false;
			this->cargoTable->AllowUserToDeleteRows = false;
			this->cargoTable->AllowUserToResizeRows = false;
			this->cargoTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->cargoTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->cargoTable->Location = System::Drawing::Point(294, 12);
			this->cargoTable->MultiSelect = false;
			this->cargoTable->Name = L"cargoTable";
			this->cargoTable->ReadOnly = true;
			this->cargoTable->RowHeadersVisible = false;
			this->cargoTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->cargoTable->Size = System::Drawing::Size(526, 192);
			this->cargoTable->TabIndex = 2;
			this->cargoTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::cargoTable_CellClick);
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
			this->manageFlights->Controls->Add(this->tariffsTable);
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
			// tariffsTable
			// 
			this->tariffsTable->AllowUserToAddRows = false;
			this->tariffsTable->AllowUserToDeleteRows = false;
			this->tariffsTable->AllowUserToResizeRows = false;
			this->tariffsTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->tariffsTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->tariffsTable->Location = System::Drawing::Point(5, 6);
			this->tariffsTable->MultiSelect = false;
			this->tariffsTable->Name = L"tariffsTable";
			this->tariffsTable->ReadOnly = true;
			this->tariffsTable->RowHeadersVisible = false;
			this->tariffsTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->tariffsTable->Size = System::Drawing::Size(215, 192);
			this->tariffsTable->TabIndex = 3;
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
			this->groupBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox9->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->groupBox9->Location = System::Drawing::Point(543, 19);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(262, 197);
			this->groupBox9->TabIndex = 1;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Удаление";
			// 
			// delFlightButton
			// 
			this->delFlightButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->delFlightButton->ForeColor = System::Drawing::SystemColors::ControlText;
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
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label26->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label26->Location = System::Drawing::Point(3, 16);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(126, 13);
			this->label26->TabIndex = 18;
			this->label26->Text = L"№ Рейса для удаления:";
			// 
			// delFlightId
			// 
			this->delFlightId->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
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
			this->groupBox8->Controls->Add(this->label52);
			this->groupBox8->Controls->Add(this->updFlightPrice);
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
			this->groupBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox8->ForeColor = System::Drawing::SystemColors::HotTrack;
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
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label25->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label25->Location = System::Drawing::Point(6, 20);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(132, 13);
			this->label25->TabIndex = 17;
			this->label25->Text = L"№ Рейса для изменения";
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label52->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label52->Location = System::Drawing::Point(156, 100);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(33, 13);
			this->label52->TabIndex = 16;
			this->label52->Text = L"Цена";
			// 
			// updFlightPrice
			// 
			this->updFlightPrice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updFlightPrice->Location = System::Drawing::Point(156, 116);
			this->updFlightPrice->Name = L"updFlightPrice";
			this->updFlightPrice->Size = System::Drawing::Size(64, 20);
			this->updFlightPrice->TabIndex = 15;
			this->updFlightPrice->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// updFlightId
			// 
			this->updFlightId->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
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
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label24->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label24->Location = System::Drawing::Point(162, 20);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(70, 13);
			this->label24->TabIndex = 12;
			this->label24->Text = L"№ самолета";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label23->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label23->Location = System::Drawing::Point(133, 60);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(99, 13);
			this->label23->TabIndex = 12;
			this->label23->Text = L"Пункт назначения";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label22->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label22->Location = System::Drawing::Point(9, 59);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(105, 13);
			this->label22->TabIndex = 12;
			this->label22->Text = L"Пункт отправления";
			// 
			// updFlightButton
			// 
			this->updFlightButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updFlightButton->ForeColor = System::Drawing::SystemColors::ControlText;
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
			this->updFlightArrivalDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
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
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label20->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label20->Location = System::Drawing::Point(6, 140);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(92, 13);
			this->label20->TabIndex = 14;
			this->label20->Text = L"Время прибытия";
			// 
			// updFlightDest
			// 
			this->updFlightDest->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updFlightDest->Location = System::Drawing::Point(136, 77);
			this->updFlightDest->Name = L"updFlightDest";
			this->updFlightDest->Size = System::Drawing::Size(116, 20);
			this->updFlightDest->TabIndex = 12;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label21->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label21->Location = System::Drawing::Point(6, 101);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(108, 13);
			this->label21->TabIndex = 13;
			this->label21->Text = L"Время отправления";
			// 
			// updFlightDep
			// 
			this->updFlightDep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updFlightDep->Location = System::Drawing::Point(9, 76);
			this->updFlightDep->Name = L"updFlightDep";
			this->updFlightDep->Size = System::Drawing::Size(104, 20);
			this->updFlightDep->TabIndex = 12;
			// 
			// updFlightDepDate
			// 
			this->updFlightDepDate->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->updFlightDepDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->updFlightDepDate->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->updFlightDepDate->Location = System::Drawing::Point(9, 117);
			this->updFlightDepDate->Name = L"updFlightDepDate";
			this->updFlightDepDate->Size = System::Drawing::Size(142, 20);
			this->updFlightDepDate->TabIndex = 12;
			// 
			// updFlightPlaneId
			// 
			this->updFlightPlaneId->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
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
			this->groupBox7->Controls->Add(this->label50);
			this->groupBox7->Controls->Add(this->label49);
			this->groupBox7->Controls->Add(this->addFlightPrice);
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
			this->groupBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox7->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->groupBox7->Location = System::Drawing::Point(6, 19);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(266, 197);
			this->groupBox7->TabIndex = 0;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Добавление";
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label50->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label50->Location = System::Drawing::Point(219, 44);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(49, 13);
			this->label50->TabIndex = 14;
			this->label50->Text = L"Ден. ед.";
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label49->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label49->Location = System::Drawing::Point(148, 20);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(33, 13);
			this->label49->TabIndex = 13;
			this->label49->Text = L"Цена";
			// 
			// addFlightPrice
			// 
			this->addFlightPrice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addFlightPrice->Location = System::Drawing::Point(148, 36);
			this->addFlightPrice->Name = L"addFlightPrice";
			this->addFlightPrice->Size = System::Drawing::Size(64, 20);
			this->addFlightPrice->TabIndex = 12;
			this->addFlightPrice->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// addFlightButton
			// 
			this->addFlightButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addFlightButton->ForeColor = System::Drawing::SystemColors::ControlText;
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
			this->addFlightArrivalTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->addFlightArrivalTime->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->addFlightArrivalTime->Location = System::Drawing::Point(6, 158);
			this->addFlightArrivalTime->Name = L"addFlightArrivalTime";
			this->addFlightArrivalTime->Size = System::Drawing::Size(142, 20);
			this->addFlightArrivalTime->TabIndex = 10;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label18->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label18->Location = System::Drawing::Point(6, 140);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(92, 13);
			this->label18->TabIndex = 9;
			this->label18->Text = L"Время прибытия";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label17->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label17->Location = System::Drawing::Point(6, 101);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(108, 13);
			this->label17->TabIndex = 8;
			this->label17->Text = L"Время отправления";
			// 
			// addFlightDepartTime
			// 
			this->addFlightDepartTime->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->addFlightDepartTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
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
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label15->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label15->Location = System::Drawing::Point(145, 60);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(99, 13);
			this->label15->TabIndex = 5;
			this->label15->Text = L"Пункт назначения";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label14->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label14->Location = System::Drawing::Point(2, 60);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(105, 13);
			this->label14->TabIndex = 4;
			this->label14->Text = L"Пункт отправления";
			// 
			// addFlightArrive
			// 
			this->addFlightArrive->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addFlightArrive->Location = System::Drawing::Point(148, 76);
			this->addFlightArrive->Name = L"addFlightArrive";
			this->addFlightArrive->Size = System::Drawing::Size(112, 20);
			this->addFlightArrive->TabIndex = 3;
			// 
			// addFlightDepart
			// 
			this->addFlightDepart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addFlightDepart->Location = System::Drawing::Point(5, 76);
			this->addFlightDepart->Name = L"addFlightDepart";
			this->addFlightDepart->Size = System::Drawing::Size(112, 20);
			this->addFlightDepart->TabIndex = 2;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label13->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label13->Location = System::Drawing::Point(6, 20);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(70, 13);
			this->label13->TabIndex = 1;
			this->label13->Text = L"№ самолета";
			// 
			// addFlightPlaneId
			// 
			this->addFlightPlaneId->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
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
			this->flightsTable->AllowUserToResizeRows = false;
			this->flightsTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->flightsTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->flightsTable->Location = System::Drawing::Point(226, 6);
			this->flightsTable->MultiSelect = false;
			this->flightsTable->Name = L"flightsTable";
			this->flightsTable->ReadOnly = true;
			this->flightsTable->RowHeadersVisible = false;
			this->flightsTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->flightsTable->Size = System::Drawing::Size(588, 192);
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
			this->groupBox1->Location = System::Drawing::Point(175, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(170, 169);
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
			this->addPlanesParametrsGroupBox->Size = System::Drawing::Size(163, 169);
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
			this->spotNumericUpDown->Location = System::Drawing::Point(109, 78);
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
			this->label2->Location = System::Drawing::Point(6, 81);
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
			this->adminsPage->Controls->Add(this->groupBox23);
			this->adminsPage->Controls->Add(this->groupBox22);
			this->adminsPage->Controls->Add(this->groupBox10);
			this->adminsPage->Controls->Add(this->ctrlUsersTable);
			this->adminsPage->Location = System::Drawing::Point(4, 22);
			this->adminsPage->Name = L"adminsPage";
			this->adminsPage->Size = System::Drawing::Size(831, 458);
			this->adminsPage->TabIndex = 3;
			this->adminsPage->Text = L"Управление пользователями";
			this->adminsPage->UseVisualStyleBackColor = true;
			// 
			// groupBox23
			// 
			this->groupBox23->Controls->Add(this->delUserButton);
			this->groupBox23->Controls->Add(this->label80);
			this->groupBox23->Controls->Add(this->delUserPassp);
			this->groupBox23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox23->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->groupBox23->Location = System::Drawing::Point(552, 250);
			this->groupBox23->Name = L"groupBox23";
			this->groupBox23->Size = System::Drawing::Size(268, 197);
			this->groupBox23->TabIndex = 5;
			this->groupBox23->TabStop = false;
			this->groupBox23->Text = L"Удаление";
			// 
			// delUserButton
			// 
			this->delUserButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->delUserButton->ForeColor = System::Drawing::SystemColors::WindowText;
			this->delUserButton->Location = System::Drawing::Point(191, 162);
			this->delUserButton->Name = L"delUserButton";
			this->delUserButton->Size = System::Drawing::Size(71, 23);
			this->delUserButton->TabIndex = 17;
			this->delUserButton->Text = L"Удалить";
			this->delUserButton->UseVisualStyleBackColor = true;
			this->delUserButton->Click += gcnew System::EventHandler(this, &mainForm::delUserButton_Click);
			// 
			// label80
			// 
			this->label80->AutoSize = true;
			this->label80->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label80->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label80->Location = System::Drawing::Point(6, 26);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(71, 13);
			this->label80->TabIndex = 18;
			this->label80->Text = L"№ паспорта:";
			// 
			// delUserPassp
			// 
			this->delUserPassp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->delUserPassp->ForeColor = System::Drawing::SystemColors::WindowText;
			this->delUserPassp->Location = System::Drawing::Point(6, 42);
			this->delUserPassp->MaxLength = 11;
			this->delUserPassp->Name = L"delUserPassp";
			this->delUserPassp->Size = System::Drawing::Size(116, 20);
			this->delUserPassp->TabIndex = 17;
			this->delUserPassp->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// groupBox22
			// 
			this->groupBox22->Controls->Add(this->label75);
			this->groupBox22->Controls->Add(this->label78);
			this->groupBox22->Controls->Add(this->addPasswText);
			this->groupBox22->Controls->Add(this->addRulesBox);
			this->groupBox22->Controls->Add(this->label76);
			this->groupBox22->Controls->Add(this->addPasspText);
			this->groupBox22->Controls->Add(this->label77);
			this->groupBox22->Controls->Add(this->addNameText);
			this->groupBox22->Controls->Add(this->addUserButton);
			this->groupBox22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox22->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->groupBox22->Location = System::Drawing::Point(10, 249);
			this->groupBox22->Name = L"groupBox22";
			this->groupBox22->Size = System::Drawing::Size(270, 197);
			this->groupBox22->TabIndex = 4;
			this->groupBox22->TabStop = false;
			this->groupBox22->Text = L"Добавление";
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label75->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label75->Location = System::Drawing::Point(6, 149);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(48, 13);
			this->label75->TabIndex = 23;
			this->label75->Text = L"Пароль:";
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label78->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label78->Location = System::Drawing::Point(6, 27);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(71, 13);
			this->label78->TabIndex = 19;
			this->label78->Text = L"№ паспорта:";
			// 
			// addPasswText
			// 
			this->addPasswText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addPasswText->ForeColor = System::Drawing::SystemColors::WindowText;
			this->addPasswText->Location = System::Drawing::Point(6, 165);
			this->addPasswText->MaxLength = 25;
			this->addPasswText->Name = L"addPasswText";
			this->addPasswText->Size = System::Drawing::Size(181, 20);
			this->addPasswText->TabIndex = 22;
			// 
			// addRulesBox
			// 
			this->addRulesBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addRulesBox->ForeColor = System::Drawing::SystemColors::WindowText;
			this->addRulesBox->FormattingEnabled = true;
			this->addRulesBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Администратор", L"Орг. менеджер", L"Пользователь", 
				L"Редактор билетов", L"Редактор грузов"});
			this->addRulesBox->Location = System::Drawing::Point(6, 86);
			this->addRulesBox->Name = L"addRulesBox";
			this->addRulesBox->Size = System::Drawing::Size(121, 21);
			this->addRulesBox->Sorted = true;
			this->addRulesBox->TabIndex = 16;
			this->addRulesBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label76->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label76->Location = System::Drawing::Point(6, 70);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(42, 13);
			this->label76->TabIndex = 20;
			this->label76->Text = L"Права:";
			// 
			// addPasspText
			// 
			this->addPasspText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addPasspText->ForeColor = System::Drawing::SystemColors::WindowText;
			this->addPasspText->Location = System::Drawing::Point(6, 43);
			this->addPasspText->MaxLength = 11;
			this->addPasspText->Name = L"addPasspText";
			this->addPasspText->Size = System::Drawing::Size(116, 20);
			this->addPasspText->TabIndex = 17;
			this->addPasspText->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label77->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label77->Location = System::Drawing::Point(6, 110);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(37, 13);
			this->label77->TabIndex = 21;
			this->label77->Text = L"ФИО:";
			// 
			// addNameText
			// 
			this->addNameText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addNameText->ForeColor = System::Drawing::SystemColors::WindowText;
			this->addNameText->Location = System::Drawing::Point(6, 126);
			this->addNameText->MaxLength = 50;
			this->addNameText->Name = L"addNameText";
			this->addNameText->Size = System::Drawing::Size(244, 20);
			this->addNameText->TabIndex = 18;
			// 
			// addUserButton
			// 
			this->addUserButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->addUserButton->ForeColor = System::Drawing::SystemColors::WindowText;
			this->addUserButton->Location = System::Drawing::Point(193, 165);
			this->addUserButton->Name = L"addUserButton";
			this->addUserButton->Size = System::Drawing::Size(71, 23);
			this->addUserButton->TabIndex = 15;
			this->addUserButton->Text = L"Добавить";
			this->addUserButton->UseVisualStyleBackColor = true;
			this->addUserButton->Click += gcnew System::EventHandler(this, &mainForm::addUserButton_Click);
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->label79);
			this->groupBox10->Controls->Add(this->updNewPassp);
			this->groupBox10->Controls->Add(this->label27);
			this->groupBox10->Controls->Add(this->updPasswText);
			this->groupBox10->Controls->Add(this->label28);
			this->groupBox10->Controls->Add(this->label29);
			this->groupBox10->Controls->Add(this->label30);
			this->groupBox10->Controls->Add(this->updUserButton);
			this->groupBox10->Controls->Add(this->updNameText);
			this->groupBox10->Controls->Add(this->updPasspText);
			this->groupBox10->Controls->Add(this->updRulesBox);
			this->groupBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox10->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->groupBox10->Location = System::Drawing::Point(286, 249);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(259, 197);
			this->groupBox10->TabIndex = 3;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Редактирование";
			// 
			// label79
			// 
			this->label79->AutoSize = true;
			this->label79->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label79->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label79->Location = System::Drawing::Point(125, 27);
			this->label79->Name = L"label79";
			this->label79->Size = System::Drawing::Size(108, 13);
			this->label79->TabIndex = 16;
			this->label79->Text = L"Новый № паспорта:";
			// 
			// updNewPassp
			// 
			this->updNewPassp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updNewPassp->ForeColor = System::Drawing::SystemColors::WindowText;
			this->updNewPassp->Location = System::Drawing::Point(128, 43);
			this->updNewPassp->MaxLength = 11;
			this->updNewPassp->Name = L"updNewPassp";
			this->updNewPassp->Size = System::Drawing::Size(122, 20);
			this->updNewPassp->TabIndex = 15;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label27->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label27->Location = System::Drawing::Point(6, 149);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(48, 13);
			this->label27->TabIndex = 14;
			this->label27->Text = L"Пароль:";
			// 
			// updPasswText
			// 
			this->updPasswText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updPasswText->ForeColor = System::Drawing::SystemColors::WindowText;
			this->updPasswText->Location = System::Drawing::Point(6, 165);
			this->updPasswText->MaxLength = 25;
			this->updPasswText->Name = L"updPasswText";
			this->updPasswText->Size = System::Drawing::Size(162, 20);
			this->updPasswText->TabIndex = 13;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label28->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label28->Location = System::Drawing::Point(6, 70);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(42, 13);
			this->label28->TabIndex = 12;
			this->label28->Text = L"Права:";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label29->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label29->Location = System::Drawing::Point(6, 110);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(37, 13);
			this->label29->TabIndex = 12;
			this->label29->Text = L"ФИО:";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label30->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label30->Location = System::Drawing::Point(6, 27);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(71, 13);
			this->label30->TabIndex = 12;
			this->label30->Text = L"№ паспорта:";
			// 
			// updUserButton
			// 
			this->updUserButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updUserButton->ForeColor = System::Drawing::SystemColors::WindowText;
			this->updUserButton->Location = System::Drawing::Point(179, 165);
			this->updUserButton->Name = L"updUserButton";
			this->updUserButton->Size = System::Drawing::Size(71, 23);
			this->updUserButton->TabIndex = 12;
			this->updUserButton->Text = L"Заменить";
			this->updUserButton->UseVisualStyleBackColor = true;
			this->updUserButton->Click += gcnew System::EventHandler(this, &mainForm::updUserButton_Click);
			// 
			// updNameText
			// 
			this->updNameText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updNameText->ForeColor = System::Drawing::SystemColors::WindowText;
			this->updNameText->Location = System::Drawing::Point(6, 126);
			this->updNameText->MaxLength = 50;
			this->updNameText->Name = L"updNameText";
			this->updNameText->Size = System::Drawing::Size(244, 20);
			this->updNameText->TabIndex = 12;
			// 
			// updPasspText
			// 
			this->updPasspText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updPasspText->ForeColor = System::Drawing::SystemColors::WindowText;
			this->updPasspText->Location = System::Drawing::Point(6, 43);
			this->updPasspText->MaxLength = 11;
			this->updPasspText->Name = L"updPasspText";
			this->updPasspText->Size = System::Drawing::Size(116, 20);
			this->updPasspText->TabIndex = 12;
			this->updPasspText->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::newSpotNumericUpDown_KeyPress);
			// 
			// updRulesBox
			// 
			this->updRulesBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->updRulesBox->ForeColor = System::Drawing::SystemColors::WindowText;
			this->updRulesBox->FormattingEnabled = true;
			this->updRulesBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Администратор", L"Орг. менеджер", L"Пользователь", 
				L"Редактор билетов", L"Редактор грузов"});
			this->updRulesBox->Location = System::Drawing::Point(6, 86);
			this->updRulesBox->Name = L"updRulesBox";
			this->updRulesBox->Size = System::Drawing::Size(121, 21);
			this->updRulesBox->Sorted = true;
			this->updRulesBox->TabIndex = 12;
			this->updRulesBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mainForm::addPlaneModelComboBox_KeyPress);
			// 
			// ctrlUsersTable
			// 
			this->ctrlUsersTable->AllowUserToAddRows = false;
			this->ctrlUsersTable->AllowUserToDeleteRows = false;
			this->ctrlUsersTable->AllowUserToResizeRows = false;
			this->ctrlUsersTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ctrlUsersTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->ctrlUsersTable->Location = System::Drawing::Point(446, 12);
			this->ctrlUsersTable->MultiSelect = false;
			this->ctrlUsersTable->Name = L"ctrlUsersTable";
			this->ctrlUsersTable->ReadOnly = true;
			this->ctrlUsersTable->RowHeadersVisible = false;
			this->ctrlUsersTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->ctrlUsersTable->Size = System::Drawing::Size(374, 231);
			this->ctrlUsersTable->TabIndex = 2;
			this->ctrlUsersTable->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainForm::ctrlUsersTable_CellClick);
			// 
			// printDocument1
			// 
			this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &mainForm::printDocument1_PrintPage);
			// 
			// printPreviewDialog1
			// 
			this->printPreviewDialog1->AutoScrollMargin = System::Drawing::Size(0, 0);
			this->printPreviewDialog1->AutoScrollMinSize = System::Drawing::Size(0, 0);
			this->printPreviewDialog1->ClientSize = System::Drawing::Size(400, 300);
			this->printPreviewDialog1->Document = this->printDocument1;
			this->printPreviewDialog1->Enabled = true;
			this->printPreviewDialog1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"printPreviewDialog1.Icon")));
			this->printPreviewDialog1->Name = L"printPreviewDialog1";
			this->printPreviewDialog1->Visible = false;
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
			this->tabControl1->ResumeLayout(false);
			this->usersPage->ResumeLayout(false);
			this->usersPage->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainGrid))->EndInit();
			this->groupBox21->ResumeLayout(false);
			this->groupBox21->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ordTable))->EndInit();
			this->tellersPage->ResumeLayout(false);
			this->groupBox17->ResumeLayout(false);
			this->groupBox20->ResumeLayout(false);
			this->groupBox20->PerformLayout();
			this->groupBox19->ResumeLayout(false);
			this->groupBox19->PerformLayout();
			this->groupBox18->ResumeLayout(false);
			this->groupBox18->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ticketsTable))->EndInit();
			this->cargoPage->ResumeLayout(false);
			this->groupBox11->ResumeLayout(false);
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoWeight))->EndInit();
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoDimZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoDimY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updCargoDimX))->EndInit();
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoWeight))->EndInit();
			this->groupBox13->ResumeLayout(false);
			this->groupBox13->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoDimZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoDimY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->addCargoDimX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cargoTable))->EndInit();
			this->managersPage->ResumeLayout(false);
			this->orgTab->ResumeLayout(false);
			this->manageFlights->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tariffsTable))->EndInit();
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
			this->adminsPage->ResumeLayout(false);
			this->groupBox23->ResumeLayout(false);
			this->groupBox23->PerformLayout();
			this->groupBox22->ResumeLayout(false);
			this->groupBox22->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ctrlUsersTable))->EndInit();
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
			 numTab = 2;
			 executeReq("INSERT INTO "+PREFIX+".plane_parametrs (model,spot_num) VALUES('"
								   +planesParamModelTextBox->Text+"',"+spotNumericUpDown->Value+")");
			 loadData("select * from "+PREFIX+".plane_parametrs", planeParamTable);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
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
			 numTab = 2;
			 executeReq("UPDATE "+PREFIX+".plane_parametrs SET model='"+newPlanesParamModelTextBox->Text+"', spot_num ="+newSpotNumericUpDown->Value+" WHERE model = '"+updPlanesParamModelComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".plane_parametrs", planeParamTable);
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
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
			 numTab = 2;
			 executeReq("DELETE FROM "+PREFIX+".plane_parametrs where model='"+delPlaneParamModelComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".plane_parametrs", planeParamTable);
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT model FROM "+PREFIX+".plane_parametrs","model",delPlaneParamModelComboBox);
			 CopyCombo(updPlanesParamModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(updPlaneModelComboBox,delPlaneParamModelComboBox);
			 CopyCombo(addPlaneModelComboBox,delPlaneParamModelComboBox);
			 deletePlanesParametrsButton->Enabled = true;
			 }
		 }
private: System::Void planeParamTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 planeParamTable->Enabled = false;
			 updPlanesParamModelComboBox->Text = planeParamTable->CurrentRow->Cells[0]->Value->ToString();
			 newSpotNumericUpDown->Value = Convert::ToInt32(planeParamTable->CurrentRow->Cells[1]->Value->ToString(),10);
			 delPlaneParamModelComboBox->Text = planeParamTable->CurrentRow->Cells[0]->Value->ToString();
			 planeParamTable->Enabled = true;
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
			 numTab = 3;
			 executeReq("INSERT INTO "+PREFIX+".planes (model,company) VALUES('"+
								   addPlaneModelComboBox->Text+"','"+addPlaneCompanyTextBox->Text+"')");
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",updPlaneIdComboBox);
			 CopyCombo(delPlaneIdComboBox,updPlaneIdComboBox);
			 CopyCombo(addFlightPlaneId,updPlaneIdComboBox);
			 CopyCombo(updFlightPlaneId,updPlaneIdComboBox);
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
			 executeReq("UPDATE "+PREFIX+".planes SET model='"+
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
			 executeReq("DELETE FROM "+PREFIX+".planes where id_plane='"+delPlaneIdComboBox->Text+"';");
			 loadData("select * from "+PREFIX+".planes", planesTable);
			 FillCombo("SELECT id_plane FROM "+PREFIX+".planes","id_plane",updPlaneIdComboBox);
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
			 if (addFlightArrivalTime->Value.Date <= addFlightDepartTime->Value.Date &&
				 addFlightArrivalTime->Value.TimeOfDay <=  addFlightDepartTime->Value.TimeOfDay)
			 {
				 MessageBox::Show("Дата прибытия должна быть позже даты отправления", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addFlightButton->Enabled = true;
				 return;
			 }
			 if(addFlightPrice->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Цена' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addFlightButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 4;
			 executeReq("INSERT INTO "+PREFIX+".flights (id_plane,departure,destination,departure_date,arrival_date) VALUES("+
				 addFlightPlaneId->Text+",'"+addFlightDepart->Text+"','"+addFlightArrive->Text+"','"+addFlightDepartTime->Text+"','"+addFlightArrivalTime->Text+"')");
			 myReader = executeReq("select max(id_flight) from "+PREFIX+".flights");
			 myReader->Read();
			 String^ addFlightId = myReader->GetString(0);
			 executeReq("INSERT INTO "+PREFIX+".tariffs (id_flight,class,price) VALUES("+addFlightId+",'B',"+Convert::ToInt32(addFlightPrice->Text,10)+")");
			 executeReq("INSERT INTO "+PREFIX+".tariffs (id_flight,class,price) VALUES("+addFlightId+",'A',"+(Convert::ToInt32(addFlightPrice->Text,10)*1.15).ToString()+")");
			 loadData("select * from "+PREFIX+".flights", flightsTable);
			 loadData("select * from "+PREFIX+".tariffs",tariffsTable);
			 loadData("select flights.departure,flights.destination,DATE_FORMAT(flights.departure_date,'%Y-%m-%d %H:%i:%s'),DATE_FORMAT(flights.arrival_date,'%Y-%m-%d %H:%i:%s'),tariffs.price from  "+PREFIX+
				 ".flights join "+PREFIX+".tariffs on flights.id_flight=tariffs.id_flight where tariffs.class='B' AND flights.departure_date>curdate();",ordTable);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 loadData("select * from "+PREFIX+".tickets",ticketsTable);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
				 updFlightId);
			 CopyCombo(delFlightId,updFlightId);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights WHERE departure_date>curdate() AND departure_date>curtime()","id_flight",
				 addCargoFlight);
			 addTicketDep->Text="";
			 addTicketDest->Text="";
			 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights","departure",addTicketDep);
			 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights","destination",addTicketDest);
			 CopyCombo(updTicketDep,addTicketDep);
			 CopyCombo(updTicketDest,addTicketDest);
			 CopyCombo(ordTicketDep,addTicketDep);
			 CopyCombo(ordTicketDest,addTicketDest);
			 CopyCombo(updCargoFlight,addCargoFlight);
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
			 if (updFlightArrivalDate->Value.Date <= updFlightDepDate->Value.Date && 
				 updFlightArrivalDate->Value.TimeOfDay <= updFlightDepDate->Value.TimeOfDay)
			 {
				 MessageBox::Show("Дата прибытия должна быть позже даты отправления", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 if(updFlightPrice->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Цена' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updFlightButton->Enabled = true;
				 return;
			 }
			 numTab = 4;
			 executeReq("UPDATE "+PREFIX+".flights SET id_plane="+updFlightPlaneId->Text+
				 ", departure ='"+updFlightDep->Text+"', destination ='"+updFlightDest->Text+
				 "', departure_date = '"+updFlightDepDate->Text+
				 "', arrival_date ='"+updFlightArrivalDate->Text+"' WHERE id_flight = "+updFlightId->Text+";");
			 executeReq("UPDATE "+PREFIX+".tariffs SET price="+updFlightPrice->Text+
				 " WHERE id_flight = "+updFlightId->Text+" AND class='B';");
			 executeReq("UPDATE "+PREFIX+".tariffs SET price="+(Convert::ToInt32(updFlightPrice->Text)*1.15).ToString()+
				 " WHERE id_flight = "+updFlightId->Text+" AND class='A';");
			 loadData("select * from "+PREFIX+".flights", flightsTable);
			 loadData("select * from "+PREFIX+".tariffs",tariffsTable);
			 loadData("select flights.departure,flights.destination,DATE_FORMAT(flights.departure_date,'%Y-%m-%d %H:%i:%s'),DATE_FORMAT(flights.arrival_date,'%Y-%m-%d %H:%i:%s'),tariffs.price from  "+PREFIX+
				 ".flights join "+PREFIX+".tariffs on flights.id_flight=tariffs.id_flight where tariffs.class='B' AND flights.departure_date>curdate();",ordTable);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 loadData("select * from "+PREFIX+".tickets",ticketsTable);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights WHERE departure_date>curdate() AND departure_date>curtime()","id_flight",
				 addCargoFlight);
			 CopyCombo(updCargoFlight,addCargoFlight);
			 addTicketDep->Text="";
			 addTicketDest->Text="";
			 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights","departure",addTicketDep);
			 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights","destination",addTicketDest);
			 CopyCombo(updTicketDep,addTicketDep);
			 CopyCombo(updTicketDest,addTicketDest);
			 CopyCombo(ordTicketDep,addTicketDep);
			 CopyCombo(ordTicketDest,addTicketDest);
			 updFlightButton->Enabled = true;
		 }
private: System::Void flightsTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 flightsTable->Enabled=false;
			 updFlightId->Text = flightsTable->CurrentRow->Cells[0]->Value->ToString();
			 updFlightPlaneId->Text = flightsTable->CurrentRow->Cells[1]->Value->ToString();
			 updFlightDep->Text = flightsTable->CurrentRow->Cells[2]->Value->ToString();
			 updFlightDest->Text = flightsTable->CurrentRow->Cells[3]->Value->ToString();
			 updFlightDepDate->Text = flightsTable->CurrentRow->Cells[4]->Value->ToString();
			 updFlightArrivalDate->Text = flightsTable->CurrentRow->Cells[5]->Value->ToString();
			 delFlightId->Text = flightsTable->CurrentRow->Cells[0]->Value->ToString();
			 MySqlDataReader^ myReader = executeReq("SELECT price FROM "+PREFIX+".tariffs WHERE class='B' AND id_flight="+updFlightId->Text+";");
			 myReader->Read();
			 updFlightPrice->Text = myReader->GetString(0);
			 loadData("select * from "+PREFIX+".tariffs WHERE id_flight="+updFlightId->Text+";",tariffsTable);
			 flightsTable->Enabled=true;
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
			 executeReq("DELETE FROM "+PREFIX+".flights where id_flight="+delFlightId->Text+";");
			 loadData("select * from "+PREFIX+".flights", flightsTable);
			 loadData("select * from "+PREFIX+".tariffs",tariffsTable);
			 loadData("select flights.departure,flights.destination,DATE_FORMAT(flights.departure_date,'%Y-%m-%d %H:%i:%s'),DATE_FORMAT(flights.arrival_date,'%Y-%m-%d %H:%i:%s'),tariffs.price from  "+PREFIX+
				 ".flights join "+PREFIX+".tariffs on flights.id_flight=tariffs.id_flight where tariffs.class='B' AND flights.departure_date>curdate();",ordTable);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 loadData("select * from "+PREFIX+".tickets",ticketsTable);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights","id_flight",
				 updFlightId);
			 CopyCombo(delFlightId,updFlightId);
			 FillCombo("SELECT id_flight FROM "+PREFIX+".flights WHERE departure_date>curdate() AND departure_date>curtime()","id_flight",
				 addCargoFlight);
			 CopyCombo(updCargoFlight,addCargoFlight);
			 addTicketDep->Text="";
			 addTicketDest->Text="";
			 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights","departure",addTicketDep);
			 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights","destination",addTicketDest);
			 CopyCombo(updTicketDep,addTicketDep);
			 CopyCombo(updTicketDest,addTicketDest);
			 CopyCombo(ordTicketDep,addTicketDep);
			 CopyCombo(ordTicketDest,addTicketDest);
			 delFlightButton->Enabled = true;
		 }
private: System::Void ctrlUsersTable_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			  updPasspText->Text = ctrlUsersTable->CurrentRow->Cells[0]->Value->ToString();
			  updNameText->Text  = ctrlUsersTable->CurrentRow->Cells[1]->Value->ToString();
			  updPasswText->Text  = ctrlUsersTable->CurrentRow->Cells[2]->Value->ToString();
			  updNewPassp->Text = ctrlUsersTable->CurrentRow->Cells[0]->Value->ToString();
			  delUserPassp->Text = ctrlUsersTable->CurrentRow->Cells[0]->Value->ToString();

			  String^ querry;
			  querry = "select user_rules, teller_rules, cargo_rules, manager_rules, admin_rules";
			  querry += " from "+PREFIX+".users where passport="+updPasspText->Text+";";
			  MySqlDataReader^ myReader;
			  myReader = executeReq(querry);
			  myReader->Read();
			  if (!myReader) return;

			  if (myReader->GetString(0) == "1")
			  {
				  updRulesBox->Text = "Пользователь";
			  }
			  if (myReader->GetString(1) == "1")
			  {
				  updRulesBox->SelectedItem = 1;
				  updRulesBox->Text = "Редактор билетов";
			  }
			  if (myReader->GetString(2) == "1")
			  {
				  updRulesBox->SelectedItem = 2;
				  updRulesBox->Text = "Редактор грузов";
			  }
			  if (myReader->GetString(3) == "1")
			  {
				  updRulesBox->SelectedItem = 3;
				  updRulesBox->Text = "Орг. менеджер";
			  }
			  if (myReader->GetString(4) == "1")
			  {
				  updRulesBox->SelectedItem = 4;
				  updRulesBox->Text = "Администратор";
			  }
		 }
private: System::Void updUserButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 updUserButton->Enabled = false;
			 if(updPasspText->Text->Length==0)
			 {
				 MessageBox::Show("Поле '№ паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }
			 /*if(updPasspText->Text->Length!=11)
			 {
				 MessageBox::Show("Поле '№ паспорта' введено неверно. Проверьте что введено 11 цифр", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }*/
			 if(updNewPassp->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Новый № паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }
			 if(updNewPassp->Text->Length!=11)
			 {
				 MessageBox::Show("Поле 'Новый № паспорта' введено неверно. Проверьте что введено 11 цифр", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }
			 if(updRulesBox->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Права' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }
			 if(updNameText->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'ФИО' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }
			 if(updPasswText->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пароль' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updUserButton->Enabled = true;
				 return;
			 }

			 String ^user, ^teller, ^cargo, ^admin, ^manager;
			 if (updRulesBox->Text == "Администратор")
				 user = teller = cargo = manager = admin = "1";
			 
			 if (updRulesBox->Text == "Пользователь"){
				 user = "1";
				 teller = cargo = manager = admin = "0";
			 }
			 if (updRulesBox->Text == "Орг. менеджер"){
				 manager = "1";
				 teller = cargo = user = admin = "0";
			 }
			 if (updRulesBox->Text == "Редактор билетов"){
				 teller = "1";
				 manager = cargo = user = admin = "0";
			 }
			 if (updRulesBox->Text == "Редактор грузов"){
				 cargo = "1";
				 manager = teller = user = admin = "0";
			 }

			 executeReq("UPDATE "+PREFIX+".users SET passport ='"+updNewPassp->Text+"', password ='"
				 +updPasswText->Text+"', user_rules ='"+user+
				 "', teller_rules = '"+teller+
				 "', cargo_rules ='"+cargo+"', manager_rules ='"+manager+
				 "', admin_rules ='"+admin+"' WHERE passport = '"+updPasspText->Text+"';");

			 executeReq("update "+PREFIX+".passengers SET full_name='"+updNameText->Text+
				 "', id_pass='"+updNewPassp->Text+"' where id_pass='"+updPasspText->Text+"';");

			 asAdmin(ctrlUsersTable);
			 updUserButton->Enabled = true;
		 }
private: System::Void addCargoButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 addCargoButton->Enabled = false;
			 if(addCargoPass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 if(addCargoFlight->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер рейса' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 if(addCargoName->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Наименование' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 if(addCargoDimX->Value > 500)
			 {
				 MessageBox::Show("Поля размеров не могут превышать 500 см", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 if(addCargoDimY->Value > 500)
			 {
				 MessageBox::Show("Поля размеров не могут превышать 500 см", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 if(addCargoDimZ->Value > 500)
			 {
				 MessageBox::Show("Поля размеров не могут превышать 500 см", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 if(addCargoWeight->Value > 50000)
			 {
				 MessageBox::Show("Поле 'Вес' не может превышать 50000 г", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addCargoButton->Enabled = true;
				 return;
			 }
			 numTab = 5;
			 executeReq("INSERT INTO "+PREFIX+".cargo (id_pass,id_flight,name,dimensions,weight) VALUES('"+
				 addCargoPass->Text+"',"+addCargoFlight->Text+",'"+addCargoName->Text+"','"
				 +addCargoDimX->Text+"x"+addCargoDimY->Text+"x"+addCargoDimZ->Text+"','"+addCargoWeight->Text+"')");
			 loadData("select * from "+PREFIX+".cargo", cargoTable);
			 FillCombo("SELECT id_cargo FROM "+PREFIX+".cargo","id_cargo",updCargoId);
			 CopyCombo(delCargoId,updCargoId);
			 addCargoButton->Enabled = true;
		 }
private: System::Void updCargoButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 updCargoButton->Enabled = false;
			 if(updCargoId->Text->Length ==0)
			 {
				 MessageBox::Show("Поле 'Номер груза' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoPass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoFlight->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер рейса' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoName->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Наименование' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoDimX->Value > 500)
			 {
				 MessageBox::Show("Поля размеров не могут превышать 500 см", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoDimY->Value > 500)
			 {
				 MessageBox::Show("Поля размеров не могут превышать 500 см", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoDimZ->Value > 500)
			 {
				 MessageBox::Show("Поля размеров не могут превышать 500 см", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 if(updCargoWeight->Value > 50000)
			 {
				 MessageBox::Show("Поле 'Вес' не может превышать 50000 г", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updCargoButton->Enabled = true;
				 return;
			 }
			 numTab = 5;
			 executeReq("UPDATE "+PREFIX+".cargo SET id_pass='"+updCargoPass->Text+
				 "', id_flight ="+updCargoFlight->Text+", name ='"+updCargoName->Text+
				 "', dimensions = '"+updCargoDimX->Text+"x"+updCargoDimY->Text+"x"+updCargoDimZ->Text+
				 "', weight ='"+updCargoWeight->Text+"' WHERE id_cargo = "+updCargoId->Text+";");
			 loadData("select * from "+PREFIX+".cargo", cargoTable);
			 updCargoButton->Enabled = true;
		 }
private: System::Void cargoTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 cargoTable->Enabled = false;
			 updCargoId->Text = cargoTable->CurrentRow->Cells[0]->Value->ToString();
			 delCargoId->Text = cargoTable->CurrentRow->Cells[0]->Value->ToString();
			 updCargoPass->Text = cargoTable->CurrentRow->Cells[1]->Value->ToString();
			 updCargoFlight->Text = cargoTable->CurrentRow->Cells[2]->Value->ToString();
			 updCargoName->Text = cargoTable->CurrentRow->Cells[3]->Value->ToString();
			 updCargoDimX->Text = "";
			 updCargoDimY->Text = "";
			 updCargoDimZ->Text = "";
			 String^ s1 = cargoTable->CurrentRow->Cells[4]->Value->ToString();
			 int k=0;
			 for(;s1[k]!='x';k++)
				 updCargoDimX->Text += s1[k];
			 k++;
			 for(;s1[k]!='x';k++)
				 updCargoDimY->Text += s1[k];
			 k++;
			 for(;k<s1->Length;k++)
				 updCargoDimZ->Text += s1[k];
			 updCargoWeight->Text = cargoTable->CurrentRow->Cells[5]->Value->ToString();
			 cargoTable->Enabled = true;
		 }
private: System::Void delCargoButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 delCargoButton->Enabled = false;
			 if(delCargoId->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер груза' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 delCargoButton->Enabled = true;
				 return;
			 }
			 numTab = 5;
			 executeReq("DELETE FROM "+PREFIX+".cargo where id_cargo="+delCargoId->Text+";");
			 loadData("select * from "+PREFIX+".cargo", cargoTable);
			 FillCombo("SELECT id_cargo FROM "+PREFIX+".cargo","id_cargo",updCargoId);
			 CopyCombo(delCargoId,updCargoId);
			 delCargoButton->Enabled = true;
		 }
private: System::Void addTicketDep_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(addTicketDep->Text->Length!=0)
				FillCombo("SELECT distinct destination FROM "+PREFIX+".flights WHERE departure='"+addTicketDep->Text+"';","destination",addTicketDest);
			 else
			 {
				FillCombo("SELECT distinct destination FROM "+PREFIX+".flights;","destination",addTicketDest);
				addTicketDate->Items->Clear();
			 }
			 if(addTicketDep->Text->Length!=0 && addTicketDest->Text->Length!=0)
			 {
				 FillCombo("SELECT DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE destination='"
					 +addTicketDest->Text+"' AND departure='"+addTicketDep->Text+"' AND departure_date>curdate();","DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s')",addTicketDate);
				 if(addTicketDate->Items->Count==0)
					 addTicketDate->Text = "На данный момент рейсов нет";
				 else addTicketDate->Text = "";
			 }
		 }
private: System::Void addTicketDest_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(addTicketDest->Text->Length!=0)
				FillCombo("SELECT distinct departure FROM "+PREFIX+".flights WHERE destination='"+addTicketDest->Text+"';","departure",addTicketDep);
			 else
			 {
				FillCombo("SELECT distinct departure FROM "+PREFIX+".flights;","departure",addTicketDep);
				addTicketDate->Items->Clear();
			 }
			 if(addTicketDep->Text->Length!=0 && addTicketDest->Text->Length!=0)
			 {
				 FillCombo("SELECT DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE destination='"
				 +addTicketDest->Text+"' AND departure='"+addTicketDep->Text+"' AND departure_date>curdate();","DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s')",addTicketDate);
				 if(addTicketDate->Items->Count==0)
					addTicketDate->Text = "На данный момент рейсов нет";
				 else addTicketDate->Text = "";
			 }
		 }
private: System::Void addTicketButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 addTicketButton->Enabled = false;
			 if(addTicketPass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 if(addTicketDep->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт Отправления' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 if(addTicketDest->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт Назначения' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 if(addTicketClass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Класс' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 if(addTicketDate->Text->Length==0 || addTicketDate->Items->Count==0)
			 {
				 MessageBox::Show("Поле 'Дата отправления' не может быть пустым.", "Ошибка",
			     MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 6;
			 myReader = executeReq("SELECT id_flight FROM "+PREFIX+".flights WHERE departure='"+addTicketDep->Text+
				 "' AND destination='"+addTicketDest->Text+"' AND departure_date='"+addTicketDate->Text+"';");
			 //SELECT id_flight FROM airlines.flights WHERE departure='Москва' AND destination='Киев' AND departure_date='2013-11-22 21:42:58';
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Такого рейса не существует", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 String^ idFlight=myReader->GetString(0);
			 myReader = executeReq("SELECT * FROM "+PREFIX+".tickets WHERE id_flight="+idFlight+" AND id_pass='"+addTicketPass->Text+"';");
			 if(myReader->HasRows)
			 {
				 MessageBox::Show("Пользователь с данным паспортом уже заказал билет на данный рейс", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 myReader = executeReq("SELECT spot_num FROM "+PREFIX+".plane_parametrs WHERE model=(SELECT model FROM "+PREFIX+".planes WHERE id_plane=(SELECT id_plane FROM "+PREFIX+".flights WHERE id_flight="+idFlight+"))");
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Невозможно найти самолет рейса №"+idFlight, "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 int spotAmount = myReader->GetUInt32(0);
			 myReader = executeReq("SELECT count(*) FROM "+PREFIX+".tickets WHERE id_flight="+idFlight+";");
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Невозможно найти билеты рейса №"+idFlight, "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }
			 int ticketAmount = myReader->GetUInt32(0);
			 if(ticketAmount>=spotAmount)
			 {
				 MessageBox::Show("Все билеты на рейс № "+idFlight+" проданы", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addTicketButton->Enabled = true;
				 return;
			 }	 
			 /*else  MessageBox::Show(ticketAmount.ToString()+" "+spotAmount.ToString(), "Ошибка",
				 MessageBoxButtons::OK,MessageBoxIcon::Error);	*/
			 myReader = executeReq("INSERT INTO "+PREFIX+".tickets (id_pass,id_flight,class,sale_date) VALUES('"+
				 addTicketPass->Text+"',"+idFlight+",'"+addTicketClass->Text+"',curdate())");
			 loadData("select * from "+PREFIX+".tickets", ticketsTable);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 FillCombo("SELECT distinct id_pass FROM "+PREFIX+".tickets","id_pass",updTicketPass);
			 CopyCombo(delTicketPass,updTicketPass);
			 addTicketButton->Enabled = true;
		 }
		 private: System::Void addTicketDep_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
					  int i = (int)e->KeyChar;
					  if (!(i == 8))
						  e->Handled = true;
					  else addTicketDep->Text="";
}
private: System::Void addTicketDest_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 int i = (int)e->KeyChar;
			 if (!(i == 8))
				 e->Handled = true;
			 else addTicketDest->Text="";
		 }
private: System::Void updTicketPass_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 updTicketId->Text="";
			 FillCombo("SELECT id_ticket FROM "+PREFIX+".tickets WHERE id_pass="+updTicketPass->Text+";","id_ticket",updTicketId);
		 }
private: System::Void updTicketDep_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 int i = (int)e->KeyChar;
			 if (!(i == 8))
				 e->Handled = true;
			 else updTicketDep->Text="";
		 }
private: System::Void updTicketDest_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 int i = (int)e->KeyChar;
			 if (!(i == 8))
				 e->Handled = true;
			 else updTicketDest->Text="";
		 }
private: System::Void updTicketDep_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if(!isCellClick)
		{
			 if(updTicketDep->Text->Length!=0)
				 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights WHERE departure='"+updTicketDep->Text+"';","destination",updTicketDest);
			 else
			 {
				 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights;","destination",updTicketDest);
				 updTicketDate->Items->Clear();
			 }
			 if(updTicketDep->Text->Length!=0 && updTicketDest->Text->Length!=0)
			 {
				 FillCombo("SELECT DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE destination='"
					 +updTicketDest->Text+"' AND departure='"+updTicketDep->Text+"' AND departure_date>curdate();","DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s')",updTicketDate);
				 if(updTicketDate->Items->Count==0)
					 updTicketDate->Text = "На данный момент рейсов нет";
				 else updTicketDate->Text = "";
			 }
		}
	}
private: System::Void updTicketDest_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if(!isCellClick)
		{
			 if(updTicketDest->Text->Length!=0)
				 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights WHERE destination='"+updTicketDest->Text+"';","departure",updTicketDep);
			 else
			 {
				 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights;","departure",updTicketDep);
				 updTicketDate->Items->Clear();
			 }
			 if(updTicketDep->Text->Length!=0 && updTicketDest->Text->Length!=0)
			 {
				 FillCombo("SELECT DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE destination='"
					 +updTicketDest->Text+"' AND departure='"+updTicketDep->Text+"' AND departure_date>curdate();","DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s')",updTicketDate);
				 if(updTicketDate->Items->Count==0)
					 updTicketDate->Text = "На данный момент рейсов нет";
				 else updTicketDate->Text = "";
			 }
		}
	}
private: System::Void ticketsTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 isCellClick = true;
			 ticketsTable->Enabled = false;
			 updTicketPass->Text = ticketsTable->CurrentRow->Cells[2]->Value->ToString();
			 delTicketPass->Text = ticketsTable->CurrentRow->Cells[2]->Value->ToString();
			 updTicketId->Text = ticketsTable->CurrentRow->Cells[0]->Value->ToString();
			 delTicketId->Text = ticketsTable->CurrentRow->Cells[0]->Value->ToString();
			 updTicketClass->Text = ticketsTable->CurrentRow->Cells[3]->Value->ToString();
			 MySqlDataReader^ myReader;
			 myReader = executeReq("SELECT departure,destination,DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE id_flight="+ticketsTable->CurrentRow->Cells[1]->Value->ToString()+";");
			 myReader->Read();
			 updTicketDate->Items->Clear();
			 updTicketDep->Text = myReader->GetString(0);
			 updTicketDest->Text = myReader->GetString(1);
			 updTicketDate->Text = myReader->GetString(2);
			 isCellClick = false;
			 ticketsTable->Enabled = true;
		 }
private: System::Void button1_Click_2(System::Object^  sender, System::EventArgs^  e) {
			 updTicketButton->Enabled = false;
			 if(updTicketId->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Номер билета' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 if(updTicketPass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Номер паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 if(updTicketDep->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт Отправления' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 if(updTicketDest->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт Назначения' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 if(updTicketClass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Класс' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 if(updTicketDate->Text->Length==0 || updTicketDate->Items->Count==0)
			 {
				 MessageBox::Show("Поле 'Дата' не может быть пустым.", "Ошибка",
			     MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 6;
			 myReader = executeReq("SELECT id_flight FROM "+PREFIX+".flights WHERE departure='"+updTicketDep->Text+
				 "' AND destination='"+updTicketDest->Text+"' AND departure_date='"+updTicketDate->Text+"';");
			 //SELECT id_flight FROM airlines.flights WHERE departure='Москва' AND destination='Киев' AND departure_date='2013-11-22 21:42:58';
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Такого рейса не существует", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 updTicketButton->Enabled = true;
				 return;
			 }
			 String^ idFlight=myReader->GetString(0);
			 myReader = executeReq("UPDATE "+PREFIX+".tickets SET id_pass='"+updTicketPass->Text+
				 "', id_flight ="+idFlight+", class ='"+updTicketClass->Text+
				 "', sale_date = curdate() WHERE id_ticket = "+updTicketId->Text+";");
			 loadData("select * from "+PREFIX+".tickets", ticketsTable);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 updTicketButton->Enabled = true;
		 }
private: System::Void delTicketPass_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 delTicketId->Text="";
			 if(delTicketPass->Text->Length!=0)
				FillCombo("SELECT id_ticket FROM "+PREFIX+".tickets WHERE id_pass="+delTicketPass->Text+";","id_ticket",delTicketId);
		 }
private: System::Void delTicketButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 delTicketButton->Enabled = false;
			 if(delTicketPass->Text->Length ==0)
			 {
				 MessageBox::Show("Поле 'Номер паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 delTicketButton->Enabled = true;
				 return;
			 }
			 if(delTicketId->Text->Length ==0)
			 {
				 MessageBox::Show("Поле 'Номер билета' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 delTicketButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 6;
			 myReader = executeReq("DELETE FROM "+PREFIX+".tickets WHERE id_ticket="+delTicketId->Text+";");
			 loadData("select * from "+PREFIX+".tickets", ticketsTable);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 FillCombo("Select distinct id_pass from "+PREFIX+".tickets","id_pass",updTicketPass);
			 CopyCombo(delTicketPass,updTicketPass);
			 delTicketPass->Text = "";
			 delTicketId->Text = "";
			 delTicketButton->Enabled = true;
		 }
private: System::Void ordTicketDep_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(ordTicketDep->Text->Length!=0)
				 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights WHERE departure='"+ordTicketDep->Text+"';","destination",ordTicketDest);
			 else
			 {
				 FillCombo("SELECT distinct destination FROM "+PREFIX+".flights;","destination",ordTicketDest);
				 ordTicketDate->Items->Clear();
			 }
			 if(ordTicketDep->Text->Length!=0 && ordTicketDest->Text->Length!=0)
			 {
				 FillCombo("SELECT DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE destination='"
					 +ordTicketDest->Text+"' AND departure='"+ordTicketDep->Text+"' AND departure_date>curdate();","DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s')",ordTicketDate);
				 if(ordTicketDate->Items->Count==0)
					 ordTicketDate->Text = "На данный момент рейсов нет";
				 else ordTicketDate->Text = "";
		 }
		 }
private: System::Void ordTicketDest_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(ordTicketDest->Text->Length!=0)
				 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights WHERE destination='"+ordTicketDest->Text+"';","departure",ordTicketDep);
			 else
			 {
				 FillCombo("SELECT distinct departure FROM "+PREFIX+".flights;","departure",ordTicketDep);
				 ordTicketDate->Items->Clear();
			 }
			 if(ordTicketDep->Text->Length!=0 && ordTicketDest->Text->Length!=0)
			 {
				 FillCombo("SELECT DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s') FROM "+PREFIX+".flights WHERE destination='"
					 +ordTicketDest->Text+"' AND departure='"+ordTicketDep->Text+"' AND departure_date>curdate();","DATE_FORMAT(departure_date,'%Y-%m-%d %H:%i:%s')",ordTicketDate);
				 if(ordTicketDate->Items->Count==0)
					 ordTicketDate->Text = "На данный момент рейсов нет";
				 else ordTicketDate->Text = "";
			 }
		 }
private: System::Void ordTicketDep_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 int i = (int)e->KeyChar;
			 if (!(i == 8))
				 e->Handled = true;
			 else ordTicketDep->Text="";
		 }
private: System::Void ordButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 ordTicketButton->Enabled = false;
			 if(ordTicketDep->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт Отправления' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 if(ordTicketDest->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пункт Назначения' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 if(ordTicketClass->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Класс' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 if(ordTicketDate->Text->Length==0 || ordTicketDate->Items->Count==0)
			 {
				 MessageBox::Show("Поле 'Дата отправления' не может быть пустым.", "Ошибка",
			     MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 MySqlDataReader^ myReader;
			 numTab = 6;
			 myReader = executeReq("SELECT id_flight FROM "+PREFIX+".flights WHERE departure='"+ordTicketDep->Text+
				 "' AND destination='"+ordTicketDest->Text+"' AND departure_date='"+ordTicketDate->Text+"';");
			 //SELECT id_flight FROM airlines.flights WHERE departure='Москва' AND destination='Киев' AND departure_date='2013-11-22 21:42:58';
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Такого рейса не существует", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 String^ idFlight=myReader->GetString(0);
			 String^ idPassStr = gcnew String(idPass);
			 myReader = executeReq("SELECT * FROM "+PREFIX+".tickets WHERE id_flight="+idFlight+" AND id_pass='"+idPassStr+"';");
			 if(myReader->HasRows)
			 {
				 MessageBox::Show("Пользователь с данным паспортом уже заказал билет на данный рейс", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 myReader = executeReq("SELECT spot_num FROM "+PREFIX+".plane_parametrs WHERE model=(SELECT model FROM "+
				 PREFIX+".planes WHERE id_plane=(SELECT id_plane FROM "+PREFIX+".flights WHERE id_flight="+idFlight+"))");
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Невозможно найти самолет рейса №"+idFlight, "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 int spotAmount = myReader->GetUInt32(0);
			 myReader = executeReq("SELECT count(*) FROM "+PREFIX+".tickets WHERE id_flight="+idFlight+";");
			 if(!myReader->Read())
			 {
				 MessageBox::Show("Невозможно найти билеты рейса №"+idFlight, "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }
			 int ticketAmount = myReader->GetUInt32(0);
			 if(ticketAmount>=spotAmount)
			 {
				 MessageBox::Show("Все билеты на рейс № "+idFlight+" проданы", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 ordTicketButton->Enabled = true;
				 return;
			 }	 
			 /*else  MessageBox::Show(ticketAmount.ToString()+" "+spotAmount.ToString(), "Ошибка",
				 MessageBoxButtons::OK,MessageBoxIcon::Error);	*/
			 myReader = executeReq("INSERT INTO "+PREFIX+".tickets (id_pass,id_flight,class,sale_date) VALUES('"+
				 idPassStr+"',"+idFlight+",'"+ordTicketClass->Text+"',curdate())");
			 loadData("select * from "+PREFIX+".tickets", ticketsTable);
			 loadData("select flights.departure,flights.destination,DATE_FORMAT(flights.departure_date,'%Y-%m-%d %H:%i:%s'),DATE_FORMAT(flights.arrival_date,'%Y-%m-%d %H:%i:%s'),tariffs.price from  "+PREFIX+
				 ".flights join "+PREFIX+".tariffs on flights.id_flight=tariffs.id_flight where tariffs.class='B' AND flights.departure_date>curdate();",ordTable);
			 FillCombo("SELECT distinct id_pass FROM "+PREFIX+".tickets","id_pass",updTicketPass);
			 loadData("SELECT tickets.id_ticket,tickets.id_flight,flights.departure,flights.destination,flights.departure_date,flights.arrival_date,tariffs.price,tickets.sale_date from "+
				 PREFIX+".tickets join "+PREFIX+".tariffs on tariffs.id_flight=tickets.id_flight join "+PREFIX+
				 ".flights on flights.id_flight=tickets.id_flight where tariffs.class=tickets.class AND tickets.id_pass='"+(gcnew String(idPass))+"';",mainGrid);
			 CopyCombo(delTicketPass,updTicketPass);
			 ordTicketButton->Enabled = true;
		 }
private: System::Void ordTable_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 ordTicketDep->Text = ordTable->CurrentRow->Cells[0]->Value->ToString();
			 ordTicketDest->Text = ordTable->CurrentRow->Cells[1]->Value->ToString();
			 ordTicketDate->Text = ordTable->CurrentRow->Cells[2]->Value->ToString();

		 }
private: System::Void addUserButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 addUserButton->Enabled = false;
			 if(addPasspText->Text->Length==0)
			 {
				 MessageBox::Show("Поле '№ паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addUserButton->Enabled = true;
				 return;
			 }
			 if(addPasspText->Text->Length!=11)
			 {
				 MessageBox::Show("Поле '№ паспорта' введено неверно. Проверьте что введено 11 цифр", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addUserButton->Enabled = true;
				 return;
			 }
			 if(addRulesBox->Text->Length==0)
			 {
				 MessageBox::Show("Поле 'Права' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addUserButton->Enabled = true;
				 return;
			 }
			 if(addNameText->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'ФИО' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addUserButton->Enabled = true;
				 return;
			 }
			 if(addPasswText->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'Пароль' не может быть пустым", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 addUserButton->Enabled = true;
				 return;
			 }

			 String ^user, ^teller, ^cargo, ^admin, ^manager;
			 if (addRulesBox->Text == "Администратор")
				 user = teller = cargo = manager = admin = "1";

			 if (addRulesBox->Text == "Пользователь"){
				 user = "1";
				 teller = cargo = manager = admin = "0";
			 }
			 if (addRulesBox->Text == "Орг. менеджер"){
				 manager = "1";
				 teller = cargo = user = admin = "0";
			 }
			 if (addRulesBox->Text == "Редактор билетов"){
				 teller = "1";
				 manager = cargo = user = admin = "0";
			 }
			 if (addRulesBox->Text == "Редактор грузов"){
				 cargo = "1";
				 manager = teller = user = admin = "0";
			 }

			 executeReq("INSERT INTO "+PREFIX+".users (passport,password,user_rules,teller_rules,cargo_rules,manager_rules,admin_rules) VALUES('"+
				 addPasspText->Text+"','"+addPasswText->Text+"','"+user+"','"+teller+"','"+cargo+"','"+manager+"','"+admin+"')");
			 executeReq("INSERT INTO "+PREFIX+".passengers (id_pass,full_name) VALUES('"+addPasspText->Text+"','"+addNameText->Text+"')");
			 asAdmin(ctrlUsersTable);
			 addUserButton->Enabled = true;
		 }
private: System::Void delUserButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 delUserButton->Enabled = false;
			 if(delUserPassp->Text->Length==0)
			 {
				 MessageBox::Show("Поле '№ паспорта' не может быть пустым.", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 delUserButton->Enabled = true;
				 return;
			 }
			 if(delUserPassp->Text->Length!=11)
			 {
				 MessageBox::Show("Поле '№ паспорта' введено неверно. Проверьте что введено 11 цифр", "Ошибка",
					 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 delUserButton->Enabled = true;
				 return;
			 }
			 executeReq("DELETE FROM "+PREFIX+".users where passport='"+delUserPassp->Text+"';");
			 executeReq("DELETE FROM "+PREFIX+".passengers where id_pass='"+delUserPassp->Text+"';");
			 asAdmin(ctrlUsersTable);
			 delUserButton->Enabled = true;
		 }
private: System::Void printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e) {
			 String^ line ="";
			 try
			 {
				 if(!mainGrid->Rows->Count==1)
					 return;
				printFont = gcnew System::Drawing::Font( "Arial",12 );
				line=Environment::NewLine+"№ билета: "+mainGrid->CurrentRow->Cells[0]->Value->ToString()+Environment::NewLine+
				"№ рейса: "+mainGrid->CurrentRow->Cells[1]->Value->ToString()+Environment::NewLine+
				"Пункт отправления: "+mainGrid->CurrentRow->Cells[2]->Value->ToString()+Environment::NewLine+
				"Пункт Назначения: "+mainGrid->CurrentRow->Cells[3]->Value->ToString()+Environment::NewLine+
				"Время отправления: "+mainGrid->CurrentRow->Cells[4]->Value->ToString()+Environment::NewLine+
				"Время прибытия: "+mainGrid->CurrentRow->Cells[5]->Value->ToString()+Environment::NewLine+
				"Цена: "+mainGrid->CurrentRow->Cells[6]->Value->ToString()+Environment::NewLine+
				"Дата продажи: "+mainGrid->CurrentRow->Cells[7]->Value->ToString();
				 e->Graphics->DrawString(line,printFont,Brushes::Black,(float)e->MarginBounds.Left,0,gcnew StringFormat);
			 }
			 catch(Exception^ ex)
			 {
				MessageBox::Show( ex->Message );
			 }
		 }
private: System::Void prntButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 try
			 {
				 printDocument1->Print();
			 }
			 catch(Exception^ ex)
			 {
				 MessageBox::Show( ex->Message );
			 }
		 }
private: System::Void previewButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 printPreviewDialog1->ShowDialog();
		 }
};
}
