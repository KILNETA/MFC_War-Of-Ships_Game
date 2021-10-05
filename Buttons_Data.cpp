#include "Buttons_Data.h"

CString Buttons_Data::GetButtonsNameNumber()
{
	switch (this->buttonID % 10)
	{
	case 0:	return L"¢°"; break;
	case 1:	return L"¢±"; break;
	case 2:	return L"¢²"; break;
	case 3:	return L"¢³" ; break;
	case 4:	return L"¢´" ; break;
	case 5:	return L"¢µ" ; break;
	case 6:	return L"¢¶" ; break;
	case 7:	return L"¢·" ; break;
	case 8:	return L"¢¸" ; break;
	case 9:	return L"¢°¢¯" ; break;
	}
}

Buttons_Data::Buttons_Data(int buttonID)
{
	this->buttonID = buttonID;
}

int Buttons_Data::GiveShipID()
{
	return this->shipID;
}

CString Buttons_Data::GetButtonsName()
{
	switch((this->buttonID%100)/10)
	{
	case 0:	return L"¢Ï" + Buttons_Data::GetButtonsNameNumber(); break;
	case 1:	return L"¢Ð" + Buttons_Data::GetButtonsNameNumber(); break;
	case 2:	return L"¢Ñ" + Buttons_Data::GetButtonsNameNumber(); break;
	case 3:	return L"¢Ò" + Buttons_Data::GetButtonsNameNumber(); break;
	case 4:	return L"¢Ó" + Buttons_Data::GetButtonsNameNumber(); break;
	case 5:	return L"¢Ô" + Buttons_Data::GetButtonsNameNumber(); break;
	case 6:	return L"¢Õ" + Buttons_Data::GetButtonsNameNumber(); break;
	case 7:	return L"¢Ö" + Buttons_Data::GetButtonsNameNumber(); break;
	case 8:	return L"¢×" + Buttons_Data::GetButtonsNameNumber(); break;
	case 9:	return L"¢Ø" + Buttons_Data::GetButtonsNameNumber(); break;
	}
}


void Buttons_Data::SetShipID(int shipID)
{
	this->shipID = shipID;
}