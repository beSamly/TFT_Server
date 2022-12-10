#pragma once
#include "PacketHeader.h"
#include "SendBuffer.h"

class Packet
{
public:
	Packet(int p_prefix, int packetId) : prefix(p_prefix), packet_id(packetId) {}

private:
	int packet_id;
	int prefix;
	std::shared_ptr<SendBuffer> send_buffer;

public:
	template <typename T>
	void WriteData(T& pkt);
	void WriteData();
	int GetSize() { return send_buffer->WriteSize(); }

	std::shared_ptr<SendBuffer> ToSendBuffer() { return send_buffer; };
	BYTE* GetByteBuffer() { return send_buffer->GetBuffer(); }
};

template <typename T>
inline void Packet::WriteData(T& pkt)
{
	const int dataSize = static_cast<int>(pkt.ByteSizeLong());
	const int packetSize = dataSize + sizeof(PacketHeader);

	send_buffer = MakeShared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(send_buffer->Buffer());

	header->size = packetSize;
	header->prefix = prefix;
	header->id = packet_id;

	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	send_buffer->Close(packetSize);
}
