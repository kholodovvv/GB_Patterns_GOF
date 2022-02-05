
#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "ScreenSingleton.h"
#include "enums/CraterSize.h"
#include <chrono>
#include <thread>
#include <iostream>

SBomber::SBomber()
  : exitFlag(false), startTime(0), finishTime(0), deltaTime(0), passedTime(0),
    fps(0), bombsNumber(10), score(0) {
  //MyTools::WriteToLog(std::string(__func__) + " was invoked");
    ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");

  Plane* p = new Plane;
  p->SetDirection(1, 0.1);
  p->SetSpeed(4);
  p->SetPos(5, 10);
  vecDynamicObj.push_back(p);

  LevelGUI* pGUI = new LevelGUI;
  pGUI->SetParam(passedTime, fps, bombsNumber, score);
  const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
  const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
  const uint16_t offset = 3;
  const uint16_t width = maxX - 7;
  pGUI->SetPos(offset, offset);
  pGUI->SetWidth(width);
  pGUI->SetHeight(maxY - 4);
  pGUI->SetFinishX(offset + width - 4);
  vecStaticObj.push_back(pGUI);

  Ground* pGr = new WinterGround();
  const uint16_t groundY = maxY - 5;
  pGr->SetPos(offset + 1, groundY);
  pGr->SetWidth(width - 2);
  vecStaticObj.push_back(pGr);

  TankAdapter* ptank = new TankAdapter;
  ptank->SetWidth(13);
  ptank->SetPos(30, groundY - 1);
  vecStaticObj.push_back(ptank);

  /*Tank* pTank = new Tank;
  pTank->SetWidth(13);
  pTank->SetPos(30, groundY - 1);
  vecStaticObj.push_back(pTank);*/

  ptank = new TankAdapter;
  ptank->SetWidth(13);
  ptank->SetPos(50, groundY - 1);
  vecStaticObj.push_back(ptank);

    HouseDirector dir;
    HouseBuilderB houseB;
    House* pHouse = dir.BuildHouse(houseB);

    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

  /*House* pHouse = new House;
  pHouse->SetWidth(13);
  pHouse->SetPos(80, groundY - 1);
  vecStaticObj.push_back(pHouse);*/

}

SBomber::~SBomber() {
  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    if (vecDynamicObj[i] != nullptr) {
      delete vecDynamicObj[i];
    }
  }

  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    if (vecStaticObj[i] != nullptr) {
      delete vecStaticObj[i];
    }
  }
}

void SBomber::MoveObjects() {
 //MyTools::WriteToLog(std::string(__func__) + " was invoked");
 ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");

  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    if (vecDynamicObj[i] != nullptr) {
      vecDynamicObj[i]->Move(deltaTime);
    }
  }
};

void SBomber::CheckObjects() {
  //MyTools::WriteToLog(std::string(__func__) + " was invoked");
  ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");

  CheckPlaneAndLevelGUI();
  CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI() {
  if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
    exitFlag = true;
  }
}

void SBomber::CheckBombsAndGround() {
  std::vector<Bomb*> vecBombs = FindAllBombs();
  Ground* pGround = FindGround();
  const double y = pGround->GetY();
  for (size_t i = 0; i < vecBombs.size(); i++) {
    if (vecBombs[i]->GetY() >= y) {
      pGround->AddCrater(vecBombs[i]->GetX());
      CheckDestoyableObjects(vecBombs[i]);
      DeleteDynamicObj(vecBombs[i]);
    }
  }
}

void SBomber::CheckDestoyableObjects(Bomb* pBomb) {
  std::vector<DestroyableGroundObject*> vecDestoyableObjects =
      FindDestoyableGroundObjects();
  const double size = pBomb->GetWidth();
  const double size_2 = size / 2;
  for (size_t i = 0; i < vecDestoyableObjects.size(); i++) {
    const double x1 = pBomb->GetX() - size_2;
    const double x2 = x1 + size;
    if (vecDestoyableObjects[i]->isInside(x1, x2)) {
      score += vecDestoyableObjects[i]->GetScore();
      DeleteStaticObj(vecDestoyableObjects[i]);
    }
  }
}

void SBomber::CommandExecuter(Command* pCommand){
    pCommand->Execute();
    delete pCommand;
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj) {
  /*auto it = vecDynamicObj.begin();
  for (; it != vecDynamicObj.end(); it++) {
    if (*it == pObj) {
      vecDynamicObj.erase(it);
      break;
    }
  }*/

  DeleteDynamicObject* dlt = new DeleteDynamicObject();
  dlt->setParams(vecDynamicObj, pObj);
  SBomber::CommandExecuter(dlt);
}

