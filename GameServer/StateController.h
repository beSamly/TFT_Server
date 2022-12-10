#pragma once

// 가능한 상태리스트 : 기절, 에어본, 죽음,

class StateController
{
private:

private:
    /*int currentHp;
    int currentMp;*/

public:
    StateController() {};
    void Update(float deltaTime);
    bool IsActionDisabled();
    bool IsDead();
};
