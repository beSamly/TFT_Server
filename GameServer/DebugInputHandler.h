#include "pch.h"
#include "GameSystem.h"
#include "GameHost.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "Player.h"


/*
�׽�Ʈ ��� �޸�
ȣ��Ʈ ���� ���� - HostCreate
�÷��̾���� ���� Ȯ�� - ShowBencnAndFieldData
è�Ǿ� ���� - BuyChamp
�ʵ忡 ��ġ - ChampLocateToField
(Optional) ��ġ, �ʵ� ���� Ȯ��- ShowBencnAndFieldData
���� ���� - StartRound

*/

namespace {
#define TO_LAMBDA(FUNC) [&]() { FUNC(); }
}

class DebugInputHandler {

private:
	sptr<GameSystem> gameSystem;
	map<int, function<void()>> handlers;
	sptr<Proxy> proxySession;
	sptr<ClientSession> clientSession1;
	sptr<ClientSession> clientSession2;
	shared_ptr<asio::io_context> ioContext;

	DebugInputHandler() {
		proxySession = make_shared<Proxy>(SERVER_TYPE::AGENT, ioContext);
		clientSession1 = make_shared<ClientSession>(ioContext);
		sptr<Player> player1 = make_shared<Player>();
		player1->SetPlayerId(1);
		clientSession1->SetPlayer(player1);

		clientSession2 = make_shared<ClientSession>(ioContext);
		sptr<Player> player2 = make_shared<Player>();
		player2->SetPlayerId(2);
		clientSession2->SetPlayer(player2);
	}

private:
	sptr<GameHost> GetGameHost() {
		return gameSystem->GetGameHostByPlayerId(1);
	}

public:
	DebugInputHandler(sptr<GameSystem> paramGameSystem) : gameSystem(paramGameSystem) {
		handlers.emplace(1, TO_LAMBDA(HandleHostCreate));
		handlers.emplace(2, TO_LAMBDA(HandleEnterClient));
		handlers.emplace(3, TO_LAMBDA(HandleShowShopData));
		handlers.emplace(4, TO_LAMBDA(HandleBuyChamp));
		handlers.emplace(5, TO_LAMBDA(HandleChampLocateToField));
		handlers.emplace(6, TO_LAMBDA(HandleChampLocateToBench));
		handlers.emplace(7, TO_LAMBDA(HandleShowBencnAndFieldData));
		handlers.emplace(8, TO_LAMBDA(HandleStartRound));
		handlers.emplace(9, TO_LAMBDA(HandleStopRound));
	}

	void PrintInstruction() {
		cout << "[1] HostCreate" << endl;
		cout << "[2] EnterClient" << endl;
		cout << "[3] ShowShopData" << endl;
		cout << "[4] BuyChamp" << endl;
		cout << "[5] ChampLocateToField" << endl;
		cout << "[6] ChampLocateToBench" << endl;
		cout << "[7] ShowBencnAndFieldData" << endl;
		cout << "[8] StartRound" << endl;
		cout << "[9] StopRound" << endl;
	}

	void HandleInput(int key) {

		if (!handlers.count(key))
		{
			spdlog::error("[DebugInputHandler] handler for key {} not found!", key);
		}
		else {
			handlers[key]();
		}
	};

	void HandleHostCreate() {
		vector<int> vecPlayerId;
		vecPlayerId.push_back(1);
		vecPlayerId.push_back(2);

		// ���� �ý��ۿ� ��û
		sptr<N2G::HostCreateCommand> command = make_shared<N2G::HostCreateCommand>(99999, vecPlayerId, proxySession);
		gameSystem->PushCommand(command);
	}

	void HandleEnterClient() {

		sptr<GameHost> host = gameSystem->GetGameHostByPlayerId(1);

		if (!host) {
			spdlog::error("[DebugInputController] host not found for playerId = {}", 1);
			return;
		}

		host->EnterClient(clientSession1);
		host->EnterClient(clientSession2);
	}

