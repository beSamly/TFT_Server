#include "pch.h"
#include "AuthController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "LoginRequest.pb.h"
#include "LoginResponse.pb.h"
#include "Packet.h"
#include "Player.h"
#include "PacketId_Common.h"
#include "TempClientManager.h"
#include "ProxyLoginReq.pb.h"

AuthController::AuthController(sptr<TempClientManager> p_tempClientManager, sptr<ProxyManager> p_proxyManager)
    : tempClientManager(p_tempClientManager), proxyManager(p_proxyManager)
{
    AddClientHandler((int)PacketId_Common::Auth::PROXY_LOGIN_REQ, TO_LAMBDA(HandleProxyLoginReq));
}

void AuthController::HandleProxyLoginReq(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::ProxyLoginReq pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int serverType = pkt.servertype();

    // ClientSession => Proxy로 변환 후 ProxyManager에 추가
    sptr<Proxy> proxy = make_shared<Proxy>(serverType, std::move(session->socket));
    proxy->Start();
    proxyManager->AddProxy(serverType, proxy);
  
    session->socket.close();

    // TempClientManager에서 삭제
    tempClientManager->RemoveClient(session->proxyId);
}
