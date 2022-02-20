
#include <iostream>

#include "Plane.h"
#include "MyTools.h"
#include "ScreenSingleton.h"
#include "SBomber.h"

void Plane::Draw() const
{
this->DrawBody();
this->DrawTail();
this->DrawWings();
}

void Plane::DrawBody() const {
    ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    ScreenSingleton::getInstance().GotoXY(x, y);
    std::cout << "=========>";
}

void Plane::DrawWings() const {
    ScreenSingleton::getInstance().GotoXY(x + 3, y - 1);
    std::cout << "\\\\\\\\";
    ScreenSingleton::getInstance().GotoXY(x + 3, y + 1);
    std::cout << "////";
}

void Plane::DrawTail() const {
    ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    std::cout << "===";
}

void Plane::Accept(Visitor* v) {
    v->logPlane(this);
}

void ColorPlane::DrawBody() const {
    ScreenSingleton::getInstance().SetColor(CC_LightGreen);
    ScreenSingleton::getInstance().GotoXY(x, y);
    std::cout << "=========>";
}

void ColorPlane::DrawWings() const {
    ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    ScreenSingleton::getInstance().GotoXY(x + 3, y - 1);
    std::cout << "\\\\\\\\";
    ScreenSingleton::getInstance().GotoXY(x + 3, y + 1);
    std::cout << "////";
}

void ColorPlane::DrawTail() const {
    ScreenSingleton::getInstance().SetColor(CC_LightRed);
    ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    std::cout << "===";
}

void BigPlane::DrawBody() const {
    ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    ScreenSingleton::getInstance().GotoXY(x, y);
    std::cout << "=============>";
}

void BigPlane::DrawWings() const {
    ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    ScreenSingleton::getInstance().GotoXY(x + 3, y - 1);
    std::cout << "\\\\\\\\\\\\";
    ScreenSingleton::getInstance().GotoXY(x + 3, y + 1);
    std::cout << "////////";
}

void BigPlane::DrawTail() const {
    ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    std::cout << "=======";
}