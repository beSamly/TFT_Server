#include "pch.h"
#include "SocketServer.h"
#include "ClientSession.h"
#include "spdlog/spdlog.h"
#include <ProxyManager.h>

SocketServer::SocketServer(sptr<asio::io_context> context, int port)
    : ioContext(context), AsioBaseSocketServer(context, port)
{
}

shared_ptr<AsioSession> SocketServer::CreateSession()
{
    //shared_ptr<Proxy> proxySession = std::make_shared<Proxy>(SERVER_TYPE::NOT_INITIALIZED, ioContext);
    shared_ptr<ClientSession> proxySession = std::make_shared<ClientSession>(ioContext);
    proxySession->SetOnRecvCallback(onClientRecv);
    proxySession->SetOnDisconnectCallback(onClientDisconnect);
    return proxySession;
}
