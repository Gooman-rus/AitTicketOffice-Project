#include "stdafx.h"
#include "common.h"
int numTab=1;
using namespace System;
using namespace System::Windows::Forms;
String^ getError()
{
	switch(numTab)
	{
		case 1:return "Пользователь с таким паспортом уже зарегистрирован в системе.";break;
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
				else
					MessageBox::Show("Error "+code.ToString()+": "+ex->Message);
	}

	return myReader;
}
