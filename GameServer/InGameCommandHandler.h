#pragma once
#include "Command.h"

class GameHost;

using namespace Command;

class InGameCommandHandler
{
private:
	map<int, function<void(GameHost& host, sptr<ICommand>)>> commandHandler;

	//map<int, sptr<IInGameEvent>> InGameCommandHandlerMap;

public:
	InGameCommandHandler();
	void ProcessCommand(GameHost& host, sptr<ICommand> command);
private:
	/*  void HandleBuyCommand(GameHost& host, sptr<ICommand> command);*/
	void HandleHostCreateCommand(GameHost& host, sptr<ICommand> command);
};
