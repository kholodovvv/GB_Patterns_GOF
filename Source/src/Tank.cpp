
#include <iostream>

#include "Tank.h"
#include "MyTools.h"
#include "ScreenSingleton.h"

using namespace std;
//using namespace MyTools;

bool Tank::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void Tank::Draw() const
{
	ScreenSingleton::getInstance().SetColor(CC_Cyan);
	ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "    #####";
	ScreenSingleton::getInstance().GotoXY(x-2, y - 2);
	cout << "#######   #";
	ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "    #####";
	ScreenSingleton::getInstance().GotoXY(x,y);
	cout << " ###########";
}

void TankAdaptee::Paint() const{
    ScreenSingleton::getInstance().SetColor(CC_Cyan);
    ScreenSingleton::getInstance().GotoXY(x, y - 3);
    cout << "    #####";
    ScreenSingleton::getInstance().GotoXY(x-2, y - 2);
    cout << "#######   #";
    ScreenSingleton::getInstance().GotoXY(x, y - 1);
    cout << "    #####";
    ScreenSingleton::getInstance().GotoXY(x,y);
    cout << " ###########";
}

bool TankAdaptee::isInRange(double x1, double x2) const
{
    const double XBeg = x + 2;
    const double XEnd = x + width - 1;

    if (x1 < XBeg && x2 > XEnd)
    {
        return true;
    }

    if (x1 > XBeg && x1 < XEnd)
    {
        return true;
    }

    if (x2 > XBeg && x2 < XEnd)
    {
        return true;
    }

    return false;
}


bool TankAdapter::isInside(double x1, double x2) const
{
    return tank.isInRange(x1, x2);
}