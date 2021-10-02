#include "Buttons_Data.h"

Buttons_Data::Buttons_Data(int buttonID)
{
	this->buttonID = buttonID;
}

int Buttons_Data::GiveButtonID()
{
	return this->buttonID;
}

int Buttons_Data::GiveShipID()
{
	return this->shipID;
}

void Buttons_Data::SetShipID(int shipID)
{
	this->shipID = shipID;
}