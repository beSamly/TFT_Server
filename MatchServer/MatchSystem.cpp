#include "pch.h"
#include "MatchSystem.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "PacketId_AG_MT.h"
#include "PlayerInfo.pb.h"
#include "MatchCancelResponse.pb.h"
#include "PacketId_MT_GM.h"
#include "CreateHostRequest.pb.h"

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

using namespace Command::N2M;

MatchSystem::MatchSystem()
{
	commandHandler.emplace((int)N2M::CommandId::MATCH_REQUEST, TO_LAMBDA(HandleMatchRequestCommand));
	commandHandler.emplace((int)N2M::CommandId::MATCH_CANCEL, TO_LAMBDA(HandleMatchCancelCommand));
	commandHandler.emplace((int)N2M::CommandId::MATCH_ACCEPT, TO_LAMBDA(HandleMatchAcceptCommand));
	commandHandler.emplace((int)N2M::CommandId::MATCH_DECLINE, TO_LAMBDA(HandleMatchDeclineCommand));
}

void MatchSystem::Run()
{
	DWORD intervalTick = 3000; // �ϴ� 10�ʿ� �� ����
	DWORD nextTickTime = GetTickCount() + intervalTick;
	DWORD prevTickTime = GetTickCount();

	while (true)
	{
		DWORD currentTime = GetTickCount();

		if (currentTime > nextTickTime)
		{
			float deltaTime = currentTime - prevTickTime;
			prevTickTime = currentTime;
			nextTickTime = currentTime + intervalTick;
			float deltaTimeInSec = deltaTime / 1000;
			Update(deltaTimeInSec);
		}
	}
}

void MatchSystem::PushCommand(sptr<ICommand> command)
{
	WRITE_LOCK;
	commandQueue.push(command);
}

queue<sptr<ICommand>> MatchSystem::FlushQueue()
{
	WRITE_LOCK;
	queue<sptr<ICommand>> copied;

	while (!commandQueue.empty())
	{
		copied.push(commandQueue.front());
		commandQueue.pop();
	}

	return copied;
}

void MatchSystem::ProcessCommand()
{
	queue<sptr<ICommand>> copied = FlushQueue();

	while (!copied.empty())
	{
		sptr<ICommand> command = copied.front();
		int commandId = command->GetCommandId();
		if (commandHandler[commandId])
		{
			commandHandler[commandId](command);
		}
		copied.pop();
	}
}

void MatchSystem::DoMatching()
{
	spdlog::debug("[MatchSystem] waiting for match = {}", playerMap.size());
	if (playerMap.size() < playerPerMatch)
	{
		return;
	}

	vector<sptr<PendingMatch>> pendingMatchCreated;
	for (const auto& [i_playerId, i_player] : playerMap)
	{
		// �̹� ��Ī�̵� ������� �н�
		if (i_player->IsMatched())
			continue;

		// Todo pending match uid ������ rand�� ���������� ���߿��� ���� �ʿ�
		sptr<PendingMatch> pendingMatch = make_shared<PendingMatch>(playerPerMatch, rand());
		pendingMatch->AddPlayer(i_playerId, i_player);

		for (const auto& [j_playerId, j_player] : playerMap)
		{

			if (i_playerId == j_playerId)
			{
				continue;
			}

			if (j_player->IsMatched())
			{
				continue;
			}

			pendingMatch->AddPlayer(j_playerId, j_player);
			if (pendingMatch->IsFull())
			{
				break;
			}
		}

		// ��Ī ����!
		if (pendingMatch->IsFull())
		{
			OnPendingMatchCreated(pendingMatch);
		}
		else
		{
			//�� �̻� ��Ī�� �� ����.
			break;
		}
	}

	for (const auto& [playerId, player] : playerMap)
	{
		player->SetUnmatched();
	}

	for (sptr<PendingMatch>& pendingMatch : pendingMatchCreated) {
		for (int playerId : pendingMatch->GetPlayerId())
		{
			spdlog::debug("[MatchSystem] pendingMatchCreated for playerId = {}", playerId);
			playerMap.erase(playerId);
		}
	}
}

void MatchSystem::UpdatePendingMatch(float deltaTime)
{
	spdlog::debug("[MatchSystem] number of pending match = {}", pendingMatchPool.size());
	vector<int> removePendingMatchIds;
	for (auto& [matchId, pendingMatch] : pendingMatchPool)
	{
		pendingMatch->Update(deltaTime);

		if (pendingMatch->IsWaitingForHost())
		{
			continue;
		}

		if (pendingMatch->IsCanceled())
		{
			removePendingMatchIds.push_back(matchId);
			continue;
		}

		if (pendingMatch->IsExpired())
		{
			removePendingMatchIds.push_back(matchId);
			continue;
		}

		if (pendingMatch->IsReady())
		{
			OnPendingMatchReady(pendingMatch);
			continue;
		}
	}

	for (int matchId : removePendingMatchIds)
	{
		CancelPendingMatch(pendingMatchPool[matchId]);
	}
}

