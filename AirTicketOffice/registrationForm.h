#pragma once
#include "reg_check.h"
#include "common.h"

namespace AirTicketOffice {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	using namespace System::Text::RegularExpressions;

	/// <summary>
	/// Сводка для registrationForm
	/// </summary>
	public ref class registrationForm : public System::Windows::Forms::Form
	{
	public:
		registrationForm(void)
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
		~registrationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  nameInput;
	private: System::Windows::Forms::Label^  label1;


	private: System::Windows::Forms::TextBox^  inputPassword;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  inputPasswordAgain;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  inputPassport;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  registerButton;
	private: System::Windows::Forms::CheckBox^  checkRules;

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
			this->nameInput = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->inputPassword = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->inputPasswordAgain = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->inputPassport = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->registerButton = (gcnew System::Windows::Forms::Button());
			this->checkRules = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// nameInput
			// 
			this->nameInput->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->nameInput->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->nameInput->Location = System::Drawing::Point(136, 12);
			this->nameInput->MaxLength = 50;
			this->nameInput->Name = L"nameInput";
			this->nameInput->Size = System::Drawing::Size(210, 21);
			this->nameInput->TabIndex = 0;
			this->nameInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &registrationForm::nameInput_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(93, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"ФИО:";
			// 
			// inputPassword
			// 
			this->inputPassword->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->inputPassword->Location = System::Drawing::Point(136, 64);
			this->inputPassword->MaxLength = 25;
			this->inputPassword->Name = L"inputPassword";
			this->inputPassword->PasswordChar = '*';
			this->inputPassword->Size = System::Drawing::Size(210, 21);
			this->inputPassword->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(79, 67);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Пароль:";
			// 
			// inputPasswordAgain
			// 
			this->inputPasswordAgain->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->inputPasswordAgain->Location = System::Drawing::Point(136, 90);
			this->inputPasswordAgain->MaxLength = 25;
			this->inputPasswordAgain->Name = L"inputPasswordAgain";
			this->inputPasswordAgain->PasswordChar = '*';
			this->inputPasswordAgain->Size = System::Drawing::Size(210, 21);
			this->inputPasswordAgain->TabIndex = 3;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(14, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(120, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Повторите пароль:";
			// 
			// inputPassport
			// 
			this->inputPassport->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->inputPassport->Location = System::Drawing::Point(136, 38);
			this->inputPassport->MaxLength = 11;
			this->inputPassport->Name = L"inputPassport";
			this->inputPassport->Size = System::Drawing::Size(210, 21);
			this->inputPassport->TabIndex = 1;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(17, 41);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(117, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"№ загр. паспорта:";
			// 
			// registerButton
			// 
			this->registerButton->Location = System::Drawing::Point(136, 152);
			this->registerButton->Name = L"registerButton";
			this->registerButton->Size = System::Drawing::Size(139, 23);
			this->registerButton->TabIndex = 5;
			this->registerButton->Text = L"Зарегистрироваться";
			this->registerButton->UseVisualStyleBackColor = true;
			this->registerButton->Click += gcnew System::EventHandler(this, &registrationForm::registerButton_Click);
			// 
			// checkRules
			// 
			this->checkRules->AutoSize = true;
			this->checkRules->Location = System::Drawing::Point(135, 129);
			this->checkRules->Name = L"checkRules";
			this->checkRules->Size = System::Drawing::Size(158, 17);
			this->checkRules->TabIndex = 4;
			this->checkRules->Text = L"С правилами соглашаюсь";
			this->checkRules->UseVisualStyleBackColor = true;
			// 
			// registrationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(358, 185);
			this->Controls->Add(this->checkRules);
			this->Controls->Add(this->registerButton);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->inputPassport);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->inputPasswordAgain);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->inputPassword);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->nameInput);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"registrationForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Регистрация нового пользователя";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &registrationForm::registrationForm_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void registrationForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				//this->Hide();
				//loginForm.ShowDialog();
				 
			 }
private: System::Void registerButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // todo: соглашение с правилами
			 // проверка ФИО: 3 слова (с мин. двумя символами) с большой буквы лат. или русск. алфавита
			 // пароли мин. 3 символа, совпадают друг с другом
			 // todo: проверки существующего паспорта в БД.
			 // если паспорт есть, но пользователь не зарегистрирован в системе,
			 // то зарегистрировать его, иначе - нет.
			 // ФИО в базу добавлять в ВЕРХНЕМ РЕГИСТРЕ
			 registerButton->Enabled = false;
			 if (nameInput->Text->Length == 0)
			 {
				 MessageBox::Show("Поле 'ФИО' не может быть пустым.", "Ошибка",
								 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 registerButton->Enabled = true;
				 return;
			 }

			 if (!checkName(nameInput->Text))
			 {
				MessageBox::Show("ФИО заполнено неверно.", "Ошибка",
								 MessageBoxButtons::OK,MessageBoxIcon::Error);
				registerButton->Enabled = true;
				return;
			 }

			 if (inputPassport->Text->Length == 0)
			 {
				MessageBox::Show("Поле для ввода номера паспорта не может быть пустым.", "Ошибка",
								 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				registerButton->Enabled = true;
				return;
			 }

			 if (!checkPassport(inputPassport->Text))
			 {
				MessageBox::Show("Поле для ввода номера паспорта заполнено неверно.", "Ошибка",
								 MessageBoxButtons::OK,MessageBoxIcon::Error);
				registerButton->Enabled = true;
				return;
			 }

			 if (inputPassword->Text->Length == 0 || inputPasswordAgain->Text->Length == 0)
			 {
				 MessageBox::Show("Одно из полей ввода паролей не заполнено.", "Ошибка",
								 MessageBoxButtons::OK,MessageBoxIcon::Error);	
				 registerButton->Enabled = true;
				 return;
			 }

			 if (!checkPassword(inputPassword->Text, inputPasswordAgain->Text))
			 {
				MessageBox::Show("Пароли должны совпадать, состоять из минимум 3-х символов.", 
								 "Ошибка", MessageBoxButtons::OK,MessageBoxIcon::Error);
				registerButton->Enabled = true;
				return;
			 }
			 
			 if (!checkRules->Checked)
			 {
				MessageBox::Show("Для регистрации в системе нужно согласиться с правилами.", "Ошибка",
								 MessageBoxButtons::OK,MessageBoxIcon::Exclamation);
				registerButton->Enabled = true;
				return;
			 }

			 //String^ constring = L"datasource="+SERVER+";port="+PORT+";username="+USER+";password="+PASSWD;
			 //MySqlConnection^ conDataBase = gcnew MySqlConnection(constring);
			 MySqlDataReader^ myReader;
			 numTab =  1;
			myReader = executeReq("INSERT INTO "+PREFIX+".users (passport,password) VALUES('"+
				        inputPassport->Text+"',"+inputPassword->Text+")");
			 if (!myReader) 
			 {
				 registerButton->Enabled = true;
				 return;
			 }
			 myReader = executeReq("INSERT INTO "+PREFIX+".passengers VALUES('"+
				        inputPassport->Text+"','"+nameInput->Text+"')");
			 if (!myReader) 
			 {
				 registerButton->Enabled = true;
				 return;
			 }
			 // todo: проверка на наличие человека с таким же паспортом
			 // если такой пассп. есть в passengers, то проверить, есть ли у него пароль в users
			 // если есть, то ошибка (пользователь существует)
			 // иначе пользователь пользовался услугами полета, но не регистрировался лично
			 // тогда добавить в users информацию о нем

			 if (myReader)
			 {
				 MessageBox::Show("Вы зарегистрированы.", "Успешно!",
							      MessageBoxButtons::OK,MessageBoxIcon::Information);
				 this->Close();
			 }


		 }
private: System::Void nameInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			Regex^ rx = gcnew Regex("[a-zA-Z]|[а-яА-Я]");//регулярное выражение для ФИО,
														 //которое содержит только буквы
			String^ c1 = e->KeyChar.ToString();
            int i = (int)e->KeyChar;
            if (!(i == 8 || i==32 || rx->IsMatch(c1)))
            {
                // запрет ввода любых символов, кроме англ. и русских
                e->Handled = true;
            }
		 }
private: System::Void inputPassport_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

		 }
};
}
