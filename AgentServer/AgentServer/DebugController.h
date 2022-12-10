//#pragma once
//#include "IController.h"
//#include "GameSystem.h"
//
//class DebugController : public IController
//{
//private:
//    map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;
//    sptr<GameSystem> gameSystem;
//
//public:
//    DebugController(sptr<GameSystem> gameSystem);
//
//    void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;
//
//private:
//    void HandleCreateDebugModeHostRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
//};
