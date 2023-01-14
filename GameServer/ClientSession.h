#pragma once
#include "pch.h"
#include "AsioSession.h"
#include "Player.h"
#include <asio/io_context.hpp>

/*-----------------
                ClientSession
------------------*/

class ClientSession : public AsioSession
{
public:
    ClientSession(sptr<asio::io_context> context);
    virtual ~ClientSession();

private:
    sptr<Player> player;

public:
    bool isAuthenticated = false;
    int tempClientId = 0;
    sptr<Player> GetPlayer();
    void SetPlayer(sptr<Player> player);
};
