#include "stdafx.h"
#include "work_with_tables.h"
#include "common.h"

// ��������� ������ ��� ������� ����������
// (����� � ��������)
bool asMainManager (System::Windows::Forms::DataGridView^ tableFlights, 
					System::Windows::Forms::DataGridView^ tablePlanes,
					System::Windows::Forms::DataGridView^ tablePlaneParam,
					System::Windows::Forms::DataGridView^ tableTariffs,
					System::Windows::Forms::TabControl^   tabCtrl, bool admin)
{
	
	// ����� �������� ����� ������� ������ ��������
	if (!admin) {
		tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);	
		tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);
		tabCtrl->TabPages->Remove(tabCtrl->TabPages[2]);
		//tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);
	}

	bool check;
	check = loadData("select * from "+PREFIX+".flights", tableFlights);
	check = loadData("select * from "+PREFIX+".planes", tablePlanes);
	check = loadData("select * from "+PREFIX+".plane_parametrs", tablePlaneParam);
	check = loadData("select * from "+PREFIX+".tariffs",tableTariffs);

	tableFlights->Columns[0]->HeaderText = "� �����";
	tableFlights->Columns[1]->HeaderText = "� ��������";
	tableFlights->Columns[2]->HeaderText = "����� ����.";
	tableFlights->Columns[3]->HeaderText = "����� ����.";
	tableFlights->Columns[4]->HeaderText = "�����������";
	tableFlights->Columns[5]->HeaderText = "��������";
	tableFlights->Columns[6]->HeaderText = "����� ������";
	tableFlights->Columns[0]->Width = 59;
	tableFlights->Columns[1]->Width = 80;
	tableFlights->Columns[2]->Width = 85;
	tableFlights->Columns[3]->Width = 85;
	tableFlights->Columns[4]->Width = 90;
	tableFlights->Columns[5]->Width = 90;
	tableFlights->Columns[6]->Width = 93;

	tablePlanes->Columns[0]->HeaderText = "� �����.";
	tablePlanes->Columns[1]->HeaderText = "������";
	tablePlanes->Columns[2]->HeaderText = "��������";
	tablePlanes->Columns[0]->Width = 75;
	tablePlanes->Columns[1]->Width = 90;
	tablePlanes->Columns[2]->Width = 80;

	tablePlaneParam->Columns[0]->HeaderText = "������";
	tablePlaneParam->Columns[1]->HeaderText = "���-�� ����";
	tablePlaneParam->Columns[0]->Width = 90;
	tablePlaneParam->Columns[1]->Width = 80;

	tableTariffs->Columns[0]->HeaderText = "� �����";
	tableTariffs->Columns[1]->HeaderText = "�����";
	tableTariffs->Columns[2]->HeaderText = "����";
	tableTariffs->Columns[0]->Width = 59;
	tableTariffs->Columns[1]->Width = 59;
	tableTariffs->Columns[2]->Width = 75;
	return check;
}

bool asUser(System::Windows::Forms::TabControl^ tabCtrl, bool admin) {
	bool check;

	if (!admin)
	for (int i=0;i<4;i++) tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);

	return check;
}

bool asTeller(System::Windows::Forms::TabControl^ tabCtrl, bool admin) {
	bool check;

	if (!admin) {
	//tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);
	for (int i=0;i<3;i++) tabCtrl->TabPages->Remove(tabCtrl->TabPages[2]);
	}


	return check;
}

bool asCargoManager(System::Windows::Forms::DataGridView^ tableCargo,
					System::Windows::Forms::TabControl^ tabCtrl, bool admin) {
	bool check;

	if (!admin) {
		tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);	
		tabCtrl->TabPages->Remove(tabCtrl->TabPages[2]);
		tabCtrl->TabPages->Remove(tabCtrl->TabPages[2]);
		//tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);
	}

	check = loadData("select * from "+PREFIX+".cargo", tableCargo);

	tableCargo->Columns[0]->HeaderText = "� �����";
	tableCargo->Columns[1]->HeaderText = "� ��������";
	tableCargo->Columns[2]->HeaderText = "� �����";
	tableCargo->Columns[3]->HeaderText = "������������";
	tableCargo->Columns[4]->HeaderText = "�������";
	tableCargo->Columns[5]->HeaderText = "���";
	tableCargo->Columns[0]->Width = 59;
	tableCargo->Columns[1]->Width = 80;
	tableCargo->Columns[2]->Width = 59;
	tableCargo->Columns[3]->Width = 90;
	tableCargo->Columns[4]->Width = 75;
	tableCargo->Columns[5]->Width = 75;
	return check;
}

bool asAdmin(System::Windows::Forms::DataGridView^ ctrlUsersTable)
{
	bool check;

	String^ querry = "select passengers.id_pass, passengers.Name, users.password ";
	querry += "from "+PREFIX+".passengers join "+PREFIX+".users where passengers.id_pass = users.passport"; 
	check = loadData(querry, ctrlUsersTable);

	ctrlUsersTable->Columns[0]->HeaderText = "� ��������";
	ctrlUsersTable->Columns[1]->HeaderText = "���";
	ctrlUsersTable->Columns[2]->HeaderText = "������";
	
	ctrlUsersTable->Columns[0]->Width = 80;
	ctrlUsersTable->Columns[1]->Width = 200;
	ctrlUsersTable->Columns[2]->Width = 80;



	return check;
}