#pragma once
#include "Command.h"

class GameHost;

using namespace Command;

class CommandHandler
{
private:
    map<int, function<void(GameHost& host, sptr<ICommand>)>> commandHandler;

    //map<int, sptr<IInGameEvent>> CommandHandlerMap;

public:
    CommandHandler();
    void ProcessCommand(GameHost& host, sptr<ICommand> command);
private:
    /*  void HandleBuyCommand(GameHost& host, sptr<ICommand> command);
      void HandleSellCommand(GameHost& host, sptr<ICommand> command);*/
};
