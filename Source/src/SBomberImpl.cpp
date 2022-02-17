//
// Created by sa on 16.02.2022.
//
#include "SBomberImpl.h"
#include "MyTools.h"
#include "enums/CraterSize.h"

extern _FileLogger logger;

SBomberImpl::SBomberImpl() : exitFlag(false), startTime(0), finishTime(0), deltaTime(0), passedTime(0),
                              fps(0), bombsNumber(10), score(0){

}

SBomberImpl::~SBomberImpl() {
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

    delete lV;
}

void SBomberImpl::DeleteDynamicObj(DynamicObject* pObj){
    DeleteDynamicObject* dlt = new DeleteDynamicObject();
    dlt->setParams(vecDynamicObj, pObj);
    SBomberImpl::CommandExecuter(dlt);
}

void SBomberImpl::DeleteStaticObj(GameObject *pObj) {
    DeleteStaticObject* dso = new DeleteStaticObject();
    dso->setParams(vecStaticObj, pObj);
    SBomberImpl::CommandExecuter(dso);
}

void SBomberImpl::CheckPlaneAndLevelGUI() {
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
        exitFlag = true;
    }

}

Plane* SBomberImpl::FindPlane() const {
    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomberImpl::FindLevelGUI() const {
    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        LevelGUI *p = dynamic_cast<LevelGUI *>(vecStaticObj[i]);
        if (p != nullptr) {
            return p;
        }
    }
}

Ground* SBomberImpl::FindGround() const {
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
        if (pGround != nullptr) {
            return pGround;
        }
    }

    return nullptr;
}

std::vector<DestroyableGroundObject*> SBomberImpl::FindDestoyableGroundObjects() const {
    std::vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr) {
            vec.push_back(pTank);
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

std::vector<Bomb*> SBomberImpl::FindAllBombs() const {
    std::vector<Bomb*> vecBombs;

    BombIterator* it = new BombIterator(vecDynamicObj);

    for(;it->cPos() != it->end(); it->next()){
        vecBombs.push_back(it->get());
    }

    delete it;
    return vecBombs;
}

void SBomberImpl::DropBomb() {

    const Plane* pPlane = FindPlane();
    std::vector<DestroyableGroundObject*> vecDGObject = SBomberImpl::FindDestoyableGroundObjects();

    DropBombs* drp = new DropBombs();
    drp->setParams(bombsNumber, pPlane, vecDynamicObj, score, vecDGObject);
    CommandExecuter(drp);
}

Plane *SBomberImpl::ChoicePlane() {
    srand(time(0));
    int number = 0;
    number = rand()%(2 + 0);

    if(number == 0){
        Plane* p = new BigPlane;
        return p;
    }else if(number == 1){
        Plane* p = new ColorPlane;
        return p;
    }else{
        Plane* p = new Plane;
        return p;
    }
}

void DropBombs::Execute() {
    if (*bombNumber > 0) {

        //ProxyLoggerSingletone::getInstance().WriteToLog(std::string(__func__) + " was invoked");
        logger.WriteToLog(std::string(__func__) + " was invoked");

        double x = plane->GetX() + 4;
        double y = plane->GetY() + 2;

        //BombDecorator *pBomb = new BombDecorator(new Bomb);
        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        //Подписка на бомбу
        for(size_t j = 0; j < vecDGO_->size(); j++){
            pBomb->AddObserver(vecDGO_->at(j));
        }

        vecDynamicObj_->push_back(pBomb);
        *bombNumber--;
        *score -= Bomb::BombCost;
    }
}

void Chat::AddMessage(std::string message) {
    if(!message.empty()){
        addressee->QueueTankMessage.push(message);
    }
}

void Chat::SendMessage(){
    addressee->DrawMessage();
}

void Chat::AddAdressee(LevelGUI* Addressee) {
    addressee = Addressee;
}

void SBomberImpl::CommandExecuter(Command* pCommand){
    pCommand->Execute();
    delete pCommand;
}

void SBomberImpl::CheckBombsAndGround() {
    std::vector<Bomb*> vecBombs = FindAllBombs();

    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++) {
      if (vecBombs[i]->GetY() >= y) { //Пересечение бомбы с землёй
        pGround->AddCrater(vecBombs[i]->GetX());
          if(vecBombs[i]->CheckDestoyableObjects() != nullptr){ //Пересечение бомбы с разрушаемым объектом
              score += vecBombs[i]->CheckDestoyableObjects()->GetScore();
              DeleteStaticObj(vecBombs[i]->CheckDestoyableObjects());
          }
        DeleteDynamicObj(vecBombs[i]);
      }
    }
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

void LogVisitor::logBomb(Bomb* pBomb) const{
    logger.WriteToLog(std::string(__func__) + " Bomb speed = ", pBomb->GetSpeed());
    logger.WriteToLog(std::string(__func__) + " Bomb Direction X = ", pBomb->GetDirection().first);
    logger.WriteToLog(std::string(__func__) + " Bomb Direction Y = ", pBomb->GetDirection().second);

}

void LogVisitor::logPlane(Plane* pPlane) const{
    logger.WriteToLog(std::string(__func__) + " Plane speed = ", pPlane->GetSpeed());
    logger.WriteToLog(std::string(__func__) + " Plane Direction X = ", pPlane->GetDirection().first);
    logger.WriteToLog(std::string(__func__) + " Plane Direction Y = ", pPlane->GetDirection().second);
}