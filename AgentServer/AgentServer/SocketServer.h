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
    shared_ptr<AsioSession> CreateSession() override;

protected:
    sptr<asio::io_context> ioContext;
};
