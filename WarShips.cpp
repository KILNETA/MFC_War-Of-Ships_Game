#include "WarShips.h"

WarShips::WarShips(int shipID, int size)
{
	this->shipID = shipID;
	for(int n=0;n<size;n++){
		this->Coordinate.push_back(NULL);
	}
}

void WarShips::setCoordinate(int location, int coordinateID)
{
	this->Coordinate[location]=coordinateID;
}

void WarShips::setPlace(bool place)
{
	this->place = place;
}

int WarShips::GetShipID()
{
	return this->shipID;
}

int WarShips::GetCoordinate_Size()
{
	return this->Coordinate.size();
}
int WarShips::GetCoordinate(int uId)
{
	return this->Coordinate[uId];
}

bool WarShips::GetPlace()
{
	return this->place;
}

CString WarShips::GetShipName()
{
	switch (this->shipID % 10){
	case 0:
		return _T("CV");
		break;
	case 1:
		return _T("BB");
		break;
	case 2:
		return _T("CL ");
		break;
	case 3:
		return _T("DD");
		break;
	case 4:
		return _T("PB");
		break;
	}
	return _T("");
}