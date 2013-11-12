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

MySqlDataReader^ executeReq(String^ request);	// выполняет запрос
bool loadData(String^ request, System::Windows::Forms::DataGridView^ dataGrid);
void FillCombo(String^ query,String^ column, System::Windows::Forms::ComboBox^ box);

String^ getError();
#endif