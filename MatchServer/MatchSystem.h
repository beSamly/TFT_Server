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
	void DoMatching();
	void UpdatePendingMatch(float deltaTime);
	void CancelPendingMatch(const sptr<PendingMatch>& match);
	void OnPendingMatchCreated(const sptr<PendingMatch>& pendingMatch); // 임시 매칭이 성공 됐을 때
	void OnPendingMatchReady(const sptr<PendingMatch>& pendingMatch); // 모두 매칭을 수락했을 때

private:
	void HandleMatchRequestCommand(sptr<ICommand> command);
	void HandleMatchCancelCommand(sptr<ICommand> command);
	void HandleMatchAcceptCommand(sptr<ICommand> command);
	void HandleMatchDeclineCommand(sptr<ICommand> command);
	void HandleHostCreatedCommand(sptr<ICommand> command);
};
