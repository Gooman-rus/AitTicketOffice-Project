#ifndef WORK
#define WORK

#pragma once

using namespace MySql::Data::MySqlClient;
using namespace System;


bool asMainManager (System::Windows::Forms::DataGridView^ tableFlights, 
					System::Windows::Forms::DataGridView^ tablePlanes,
					System::Windows::Forms::DataGridView^ tablePlaneParam,
					System::Windows::Forms::TabControl^   tabCtrl, bool admin);

bool asUser(System::Windows::Forms::TabControl^ tabCtrl, bool admin);
bool asTeller(System::Windows::Forms::TabControl^ tabCtrl, bool admin);
bool asCargoManager(System::Windows::Forms::DataGridView^ tableCargo,
					System::Windows::Forms::TabControl^ tabCtrl, bool admin);
bool asAdmin(System::Windows::Forms::DataGridView^ ctrlUsersTable);

#endif