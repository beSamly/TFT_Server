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
#include "PacketId_MT_GM.h"
#include "PacketId_CL_GM.h"

CAuthController::CAuthController(sptr<TempClientManager> p_tempClientManager) : tempClientManager(p_tempClientManager)
{
    AddClientHandler((int)PacketId_CL_GM::Auth::LOGIN_REQ, TO_LAMBDA(HandleLoginRequest));
}

void CAuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::LoginRequest pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    auto email = pkt.email();
    auto password = pkt.password();
    auto w_email = wstring(email.begin(), email.end());
}

ProxyAuthController::ProxyAuthController(sptr<TempClientManager> p_tempClientManager)
    : tempClientManager(p_tempClientManager)
{
    AddClientHandler((int)PacketId_MT_GM::Auth::LOGIN_REQ, TO_LAMBDA(HandleLoginRequest));
}

void ProxyAuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::LoginRequest pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    auto email = pkt.email();
    auto password = pkt.password();
    auto w_email = wstring(email.begin(), email.end());
}
