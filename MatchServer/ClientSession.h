#pragma once
#include <asio/io_context.hpp>

#include "AsioSession.h"
#include "Player.h"
#include "pch.h"

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
        sptr<Player> GetPlayer();
        void SetPlayer(sptr<Player> player);
};
