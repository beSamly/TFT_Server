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
        sptr<ClientSession> GetClientSessionRef();

    private:
        sptr<Player> player;

    public:
        sptr<Player> GetPlayer();
        void SetPlayer(sptr<Player> player);

    public:
        /* 네트워크 콜백 */
        function<void(sptr<ClientSession>, BYTE*, int32)> OnRecvCallback;
        function<void(sptr<ClientSession>)> OnDisconnectCallback;
        function<void(sptr<ClientSession>)> OnConnectCallback;

    private:
        /* 인터페이스 구현 */
        int OnRecv(BYTE* buffer, int len) override;
        void OnDisconnect() override;
        void OnConnect() override;
};
