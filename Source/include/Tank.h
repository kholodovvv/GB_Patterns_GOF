#pragma once

#include <stdint.h>
#include <vector>

#include "DestroyableGroundObject.h"
#include "SBomberImpl.h"
class Chat;


class Tank : public DestroyableGroundObject
{
public:

    Tank(Chat* chat): pChat(chat){}

	bool  isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score;}
    virtual DestroyableGroundObject* Clone() const override;
    void Draw() const override;

private:
    Chat* pChat;
    std::vector<std::string> messages = {"HA, HA!", "THEY WON'T CATCH UP WITH US!", "KISS MY PUSSY!", "RACCOON IN YOUR MOUTH!"};
	const uint16_t score = 30;
};

class TankAdaptee{ //Адаптируемый класс содержит некоторое полезное поведение, но его интерфейс не совместим с клиентским кодом
public:
    TankAdaptee() : x(0.0), y(0.0), width(0) {}
    TankAdaptee(double xx, double yy, uint16_t wwidth) : x(xx), y(yy), width(wwidth) { }

    void Paint() const;

    bool isInRange(double x1, double x2) const;

    inline uint16_t GetScore() const{ return score; }

    inline void SetPos(double nx, double ny){
        x = nx;
        y = ny;
    }

    inline double GetY() const { return y; }
    inline double GetX() const { return x; }
    inline void SetWidth(uint16_t widthN) { width = widthN; }
    inline uint16_t GetWidth() const { return width; }

protected:
    double x, y;
    uint16_t width;
    const uint16_t score = 30;
};

class TankAdapter : public DestroyableGroundObject{ //Адаптер делает интерфейс Адаптируемого класса совместимым с целевым интерфейсом
public:

    void SetPos(double nx, double ny) override{
        tank.SetPos(nx, ny);
    }

    uint16_t GetWidth() const override{
        return tank.GetWidth();
    }

    void Draw() const override{
        tank.Paint();
    }

    inline uint16_t GetScore() const override{
        return tank.GetScore();
    }

    bool isInside(double x1, double x2) const override;

private:
    TankAdaptee tank;
};