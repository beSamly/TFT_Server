#pragma once

// ������ ���¸���Ʈ : ����, ���, ����,

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
