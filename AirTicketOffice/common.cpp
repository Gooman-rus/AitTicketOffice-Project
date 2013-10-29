#include "stdafx.h"
#include "common.h"

using namespace System;
using namespace System::Windows::Forms;

// выполняет запрос
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
		MessageBox::Show("Error "+code.ToString()+": "+ex->Message);
	}

	return myReader;
}