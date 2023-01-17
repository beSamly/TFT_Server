#pragma once

class GameHost;

class Player
{
private:
	wptr<GameHost> currentGame;
	int playerId;
public:
	int GetPlayerId() { return playerId; }
	void SetPlayerId(int id) { playerId = id; }
	// Player(){};
	void SetCurrentGameHost(wptr<GameHost> gameHost) { currentGame = gameHost; }
	wptr<GameHost> GetCurrentGameHost() { return currentGame; }
};
