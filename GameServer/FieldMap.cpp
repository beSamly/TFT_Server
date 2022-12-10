#include "pch.h"
#include "FieldMap.h"

FieldMap::FieldMap() {
    float triangleHeight = GetTriangleHeight();
    float hexagoneHeight = triangleHeight * 2;
    float halfTriangleHeight = triangleHeight / 2;

    for (int i = 1; i <= rowCount; i++) {

        bool isOddRow = (i % 2) == 1;

        float zOffset = (hexagoneHeight * (i - 1)) + halfTriangleHeight;

        for (int j = 1; j <= hexagonCountInRow; j++) {

            float xOffset = 0 + (isOddRow ? halfTriangleHeight : 0);
            xOffset += (hexagoneHeight * (j - 1)) + halfTriangleHeight;

            sptr<Hexagon> node = make_shared<Hexagon>();
            node->SetPosition(Vector3(xOffset, 0, zOffset));
            mapData.emplace((i * 10) + j, node);
        }
    }

    //Init adjacent node
    for (const auto& [index_i, hexagon_i] : mapData) {
        for (const auto& [index_j, hexagon_j] : mapData) {
            Vector3 distance = hexagon_i->GetPosition() - hexagon_j->GetPosition();
            if (distance.GetMagnitude() == hexagoneHeight) {
                hexagon_i->AddAdjacent(hexagon_j);
            }
        }
    }
}

void FieldMap::LocateChampion(int fieldUid, sptr<Champion> champion)
{
    if (mapData.count(fieldUid)) {
        mapData[fieldUid]->SetChampion(champion);
        championAt.emplace(champion->uid, mapData[fieldUid]);
    }
}

sptr<Hexagon> FieldMap::GetHexagonByChampion(sptr<Champion>& champion)
{
    if (championAt.count(champion->uid)) {
        return championAt[champion->uid];
    }
    return nullptr;
}

float FieldMap::GetTriangleHeight()
{
    return (sqrt(3) * edgeLength) / 2;
}

vector<wptr<Hexagon>> Hexagon::GetAdjacentsSortedByDistance(Vector3 direction)
{
    vector<wptr<Hexagon>> ret;
    vector<wptr<Hexagon>> copied = adjacentNode;

    int size = copied.size();
    for (int i = 0; i < size; i++) {
        float max = -1000;
        int maxIndex = -1;

        for (int j = 0; j < copied.size(); j++) {
            if (sptr<Hexagon> temp = adjacentNode[j].lock()) {
                float dotProduct = direction.Dot(temp->GetPosition());
                if (max < dotProduct) {
                    max = dotProduct;
                    maxIndex = j;
                }
            }
        }

        ret.push_back(copied[maxIndex]);
    }

    return ret;
}

wptr<Hexagon> Hexagon::GetEmptyNodeTowardDirection(Vector3 direction)
{
    vector<wptr<Hexagon>> adjacent = GetAdjacentsSortedByDistance(direction);

    for (wptr<Hexagon>& hexagon : adjacent) {
        if (sptr<Hexagon> temp = hexagon.lock()) {
            if (!temp->IsOccupied()) {
                return hexagon;
            }
        }
    }
}
