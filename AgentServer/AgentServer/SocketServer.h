#pragma once
#include <functional>
#include "ClientSession.h"
#include "AsioBaseSocketServer.h"

using SessionFactory = std::function<SessionRef(void)>;
using std::shared_ptr;

class SocketServer : public AsioBaseSocketServer
{
    public:
        SocketServer(sptr<asio::io_context> context, int port);

    public:
        void StartAccept();
        void OnAccept(sptr<AsioSession> session) override;
        sptr<AsioSession> CreateSession() override;
        void RunIoContext();

    protected:
        sptr<asio::io_context> ioContext;

    public:
        std::function<void(sptr<ClientSession>, BYTE*, int32)> OnClientRecv;
        std::function<void(sptr<ClientSession>)> OnClientDisconnect;
        std::function<void(sptr<ClientSession>)> OnClientConnect;
};
