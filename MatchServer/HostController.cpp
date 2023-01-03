#include "pch.h"
#include "HostController.h"
#include "MatchSystem.h"
#include "PacketHeader.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "PacketId_MT_GM.h"
#include "CreateHostResponse.pb.h"

HostController::HostController(sptr<MatchSystem> p_matchSystem) : matchSystem(p_matchSystem)
{
	AddProxyHandler((int)PacketId_MT_GM::Host::CREATE_HOST_REQ, TO_LAMBDA_FOR_PROXY(HandleHostCreateRes));
}

void HostController::HandleHostCreateRes(sptr<Proxy>& proxy, BYTE* buffer, int32 len)
{
	Protocol::CreateHostResponse res;
	if (res.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	// 매칭 시스템에 알림
	sptr<N2M::CreateHostResCommand> command = make_shared<N2M::CreateHostResCommand>(proxy);
	command->result = res.result();
	command->matchId = res.matchid();
	matchSystem->PushCommand(command);
}
