#include "pch.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"


ClientSession::ClientSession(sptr<asio::io_context> context) : AsioSession(context)
{

}

ClientSession::~ClientSession()
{
	spdlog::debug("[ClientSession] deconstructed");
}

sptr<ClientSession> ClientSession::GetClientSessionRef()
{
	return static_pointer_cast<ClientSession>(shared_from_this());
}

int ClientSession::OnRecv(BYTE* buffer, int len)
{
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// 데이터 사이즈가 헤더 사이즈 보다 작을 순 없다
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		// 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
		if (dataSize < header.size)
			break;

		// 패킷 조립 성공
		OnRecvCallback(this->GetClientSessionRef(), &buffer[processLen], header.size);
		processLen += header.size;
	}

	return processLen;
}

void ClientSession::OnConnect()
{
	OnConnectCallback(this->GetClientSessionRef());
}

void ClientSession::OnDisconnect()
{
	OnDisconnectCallback(this->GetClientSessionRef());
}

sptr<Player> ClientSession::GetPlayer() { return player; }

void ClientSession::SetPlayer(sptr<Player> p_player) { player = p_player; }
