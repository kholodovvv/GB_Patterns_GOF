#include "Bomb.h"
#include <iostream>
#include "ScreenSingleton.h"

void Bomb::Draw() const {
  ScreenSingleton::getInstance().GotoXY(x, y);
  std::cout << "*";
}

void BombDecorator::Draw() const {
    pBomb->Draw();
    ScreenSingleton::getInstance().GotoXY(x, y);
    std::cout << "|";
}

void BombDecorator::Move(uint16_t time){
    x += xDirction * speed * time * 0.001;
    y += yDirection * speed * time * 0.001;
    pBomb->Move(time * 2);
}
