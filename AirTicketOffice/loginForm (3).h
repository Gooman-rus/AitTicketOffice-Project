#pragma once
#include "MainProgramm.h"
namespace AirTicketOffice {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  loginButton;
	protected: 
	private: System::Windows::Forms::Label^  loginLabel;
	private: System::Windows::Forms::Label^  passLabel;
	private: System::Windows::Forms::TextBox^  loginTextBox;
	private: System::Windows::Forms::TextBox^  passTextBox;

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->loginLabel = (gcnew System::Windows::Forms::Label());
			this->passLabel = (gcnew System::Windows::Forms::Label());
			this->loginTextBox = (gcnew System::Windows::Forms::TextBox());
			this->passTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// loginButton
			// 
			this->loginButton->Location = System::Drawing::Point(53, 77);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(75, 23);
			this->loginButton->TabIndex = 0;
			this->loginButton->Text = L"¬ход";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &Form1::loginButton_Click);
			// 
			// loginLabel
			// 
			this->loginLabel->AutoSize = true;
			this->loginLabel->Location = System::Drawing::Point(12, 26);
			this->loginLabel->Name = L"loginLabel";
			this->loginLabel->Size = System::Drawing::Size(38, 13);
			this->loginLabel->TabIndex = 1;
			this->loginLabel->Text = L"Ћогин";
			// 
			// passLabel
			// 
			this->passLabel->AutoSize = true;
			this->passLabel->Location = System::Drawing::Point(12, 54);
			this->passLabel->Name = L"passLabel";
			this->passLabel->Size = System::Drawing::Size(45, 13);
			this->passLabel->TabIndex = 2;
			this->passLabel->Text = L"ѕароль";
			// 
			// loginTextBox
			// 
			this->loginTextBox->Location = System::Drawing::Point(53, 23);
			this->loginTextBox->Name = L"loginTextBox";
			this->loginTextBox->Size = System::Drawing::Size(100, 20);
			this->loginTextBox->TabIndex = 3;
			this->loginTextBox->Text = L"admin";
			// 
			// passTextBox
			// 
			this->passTextBox->Location = System::Drawing::Point(53, 51);
			this->passTextBox->Name = L"passTextBox";
			this->passTextBox->Size = System::Drawing::Size(100, 20);
			this->passTextBox->TabIndex = 4;
			this->passTextBox->Text = L"123";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(180, 113);
			this->Controls->Add(this->passTextBox);
			this->Controls->Add(this->loginTextBox);
			this->Controls->Add(this->passLabel);
			this->Controls->Add(this->loginLabel);
			this->Controls->Add(this->loginButton);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"¬ход";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loginButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 String^ constring=L"datasource=localhost;port=3306;username=root;password=qwerty721";
			 MySqlConnection^ conDataBase = gcnew MySqlConnection(constring);
			 MySqlCommand^ cmdDataBase = gcnew MySqlCommand("Select * from airlines.users;",conDataBase);
			 MySqlDataReader^ myReader;
			 try{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				while(myReader->Read())
				{
					if(myReader->GetString(1)==loginTextBox->Text && myReader->GetString(2)==passTextBox->Text)
					{
						this->Hide();
						MainProgramm^ secondForm = gcnew MainProgramm();
						secondForm->ShowDialog();
						break;
					}
					else
						 MessageBox::Show("not OK");
				}
			 }
			 catch(Exception^ ex){
			 
				 MessageBox::Show(ex->Message);
			 }
			 }
};
}