void DeleteDynamicObject::Execute(){
    auto it = vecDynamicObj_->begin();
    for (; it != vecDynamicObj_->end(); it++) {
        if (*it == dObject) {
            vecDynamicObj_->erase(it);
            break;
        }
    }
}

void DeleteStaticObject::Execute() {
    auto it = vecStaticObj_->begin();
    for (; it != vecStaticObj_->end(); it++) {
        if (*it == gObject) {
            vecStaticObj_->erase(it);
            break;
        }
    }
}

void SBomber::DeleteStaticObj(GameObject* pObj) {
  /*auto it = vecStaticObj.begin();
  for (; it != vecStaticObj.end(); it++) {
    if (*it == pObj) {
      vecStaticObj.erase(it);
      break;
    }
  }*/

    DeleteStaticObject* dso = new DeleteStaticObject();
    dso->setParams(vecStaticObj, pObj);
    SBomber::CommandExecuter(dso);

}

std::vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const {
  std::vector<DestroyableGroundObject*> vec;
  TankAdapter* ptank;
  House* pHouse;
  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    ptank = dynamic_cast<TankAdapter*>(vecStaticObj[i]);
    if (ptank != nullptr) {
      vec.push_back(ptank);
      continue;
    }

    pHouse = dynamic_cast<House*>(vecStaticObj[i]);
    if (pHouse != nullptr) {
      vec.push_back(pHouse);
      continue;
    }
  }

  return vec;
}

Ground* SBomber::FindGround() const {
  Ground* pGround;

  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
    if (pGround != nullptr) {
      return pGround;
    }
  }

  return nullptr;
}

std::vector<Bomb*> SBomber::FindAllBombs() const {
  std::vector<Bomb*> vecBombs;

  BombIterator* it = new BombIterator(vecDynamicObj);

  for(;it->cPos() != it->end(); it->next()){
      vecBombs.push_back(it->get());
  }

  delete it;
  return vecBombs;
}

Plane* SBomber::FindPlane() const {
  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
    if (p != nullptr) {
      return p;
    }
  }

  return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const {
  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
    if (p != nullptr) {
      return p;
    }
  }

  return nullptr;
}

void SBomber::ProcessKBHit() {
  int c = getchar();

  if (c == 224) {
    c = getchar();
  }

  //MyTools::WriteToLog(std::string(__func__) + " was invoked. key = ", c);
  ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked. key = ", c);

  switch (c) {

    case 27: // esc
      exitFlag = true;
      break;

    case 72: // up
      FindPlane()->ChangePlaneY(-0.25);
      break;

    case 80: // down
      FindPlane()->ChangePlaneY(0.25);
      break;

    case 'b':
      DropBomb();
      break;

    case 'B':
      DropBomb();
      break;

    default:
      break;
  }
}

void SBomber::DrawFrame() {
  //MyTools::WriteToLog(std::string(__func__) + " was invoked");
  ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");

  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    if (vecDynamicObj[i] != nullptr) {
      vecDynamicObj[i]->Draw();
    }
  }

  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    if (vecStaticObj[i] != nullptr) {
      vecStaticObj[i]->Draw();
    }
  }

  ScreenSingleton::getInstance().GotoXY(0, 0);
  fps++;

  FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart() {
  //MyTools::WriteToLog(std::string(__func__) + " was invoked");
  ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");
  startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void SBomber::TimeFinish() {
  finishTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
  deltaTime = uint16_t(finishTime - startTime);
  passedTime += deltaTime;

  //MyTools::WriteToLog(std::string(__func__) + " deltaTime = ", (int)deltaTime);
  ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::DropBomb() {
/*  if (bombsNumber > 0) {
    //MyTools::WriteToLog(std::string(__func__) + " was invoked");
    ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");

    Plane* pPlane = FindPlane();
    double x = pPlane->GetX() + 4;
    double y = pPlane->GetY() + 2;

    //Bomb* pBomb = new Bomb;
    BombDecorator *pBomb = new BombDecorator(new Bomb);
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(x, y);
    pBomb->SetWidth(SMALL_CRATER_SIZE);

    vecDynamicObj.push_back(pBomb);
    bombsNumber--;
    score -= Bomb::BombCost;
  }*/

 const Plane* pPlane = FindPlane();
 DropBombs* drp = new DropBombs();
 drp->setParams(bombsNumber, pPlane, vecDynamicObj, score);
 CommandExecuter(drp);
}

void DropBombs::Execute() {
    if (*bombNumber > 0) {

        ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");

        double x = plane->GetX() + 4;
        double y = plane->GetY() + 2;

        //BombDecorator *pBomb = new BombDecorator(new Bomb);
        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj_->push_back(pBomb);
        *bombNumber--;
        *score -= Bomb::BombCost;
    }
}