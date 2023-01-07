#include "pch.h"
#include "InGameCommandHandler.h"
#include "Command.h"

using namespace Command;

namespace
{
#define TO_LAMBDA(FUNC) [&](GameHost& host, sptr<ICommand> command) { FUNC(host, command); }
} // namespace

InGameCommandHandler::InGameCommandHandler()
{
	commandHandler.emplace((int)N2G::CommandId::CREATE_HOST, TO_LAMBDA(HandleHostCreateCommand));
}

void InGameCommandHandler::ProcessCommand(GameHost& host, sptr<ICommand> command)
{
	int commandId = command->GetCommandId();

	if (commandHandler.count(commandId)) {
		commandHandler[commandId](host, command);
	}
}

void InGameCommandHandler::HandleHostCreateCommand(GameHost& host, sptr<ICommand> command)
{

}

//void InGameCommandHandler::HandleBuyCommand(GameHost& host, sptr<ICommand> command)
//{
//    sptr<BuyCommand> buyCommand = dynamic_pointer_cast<BuyCommand>(command);
//
//    if (buyCommand == nullptr)
//    {
//        // error
//        return;
//    }
//
//    // �����Ϸ��� champData ������� champion ������ ���� ��ġ�� �־��ֱ�
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
//    // �ش� ������ ������ �ش� è�Ǿ� �����ϴ��� üũ
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
//    // sptr<Champion> ������ ����
//    sptr<Champion> champ = make_shared<Champion>();
//    champ->SetBaseStat(statData);
//
//    // bench �� �־��ֱ�
//    inGamePlayer->bench.Locate(freeBenchIndex, champ);
//
//    // TODO ��� ����
//}
//
//void InGameCommandHandler::HandleSellCommand(GameHost& host, sptr<ICommand> command)
//{
//
//    // �Ǹ��ϴ� champ �� star ����ؼ� champPool�� ��ȯ�����ֱ�
//}
