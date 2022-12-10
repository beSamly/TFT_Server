#pragma once
#include <functional>

#include "AsioBaseSocketServer.h"
#include "AsioSession.h"
#include "ClientSession.h"

class SocketServer : public AsioBaseSocketServer
{
public:
    SocketServer(sptr<asio::io_context> context, int port);
    shared_ptr<AsioSession> CreateSession() override;

protected:
    sptr<asio::io_context> ioContext;
};
