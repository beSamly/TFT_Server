#include "pch.h"
#include "IController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"

void IController::AddClientHandler(int key,
                                   function<void(sptr<ClientSession>& client, BYTE* buffer, int32 len)> handler)
{
    clientHandlers[key] = handler;
}

void IController::AddProxyHandler(int key, function<void(sptr<Proxy>& client, BYTE* buffer, int32 len)> handler)
{
    proxyHandlers[key] = handler;
}

void IController::HandleClientPacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto packetId = header->id;

    if (clientHandlers[packetId])
    {
        clientHandlers[packetId](session, buffer, len);
    }
    else
    {
        spdlog::error("[CAuthController] invalid packetId = {}", packetId);
    }
}

void IController::HandleProxyPacket(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto packetId = header->id;

    if (proxyHandlers[packetId])
    {
        proxyHandlers[packetId](session, buffer, len);
    }
    else
    {
        spdlog::error("[CAuthController] invalid packetId = {}", packetId);
    }
}
