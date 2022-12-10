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
		// ������ ����� ��� ������ ���� ���� �� ����
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		// ����� ��ϵ� ��Ŷ ũ�⸦ �Ľ��� �� �־�� �Ѵ�
		if (dataSize < header.size)
			break;

		// ��Ŷ ���� ����
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
