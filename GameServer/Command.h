#pragma once
#include "ClientSession.h"
#include "ProxyManager.h"

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
		virtual int GetCommandId() abstract;
	};

	/*-----------------------------------
			NetworkSystem To GameSystem
	-------------------------------------*/
	namespace N2G
	{
		enum CommandId
		{
			BUY_COMMAND = 1,
			CREATE_HOST,
			CREATE_DEBUG_MODE_HOST,
			CHAMP_BUY,
			CHAMP_SELL,
			CHAMP_LOCATE,
		};

		class BuyChampCommand : public ICommand
		{
		public:
			BuyChampCommand(wptr<ClientSession> p_client, int p_champUid) : champUid(p_champUid), ICommand(p_client)
			{
			};

			virtual int GetCommandId() override {
				return CommandId::BUY_COMMAND;
			};

		public:
			int champUid;
		};


		enum LOCATION_TYPE : int {
			BENCH = 1,
			FIELD
		};

		class LocateChampCommand : public ICommand
		{
		public:
			int index;
			int champUid;
			LOCATION_TYPE from;
			LOCATION_TYPE to;

		public:
			LocateChampCommand(wptr<ClientSession> p_client, LOCATION_TYPE paramFrom, LOCATION_TYPE paramTo, int paramIndex, int uid)
				: from(paramFrom), to(paramTo), index(paramIndex), champUid(uid), ICommand(p_client) {};

			virtual int GetCommandId() override {
				return CommandId::CHAMP_LOCATE;
			};
		};

		//class LocateToFieldCommand : public ICommand
		//{
		//public:
		//	int fieldIndex;
		//	int champUid;

		//public:
		//	LocateToFieldCommand(wptr<ClientSession> p_client, int paramFieldIndex, int uid)
		//		: fieldIndex(paramFieldIndex), champUid(uid), ICommand(p_client) {};
		//	virtual int GetCommandId() override {
		//		return CommandId::CHAMP_LOCATE_TO_FIELD;
		//	};
		//};

		//class LocateToBenchCommand : public ICommand
		//{
		//public:
		//	int benchIndex;
		//	int champUid;

		//public:
		//	LocateToBenchCommand(wptr<ClientSession> p_client, int p_benchIndex, int uid)
		//		: benchIndex(p_benchIndex), champUid(uid), ICommand(p_client) {};
		//	virtual int GetCommandId() override {
		//		return CommandId::CHAMP_LOCATE_TO_BENCH;
		//	};
		//};

		//class CreateDebugModeHostCommand : public ICommand
		//{

		//public:
		//	CreateDebugModeHostCommand(wptr<ClientSession> p_client) : ICommand(p_client) {};
		//};

		class HostCreateCommand : public ICommand
		{
		public:
			vector<int> vecPlayerId;
			int matchId;

		public:
			HostCreateCommand(int paramMatchId, vector<int> paramVecPlayerId, wptr<Proxy> paramProxy)
				: matchId(paramMatchId), vecPlayerId(paramVecPlayerId), ICommand(paramProxy)
			{};

			virtual int GetCommandId() override {
				return CommandId::CREATE_HOST;
			};
		};
	} // namespace N2G

} // namespace Command
