#pragma once
#include "ClientSession.h"

namespace Command
{
	class ICommand
	{
	public:
		wptr<ClientSession> client;
		wptr<Proxy> proxy;
		int commandId;

	public:
		ICommand() {};
		ICommand(wptr<ClientSession> p_client) : client(p_client) {};
		ICommand(wptr<Proxy> paramProxy) : proxy(paramProxy) {};
		virtual int GetCommandId() { return commandId; };
	};

	/*-----------------------------------
		NetworkSystem To GameSystem
	-------------------------------------*/
	namespace N2G {
		enum CommandId {
			BUY_COMMAND = 1,
			CREATE_HOST,
			CREATE_DEBUG_MODE_HOST
		};

		class BuyCommand : public ICommand
		{
		public:
			BuyCommand(wptr<ClientSession> p_client, int p_champUid) : champUid(p_champUid), ICommand(p_client)
			{
				ICommand::commandId = CommandId::BUY_COMMAND;
			};

		public:
			int champUid;
		};

		class LocateToFieldCommand : public ICommand
		{
		public:
			int fieldIndex;

		public:
			LocateToFieldCommand(wptr<ClientSession> p_client, int p_fieldIndex)
				: fieldIndex(p_fieldIndex), ICommand(p_client) {};
		};

		class LocateToBenchCommand : public ICommand
		{
		public:
			int benchIndex;

		public:
			LocateToBenchCommand(wptr<ClientSession> p_client, int p_benchIndex)
				: benchIndex(p_benchIndex), ICommand(p_client) {};
		};

		class CreateDebugModeHostCommand : public ICommand
		{

		public:
			CreateDebugModeHostCommand(wptr<ClientSession> p_client) : ICommand(p_client) {};
		};

		class CreateHostCommand : public ICommand
		{
		public:
			vector<int> vecPlayerId;
			int			matchId;

		public:
			CreateHostCommand(vector<int> paramVecPlayerId) : vecPlayerId(paramVecPlayerId)
			{
				ICommand::commandId = CommandId::CREATE_HOST;
			};
		};
	}

} // namespace Command
