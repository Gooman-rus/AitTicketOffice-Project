#include "stdafx.h"
#include "common.h"

using namespace System;
using namespace System::Windows::Forms;
//using namespace MySql::Data::MySqlClient;

int numTab = 1;

String^ getError()
{
	switch(numTab)
	{
		case 1:return "ѕользователь с таким паспортом уже зарегистрирован в системе.";break;
		case 2:return "ƒанна€ модель самолета уже есть в базе";break;
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
					MessageBox::Show(getError());
					return myReader;
				}
				if(code==1451)
				{
					MessageBox::Show("Ќевозможно удалить элемент,т.к. на него ссылаютс€ пол€ другой таблицы");
					return myReader;
				}
				if(code==1452)
				{
					MessageBox::Show("Ќевозможно удалить элемент,т.к. на него ссылаютс€ пол€ другой таблицы");
					return myReader;
				}
				else
					MessageBox::Show("Error "+code.ToString()+": "+ex->Message);
	}

	return myReader;
}

// загружает данные по запросу в dataGridView
bool loadData(String^ request, System::Windows::Forms::DataGridView^ dataGrid)
{
	String^ constring = L"datasource="+SERVER+";port="+PORT+";username="+USER+";password="+PASSWD;
	MySqlConnection^ conDataBase = gcnew MySqlConnection(constring);
	MySqlCommand^ cmdDataBase = gcnew MySqlCommand(request, conDataBase);
	MySqlDataReader^ myReader;
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

// заполн€ет combobox
void FillCombo(String^ query,String^ column, System::Windows::Forms::ComboBox^ box)
{
	MySqlDataReader^ myReader = executeReq(query);
	box->Items->Clear();
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