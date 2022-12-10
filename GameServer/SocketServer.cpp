#include "SocketServer.h"

#include "ClientSession.h"
#include "pch.h"
#include "spdlog/spdlog.h"

SocketServer::SocketServer(sptr<asio::io_context> context, int port)
    : ioContext(context), AsioBaseSocketServer(context, port)
{
}

shared_ptr<AsioSession> SocketServer::CreateSession()
{
    shared_ptr<ClientSession> clientSession = std::make_shared<ClientSession>(ioContext);
    clientSession->SetOnRecvCallback(onClientRecv);
    clientSession->SetOnDisconnectCallback(onClientDisconnect);
    return clientSession;
}
