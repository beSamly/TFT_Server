#pragma once;
#include "ClientSession.h"
#include "MatchWaitPlayer.h"
#include "PendingMatch.h"
#include "Command.h"
#include "ProxyManager.h"

using namespace Command;

class MatchSystem
{
private:
    sptr<ProxyManager> proxyManager;

    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;
    map<int, sptr<MatchWaitPlayer>> playerMap;
    map<int, int> playerToPendingMatchMap;
    map<int, sptr<PendingMatch>> pendingMatchPool;
    int playerPerMatch = 2;

public:
    MatchSystem();
    void Run();
    void PushCommand(sptr<ICommand> command);
    void SetProxyManager(sptr<ProxyManager> p_proxyMangaer) { proxyManager = p_proxyMangaer; }

private:
    USE_LOCK;
    void Update(float deltaTime);
    queue<sptr<ICommand>> FlushQueue();
    void ProcessCommand();
    void CreatePendingMatch();
    void UpdatePendingMatch(float deltaTime);
    void CancelPendingMatch(sptr<PendingMatch>& match);

private:
    void HandleMatchRequestCommand(sptr<ICommand> command);
    void HandleMatchCancelCommand(sptr<ICommand> command);
    void HandleMatchAcceptCommand(sptr<ICommand> command);
    void HandleMatchDeclineCommand(sptr<ICommand> command);
};
