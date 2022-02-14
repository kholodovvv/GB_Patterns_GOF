#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include <cassert>

class Command;

class Visitor{
public:
    virtual void logPlane(Plane* pPlane) const  = 0;
    virtual void logBomb(Bomb* pBomb) const = 0;
    virtual ~Visitor() = default;
};

class LogVisitor: public Visitor{
public:
    void logBomb(Bomb* pBomb) const override;
    void logPlane(Plane* pPlane) const override;
};

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    //void  CheckDestoyableObjects(Bomb* pBomb);

    void  DeleteDynamicObj(DynamicObject * pBomb);
    void  DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    Plane *  ChoicePlane();

    void DropBomb();
    LogVisitor* lV = new LogVisitor();
    void CommandExecuter(Command* pCommand);

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};

class Command{
public:
    virtual void Execute() = 0;
    virtual ~Command() = default;
};

class DeleteDynamicObject: public Command{
public:

    virtual void Execute() override;

    void setParams(std::vector<DynamicObject*>& vecDynamicObj, DynamicObject* dObj){
        this->vecDynamicObj_ = &vecDynamicObj;
        this->dObject = dObj;
    }

private:
    std::vector<DynamicObject*>* vecDynamicObj_;
    DynamicObject* dObject;
};

class DeleteStaticObject: public Command{
public:

    virtual void Execute() override;

    void setParams(std::vector<GameObject*> &vecStaticObj, GameObject* gObj){
        this->vecStaticObj_ = &vecStaticObj;
        this->gObject = gObj;
    }

private:
    std::vector<GameObject*>* vecStaticObj_;
    GameObject* gObject;
};

class DropBombs: public Command{
public:

    virtual void Execute() override;

    void setParams(uint16_t &bNumber, const Plane* Plane_, std::vector<DynamicObject*> &vecDynamicObject, int16_t &Score,
                   std::vector<DestroyableGroundObject*> &vecDGO){
        this->vecDynamicObj_ = &vecDynamicObject;
        this->plane = Plane_;
        this->score = &Score;
        this->bombNumber = &bNumber;
        this->vecDGO_ = &vecDGO;
    }

private:
    uint16_t* bombNumber;
    const Plane* plane;
    std::vector<DynamicObject*>* vecDynamicObj_;
    std::vector<DestroyableGroundObject*>* vecDGO_;
    int16_t* score;
};


class BombIterator{
public:
    BombIterator(std::vector<DynamicObject*> const &vecDynamicObject) : vecDynamicObj_(&vecDynamicObject){
        assert(!isDone());
        if (current == 0) first();
    }

    const std::vector<DynamicObject*>* begin(){
        return vecDynamicObj_;
    }

    const std::vector<DynamicObject*>* end(){
        return vecDynamicObj_ + vecDynamicObj_->size();
    }

    void next() {
        current = step;

        while (!isDone()) {
            if (dynamic_cast<Bomb*>(vecDynamicObj_->at(current)) != nullptr) {
                break;
            }
            else {
                step = ++current;
            }
        }
        step++;
    }


    const std::vector<DynamicObject*>* cPos() {
        return vecDynamicObj_ + current;
    }

    Bomb* get() {
        if(isDone()){
            return nullptr;
        }else if(dynamic_cast<Bomb*>(vecDynamicObj_->at(current)) != nullptr){
            return dynamic_cast<Bomb*>(vecDynamicObj_->at(current));
        }else{
            return nullptr;
        }
    }

    bool isDone() const {
        return (current < vecDynamicObj_->size()) ? false : true;
    }

private:
    std::vector<DynamicObject*> const *vecDynamicObj_;
    size_t current = 0;
    size_t step = 0;

    void first() {
        while (!isDone()) {
            if (dynamic_cast<Bomb*>(vecDynamicObj_->at(current)) != nullptr) {
                break;
            }
            else {
                step = ++current;
            }
        }
        step++;
    }
};


class Chat{
public:

    void AddMessage(std::string message);
    void AddAdressee(LevelGUI* Addressee);
    void SendMessage();
    ~Chat() {
        delete addressee;
    }

private:
    //Tank* sender;
    LevelGUI* addressee;
    std::vector<std::string> vecMessages;
};