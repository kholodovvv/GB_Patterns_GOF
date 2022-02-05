#include "House.h"
#include <iostream>
#include "MyTools.h"
#include "ScreenSingleton.h"

bool House::isInside(double x1, double x2) const
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

/*void House::Draw() const
{
	ScreenSingleton::getInstance().SetColor(CC_Yellow);
	ScreenSingleton::getInstance().GotoXY(x, y - 5);
	std::cout << "  ########  ";
	ScreenSingleton::getInstance().GotoXY(x, y - 4);
	std::cout << "##        ##";
	ScreenSingleton::getInstance().GotoXY(x, y - 3);
	std::cout << "############";
	ScreenSingleton::getInstance().GotoXY(x, y - 2);
	std::cout << "#          #";
	ScreenSingleton::getInstance().GotoXY(x, y - 1);
	std::cout << "#          #";
	ScreenSingleton::getInstance().GotoXY(x, y);
	std::cout << "############";
}*/

void House::Draw() const
{
    ScreenSingleton::getInstance().SetColor(CC_Yellow);
    ScreenSingleton::getInstance().GotoXY(x, y - 6);
    for(int j = 0; j < 14; ++j) std::cout << look[0][j];

    ScreenSingleton::getInstance().GotoXY(x, y - 5);
    for(int j = 0; j < 14; ++j) std::cout << look[1][j];

    ScreenSingleton::getInstance().GotoXY(x, y - 4);
    for(int j = 0; j < 14; ++j) std::cout << look[2][j];

    ScreenSingleton::getInstance().GotoXY(x, y - 3);
    for(int j = 0; j < 14; ++j) std::cout << look[3][j];

    ScreenSingleton::getInstance().GotoXY(x, y - 2);
    for(int j = 0; j < 14; ++j) std::cout << look[4][j];

    ScreenSingleton::getInstance().GotoXY(x, y - 1);
    for(int j = 0; j < 14; ++j) std::cout << look[5][j];

    ScreenSingleton::getInstance().GotoXY(x, y);
    for(int j = 0; j < 14; ++j) std::cout << look[6][j];
}

void HouseBuilderA::BuildWall() {
    for(int i = 3; i < 7; ++i){
        for (int j = 0; j < 14; ++j) {
            house->look[i][j] = '#';
        }
    }
}

void HouseBuilderA::BuildRoof() {

    for(int i = 0; i < 3; ++i){

        for (int j = 0; j < 14; ++j) {
            if((i == 0 && j == 3) || (i == 0 && j == 9)) {
                house->look[i][j] = '#';
            }else if((i == 1 && j == 2) || (i == 1 && j == 4) || (i == 1 && j == 8) || (i == 1 && j == 10)){
                house->look[i][j] = '#';
            }else if((i == 2 && j == 1) || (i == 2 && j == 5) || (i == 2 && j == 7) || (i == 2 && j == 11)){
                house->look[i][j] = '#';
            }else{
                house->look[i][j] = ' ';
            }
        }
    }
}

void HouseBuilderB::BuildWall() {
    for(int i = 3; i < 7; ++i){
        if((i == 3) || (i == 6)) {
            for (int j = 0; j < 14; ++j) {
                house->look[i][j] = '#';
            }
        }
        for (int j = 0; j < 14; ++j) {
            if((i == 4 && j == 2) || (i == 4 && j == 3) || (i == 4 && j == 9) || (i == 4 && j == 10)){
                house->look[i][j] = ' ';
            }else if((i == 5 && j == 2) || (i == 5 && j == 3) || (i == 5 && j == 9) || (i == 5 && j == 10)){
                house->look[i][j] = ' ';
            }else{
                house->look[i][j] = '#';
            }
        }
    }
}

void HouseBuilderB::BuildRoof() {

    for(int i = 0; i < 3; ++i){

        for (int j = 0; j < 14; ++j) {
            if((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) || (i == 0 && j == 7)
               || (i == 0 && j == 8) || (i == 0 && j == 12) || (i == 0 && j == 13)){
                house->look[i][j] = ' ';
            }else if((i == 1 && j == 0) || (i == 1 && j == 3) || (i == 1 && j == 6) || (i == 1 && j == 7) || (i == 1 && j == 10) || (i == 1 && j == 13)){
                house->look[i][j] = ' ';
            }else if((i == 2 && j == 2) || (i == 2 && j == 3) || (i == 2 && j == 4) || (i == 2 && j == 9) || (i == 2 && j == 10) || (i == 2 && j == 11)){
                house->look[i][j] = ' ';
            }else{
                house->look[i][j] = '#';
            }
        }
    }
}