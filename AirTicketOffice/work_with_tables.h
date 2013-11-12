#ifndef WORK
#define WORK

#pragma once

using namespace MySql::Data::MySqlClient;
using namespace System;


bool asMainManager (System::Windows::Forms::DataGridView^ tableFlights, 
					System::Windows::Forms::DataGridView^ tablePlanes,
					System::Windows::Forms::DataGridView^ tablePlaneParam,
					System::Windows::Forms::TabControl^   tabCtrl);


#endif