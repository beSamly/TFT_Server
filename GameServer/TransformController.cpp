#include "pch.h"
#include "TransformController.h"

Vector3 TransformController::GetPosition() { return position; }

void TransformController::Update(float deltaTime)
{
    if (position == targetPosition) {
        return;
    }

    Vector3 directionToTarget = targetPosition - position;

    float moveSpeed = 1;
    Vector3 moveVector = directionToTarget.Normalized() * moveSpeed * deltaTime;

    float distanceToMove = moveVector.GetMagnitude();
    float distanceToTarget = directionToTarget.GetMagnitude();

    // 이동하려는 거리가 targetPosition보다 길다면 targetPosition에 도착한거다.
    if (distanceToMove > distanceToTarget) {
        position = targetPosition;
    }
    else {
        position = position + moveVector;
    }
}

bool TransformController::IsMoving()
{
    return position == targetPosition ? false : true;
}
