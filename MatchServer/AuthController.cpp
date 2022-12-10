#include "pch.h"
#include "AuthController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "LoginRequest.pb.h"
#include "LoginResponse.pb.h"
#include "Packet.h"
#include "Player.h"
#include "PacketId_AG_MT.h"
#include "TempClientManager.h"

AuthController::AuthController(sptr<TempClientManager> p_tempClientManager) : tempClientManager(p_tempClientManager)
{
    AddClientHandler((int)PacketId_AG_MT::Auth::LOGIN_REQ, TO_LAMBDA(HandleLoginRequest));
}

void AuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::LoginRequest pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    auto email = pkt.email();
    auto password = pkt.password();
    auto w_email = wstring(email.begin(), email.end());
}
