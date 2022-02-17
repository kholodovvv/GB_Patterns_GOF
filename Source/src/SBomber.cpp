
#include "MyTools.h"
#include "SBomber.h"
#include "ScreenSingleton.h"
#include <chrono>
#include <iostream>
#include "SBomberImpl.h"

extern _FileLogger logger;

SBomber::SBomber(): pSBomberImpl(new SBomberImpl()) {

    logger.WriteToLog(std::string(__func__) + " was invoked");

    Plane* p = pSBomberImpl->ChoicePlane();
  //Plane* p = new BigPlane;
  p->SetDirection(1, 0.1);
  p->SetSpeed(4);
  p->SetPos(5, 10);
  pSBomberImpl->vecDynamicObj.push_back(p);

  LevelGUI* pGUI = new LevelGUI;
  pGUI->SetParam(pSBomberImpl->passedTime, pSBomberImpl->fps, pSBomberImpl->bombsNumber, pSBomberImpl->score);
  const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
  const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
  const uint16_t offset = 3;
  const uint16_t width = maxX - 7;
  pGUI->SetPos(offset, offset);
  pGUI->SetWidth(width);
  pGUI->SetHeight(maxY - 4);
  pGUI->SetFinishX(offset + width - 4);
  pSBomberImpl->vecStaticObj.push_back(pGUI);

  Ground* pGr = new WinterGround();
  const uint16_t groundY = maxY - 5;
  pGr->SetPos(offset + 1, groundY);
  pGr->SetWidth(width - 2);
  pSBomberImpl->vecStaticObj.push_back(pGr);

  Chat* chat = new Chat;
  chat->AddAdressee(pGUI);

  Tank* pTank = new Tank(chat);
  pTank->SetWidth(13);
  pTank->SetPos(30, groundY - 1);

  pSBomberImpl->vecStaticObj.push_back(pTank);

  pTank = new Tank(chat);
  pTank->SetWidth(13);
  pTank->SetPos(50, groundY - 1);
  pSBomberImpl->vecStaticObj.push_back(pTank);

    HouseDirector dir;
    HouseBuilderB houseB;
    House* pHouse = dir.BuildHouse(houseB);

    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    pSBomberImpl->vecStaticObj.push_back(pHouse);

}

SBomber::~SBomber() {
    delete pSBomberImpl;
}

void SBomber::MoveObjects() {

 logger.WriteToLog(std::string(__func__) + " was invoked");

    for (size_t i = 0; i < pSBomberImpl->vecDynamicObj.size(); i++) {
        if (pSBomberImpl->vecDynamicObj[i] != nullptr) {
            pSBomberImpl->vecDynamicObj[i]->Move(pSBomberImpl->deltaTime);

            if(dynamic_cast<Bomb*>(pSBomberImpl->vecDynamicObj[i]) != nullptr) {
                dynamic_cast<Bomb*>(pSBomberImpl->vecDynamicObj[i])->Accept(pSBomberImpl->lV);
            }else {
                dynamic_cast<Plane*>(pSBomberImpl->vecDynamicObj[i])->Accept(pSBomberImpl->lV);
            }

        }
    }
};

void SBomber::CheckObjects() {
  logger.WriteToLog(std::string(__func__) + " was invoked");

    pSBomberImpl->CheckPlaneAndLevelGUI();
    pSBomberImpl->CheckBombsAndGround();
};


void SBomber::ProcessKBHit() {
  int c = getchar();

  if (c == 224) {
    c = getchar();
  }

  logger.WriteToLog(std::string(__func__) + " was invoked. key = ", c);

  switch (c) {

    case 27: // esc
      pSBomberImpl->exitFlag = true;
      break;

    case 72: // up
        pSBomberImpl->FindPlane()->ChangePlaneY(-0.25);
      break;

    case 80: // down
        pSBomberImpl->FindPlane()->ChangePlaneY(0.25);
      break;

    case 'b':
        pSBomberImpl->DropBomb();
      break;

    case 'B':
        pSBomberImpl->DropBomb();
      break;

    default:
      break;
  }
}

void SBomber::DrawFrame() {

  logger.WriteToLog(std::string(__func__) + " was invoked");


    for (size_t i = 0; i < pSBomberImpl->vecDynamicObj.size(); i++) {
        if (pSBomberImpl->vecDynamicObj[i] != nullptr) {
            pSBomberImpl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < pSBomberImpl->vecStaticObj.size(); i++) {
        if (pSBomberImpl->vecStaticObj[i] != nullptr) {
            pSBomberImpl->vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    pSBomberImpl->fps++;

    pSBomberImpl->FindLevelGUI()->SetParam(pSBomberImpl->passedTime, pSBomberImpl->fps, pSBomberImpl->bombsNumber, pSBomberImpl->score);
}

void SBomber::TimeStart() {

  logger.WriteToLog(std::string(__func__) + " was invoked");

pSBomberImpl->startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void SBomber::TimeFinish() {

pSBomberImpl->finishTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
pSBomberImpl->deltaTime = uint16_t(pSBomberImpl->finishTime - pSBomberImpl->startTime);
pSBomberImpl->passedTime += pSBomberImpl->deltaTime;

logger.WriteToLog(std::string(__func__) + " deltaTime = ", (int)pSBomberImpl->deltaTime);
}

bool SBomber::GetExitFlag() const {
    return pSBomberImpl->exitFlag;
}