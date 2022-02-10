#pragma once

#include "DynamicObject.h"
#include <vector>

class Visitor;
class DestroyableGroundObject;

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // ��������� ����� � �����

	void Draw() const override;
    void Accept(Visitor* v);
    void AddObserver(DestroyableGroundObject* DGObject);
    DestroyableGroundObject* CheckDestoyableObjects();

private:
    std::vector<DestroyableGroundObject*> Subscribers;
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

