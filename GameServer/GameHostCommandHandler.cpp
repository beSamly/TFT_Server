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

	// 해당 유저의 상점에 해당 챔피언 존재하는지 체크
	int uid = buyCommand->champUid;

	// 해당 챔피언이 유저의 상점에 없을 때
	bool isExist = inGamePlayer->GetChampShop().Exist(uid);
	if (!isExist)
	{
		spdlog::debug("[ChampBuyCommand] champ uid = {} not exist in player's shop!", uid);
		return;
	}

	ChampData champData = inGamePlayer->GetChampShop().Find(uid);

	// 벤치가 가득 찼을 때
	int freeBenchIndex = inGamePlayer->GetBench().GetEmptyBenchIndex();
	if (!freeBenchIndex)
	{
		spdlog::debug("[ChampBuyCommand] player bench is full!");
		return;
	}

	// 충분한 골드를 보유하지 않았을 때
	if (inGamePlayer->GetGold() < champData.cost)
	{
		spdlog::debug("[ChampBuyCommand] player has not enough gold! current gold = {} cost ={}!", inGamePlayer->GetGold(), champData.cost);
		return;
	}

	// sptr<Champion> 데이터 생성
	ChampStatData statData = host.GetChampDataFactory()->GetStatData(champData.index, 1);

	sptr<Champion> champ = make_shared<Champion>();
	champ->SetBaseStat(statData);

	// bench 에 넣어주기
	inGamePlayer->GetBench().Locate(freeBenchIndex, champ);

	// 골드 차감
	inGamePlayer->SpendGold(champData.cost);

	// 디버깅
	spdlog::debug("[ChampBuyCommand] player id = {} has bought champion uid = {}!", playerId, uid);
}

void GameHostCommandHandler::HandleChampSellCommand(GameHost& host, sptr<ICommand> command)
{
	// 판매하는 champ 의 star 계산해서 champPool로 반환시켜주기
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
