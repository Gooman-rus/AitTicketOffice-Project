//#pragma once
#ifndef COMMON
#define COMMON

#define SERVER	"localhost"
#define PORT	"3306"
#define USER	"root"
#define PASSWD	"qwerty721"
#pragma once

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;

extern int numTab;

// выполняет запрос
MySqlDataReader^ executeReq(String^ request);	
// загружает данные в dataGridView
bool loadData(String^ request, System::Windows::Forms::DataGridView^ dataGrid);
// заполняет comboBox
void FillCombo(String^ query,String^ column, System::Windows::Forms::ComboBox^ box);

String^ getError();

#endif