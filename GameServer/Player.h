#pragma once

class GameHost;

class Player
{
private:
    wptr<GameHost> currentGame;

public:
    int playerId;
    // Player(){};
    void SetCurrentGameHost(wptr<GameHost> gameHost) { currentGame = gameHost; }
    wptr<GameHost> GetCurrentGameHost() { return currentGame; }
};
