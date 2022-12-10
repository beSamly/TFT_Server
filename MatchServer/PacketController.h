#pragma once
#include "IPacketHandler.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "PlayerManager.h"
#include "MatchSystem.h"

using std::function;
using std::map;

class PacketController
{
private:
	std::map<int, sptr<IController>> controllerMap;

public:
	PacketController(sptr<MatchSystem> matchSystem);
	~PacketController();
	void Init();

	void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len);

	template <typename T>
	static SendBufferRef PacketToSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = MakeShared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());

		header->size = packetSize;
		header->id = pktId;

		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};
