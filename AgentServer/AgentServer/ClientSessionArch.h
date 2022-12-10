#pragma once
#include "pch.h"

#include "Session.h"
#include "Player.h"

/*-----------------
        ClientSession
------------------*/
//
//class ClientSession : public Session
//{
//public:
//    ClientSession();
//    virtual ~ClientSession();
//    function<void(sptr<ClientSession>, BYTE*, int32)> OnRecvCallback;
//    function<void(sptr<ClientSession>)> OnDisconnectCallback;
//    
//    sptr<ClientSession> GetClientSessionRef();
//
//private:
//    sptr<Player> _player;
//
//public:
//    sptr<Player> GetPlayer();
//    void SetPlayer(sptr<Player> player);
//
//private:
//    /* 인터페이스 구현 */
//    virtual void OnConnected() override;
//    virtual void OnDisconnected() override;
//    virtual void OnSend(int32 len) override;
//    virtual int32 OnRecv(BYTE* buffer, int32 len) override;
//
//private:
//    void OnRecvPacket(BYTE* buffer, int32 len);
//
//public:
//    /* 컨텐츠 로직 */
//    // void SendLoginResponse(Protocol::LoginResponse pkt);
//};
