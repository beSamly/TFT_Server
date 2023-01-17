#pragma once
#include "pch.h"
#include "Champion.h"
#include "ShopProbability.h"
#include "ChampShop.h"
#include "Field.h"
#include "Bench.h"
#include "ClientSession.h"

class InGamePlayer
{
private:
	wptr<ClientSession> client;

public:
	InGamePlayer();

private:
	int playerId;
	ShopProbability shopProb;
	ChampShop champShop;
	Field field;
	Bench bench;
	int gold = 100;

public:
	int GetPlayerId() { return playerId; }
	void SetPlayerId(int id) { playerId = id; }
	ShopProbability& GetShopProbability() { return shopProb; };
	ChampShop& GetChampShop() { return champShop; };
	Bench& GetBench() { return bench; };
	Field& GetField() { return field; };
	int GetGold() { return gold; }
	void SpendGold(int value) { gold -= value; }

public:
	bool IsMatched() { return isMatched; }
	void SetMatched(bool value) { isMatched = value; }
	void SetClientSession(wptr<ClientSession> p_clinet) { client = p_clinet; }
	void SendToClient();

private:
	bool isMatched;
};
