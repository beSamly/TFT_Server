#include "pch.h"
#include "ProxyManager.h"
#include "spdlog/spdlog.h"
#include "Packet.h"

ProxyManager::ProxyManager(SERVER_TYPE type) : serverType(type) { ioContext = make_shared<asio::io_context>(); }

void ProxyManager::ConnectToMatchServer() { Connect("127.0.0.1", 4000, SERVER_TYPE::MATCH); }
void ProxyManager::ConnectToGameServer() { Connect("127.0.0.1", 5000, SERVER_TYPE::GAME); }

void ProxyManager::SendToMatchServer(shared_ptr<SendBuffer> sendBuffer) { SendTo(sendBuffer, SERVER_TYPE::MATCH); }
void ProxyManager::SendToGameServer(shared_ptr<SendBuffer> sendBuffer) { SendTo(sendBuffer, SERVER_TYPE::GAME); }

void ProxyManager::SendTo(shared_ptr<SendBuffer> sendBuffer, SERVER_TYPE serverType)
{
    int type = (int)serverType;
    if (!proxyMap.count(type))
    {
        return;
    }

    if (proxyMap[type].size() == 0)
    {
        return;
    }

    proxyMap[type][0]->Send(sendBuffer);
}

void ProxyManager::Connect(string address, int port, SERVER_TYPE type)
{
    shared_ptr<Proxy> session = make_shared<Proxy>(type, ioContext);

    session->SetOnConnectCallback([&](shared_ptr<AsioSession> client) { OnConnect(client); });
    session->SetOnRecvCallback([&](shared_ptr<AsioSession> client, BYTE* buffer, int len)
                               { OnRecv(client, buffer, len); });

    session->SetOnDisconnectCallback([&](shared_ptr<AsioSession> client) { OnDisconnect(client); });
    session->Connect(address, port);
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
    shared_ptr<Proxy> proxySession = dynamic_pointer_cast<Proxy>(session);
    if (!session)
    {
        return;
    }

    OnConnectCallback(proxySession, proxySession->GetServerType());
}

void ProxyManager::OnDisconnect(shared_ptr<AsioSession> session)
{
    shared_ptr<Proxy> proxySession = dynamic_pointer_cast<Proxy>(session);
    if (!proxySession)
    {
        return;
    }

    // proxyMap ���� ����

    return;
}
