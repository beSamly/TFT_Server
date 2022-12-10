#pragma once
#include "Champion.h"

namespace TargetFindUtil {
    Vector3 FindClosestTragetPosition(Vector3 from, vector <sptr<Champion>> targetVector)
    {
        Vector3 closest;

        float min = 1000000;
        for (sptr<Champion>& champion : targetVector) {
            Vector3 targetPosition = champion->transform.GetTargetPosition();
            Vector3 distanceVector = from - targetPosition;
            float distance = distanceVector.GetMagnitude();
            if (min > distance) {
                closest = targetPosition;
                min = distance;
            }
        }

        return closest;
    }
}
