#pragma once

#include "GameObject.h"
#include "Crater.h"
#include <vector>


/*class Ground : public GameObject {
public:
  Ground() = default;
  void Draw() const override;

  void AddCrater(double xn);

private:
  bool isInsideAnyCrater(double x) const;

  std::vector<Crater> vecCrates;
};*/

class Ground: public GameObject {
public:
    void Draw() const override = 0;
    virtual void AddCrater(double xn);
    virtual Crater* getCrater() const = 0;
    ~Ground() = default;

protected:
    bool isInsideAnyCrater(double x) const;
    std::vector<Crater*> vecCrates;
};

class CommonGround: public Ground{
public:

    void Draw() const override;
    Crater* getCrater() const override{
        return new CommonCrater;
    }
};

class WinterGround: public Ground{
public:

    void Draw() const override;
    Crater* getCrater() const override{
        return new OtherCrater;
    }

};