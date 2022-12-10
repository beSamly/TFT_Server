#include "pch.h"
#include "IPacketController.h"
#include "IController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"

void IPacketController::HandleClientPacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto prefix = header->prefix;

    sptr<IController> controller = controllerMap[prefix];

    if (controller)
    {
        controller->HandleClientPacket(session, buffer, len);
    }
    else
    {
        spdlog::error("[PacketController] invalid prefix = {}", prefix);
    }
}

void IPacketController::HandleProxyPacket(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto prefix = header->prefix;

    sptr<IController> controller = controllerMap[prefix];

    if (controller)
    {
        controller->HandleProxyPacket(session, buffer, len);
    }
    else
    {
        spdlog::error("[PacketController] invalid prefix = {}", prefix);
    }
}
