#pragma once
#include "Command.h"

class GameHost;

using namespace Command;

class GameHostCommandHandler
{
private:
	map<int, function<void(GameHost& host, sptr<ICommand>)>> commandHandler;
	//map<int, sptr<IInGameEvent>> GameHostCommandHandlerMap;

public:
	GameHostCommandHandler();
	void ProcessCommand(GameHost& host, sptr<ICommand> command);
private:
	void HandleChampBuyCommand(GameHost& host, sptr<ICommand> command);
	void HandleChampSellCommand(GameHost& host, sptr<ICommand> command);
	void HandleChampLocateCommand(GameHost& host, sptr<ICommand> command);
	void HandleHostCreateCommand(GameHost& host, sptr<ICommand> command);
};
