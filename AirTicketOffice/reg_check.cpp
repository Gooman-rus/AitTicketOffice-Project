#include "stdafx.h"
#include "reg_check.h"

bool isDigit(char c)
{
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool checkName(String^ text)
{
	int checks = 0; // ������� ���������� ��������
	int spaces = 0;	// ������� ��������
	//String^ buf = field->Text;
	String^ buf = text;
	int len = buf->Length;

	for (int i = 0; i < len; i++)
	{
		int c = (int)buf[i];
		// ������ �������  " ' ;
		if (c == 59 || c == 39 || c == 34) return false;
		if (buf[i] == ' ') spaces++;
		if (spaces > 2)    return false;
	}
	if (spaces < 2) return false;
	return true;

	/*// ���� ������ ����� � ������� �����, �� ok
	if ((buf[0] >= '�' && buf[0] <= '�') || (buf[0] >= 'A' && buf[0] <= 'Z'))
	{
		// ���� ������ ����� �� ������� �� ������ �������
		if (buf[1] != ' ') checks++;
	}

	for (int i = 2; i < len; i++)
	{
		// ���� ������, �� ��������� ������ � ������� �����
		if (buf[i] == ' ' && (i+1 <= len || i+2 <= len))
		{
			if (buf[i+1] != ' ' && 
			   ((buf[i+1] >= '�' && buf[i+1] <= '�') || (buf[i+1] >= 'A' && buf[i+1] <= 'Z')))
			{
			   if (buf[i+2] != ' ') checks++;
			   //if (checks == 3) return true;
			}
		}
	}*/

	// �����, ����� ���� ������� 3 �����
	/*for (int i = 0; i < len; i++)
	{
		if (buf[i] == ' ')	// ������ ?
		{
			if (i+1 < len)
				if (buf[i+1] != ' ') 
				{
					if (buf[i+2] != ' ') checks++;
				}
		}

	}

	
	if (checks == 3) return true;*/

	//return false;
}

bool checkPassport(String^ text)
{
	String^ buf = text;
	int len = buf->Length;
	if (len > 11 || len < 11) return false;

	for (int i = 0; i < len; i++)
	{
		if (!isDigit(buf[i])) return false;
	}
	return true;
}

bool checkPassword(String^ pass1, String^ pass2)
{
	if (pass1 != pass2) return false;
	if (pass1->Length < 3 || pass2->Length < 3) return false;
	
	String^ buf = pass1;
	int len = buf->Length;

	for (int i = 0; i < len; i++)
	{
		int c = (int)buf[i];
		// ������ ������� � ������ " ' ;
		if (c == 59 || c == 39 || c == 34) return false;
	}	

	return true;
}

