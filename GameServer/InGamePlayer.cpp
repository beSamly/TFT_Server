#include "pch.h"
#include "InGamePlayer.h"

InGamePlayer::InGamePlayer() {}

void InGamePlayer::SendToClient()
{
    if (sptr<ClientSession> tempClient = client.lock()) {
        //tempClient->Send();
    }
}
