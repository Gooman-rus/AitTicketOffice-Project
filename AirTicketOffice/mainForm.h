#pragma once
#include "common.h"

namespace AirTicketOffice {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	public:
		mainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			loadData("select * from airlines.flights", flightsTable);
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
	private: System::Windows::Forms::DataGridView^  flightsTable;
	private: System::Windows::Forms::TabPage^  adminsPage;






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
			this->managersPage = (gcnew System::Windows::Forms::TabPage());
			this->flightsTable = (gcnew System::Windows::Forms::DataGridView());
			this->adminsPage = (gcnew System::Windows::Forms::TabPage());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainGrid))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->usersPage->SuspendLayout();
			this->managersPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->flightsTable))->BeginInit();
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
			this->tabControl1->Controls->Add(this->managersPage);
			this->tabControl1->Controls->Add(this->adminsPage);
			this->tabControl1->Location = System::Drawing::Point(-1, 4);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(788, 436);
			this->tabControl1->TabIndex = 1;
			this->tabControl1->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &mainForm::tabControl1_Selecting);
			// 
			// usersPage
			// 
			this->usersPage->Controls->Add(this->mainGrid);
			this->usersPage->Location = System::Drawing::Point(4, 22);
			this->usersPage->Name = L"usersPage";
			this->usersPage->Padding = System::Windows::Forms::Padding(3);
			this->usersPage->Size = System::Drawing::Size(767, 402);
			this->usersPage->TabIndex = 0;
			this->usersPage->Text = L"Пользователь";
			this->usersPage->UseVisualStyleBackColor = true;
			// 
			// tellersPage
			// 
			this->tellersPage->Location = System::Drawing::Point(4, 22);
			this->tellersPage->Name = L"tellersPage";
			this->tellersPage->Padding = System::Windows::Forms::Padding(3);
			this->tellersPage->Size = System::Drawing::Size(767, 402);
			this->tellersPage->TabIndex = 1;
			this->tellersPage->Text = L"Менеджер по билетам";
			this->tellersPage->UseVisualStyleBackColor = true;
			// 
			// managersPage
			// 
			this->managersPage->Controls->Add(this->flightsTable);
			this->managersPage->Location = System::Drawing::Point(4, 22);
			this->managersPage->Name = L"managersPage";
			this->managersPage->Size = System::Drawing::Size(780, 410);
			this->managersPage->TabIndex = 2;
			this->managersPage->Text = L"Организационный менеджер";
			this->managersPage->UseVisualStyleBackColor = true;
			// 
			// flightsTable
			// 
			this->flightsTable->AllowUserToAddRows = false;
			this->flightsTable->AllowUserToDeleteRows = false;
			this->flightsTable->AllowUserToResizeColumns = false;
			this->flightsTable->AllowUserToResizeRows = false;
			this->flightsTable->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->flightsTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->flightsTable->Location = System::Drawing::Point(54, 3);
			this->flightsTable->MultiSelect = false;
			this->flightsTable->Name = L"flightsTable";
			this->flightsTable->ReadOnly = true;
			this->flightsTable->RowHeadersVisible = false;
			this->flightsTable->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->flightsTable->Size = System::Drawing::Size(673, 192);
			this->flightsTable->TabIndex = 0;
			// 
			// adminsPage
			// 
			this->adminsPage->Location = System::Drawing::Point(4, 22);
			this->adminsPage->Name = L"adminsPage";
			this->adminsPage->Size = System::Drawing::Size(767, 402);
			this->adminsPage->TabIndex = 3;
			this->adminsPage->Text = L"Администратор";
			this->adminsPage->UseVisualStyleBackColor = true;
			// 
			// mainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(788, 444);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->flightsTable))->EndInit();
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
						e->Cancel = true;
            }
			 }
};
}
