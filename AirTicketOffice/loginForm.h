#pragma once
#include "mainForm.h"
#include "registrationForm.h"
#include "common.h"


namespace AirTicketOffice {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Сводка для loginForm
	/// </summary>
	public ref class loginForm : public System::Windows::Forms::Form
	{
	public: static String^ constring = L"datasource="+SERVER+";port="+PORT+";username="+USER+";password="+PASSWD;
	public: static MySqlConnection^ conDataBase  = gcnew MySqlConnection(constring);
	public: static MySqlCommand^ cmdDataBase;
	public: static MySqlDataReader^ myReader;
	public:
		loginForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~loginForm()
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
	private: System::Windows::Forms::Label^  registrationLabel;


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
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->loginLabel = (gcnew System::Windows::Forms::Label());
			this->passLabel = (gcnew System::Windows::Forms::Label());
			this->loginTextBox = (gcnew System::Windows::Forms::TextBox());
			this->passTextBox = (gcnew System::Windows::Forms::TextBox());
			this->registrationLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// loginButton
			// 
			this->loginButton->Location = System::Drawing::Point(53, 67);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(75, 23);
			this->loginButton->TabIndex = 0;
			this->loginButton->Text = L"Вход";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &loginForm::loginButton_Click);
			// 
			// loginLabel
			// 
			this->loginLabel->AutoSize = true;
			this->loginLabel->Location = System::Drawing::Point(6, 15);
			this->loginLabel->Name = L"loginLabel";
			this->loginLabel->Size = System::Drawing::Size(41, 13);
			this->loginLabel->TabIndex = 1;
			this->loginLabel->Text = L"Логин:";
			// 
			// passLabel
			// 
			this->passLabel->AutoSize = true;
			this->passLabel->Location = System::Drawing::Point(6, 43);
			this->passLabel->Name = L"passLabel";
			this->passLabel->Size = System::Drawing::Size(48, 13);
			this->passLabel->TabIndex = 2;
			this->passLabel->Text = L"Пароль:";
			// 
			// loginTextBox
			// 
			this->loginTextBox->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->loginTextBox->Location = System::Drawing::Point(53, 12);
			this->loginTextBox->Name = L"loginTextBox";
			this->loginTextBox->Size = System::Drawing::Size(100, 21);
			this->loginTextBox->TabIndex = 3;
			this->loginTextBox->Text = L"56875896325";
			this->loginTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &loginForm::loginTextBox_KeyPress);
			// 
			// passTextBox
			// 
			this->passTextBox->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->passTextBox->Location = System::Drawing::Point(53, 40);
			this->passTextBox->Name = L"passTextBox";
			this->passTextBox->PasswordChar = '*';
			this->passTextBox->Size = System::Drawing::Size(100, 21);
			this->passTextBox->TabIndex = 4;
			this->passTextBox->Text = L"123";
			this->passTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &loginForm::passTextBox_KeyPress);
			// 
			// registrationLabel
			// 
			this->registrationLabel->AutoSize = true;
			this->registrationLabel->Cursor = System::Windows::Forms::Cursors::Hand;
			this->registrationLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->registrationLabel->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->registrationLabel->Location = System::Drawing::Point(40, 110);
			this->registrationLabel->Name = L"registrationLabel";
			this->registrationLabel->Size = System::Drawing::Size(113, 13);
			this->registrationLabel->TabIndex = 5;
			this->registrationLabel->Text = L"Зарегистрироваться";
			this->registrationLabel->Click += gcnew System::EventHandler(this, &loginForm::registrationLabel_Click);
			// 
			// loginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(180, 132);
			this->Controls->Add(this->registrationLabel);
			this->Controls->Add(this->passTextBox);
			this->Controls->Add(this->loginTextBox);
			this->Controls->Add(this->passLabel);
			this->Controls->Add(this->loginLabel);
			this->Controls->Add(this->loginButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"loginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"AirTicketOffice login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loginButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 loginButton->Enabled = false;
			 MySqlDataReader^ myReader = executeReq("select * from "+PREFIX+".users;",conDataBase,myReader);
			 if (!myReader) 
			 {
				 loginButton->Enabled = true;
				 return;
			 }
			 bool login = false;
			 while (myReader->Read())
			 {
					if (myReader->GetString(0)==loginTextBox->Text && myReader->GetString(1)==passTextBox->Text)
					{
						if (myReader->GetString(2) == "1") currRole = 1; // user
						if (myReader->GetString(3) == "1") currRole = 2; // teller
						if (myReader->GetString(4) == "1") currRole = 3; // cargoManager
						if (myReader->GetString(5) == "1") currRole = 4; // mainManager
						if (myReader->GetString(6) == "1") currRole = 5; // admin
						idPass = toCharArray(loginTextBox->Text);
						this->Hide();
						mainForm^ secondForm = gcnew mainForm();
						secondForm->ShowDialog();
						login = true;
						break;
					}
			 }
			   if (!login)
			   {
				 MessageBox::Show("Неправильный логин или пароль", "Login error", 
				 MessageBoxButtons::OK, MessageBoxIcon::Error);
				 loginButton->Enabled = true;
			   }

			   // todo: проверка  логина на отсутствие символов, кроме цифр
			   // проверка пароля на отсутствие " ; '
			   // todo: проверка  логина на отсутствие символов, кроме цифр
			   // проверка пароля на отсутствие " ; '
			   // todo: проверка  логина на отсутствие символов, кроме цифр
			   // проверка пароля на отсутствие " ; '
			   // todo: проверка  логина на отсутствие символов, кроме цифр
			   // проверка пароля на отсутствие " ; '
			 }

private: System::Void registrationLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 // todo registration
			 this->Hide();
			 registrationForm^ thirdForm;
			 if (!thirdForm) 
				 thirdForm = gcnew registrationForm();
			 thirdForm->ShowDialog();
			 this->Show();
		 }
private: System::Void loginTextBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			int i = (int)e->KeyChar;
            if (!(i == 8 || (i >= 48 && i <= 57)))
            {
                // запрет ввода любых символов, кроме цифр
                e->Handled = true;
            }
		 }
private: System::Void passTextBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			  int i = (int)e->KeyChar;
			  if (i == 34 || i == 39 || i == 59)
			  {
					// запрет ввода ; ' "
					e->Handled = true;
              }

			  // TODO ПЕРЕДЕЛАТЬ ЭТО НА РЕГУЛЯРНОЕ ВЫРАЖЕНИЕ
		 }
};
}

