#include "pch.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "PacketId.h"
#include "spdlog/spdlog.h"
//
//ClientSession::ClientSession() {}
//
//ClientSession::~ClientSession() { spdlog::debug("[ClientSession] deconstructed"); }
//
//sptr<ClientSession> ClientSession::GetClientSessionRef()
//{
//    return static_pointer_cast<ClientSession>(shared_from_this());
//}
//
//int32 ClientSession::OnRecv(BYTE* buffer, int32 len)
//{
//    int32 processLen = 0;
//
//    while (true)
//    {
//        int32 dataSize = len - processLen;
//        // 데이터 사이즈가 헤더 사이즈 보다 작을 순 없다
//        if (dataSize < sizeof(PacketHeader))
//            break;
//
//        PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
//        // 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
//        if (dataSize < header.size)
//            break;
//
//        // 패킷 조립 성공
//        OnRecvPacket(&buffer[processLen], header.size);
//
//        processLen += header.size;
//    }
//
//    return processLen;
//}
//
//void ClientSession::OnConnected() {}
//
//void ClientSession::OnDisconnected()
//{
//    OnDisconnectCallback(this->GetClientSessionRef());
//}
//
//void ClientSession::OnRecvPacket(BYTE* buffer, int32 len)
//{
//    // 아래 과정을 server system 에서 하자
//    /*PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
//    auto packetId = header->id;
//    auto session = this->GetClientSessionRef();*/
//    OnRecvCallback(this->GetClientSessionRef(), buffer, len);
//}
//
//void ClientSession::OnSend(int32 len) {}
//
//sptr<Player> ClientSession::GetPlayer() { return _player; }
//
//void ClientSession::SetPlayer(sptr<Player> player) { _player = player; }