	void HandleBuyChamp() {

		cout << "[BuyChamp] for which player" << endl;
		int playerId;
		std::cin >> playerId;

		cout << "[BuyChamp] Champ uid to buy" << endl;
		int champUid;
		std::cin >> champUid;

		sptr<GameHost> gameHost = GetGameHost();
		sptr<ClientSession> targetClient = playerId == 1 ? clientSession1 : clientSession2;
		sptr<N2G::BuyChampCommand> command = make_shared<N2G::BuyChampCommand>(targetClient, champUid);
		gameHost->PushCommand(command);
	}

	void HandleChampLocateToBench() {
		cout << "[ChampLocateToBench] for which player" << endl;
		int playerId;
		std::cin >> playerId;

		cout << "[ChampLocateToBench] Champ index to locate" << endl;
		int champUid;
		std::cin >> champUid;

		cout << "[ChampLocateToBench] bench index to locate" << endl;
		int benchIndex;
		std::cin >> benchIndex;

		sptr<ClientSession> targetClient = playerId == 1 ? clientSession1 : clientSession2;
		sptr<N2G::LocateChampCommand> command = make_shared<N2G::LocateChampCommand>(targetClient, N2G::LOCATION_TYPE::FIELD, N2G::LOCATION_TYPE::BENCH, benchIndex, champUid);

		sptr<GameHost> gameHost = GetGameHost();
		gameHost->PushCommand(command);
	}

	void HandleChampLocateToField() {
		cout << "[ChampLocateToField] for which player" << endl;
		int playerId;
		std::cin >> playerId;

		cout << "[ChampLocateToField] Champ index to locate" << endl;
		int champUid;
		std::cin >> champUid;

		cout << "[ChampLocateToField] field index to locate" << endl;
		int fieldIndex;
		std::cin >> fieldIndex;

		sptr<ClientSession> targetClient = playerId == 1 ? clientSession1 : clientSession2;
		sptr<N2G::LocateChampCommand> command = make_shared<N2G::LocateChampCommand>(targetClient, N2G::LOCATION_TYPE::BENCH, N2G::LOCATION_TYPE::FIELD, fieldIndex, champUid);

		sptr<GameHost> gameHost = GetGameHost();
		gameHost->PushCommand(command);
	}

	void HandleStartRound() {
		sptr<GameHost> gameHost = GetGameHost();
		gameHost->Start();
	}

	void HandleStopRound()
	{
		sptr<GameHost> gameHost = GetGameHost();

		// ������ ���� ��ġ ��� ����
		gameHost->SetCurrentState(nullptr);
		gameHost->GetMatchPool().Reset();
	}

	void HandleShowBencnAndFieldData() {
		sptr<GameHost> gameHost = GetGameHost();

		for (auto& [playerId, inGamePlayer] : gameHost->GetInGamePlayer())
		{
			spdlog::debug("========PlayerId {}==========", playerId);
			Bench bench = inGamePlayer->GetBench();
			for (auto& [benchIndex, champion] : bench.GetBenchData())
			{
				spdlog::debug("Bench Index {} Champion Uid = {}", benchIndex, champion->GetUid());
			}

			Field field = inGamePlayer->GetField();
			for (auto& [fieldIndex, champion] : field.GetFieldData())
			{
				spdlog::debug("Bench Index {} Champion Uid = {}", fieldIndex, champion->GetUid());
			}

			spdlog::debug("============End==============");
		}
	}

	void HandleShowShopData() {
		sptr<GameHost> gameHost = GetGameHost();

		for (auto& [playerId, inGamePlayer] : gameHost->GetInGamePlayer())
		{
			spdlog::debug("========PlayerId {}==========", playerId);
			ChampShop shop = inGamePlayer->GetChampShop();
			for (auto& [champUid, champData] : shop.GetChampData())
			{
				spdlog::debug("Champ Uid {} Champion Uid = {}", champUid, champData.displayName);
			}

			spdlog::debug("============End==============");
		}
	}
};