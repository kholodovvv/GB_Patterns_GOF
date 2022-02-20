#pragma once

class SBomberImpl;
extern int _kbhit();

class SBomber
{

public:

    SBomber();
    ~SBomber();
    
    bool GetExitFlag() const;

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    void AnimateScrolling();

private:
    SBomberImpl* pSBomberImpl;

};

