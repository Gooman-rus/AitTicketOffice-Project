//#pragma once
#ifndef COMMON
#define COMMON

#define SERVER	"localhost"
#define PORT	"3306"
#define USER	"root"
#define PASSWD	"qwerty721"

using namespace MySql::Data::MySqlClient;
using namespace System;

MySqlDataReader^ executeReq(String^ request);	// выполняет запрос

#endif