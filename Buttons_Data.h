#pragma once

#include <afxwin.h>

class Buttons_Data
{
private:
	int shipID = NULL;
	int buttonID;

	CString GetButtonsNameNumber();
public:
	Buttons_Data(int buttonID);

	int GiveButtonID();
	int GiveShipID();
	CString GetButtonsName();

	void SetShipID(int shipID);
};

