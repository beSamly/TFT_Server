#pragma once
#include "Vector3.h"
#include "Champion.h"

class Hexagon {
private:
    Vector3 position;
    sptr<Champion> champion = nullptr;
    vector<wptr<Hexagon>> adjacentNode;

private:
    vector<wptr<Hexagon>> GetAdjacentsSortedByDistance(Vector3 direction);

public:
    void SetPosition(Vector3 p_position) {
        position = p_position;
    }
    Vector3 GetPosition() { return position; }
    void SetChampion(sptr<Champion> p_champion) { champion = p_champion; }
    void AddAdjacent(wptr<Hexagon> p_hexagon) { adjacentNode.push_back(p_hexagon); }
    wptr<Hexagon> GetEmptyNodeTowardDirection(Vector3 direction);
    void Release() { champion = nullptr; }
    bool IsOccupiedBy(sptr<Champion>& p_champion) { return  champion->uid == p_champion->uid ? true : false; }
    bool IsOccupied() { return champion == nullptr ? false : true; };
};

class FieldMap {

public:
    FieldMap();
    void LocateChampion(int fieldUid, sptr<Champion> champion);
    sptr<Hexagon> GetHexagonByChampion(sptr<Champion>& champion);

private:
    map<int, sptr<Hexagon>> mapData;
    map<int, sptr<Hexagon>> championAt;
    int rowCount = 8;
    int hexagonCountInRow = 8;
    int edgeLength = 8;
    float GetTriangleHeight();
};
