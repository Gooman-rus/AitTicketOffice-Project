// AirTicketOffice.cpp: главный файл проекта.

#include "stdafx.h"
#include "loginForm.h"

using namespace AirTicketOffice;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	Application::Run(gcnew loginForm());
	return 0;
}