void MatchSystem::CancelPendingMatch(sptr<PendingMatch>& match)
{
	for (const auto& [playerId, player] : match->GetPlayerMap())
	{
		playerToPendingMatchMap.erase(playerId);

		// ��Ī ������ �������� �ٽ� ��Ī �������� Ǯ�� �־��ش�.
		if (match->IsPlayerAccepted(playerId))
		{
			spdlog::debug("[MatchSystem] pendingMatchCanceled for playerId = {}", playerId);
			playerMap.emplace(playerId, player);

			if (sptr<Proxy> proxy = player->fromProxy.lock())
			{
				Protocol::PlayerInfo pkt;
				pkt.set_playerid(playerId);

				Packet packet((int)PacketId_AG_MT::Prefix::MATCH,
					(int)PacketId_AG_MT::Match::PENDING_MATCH_CANCELED_SEND);
				packet.WriteData<Protocol::PlayerInfo>(pkt);
				proxy->Send(packet.GetSendBuffer());
			}
		}

		// ��Ī ������ ���� �������� ��Ī ��ҷ� ����.
		else
		{
			spdlog::debug("[MatchSystem] playerId {} did not accept pending match", playerId);
			if (sptr<Proxy> proxy = player->fromProxy.lock())
			{
				Protocol::MatchCancelResponse pkt;
				pkt.set_result(true);
				pkt.set_playerid(player->playerId);

				Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_RES);
				packet.WriteData<Protocol::MatchCancelResponse>(pkt);
				proxy->Send(packet.GetSendBuffer());
			}
		}
	};
	pendingMatchPool.erase(match->GetMatchId());
}

void MatchSystem::OnPendingMatchCreated(const sptr<PendingMatch>& pendingMatch)
{
	// playerMap���� ����
	vector<int> playerIds = pendingMatch->GetPlayerId();
	int matchId = pendingMatch->GetMatchId();

	for (int playerId : playerIds)
	{
		// �ϴ� �������� �ʴ´�.
		playerMap[playerId]->SetMatched();
		playerToPendingMatchMap.emplace(playerId, matchId);
	}

	// Ŭ���̾�Ʈ���� ��Ī ���� �ƴٰ� ������ - ���߿��� ��Ī������ ���� �и��ؾ��ϱ� ������ ���� ���� �ʿ�
	for (auto [playerId, player] : pendingMatch->GetPlayerMap()) {
		if (sptr<Proxy> proxy = player->fromProxy.lock())
		{
			Protocol::PlayerInfo pkt;
			pkt.set_playerid(playerId);

			Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::PENDING_MATCH_CREATED_SEND);
			packet.WriteData<Protocol::PlayerInfo>(pkt);
			proxy->Send(packet.GetSendBuffer());
		}

	};

	pendingMatchPool.emplace(pendingMatch->GetMatchId(), pendingMatch);
}

void MatchSystem::OnPendingMatchReady(const sptr<PendingMatch>& pendingMatch)
{
	// GameServer�� ��û
	Protocol::CreateHostRequest req;
	req.set_matchid(pendingMatch->GetMatchId());
	for (auto& [playerId, player] : pendingMatch->GetPlayerMap())
	{
		req.add_playerid(playerId);
	}

	Packet packet((int)PacketId_MT_GM::Prefix::GAME, (int)PacketId_MT_GM::Host::CREATE_HOST_REQ);
	packet.WriteData<Protocol::CreateHostRequest>(req);

	// TODO ���Ӽ����� ������ �����ߴٸ� ����ó�� �ʿ�
	bool result = proxyManager->SendToGameServer(packet.GetSendBuffer());
	if (result) {
		pendingMatch->SetWaitingForHost();
	}
}

void MatchSystem::Update(float deltaTime)
{
	ProcessCommand();
	UpdatePendingMatch(deltaTime);
	DoMatching();
}

void MatchSystem::HandleMatchRequestCommand(sptr<ICommand> p_command)
{
	sptr<MatchRequestCommand> command = dynamic_pointer_cast<MatchRequestCommand>(p_command);

	if (command == nullptr)
	{
		return;
	}

	if (sptr<Proxy> proxy = command->proxy.lock())
	{
		int playerId = command->playerId;
		sptr<MatchWaitPlayer> player = make_shared<MatchWaitPlayer>();
		player->fromProxy = proxy;
		player->playerId = playerId;
		playerMap.emplace(playerId, player);
	}
}

void MatchSystem::HandleMatchCancelCommand(sptr<ICommand> p_command)
{
	sptr<MatchCancelCommand> command = dynamic_pointer_cast<MatchCancelCommand>(p_command);

	if (!command)
		return;

	// ��Ī ��ٸ��� ���¿��� �� ������ Waiting list ���� ����
	int playerId = command->playerId;
	playerMap.erase(playerId);

	// Pending ��Ī�� ���� ���¿��ٸ�
	if (playerToPendingMatchMap.count(playerId))
	{
		int pendingMatchId = playerToPendingMatchMap[playerId];
		if (pendingMatchPool.count(pendingMatchId))
		{
			pendingMatchPool[pendingMatchId]->PlayerCancel(playerId);
		}
	}
}

void MatchSystem::HandleMatchAcceptCommand(sptr<ICommand> p_command)
{
	sptr<MatchAcceptCommand> command = dynamic_pointer_cast<MatchAcceptCommand>(p_command);

	if (!command)
	{
		return;
	}

	int playerId = command->playerId;
	spdlog::debug("[MatchSystem] playerId = {} accepted pending match", playerId);

	int pendingMatchId = playerToPendingMatchMap.count(playerId) ? playerToPendingMatchMap[playerId] : 0;

	if (!pendingMatchPool.count(pendingMatchId))
	{
		return;
	}

	pendingMatchPool[pendingMatchId]->PlayerAccept(playerId);
}

void MatchSystem::HandleMatchDeclineCommand(sptr<ICommand> p_command)
{
	sptr<MatchDeclineCommand> command = dynamic_pointer_cast<MatchDeclineCommand>(p_command);

	if (!command)
	{
		if (sptr<Proxy> proxy = command->proxy.lock())
		{
		}
	}
};