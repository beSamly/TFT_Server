#include "pch.h"
#include "SocketServer.h"
#include "ClientSession.h"
#include "spdlog/spdlog.h"
//
//bool SocketServer::Start()
//{
//    if (StartAccept() == false)
//        return false;
//
//    return true;
//}
//
//void SocketServer::Close()
//{
//    // TODO
//    CloseSocket();
//}
//
//void SocketServer::AddSession(SessionRef session)
//{
//    WRITE_LOCK;
//    _sessionCount++;
//    // TODO ���࿡ SocketServer���� ���۷��� ������ �� �ϸ� SessionŬ������ SOCKET�� �������
//    // recv data �� �ϳ�?
//    _sessions.insert(session);
//}
//
//void SocketServer::ReleaseSession(SessionRef session)
//{
//    WRITE_LOCK;
//    ASSERT_CRASH(_sessions.erase(session) != 0);
//    _sessionCount--;
//}
//
///*---------------------
//         �������̽� ����
//----------------------*/
//SessionRef SocketServer::CreateSession()
//{
//    auto session = MakeShared<ClientSession>();
//
//    session->SetOwner(std::static_pointer_cast<BaseSocketServer>(shared_from_this()));
//    session->OnRecvCallback = OnClientRecv;
//    session->OnDisconnectCallback = OnClientDisconnect;
//    
//    if (_iocpCore->Register(session) == false)
//        return nullptr;
//
//    return std::static_pointer_cast<Session>(session);
//}
//
//// BaseSocketServer���� ProcessAccept() ȣ�� �ÿ� �̺�Ʈ �߻�
//void SocketServer::OnConnected(SessionRef session)
//{
//    spdlog::debug("Session connected");
//    AddSession(session);
//    OnClientConnect(std::static_pointer_cast<ClientSession>(session));
//}
//
//// Session ���� ProcessDisconnect() ȣ�� �ÿ� �̺�Ʈ �߻�
//void SocketServer::OnDisconnected(SessionRef session)
//{
//    spdlog::debug("Session disconnected");
//    ReleaseSession(session);
//}