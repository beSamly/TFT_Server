#include "pch.h"
#include "MatchSystem.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "PacketId_AG_MT.h"
#include "PlayerInfo.pb.h"
#include "MatchCancelResponse.pb.h"
#include "PacketId_MT_GM.h"
#include "HostCreateRequest.pb.h"
#include "MatchCreatedSend.pb.h"
#include "MatchRequestResponse.pb.h"

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
    commandHandler.emplace((int)N2M::CommandId::HOST_CREATED, TO_LAMBDA(HandleHostCreatedCommand));
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
        // 이미 매칭이된 유저라면 패스
        if (i_player->IsMatched())
            continue;

        // Todo pending match uid 지금은 rand로 생성하지만 나중에는 로직 필요
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

        // 매칭 성공!
        if (pendingMatch->IsFull())
        {
            OnPendingMatchCreated(pendingMatch);
            pendingMatchCreated.push_back(pendingMatch);
        }
        else
        {
            //더 이상 매칭될 수 없다.
            break;
        }
    }

    for (sptr<PendingMatch>& pendingMatch : pendingMatchCreated)
    {
        for (int playerId : pendingMatch->GetPlayerId())
        {
            spdlog::debug("[MatchSystem] PendingMatchCreated for playerId = {}", playerId);
            playerMap.erase(playerId);
        }
    }
    
    // 매칭된 유저들을 playerMap에서 삭제시킨뒤 플래그값 off
    for (const auto& [playerId, player] : playerMap)
    {
        player->SetUnmatched();
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

void MatchSystem::CancelPendingMatch(const sptr<PendingMatch>& match)
{
    vector<int> acceptedPlayerIds;
    vector<int> notAcceptedPlayerIds;
    for (const auto& [playerId, player] : match->GetPlayerMap())
    {
        playerToPendingMatchMap.erase(playerId);

        // 매칭 수락한 유저들은 다시 매칭 잡히도록 풀에 넣어준다.
        if (match->IsPlayerAccepted(playerId))
        {
            acceptedPlayerIds.push_back(playerId);

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

        // 매칭 수락한 안한 유저들은 매칭 취소로 간주.
        else
        {
            notAcceptedPlayerIds.push_back(playerId);
            if (sptr<Proxy> proxy = player->fromProxy.lock())
            {
                Protocol::MatchCancelResponse pkt;
                pkt.set_result(true);
                pkt.set_playerid(playerId);

                Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_RES);
                packet.WriteData<Protocol::MatchCancelResponse>(pkt);
                proxy->Send(packet.GetSendBuffer());
            }
        }
    };

    string acceptedPlayerStr;
    for (int playerId : acceptedPlayerIds)
    {
        acceptedPlayerStr += std::to_string(playerId) + ", ";
    }

    string notAcceptedPlayerStr;
    for (int playerId : notAcceptedPlayerIds)
    {
        notAcceptedPlayerStr += std::to_string(playerId) + ", ";
    }

    spdlog::debug("[MatchSystem] PendingMatchCanceled AcceptedPlayerId = {} NotAcceptedPlayerId = {}", acceptedPlayerStr, notAcceptedPlayerStr);
    pendingMatchPool.erase(match->GetMatchId());
}

void MatchSystem::OnPendingMatchCreated(const sptr<PendingMatch>& pendingMatch)
{
    // playerMap에서 삭제
    vector<int> playerIds = pendingMatch->GetPlayerId();
    int matchId = pendingMatch->GetMatchId();

    for (int playerId : playerIds)
    {
        // 일단 loop돌고있기 떄문에 playerMap에서 삭제하지 않고 플래그 값만 세팅.
        playerMap[playerId]->SetMatched();
        playerToPendingMatchMap.emplace(playerId, matchId);
    }

    // 클라이언트에게 매칭 생성 됐다고 보내기 - 나중에는 매칭서버로 따로 분리해야하기 떄문에 로직 변경 필요
    for (auto [playerId, player] : pendingMatch->GetPlayerMap())
    {
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
    // GameServer로 요청
    Protocol::HostCreateRequest req;
    req.set_matchid(pendingMatch->GetMatchId());
    for (auto& [playerId, player] : pendingMatch->GetPlayerMap())
    {
        req.add_playerid(playerId);
    }

    Packet packet((int)PacketId_MT_GM::Prefix::HOST, (int)PacketId_MT_GM::Host::HOST_CREATE_REQ);
    packet.WriteData<Protocol::HostCreateRequest>(req);

    // TODO 게임서버로 보내기 실패했다면 예외처리 필요
    bool result = proxyManager->SendToGameServer(packet.GetSendBuffer());
    if (result)
    {
        pendingMatch->SetWaitingForHost();
    }
    else
    {
        CancelPendingMatch(pendingMatch);
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

    int playerId = command->playerId;
    if(playerMap.count(playerId))
    {
        spdlog::error("[MatchSystem] Player has already requested for match playerId = {}", playerId);
        return;
    }

    sptr<MatchWaitPlayer> player = make_shared<MatchWaitPlayer>();
    player->fromProxy = command->proxy;
    player->playerId = playerId;
    playerMap.emplace(playerId, player);

    // 유저에게 응답
    if (sptr<Proxy> proxy = command->proxy.lock())
    {
        Protocol::MatchRequestResponse response;
        response.set_result(true);
        response.set_playerid(playerId);

        Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_REQ_RES);
        packet.WriteData<Protocol::MatchRequestResponse>(response);
        proxy->Send(packet.GetSendBuffer());
    }
}

void MatchSystem::HandleMatchCancelCommand(sptr<ICommand> p_command)
{
    sptr<MatchCancelCommand> command = dynamic_pointer_cast<MatchCancelCommand>(p_command);

    if (!command)
        return;

    // 매칭 기다리는 상태였을 수 있으니 Waiting list 에서 삭제
    int playerId = command->playerId;

    if (!playerMap.count(playerId)) {
        spdlog::error("[MatchSystem] Player info not found for canceling match playerId = {}", playerId);
    };

    spdlog::debug("Player Left matching pool playerId = {}", playerId);
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

    // 요청 보내온 에이전트서버에 응답
    Protocol::MatchCancelResponse res;
    res.set_result(true);
    res.set_playerid(playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_RES);
    packet.WriteData<Protocol::MatchCancelResponse>(res);
    if (sptr<Proxy> proxy = command->proxy.lock())
    {
        proxy->Send(packet.GetSendBuffer());
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

void MatchSystem::HandleHostCreatedCommand(sptr<ICommand> paramCommand)
{
    sptr<HostCreatedCommand> command = dynamic_pointer_cast<HostCreatedCommand>(paramCommand);

    if (!command)
        return;

    bool result = command->result;

    // TODO 호스트 생성에 실패했을 경우
    if (!result)
    {
        return;
    }

    int matchId = command->matchId;
    spdlog::debug("[MatchSystem] Host created for matchId = {}", matchId);

    if (!pendingMatchPool.count(matchId))
    {
        spdlog::error("[MatchSystem] Pending match for matchId {} not exist", matchId);
        return;
    }

    sptr<PendingMatch>& pendingMatch = pendingMatchPool[matchId];
    for (const auto& [playerId, player] : pendingMatch->GetPlayerMap())
    {
        playerToPendingMatchMap.erase(playerId);

        if (sptr<Proxy> proxy = player->fromProxy.lock())
        {
            Protocol::MatchCreatedSend pkt;
            pkt.set_result(result);
            pkt.set_playerid(playerId);
            pkt.set_address(command->address);
            pkt.set_port(command->port);

            Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CREATED_SEND);
            packet.WriteData<Protocol::MatchCreatedSend>(pkt);
            proxy->Send(packet.GetSendBuffer());
        }
    }

    pendingMatchPool.erase(matchId);
}
