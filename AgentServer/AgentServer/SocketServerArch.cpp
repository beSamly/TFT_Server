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
//    // TODO 만약에 SocketServer에서 래퍼런스 저장을 안 하면 Session클래스의 SOCKET이 사라져서
//    // recv data 못 하나?
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
//         인터페이스 구현
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
//// BaseSocketServer에서 ProcessAccept() 호출 시에 이벤트 발생
//void SocketServer::OnConnected(SessionRef session)
//{
//    spdlog::debug("Session connected");
//    AddSession(session);
//    OnClientConnect(std::static_pointer_cast<ClientSession>(session));
//}
//
//// Session 에서 ProcessDisconnect() 호출 시에 이벤트 발생
//void SocketServer::OnDisconnected(SessionRef session)
//{
//    spdlog::debug("Session disconnected");
//    ReleaseSession(session);
//}