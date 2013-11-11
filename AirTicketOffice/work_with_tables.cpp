#include "stdafx.h"
#include "work_with_tables.h"

/*void loadFlights(System::Windows::Forms::DataGridView^ table)
{
	MySqlDataReader^ MyReader = executeReq("select * from flights.airlines");
	try
	{
		MySqlDataAdapter^ sda = gcnew MySqlDataAdapter();
		sda

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
}*/