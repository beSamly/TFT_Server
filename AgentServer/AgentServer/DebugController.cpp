#include "pch.h"
//#include "DebugController.h"
//#include "PacketId.h"
//
//DebugController::DebugController(sptr<GameSystem> p_gameSystem)
//{
//    gameSystem = p_gameSystem;
//
//    handlers[(int)PacketId::Debug::CREATE_DEBUG_MODE_HOST_REQ] = TO_LAMBDA(HandleCreateDebugModeHostRequest);
//}
//
//void DebugController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) {}
//
//void DebugController::HandleCreateDebugModeHostRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
//{
//    /*sptr<ICommand> command = make_shared< CreateDebugModeHostCommand>(session);
//    gameSystem->PushCommand(command);*/
//}
