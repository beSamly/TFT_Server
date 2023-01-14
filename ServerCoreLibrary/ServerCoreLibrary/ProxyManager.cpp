#include "pch.h"
#include "ProxyManager.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include <chrono>

ProxyManager::ProxyManager(SERVER_TYPE type) : serverType(type) { ioContext = make_shared<asio::io_context>(); }

void ProxyManager::RunIoContext()
{
    std::chrono::time_point<std::chrono::system_clock> targetTime = std::chrono::system_clock::now();
    targetTime += std::chrono::seconds(10);
    ioContext->run();

    DWORD intervalTick = 5000;
    DWORD nextTickTime = GetTickCount() + intervalTick;
    DWORD prevTickTime = GetTickCount();

    while (true)
    {
        DWORD currentTime = GetTickCount();

        if (currentTime > nextTickTime)
        {
            float deltaTime = currentTime - prevTickTime;
            prevTickTime = currentTime;
            nextTickTime = currentTime + intervalTick;
            float deltaTimeInSec = deltaTime / 1000;
            if(DoReconnect())
            {
                ioContext->restart();
                ioContext->run();
            }
        }
    }
}

void ProxyManager::ConnectToMatchServer() { Connect("127.0.0.1", 4000, SERVER_TYPE::MATCH); }
void ProxyManager::ConnectToGameServer() { Connect("127.0.0.1", 5000, SERVER_TYPE::GAME); }

bool ProxyManager::SendToMatchServer(shared_ptr<SendBuffer> sendBuffer)
{
    return SendTo(sendBuffer, SERVER_TYPE::MATCH);
}
bool ProxyManager::SendToGameServer(shared_ptr<SendBuffer> sendBuffer) { return SendTo(sendBuffer, SERVER_TYPE::GAME); }

bool ProxyManager::SendTo(shared_ptr<SendBuffer> sendBuffer, SERVER_TYPE serverType)
{
    int type = (int)serverType;
    if (!proxyMap.count(type))
    {
        spdlog::error("[ProxyManager] Failed to send. Proxy info not found for server type {}", (int)serverType);
        return false;
    }

    if (proxyMap[type].size() == 0)
    {
        spdlog::error("[ProxyManager] Failed to send. No connected proxy for server type {}", (int)serverType);
        return false;
    }

    proxyMap[type][0]->Send(sendBuffer);
    return true;
}

void ProxyManager::Connect(string address, int port, SERVER_TYPE type)
{
    shared_ptr<Proxy> session = make_shared<Proxy>(type, ioContext);

    session->SetOnConnectCallback([&](shared_ptr<AsioSession> client) { OnConnect(client); });
    session->SetOnRecvCallback([&](shared_ptr<AsioSession> client, BYTE* buffer, int len)
                               { OnRecv(client, buffer, len); });

    session->SetOnDisconnectCallback([&](shared_ptr<AsioSession> client) { OnDisconnect(client); });
    session->SetConnectionInfo(address, port);
    session->Connect();
    AddProxy((int)type, session);
}

void ProxyManager::AddProxy(int type, shared_ptr<Proxy> session)
{
    session->SetOnRecvCallback([&](shared_ptr<AsioSession> client, BYTE* buffer, int len)
                               { OnRecv(client, buffer, len); });
    proxyMap[type].push_back(session);
}

void ProxyManager::OnRecv(shared_ptr<AsioSession> session, BYTE* buffer, int len)
{
    shared_ptr<Proxy> proxySession = dynamic_pointer_cast<Proxy>(session);
    if (!session)
    {
        return;
    }

    HandleRecv(proxySession, buffer, len);
}

void ProxyManager::OnConnect(shared_ptr<AsioSession> session)
{
    WRITE_LOCK;

    shared_ptr<Proxy> proxySession = dynamic_pointer_cast<Proxy>(session);
    if (!session)
    {
        return;
    }

    OnConnectCallback(proxySession, proxySession->GetServerType());
}

void ProxyManager::OnDisconnect(shared_ptr<AsioSession> session)
{
    WRITE_LOCK;

    shared_ptr<Proxy> proxySession = dynamic_pointer_cast<Proxy>(session);
    if (!proxySession)
    {
        return;
    }

    int serverType = (int)proxySession->GetServerType();
    spdlog::info("[ProxyManager] Proxy disconnected for server type {}", serverType);

    if (!proxyMap.count(serverType))
    {
        return;
    }

    // proxyMap 에서 삭제
    vector<shared_ptr<Proxy>>& proxyVec = proxyMap[serverType];
    vector<shared_ptr<Proxy>>::iterator iter = proxyVec.begin();
    while (iter != proxyVec.end())
    {
        if (proxySession == *iter)
        {
            vecDisconnectedProxy.push_back(proxySession);
            proxySession->socket.close();
            iter = proxyVec.erase(iter);
        }
    }

    return;
}

bool ProxyManager::DoReconnect()
{
    if(!vecDisconnectedProxy.size())
    {
        return false;
    }

    for (shared_ptr<Proxy> proxy : vecDisconnectedProxy)
    {
        string address = proxy->GetAddress();
        SERVER_TYPE type = proxy->GetServerType();
        int port = proxy->GetPort();
        Connect(address, port, type);
    }

    vecDisconnectedProxy.clear();

    return true;
}
