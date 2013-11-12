#include "stdafx.h"
#include "work_with_tables.h"
#include "common.h"

// ��������� ������ ��� ������� ����������
// (����� � ��������)
bool asMainManager (System::Windows::Forms::DataGridView^ tableFlights, 
					System::Windows::Forms::DataGridView^ tablePlanes,
					System::Windows::Forms::DataGridView^ tablePlaneParam,
					System::Windows::Forms::TabControl^   tabCtrl)
{
	// todo: ������� �� tabControl1 �������� ��� ���� ���� �������
	// todo: ��������� ������ ������ � 3 DataGridView

	// ����� �������� ����� ������� ������ ��������
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);	
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);

	bool check;
	check = loadData("select * from airlines.flights", tableFlights);
	check = loadData("select * from airlines.planes", tablePlanes);
	check = loadData("select * from airlines.plane_parametrs", tablePlaneParam);

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

	tablePlanes->Columns[0]->HeaderText = "� ��������";
	tablePlanes->Columns[1]->HeaderText = "������";
	tablePlanes->Columns[2]->HeaderText = "��������";
	tablePlanes->Columns[0]->Width = 80;
	tablePlanes->Columns[1]->Width = 59;
	tablePlanes->Columns[2]->Width = 75;

	tablePlaneParam->Columns[0]->HeaderText = "������";
	tablePlaneParam->Columns[1]->HeaderText = "���-�� ����";
	tablePlaneParam->Columns[0]->Width = 59;
	tablePlaneParam->Columns[1]->Width = 80;

	return check;
}