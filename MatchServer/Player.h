#pragma once

class GameHost;

class Player
{
public:
    int playerId;
    // Player(){};
    wptr<GameHost> currentGame;
};
