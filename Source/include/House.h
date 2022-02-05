#pragma once

#include "DestroyableGroundObject.h"
#include <cstdint>

class House : public DestroyableGroundObject {
public:
  bool isInside(double x1, double x2) const override;

  inline uint16_t GetScore() const override {
    return score;
  }

  void Draw() const override;

  friend class HouseBuilderA;
  friend class HouseBuilderB;

private:
  const uint16_t score = 40;
  char look[7][14];
};

class HouseBuilder{
protected:
    House* house;
public:
    HouseBuilder():house(0){ }
    virtual ~HouseBuilder(){ }
    virtual void BuildHouse(){ }
    virtual void BuildWall(){ }
    virtual void BuildRoof(){ }
    virtual House* getHouse(){ return house;}
};

class HouseBuilderA: public HouseBuilder{ //Строит дома без окон
public:
    void BuildWall();
    void BuildRoof();
    void BuildHouse(){house = new House;}
};

class HouseBuilderB: public HouseBuilder{ //Строит дома с окнами
public:
    void BuildWall();
    void BuildRoof();
    void BuildHouse(){house = new House;}
};

class HouseDirector{
public:
    House* BuildHouse(HouseBuilder &builder){
        builder.BuildHouse();
        builder.BuildWall();
        builder.BuildRoof();
        return builder.getHouse();
    }
};
