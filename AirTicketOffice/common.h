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

extern int numTab;

MySqlDataReader^ executeReq(String^ request);	// выполняет запрос
String^ getError();
#endif