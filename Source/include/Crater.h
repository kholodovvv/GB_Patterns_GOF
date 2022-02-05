#pragma once

#include "GameObject.h"

/*class Crater : public GameObject {
public:
  bool isInside(double xn) const;

  virtual void Draw() const override;
};*/

class Crater : public GameObject {
public:
    ~Crater() = default;
    bool isInside(double xn) const;
    void Draw() const override = 0;
};

class CommonCrater: public Crater{
    void Draw() const override;
};

class OtherCrater: public Crater{
    void Draw() const override;
};