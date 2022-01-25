#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

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

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};

/*class BaseCommand{
protected:
    SBomber* obj;

public:
    virtual ~BaseCommand(){}
    virtual void Execute() = 0;

    void SetParams(SBomber* object){
        obj = object;
    }

};

class DeleteDynamicObj: public BaseCommand{
    DynamicObject *dObject;
    vecDynamicObj *vecDyn;

public:
    DeleteDynamicObj(DynamicObject *dynObj, vecDynamicObj *vDyn): dObject(dynObj), vecDyn(vDyn){}

    void Execute() override{
        auto it = vecDynamicObj.begin();
        for (; it != vecDynamicObj.end(); it++) {
            if (*it == pObj) {
                vecDynamicObj.erase(it);
                break;
            }
        }
    }

};*/