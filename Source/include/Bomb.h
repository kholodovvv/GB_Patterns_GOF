#pragma once

#include "DynamicObject.h"


class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // ��������� ����� � �����

	void Draw() const override;

private:

};

class BombDecorator : public DynamicObject{
public:

    BombDecorator(Bomb* bomb) : pBomb(bomb){}

    void Draw() const override;

    void Move(uint16_t time) override;

    ~BombDecorator(){
        delete pBomb;
    }

protected:
    Bomb* pBomb;
};

