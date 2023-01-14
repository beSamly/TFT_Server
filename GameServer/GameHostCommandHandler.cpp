#include "pch.h"
#include "GameHostCommandHandler.h"
#include "Command.h"

using namespace Command;

namespace
{
#define TO_LAMBDA(FUNC) [&](GameHost& host, sptr<ICommand> command) { FUNC(host, command); }
} // namespace

GameHostCommandHandler::GameHostCommandHandler()
{
	commandHandler.emplace((int)N2G::CommandId::CREATE_HOST, TO_LAMBDA(HandleHostCreateCommand));
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

//void GameHostCommandHandler::HandleBuyCommand(GameHost& host, sptr<ICommand> command)
//{
//    sptr<BuyCommand> buyCommand = dynamic_pointer_cast<BuyCommand>(command);
//
//    if (buyCommand == nullptr)
//    {
//        // error
//        return;
//    }
//
//    // 구매하려는 champData 기반으로 champion 데이터 만들어서 벤치에 넣어주기
//
//    sptr<ClientSession> client = command->client.lock();
//    if (client == nullptr)
//    {
//        // client deleted
//        return;
//    }
//
//    int playerId = client->GetPlayer()->playerId;
//
//    if (!inGamePlayerMap.count(playerId))
//    {
//        // error
//        return;
//    }
//
//    sptr<InGamePlayer> inGamePlayer = inGamePlayerMap[playerId];
//
//    // 해당 유저의 상점에 해당 챔피언 존재하는지 체크
//    int uid = buyCommand->champUid;
//
//    bool isExist = inGamePlayer->champShop.Exist(uid);
//    if (!isExist)
//    {
//        // error
//        return;
//    }
//
//    int freeBenchIndex = inGamePlayer->bench.GetEmptyBenchIndex();
//    if (!freeBenchIndex)
//    {
//        // Bench is full!!
//        return;
//    }
//
//    ChampStatData statData = champDataFactory->GetStatData(uid, 1);
//
//    // sptr<Champion> 데이터 생성
//    sptr<Champion> champ = make_shared<Champion>();
//    champ->SetBaseStat(statData);
//
//    // bench 에 넣어주기
//    inGamePlayer->bench.Locate(freeBenchIndex, champ);
//
//    // TODO 골드 차감
//}
//
//void GameHostCommandHandler::HandleSellCommand(GameHost& host, sptr<ICommand> command)
//{
//
//    // 판매하는 champ 의 star 계산해서 champPool로 반환시켜주기
//}
