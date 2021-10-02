#pragma once

#include <afxwin.h>

class Buttons_Data
{
private:
	int shipID = NULL;
	int buttonID;
public:
	Buttons_Data(int buttonID);

	int GiveButtonID();
	int GiveShipID();

	void SetShipID(int shipID);
};

