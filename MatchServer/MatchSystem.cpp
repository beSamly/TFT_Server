#include "pch.h"
#include "MatchSystem.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "PacketId.h"
#include "Packet.h"

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
	DWORD intervalTick = 3000; // 일단 10초에 한 번씩
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

void MatchSystem::CreatePendingMatch()
{
	spdlog::debug("[MatchSystem] waiting for match = {}", playerMap.size());
	if (playerMap.size() < playerPerMatch)
	{
		return;
	}

	vector<int> removePlayerIds;
	for (const auto& [i_playerId, i_player] : playerMap)
	{
		// 이미 매칭이된 유저라면 패스
		if (i_player->IsMatched())
			continue;

		sptr<PendingMatch> pendingMatch = make_shared<PendingMatch>(playerPerMatch);
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

		// 매칭 성공!
		if (pendingMatch->IsFull())
		{
			// playerMap에서 삭제
			vector<int> playerIds = pendingMatch->GetPlayerId();
			int matchId = pendingMatch->GetMatchId();

			for (int playerId : playerIds)
			{
				// 일단 삭제하지 않는다.
				// playerMap.erase(playerId);
				removePlayerIds.push_back(playerId);
				playerMap[playerId]->SetMatched();
				playerToPendingMatchMap.emplace(playerId, matchId);
			}

			pendingMatchPool.emplace(matchId, pendingMatch);
		}
		else
		{
			//더 이상 매칭될 수 없다.
			break;
		}
	}

	for (const auto& [playerId, player] : playerMap)
	{
		player->SetUnmatched();
	}

	for (int playerId : removePlayerIds)
	{
		// TODO 클라이언트에게 매칭 생성 됐다고 보내기 - 나중에는 매칭서버로 따로 분리해야하기 떄문에 로직 변경 필요
		if (sptr<ClientSession> client = playerMap[playerId]->client.lock())
		{
			Packet packet((int)PacketId::Prefix::MATCH, (int)PacketId::Match::PENDING_MATCH_CREATED_SEND);
			packet.WriteData();
			client->Send(packet.ToSendBuffer());
		}
		playerMap.erase(playerId);
	}
}

void MatchSystem::UpdatePendingMatch(float deltaTime)
{
	spdlog::debug("[MatchSystem] number of pending match = {}", pendingMatchPool.size());
	vector<int> removePendingMatchIds;
	for (auto& [matchId, pendingMatch] : pendingMatchPool)
	{
		pendingMatch->Update(deltaTime);

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
			// todo GameSystem으로 날리기
			/*sptr<ICommand> command = make_shared<CreateDebugModeHostCommand>(session);
			gameSystem->PushCommand(command);
			continue;*/
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

		// 매칭 수락한 유저들은 다시 매칭 잡히도록 풀에 넣어준다.
		if (match->IsPlayerAccepted(playerId))
		{
			playerMap.emplace(playerId, player);
		}

		// 매칭 수락한 안한 유저들은 마시 매칭 요청 보내도록 한다.
		else
		{
			if (sptr<ClientSession> client = player->client.lock())
			{
				Packet packet((int)PacketId::Prefix::MATCH, (int)PacketId::Match::MATCH_CANCEL_RES);
				packet.WriteData();
				client->Send(packet.ToSendBuffer());
			}
		}
	};
	pendingMatchPool.erase(match->GetMatchId());
}

void MatchSystem::Update(float deltaTime)
{
	ProcessCommand();
	UpdatePendingMatch(deltaTime);
	CreatePendingMatch();
}

void MatchSystem::HandleMatchRequestCommand(sptr<ICommand> p_command)
{
	sptr<MatchRequestCommand> command = dynamic_pointer_cast<MatchRequestCommand>(p_command);

	if (command != nullptr)
	{
		if (sptr<ClientSession> client = command->client.lock())
		{
			int playerId = client->GetPlayer()->playerId;
			sptr<MatchWaitPlayer> player = make_shared<MatchWaitPlayer>();
			player->client = client;
			playerMap.emplace(playerId, player);
		}
	}
}

void MatchSystem::HandleMatchCancelCommand(sptr<ICommand> p_command)
{
	sptr<MatchCancelCommand> command = dynamic_pointer_cast<MatchCancelCommand>(p_command);

	if (!command)
		return;

	// 매칭 기다리는 상태였을 수 있으니 Waiting list 에서 삭제
	int playerId = command->playerId;
	playerMap.erase(playerId);

	// Pending 매칭이 잡힌 상태였다면
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
		if (sptr<ClientSession> client = command->client.lock())
		{
		}
	}
}

void MatchSystem::HandleMatchDeclineCommand(sptr<ICommand> p_command)
{
	sptr<MatchDeclineCommand> command = dynamic_pointer_cast<MatchDeclineCommand>(p_command);

	if (!command)
	{
		if (sptr<ClientSession> client = command->client.lock())
		{
		}
	}
};