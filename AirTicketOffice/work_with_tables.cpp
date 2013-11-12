#include "stdafx.h"
#include "work_with_tables.h"
#include "common.h"

// обработка захода под главным менеджером
// (рейсы и самолеты)
bool asMainManager (System::Windows::Forms::DataGridView^ tableFlights, 
					System::Windows::Forms::DataGridView^ tablePlanes,
					System::Windows::Forms::DataGridView^ tablePlaneParam,
					System::Windows::Forms::TabControl^   tabCtrl)
{
	// todo: удаляем из tabControl1 ненужные для этой роли вкладки
	// todo: загружаем нужные данные в 3 DataGridView

	// после удаления одной вкладки индекс меняется
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);	
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[0]);
	tabCtrl->TabPages->Remove(tabCtrl->TabPages[1]);

	bool check;
	check = loadData("select * from airlines.flights", tableFlights);
	check = loadData("select * from airlines.planes", tablePlanes);
	check = loadData("select * from airlines.plane_parametrs", tablePlaneParam);

	tableFlights->Columns[0]->HeaderText = "№ рейса";
	tableFlights->Columns[1]->HeaderText = "№ самолета";
	tableFlights->Columns[2]->HeaderText = "Пункт отпр.";
	tableFlights->Columns[3]->HeaderText = "Пункт приб.";
	tableFlights->Columns[4]->HeaderText = "Отправление";
	tableFlights->Columns[5]->HeaderText = "Прибытие";
	tableFlights->Columns[6]->HeaderText = "Время полета";
	tableFlights->Columns[0]->Width = 59;
	tableFlights->Columns[1]->Width = 80;
	tableFlights->Columns[2]->Width = 85;
	tableFlights->Columns[3]->Width = 85;
	tableFlights->Columns[4]->Width = 90;
	tableFlights->Columns[5]->Width = 90;
	tableFlights->Columns[6]->Width = 93;

	tablePlanes->Columns[0]->HeaderText = "№ самолета";
	tablePlanes->Columns[1]->HeaderText = "Модель";
	tablePlanes->Columns[2]->HeaderText = "Компания";
	tablePlanes->Columns[0]->Width = 80;
	tablePlanes->Columns[1]->Width = 59;
	tablePlanes->Columns[2]->Width = 75;

	tablePlaneParam->Columns[0]->HeaderText = "Модель";
	tablePlaneParam->Columns[1]->HeaderText = "Кол-во мест";
	tablePlaneParam->Columns[0]->Width = 59;
	tablePlaneParam->Columns[1]->Width = 80;

	return check;
}