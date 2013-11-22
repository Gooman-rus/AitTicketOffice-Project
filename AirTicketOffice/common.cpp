#include "stdafx.h"
#include "common.h"

using namespace System;
using namespace System::Windows::Forms;
//using namespace MySql::Data::MySqlClient;

int numTab = 1;
int currRole;  // текущая роль

String^ getError()
{
	switch(numTab)
	{
		case 1:return "Пользователь с таким паспортом уже зарегистрирован в системе.";break;
		case 2:return "Данная модель самолета уже есть в базе.";break;
		default: return "0";
	}
}

MySqlDataReader^ executeReq(String^ request)
{
	String^ constring = L"datasource="+SERVER+";port="+PORT+";username="+USER+";password="+PASSWD;
	MySqlConnection^ conDataBase = gcnew MySqlConnection(constring);
	MySqlCommand^ cmdDataBase = gcnew MySqlCommand(request, conDataBase);
	MySqlDataReader^ myReader;
	try
	{
		conDataBase->Open();
		myReader = cmdDataBase->ExecuteReader();

	}
	catch(MySqlException^ ex) {
				int code = ex->Number;
				if(code==1062)
				{
					MessageBox::Show(getError(),"Ошибка",MessageBoxButtons::OK,MessageBoxIcon::Error);
					return myReader;
				}
				if(code==1451)
				{
					MessageBox::Show("Невозможно удалить элемент, т.к. на него ссылаются поля другой таблицы.",
									"Ошибка",MessageBoxButtons::OK,MessageBoxIcon::Error);
					return myReader;
				}
				if(code==1452)
				{
					MessageBox::Show("Невозможно удалить элемент, т.к. на него ссылаются поля другой таблицы.",
									"Ошибка",MessageBoxButtons::OK,MessageBoxIcon::Error);
					return myReader;
				}
				if (code == 1042)
				{
					MessageBox::Show("Невозможно подсоединиться к серверу базы данных.",
									"Ошибка",MessageBoxButtons::OK,MessageBoxIcon::Error);
					return myReader;
				}
				else
					MessageBox::Show("Error "+code.ToString()+": "+ex->Message,
									"Ошибка",MessageBoxButtons::OK,MessageBoxIcon::Error);
	}

	return myReader;
}

// загружает данные по запросу в dataGridView
bool loadData(String^ request, System::Windows::Forms::DataGridView^ dataGrid)
{
	String^ constring = L"datasource="+SERVER+";port="+PORT+";username="+USER+";password="+PASSWD;
	MySqlConnection^ conDataBase = gcnew MySqlConnection(constring);
	MySqlCommand^ cmdDataBase = gcnew MySqlCommand(request, conDataBase);
	try
	{
		MySqlDataAdapter^ sda = gcnew MySqlDataAdapter();
		sda->SelectCommand = cmdDataBase;
		DataTable^ dbdataset = gcnew DataTable();
		sda->Fill(dbdataset);
		BindingSource^ bSource = gcnew BindingSource();

		bSource->DataSource = dbdataset;
		dataGrid->DataSource = bSource;
		sda->Update(dbdataset);
	}
	catch(MySqlException^ ex) {
		int code = ex->Number;
		if (code == 1062)
		{
			MessageBox::Show(getError());
			return false;
		}
		else
		{
			MessageBox::Show("Error "+code.ToString()+": "+ex->Message);
			return false;
		}
	}

	return true;
}

// заполняет combobox
void FillCombo(String^ query,String^ column, System::Windows::Forms::ComboBox^ box)
{
	MySqlDataReader^ myReader = executeReq(query);
	box->Items->Clear();
	if(!myReader)
		return;
	while(myReader->Read())
	{
		box->Items->Add(myReader->GetString(column));
	}
}
void CopyCombo(System::Windows::Forms::ComboBox^ box1,System::Windows::Forms::ComboBox^ box2)
{
	box1->Items->Clear();
	for(int i=0;i<box2->Items->Count;i++)
		box1->Items->Add(box2->Items[i]);
}