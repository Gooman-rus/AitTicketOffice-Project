#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// ����� �������� �� ���� ������ ��������������� ��������� �������
// ���������. �������������� �������� ���� ���������, ����� ��������
// ����� �������� �� ���� ������.
//
[assembly:AssemblyTitleAttribute("AirTicketOffice")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("UralSOFT")];
[assembly:AssemblyProductAttribute("AirTicketOffice")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) UralSOFT 2013")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// �������� � ������ ������ ������� �� ��������� ������� ��������:
//
//      �������� ����� ������
//      �������������� ����� ������
//      ����� ����������
//      ��������
//
// ����� ������ ��� �������� ��� ������� ����� ���������� � ����� �������� �� ���������,
// ��������� "*", ��� �������� ����:

[assembly:AssemblyVersionAttribute("1.0.*")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];
