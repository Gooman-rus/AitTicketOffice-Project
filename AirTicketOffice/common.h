//#pragma once
#ifndef COMMON
#define COMMON

#define SERVER	"localhost"
#define PORT	"3306"
#define USER	"root"
#define PASSWD	"qwerty721"
#define PREFIX	"airlines"  // имя БД

#pragma once
using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;

extern int numTab;
extern int currRole;  // текущая роль
extern char* idPass;
extern bool isOpen;
extern bool isCellClick;

// выполняет запрос
MySqlDataReader^ executeReq(String^ request,MySqlConnection^ conDataBase,MySqlDataReader^ myReader);	
// загружает данные в dataGridView
bool loadData(String^ request, System::Windows::Forms::DataGridView^ dataGrid);
// заполняет comboBox
void FillCombo(String^ query,String^ column, System::Windows::Forms::ComboBox^ box,MySqlConnection^ conDataBase,MySqlDataReader^ myReader);
void CopyCombo(System::Windows::Forms::ComboBox^ box1,System::Windows::Forms::ComboBox^ box2);

char * toCharArray(System::String^ string);
String^ getError();

#endif