#include "stdafx.h"
#include "reg_check.h"

bool isDigit(char c)
{
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool checkName(String^ text)
{
	int checks = 0; // счетчик правильных проверок
	int spaces = 0;	// счетчик пробелов
	//String^ buf = field->Text;
	String^ buf = text;
	int len = buf->Length;

	for (int i = 0; i < len; i++)
	{
		int c = (int)buf[i];
		// нельзя вводить  " ' ;
		if (c == 59 || c == 39 || c == 34) return false;
		if (buf[i] == ' ') spaces++;
		if (spaces > 2)    return false;
	}
	if (spaces < 2) return false;
	return true;

	/*// если первое слово с большой буквы, то ok
	if ((buf[0] >= 'А' && buf[0] <= 'Я') || (buf[0] >= 'A' && buf[0] <= 'Z'))
	{
		// если первое слово не состоит из одного символа
		if (buf[1] != ' ') checks++;
	}

	for (int i = 2; i < len; i++)
	{
		// если пробел, то следующий символ с большой буквы
		if (buf[i] == ' ' && (i+1 <= len || i+2 <= len))
		{
			if (buf[i+1] != ' ' && 
			   ((buf[i+1] >= 'А' && buf[i+1] <= 'Я') || (buf[i+1] >= 'A' && buf[i+1] <= 'Z')))
			{
			   if (buf[i+2] != ' ') checks++;
			   //if (checks == 3) return true;
			}
		}
	}*/

	// нужно, чтобы было введено 3 слова
	/*for (int i = 0; i < len; i++)
	{
		if (buf[i] == ' ')	// пробел ?
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
		// нельзя вводить в пароль " ' ;
		if (c == 59 || c == 39 || c == 34) return false;
	}	

	return true;
}

