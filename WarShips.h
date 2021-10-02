#pragma once

#include <afxwin.h>
#include <vector>
using namespace std;

class WarShips
{
private:
	int shipID;
	vector<int> Coordinate;
	bool place = false;
public:
	WarShips(int shipID,int size);
	
	void setCoordinate(int location ,int coordinateID);
	void setPlace(bool place);

	int GetShipID();
	int GetCoordinate_Size();
	int GetCoordinate(int uId);
	bool GetPlace();
	CString GetShipName();

};

