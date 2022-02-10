#include "Bomb.h"
#include <iostream>
#include "ScreenSingleton.h"
#include "SBomber.h"

void Bomb::Draw() const {
  ScreenSingleton::getInstance().GotoXY(x, y);
  std::cout << "*";
}

void Bomb::Accept(Visitor* v) {
    v->logBomb(this);
}

void Bomb::AddObserver(DestroyableGroundObject* DGObject) {
    Subscribers.push_back(DGObject);
}

DestroyableGroundObject* Bomb::CheckDestoyableObjects() {
    //std::vector<DestroyableGroundObject*> vecDestoyableObjects = SBomber::FindDestoyableGroundObjects();

    const double size = this->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < Subscribers.size(); i++) {
        const double x1 = this->GetX() - size_2;
        const double x2 = x1 + size;
        if (Subscribers[i]->isInside(x1, x2)) {
            //SBomber::score += Subscribers[i]->GetScore();
            //SBomber::DeleteStaticObj(Subscribers[i]);
            return Subscribers[i];
        }else{
            return nullptr;
        }
    }
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

