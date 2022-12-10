#pragma once

#include <asio/io_context.hpp>
#include "AsioSession.h"

using std::map;
using std::shared_ptr;
using std::vector;

enum SERVER_TYPE
{
    NOT_INITIALIZED = 1,
    AGENT,
    MATCH,
    GAME
};

class Proxy : public AsioSession
{
public:
    Proxy(shared_ptr<asio::io_context> ioContext) : serverType(SERVER_TYPE::NOT_INITIALIZED), AsioSession(ioContext){};
    Proxy(SERVER_TYPE type, shared_ptr<asio::io_context> ioContext) : serverType(type), AsioSession(ioContext){};

    SERVER_TYPE GetServerType() { return serverType; };
    bool IsAgentServer() { return serverType == SERVER_TYPE::AGENT; }
    bool IsMatchServer() { return serverType == SERVER_TYPE::MATCH; }
    bool IsGameServer() { return serverType == SERVER_TYPE::GAME; }

private:
    SERVER_TYPE serverType;
};

class ProxyManager
{
public:
    ProxyManager();

    void RunIoContext() { ioContext->run(); }
    void AddProxy(SERVER_TYPE type, shared_ptr<Proxy> session);

    void ConnectToMatchServer();
    void ConnectToGameServer();
    void Connect(string address, int port, SERVER_TYPE type);

    void SendToMatchServer(shared_ptr<SendBuffer> sendBuffer);
    void SendToGameServer(shared_ptr<SendBuffer> sendBuffer);
    void SendTo(shared_ptr<SendBuffer> sendBuffer, SERVER_TYPE type);

    void SetHandleRecv(function<void(shared_ptr<Proxy>, BYTE*, int32)> callback) { HandleRecv = callback; };

private:
    shared_ptr<asio::io_context> ioContext;
    map<SERVER_TYPE, vector<shared_ptr<Proxy>>> proxyMap;
    function<void(shared_ptr<Proxy>, BYTE*, int32)> HandleRecv;

private:
    void OnConnect(shared_ptr<AsioSession> session);
    void OnRecv(shared_ptr<AsioSession> session, BYTE* buffer, int len);
    void OnDisconnect(shared_ptr<AsioSession> session);
};
