#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class Command;

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
    void  CheckDestoyableObjects(Bomb* pBomb);

    void  DeleteDynamicObj(DynamicObject * pBomb);
    void  DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

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

    void setParams(uint16_t &bNumber, const Plane* Plane_, std::vector<DynamicObject*> &vecDynamicObject, int16_t &Score){
        this->vecDynamicObj_ = &vecDynamicObject;
        this->plane = Plane_;
        this->score = &Score;
        this->bombNumber = &bNumber;
    }

private:
    uint16_t* bombNumber;
    const Plane* plane;
    std::vector<DynamicObject*>* vecDynamicObj_;
    int16_t* score;
};