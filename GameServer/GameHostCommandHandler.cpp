#include "pch.h"
#include "GameHostCommandHandler.h"
#include "Command.h"
#include "GameHost.h"
#include "spdlog/spdlog.h"

using namespace Command;
using namespace Command::N2G;
namespace
{
#define TO_LAMBDA(FUNC) [&](GameHost& host, sptr<ICommand> command) { FUNC(host, command); }
} // namespace

GameHostCommandHandler::GameHostCommandHandler()
{
	commandHandler.emplace((int)N2G::CommandId::CREATE_HOST, TO_LAMBDA(HandleHostCreateCommand));
	commandHandler.emplace((int)N2G::CommandId::CHAMP_BUY, TO_LAMBDA(HandleChampBuyCommand));
	commandHandler.emplace((int)N2G::CommandId::CHAMP_SELL, TO_LAMBDA(HandleChampSellCommand));
	commandHandler.emplace((int)N2G::CommandId::CHAMP_LOCATE, TO_LAMBDA(HandleChampLocateCommand));
}

void GameHostCommandHandler::ProcessCommand(GameHost& host, sptr<ICommand> command)
{
	int commandId = command->GetCommandId();

	if (commandHandler.count(commandId)) {
		commandHandler[commandId](host, command);
	}
}

void GameHostCommandHandler::HandleHostCreateCommand(GameHost& host, sptr<ICommand> command)
{

}

void GameHostCommandHandler::HandleChampBuyCommand(GameHost& host, sptr<ICommand> command)
{
	sptr<N2G::BuyChampCommand> buyCommand = dynamic_pointer_cast<N2G::BuyChampCommand>(command);

	if (buyCommand == nullptr)
	{
		return;
	}

	sptr<ClientSession> client = command->client.lock();
	if (client == nullptr)
	{
		return;
	}

	int playerId = client->GetPlayer()->GetPlayerId();
	sptr<InGamePlayer> inGamePlayer = host.FindInGamePlayer(playerId);

	if (!inGamePlayer)
	{
		return;
	}

	// �ش� ������ ������ �ش� è�Ǿ� �����ϴ��� üũ
	int uid = buyCommand->champUid;

	// �ش� è�Ǿ��� ������ ������ ���� ��
	bool isExist = inGamePlayer->GetChampShop().Exist(uid);
	if (!isExist)
	{
		spdlog::debug("[ChampBuyCommand] champ uid = {} not exist in player's shop!", uid);
		return;
	}

	ChampData champData = inGamePlayer->GetChampShop().Find(uid);

	// ��ġ�� ���� á�� ��
	int freeBenchIndex = inGamePlayer->GetBench().GetEmptyBenchIndex();
	if (!freeBenchIndex)
	{
		spdlog::debug("[ChampBuyCommand] player bench is full!");
		return;
	}

	// ����� ��带 �������� �ʾ��� ��
	if (inGamePlayer->GetGold() < champData.cost)
	{
		spdlog::debug("[ChampBuyCommand] player has not enough gold! current gold = {} cost ={}!", inGamePlayer->GetGold(), champData.cost);
		return;
	}

	// sptr<Champion> ������ ����
	ChampStatData statData = host.GetChampDataFactory()->GetStatData(champData.index, 1);

	sptr<Champion> champ = make_shared<Champion>();
	champ->SetBaseStat(statData);

	// bench �� �־��ֱ�
	inGamePlayer->GetBench().Locate(freeBenchIndex, champ);

	// ��� ����
	inGamePlayer->SpendGold(champData.cost);

	// �����
	spdlog::debug("[ChampBuyCommand] player id = {} has bought champion uid = {}!", playerId, uid);
}

void GameHostCommandHandler::HandleChampSellCommand(GameHost& host, sptr<ICommand> command)
{
	// �Ǹ��ϴ� champ �� star ����ؼ� champPool�� ��ȯ�����ֱ�
}

void GameHostCommandHandler::HandleChampLocateCommand(GameHost& host, sptr<ICommand> command)
{
	sptr<N2G::LocateChampCommand> locateChampCommand = dynamic_pointer_cast<N2G::LocateChampCommand>(command);

	if (locateChampCommand == nullptr)
	{
		return;
	}

	sptr<ClientSession> client = command->client.lock();
	if (client == nullptr)
	{
		return;
	}

	int playerId = client->GetPlayer()->GetPlayerId();
	int champUid = locateChampCommand->champUid;
	int locationIndex = locateChampCommand->index;
	LOCATION_TYPE from = locateChampCommand->from;
	LOCATION_TYPE to = locateChampCommand->to;
	sptr<InGamePlayer> inGamePlayer = host.FindInGamePlayer(playerId);

	if (!inGamePlayer)
	{
		return;
	}

	sptr<Champion> champion = nullptr;

	if (from == LOCATION_TYPE::BENCH)
	{
		sptr<Champion> champion = inGamePlayer->GetBench().FindChampionByUid(champUid);
		inGamePlayer->GetField().Remove(champion);
	}
	else if (from == LOCATION_TYPE::FIELD) {
		sptr<Champion> champion = inGamePlayer->GetField().FindChampionByUid(champUid);
		inGamePlayer->GetField().Remove(champion);
	}

	if (!champion)
	{
		spdlog::debug("[LocateChampCommand] player ");
	}

	if (to == LOCATION_TYPE::BENCH) {
		inGamePlayer->GetBench().Locate(locationIndex, champion);
	}
	else if (to == LOCATION_TYPE::FIELD) {
		inGamePlayer->GetField().Locate(locationIndex, champion);
	}
}
